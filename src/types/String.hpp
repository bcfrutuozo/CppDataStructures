//
// Created by bcfrutuozo on 12/03/2022.
//

#ifndef CPPDATASTRUCTURES_STRING_HPP
#define CPPDATASTRUCTURES_STRING_HPP

#include "../Platform.hpp"
#include "Char.hpp"
#include "../collections/Array.hpp"
#include "StringSplitOptions.hpp"
#include "StringComparison.hpp"
#include "../helpers/Algorithm.hpp"

#include <iostream>
#include <cstring>
#include <memory>
#include <string>
#include <limits>
#include <atomic>
#include <utility>
#include <cassert>
#include <cstdint>
#include <stdexcept>
#include <string_view>
#include <type_traits>

/**
 * @brief Immutable string based on a plain C-string (char *) with ref-counting.
 * @details
 *   - Shared content between multiple instances (using ref counting).
 *   - Automatic mem dealloc (when no refs point to content).
 *   - Same sizeof than a 'char *'.
 *   - Null not allowed (equals to empty string).
 *   - Empty string don't require memory allocation.
 *   - String content available on debug.
 *   - Mimics the STL basic_string class.
 * @details Memory layout:
 *
 *       ----|----|-----------NUL
 *        ^   ^    ^
 *        |   |    |-- string content (NUL-terminated)
 *        |   |-- string length (4-bytes)
 *        |-- ref counter (4-bytes)
 *
 *   mStr (cstring pointer) points to the string content (to allow view content on debug).
 *   Allocated memory is aligned to ref counter type size.
 *   Allocated memory is a multiple of ref counter type size.
 * @note This class is immutable.
 */
template<typename Char,
        typename Traits = std::char_traits<Char>,
        typename Allocator = std::allocator<Char>>
class ImmutableString {

    // Friend declarations to be a part of String class
    friend class String;

    friend class std::hash<ImmutableString<char>>;

    friend class std::hash<ImmutableString<wchar_t>>;

    friend class std::hash<ImmutableString<char8_t>>;

    friend class std::hash<ImmutableString<char16_t>>;

    friend class std::hash<ImmutableString<char32_t>>;

private:

    // Declarations
    using prefix_type = std::uint32_t;
    using atomic_prefix_type = std::atomic<prefix_type>;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using allocator_type = typename std::allocator_traits<Allocator>::template rebind_alloc<prefix_type>;
    using allocator_traits = std::allocator_traits<allocator_type>;
    using traits_type = Traits;
    using size_type = typename std::allocator_traits<Allocator>::size_type;
    using difference_type = typename std::allocator_traits<Allocator>::difference_type;
    using value_type = Char;
    using const_reference = const value_type &;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using const_iterator = const_pointer;
    using const_reverse_iterator = typename std::reverse_iterator<const_iterator>;
    using basic_cstring_view = std::basic_string_view<value_type, traits_type>;

    // Empty String representation
    struct EmptyCString {
        atomic_prefix_type counter{0};
        prefix_type len{0};
        value_type str[2] = {value_type(), value_type()};
    };

    // Static members
    // Special value indicating the maximum achievable index + 1.
    static constexpr size_type npos = std::numeric_limits<size_type>::max();

    // Returns the maximum number of elements the string is able to hold.
    static constexpr size_type max_size() noexcept {
        return std::numeric_limits<prefix_type>::max() - sizeof(prefix_type) / sizeof(value_type);
    }

    static allocator_type mAllocator;
    static constexpr EmptyCString mEmpty{};

    // Memory buffer with prefix_type alignment.
    const_pointer mStr = nullptr;

    // Sanitize a char array pointer avoiding nulls.
    static inline constexpr const_pointer sanitize(const_pointer str) noexcept {
        return ((str == nullptr || str[0] == value_type()) ? mEmpty.str : str);
    }

    // Return pointer to counter from pointer to string.
    static inline constexpr atomic_prefix_type *getPtrToCounter(const_pointer str) noexcept {
        static_assert(sizeof(atomic_prefix_type) == sizeof(prefix_type));
        static_assert(sizeof(value_type) <= sizeof(prefix_type));
        assert(str != nullptr);
        pointer ptr = const_cast<pointer>(str) - (2 * sizeof(prefix_type)) / sizeof(value_type);
        return reinterpret_cast<atomic_prefix_type *>(ptr);
    }

    // Return pointer to string length from pointer to string.
    static inline constexpr prefix_type *getPtrToLength(const_pointer str) noexcept {
        static_assert(sizeof(value_type) <= sizeof(prefix_type));
        assert(str != nullptr);
        pointer ptr = const_cast<pointer>(str) - (sizeof(prefix_type) / sizeof(value_type));
        return reinterpret_cast<prefix_type *>(ptr);
    }

    // Return pointer to string from pointer to counter.
    static inline constexpr const_pointer getPtrToString(const prefix_type *ptr) noexcept {
        static_assert(sizeof(atomic_prefix_type) == sizeof(prefix_type));
        assert(ptr != nullptr);
        return reinterpret_cast<const_pointer>(ptr + 2);
    }

    /**
     * Returns the length of the prefix_type array to allocate.
     * @details Allocator allocates an array of prefix_type (not Char) to grant the memory alignment.
     * @details The returned length considere the place for the ending NUL.
     * @example Let len=6, sizeof(Char)=2, sizeof(prefix_type)=4
     *    We need to reserve:
     *      - 4-bytes for the counter (uint32_t)
     *      - 4-bytes for the length (uint32_t)
     *      - 6 x 2-bytes = 12-bytes for the string content
     *      - 1 x 2-bytes = 2-bytes for the terminating NUL
     *    Total to reserve = 22-bytes
     *    Expresed in 4-bytes (uint32_t) units = 6 (upper rounding)
     *    In this case there are 2 ending bytes acting as padding.
     * @param[in] len Length of the string (without ending NUL).
     * @return Length of the prefix_type array.
     */
    static constexpr size_type getAllocatedLength(size_type len) noexcept {
        static_assert(sizeof(value_type) <= sizeof(prefix_type));
        return 3 + (len * sizeof(value_type)) / sizeof(prefix_type);
    }

    /**
     * Allocate memory for the ref-counter + length + string + NUL.
     * @details We allocate prefix_types to grant memory alignment.
     * @param[in] len Length to reserve (of prefix_types).
     * @return A pointer to the allocated memory.
     */
    [[nodiscard]]
    static constexpr prefix_type *allocate(size_type len) noexcept {
        static_assert(sizeof(atomic_prefix_type) == sizeof(prefix_type));
        static_assert(alignof(value_type) <= alignof(prefix_type));
        static_assert(sizeof(value_type) <= sizeof(prefix_type));
        assert(len > 0);
        prefix_type *ptr = allocator_traits::allocate(mAllocator, len);
        assert(reinterpret_cast<std::size_t>(ptr) % alignof(prefix_type) == 0);
        return ptr;
    }

    // Deallocates the memory allocated by the object.
    static constexpr void deallocate(const_pointer str) noexcept {
        assert(str != nullptr);
        assert(str != mEmpty.str);
        atomic_prefix_type *ptr = getPtrToCounter(str);
        prefix_type len = *getPtrToLength(str);
        size_type n = getAllocatedLength(len);
        ptr->~atomic_prefix_type();
        allocator_traits::deallocate(mAllocator, reinterpret_cast<prefix_type *>(ptr), n);
    }

    /**
     * Decrements the ref-counter.
     * If no more references then deallocate the memory.
     * The empty string is never deallocated.
     * @param[in] str Memory to release.
     */
    static constexpr void release(const_pointer str) noexcept {
        atomic_prefix_type *ptr = getPtrToCounter(str);
        prefix_type counts = ptr[0].load(std::memory_order_relaxed);

        // Constant (e.g. mEmpty)
        if (counts == 0) { return; }
        if (counts > 1) { counts = ptr[0].fetch_sub(1, std::memory_order_relaxed); }
        if (counts == 1) { deallocate(str); }
    }

    // Increment the reference counter (except for constants).
    static constexpr void incrementRefCounter(const_pointer str) noexcept {
        atomic_prefix_type *ptr = getPtrToCounter(str);
        if (ptr[0].load(std::memory_order_relaxed) > 0) {
            ptr[0].fetch_add(1, std::memory_order_relaxed);
        }
    }

    // Constructors
    constexpr ImmutableString() noexcept: ImmutableString(nullptr) {}

    constexpr ImmutableString(const_pointer str, size_type startIndex, size_type len) noexcept {
        assert(len < max_size() && "invalid string length");
        if (str == nullptr || len == 0) { mStr = mEmpty.str; }
        else {

            // Readjust length value based on the size of the string plus the start index
            auto totalSize = Algorithm::strlen(str) - startIndex;
            if(len > totalSize) len = totalSize;

            size_type n = getAllocatedLength(len);
            prefix_type *ptr = allocate(n);
            std::atomic_init(reinterpret_cast<atomic_prefix_type *>(ptr), 1); // ref-counter = 1
            ptr[1] = static_cast<prefix_type>(len); // length
            auto content = reinterpret_cast<pointer>(ptr + 2);
            traits_type::copy(content, str + startIndex, len);
            content[len] = value_type();
            mStr = content;
        }
    }

    constexpr ImmutableString(const_pointer str, size_type len) noexcept: ImmutableString(str, 0, len) {}

    constexpr ImmutableString(const_pointer str) noexcept: ImmutableString(str,
                                                                           (str == nullptr ? 0 : Algorithm::strlen(
                                                                                   str))) {}

    constexpr ImmutableString(value_type c, size_type len) noexcept {
        assert(len < max_size() && "invalid string length");
        size_type n = getAllocatedLength(len);
        prefix_type *ptr = allocate(n);
        std::atomic_init(reinterpret_cast<atomic_prefix_type *>(ptr), 1); // ref-counter = 1
        ptr[1] = static_cast<prefix_type>(len); // length
        pointer content = reinterpret_cast<pointer>(ptr + 2);
        for (auto i = 0; i < len; ++i)
            traits_type::copy(content + i, &c, 1);
        content[len] = value_type();
        mStr = content;
    }

    /**
     * Destructor.
     * Decrements the ref-counter if other instances exists.
     * Otherwise deallocates memory.
     */
    constexpr ~ImmutableString() { release(mStr); }

    // Copy constructor.
    constexpr ImmutableString(const ImmutableString &other) noexcept: mStr(other.mStr) { incrementRefCounter(mStr); }

    // Move constructor.
    constexpr ImmutableString(ImmutableString &&other) noexcept: mStr(std::exchange(other.mStr, mEmpty.str)) {}

    // Copy assignment.
    constexpr ImmutableString &operator=(const ImmutableString &other) noexcept {
        if (mStr == other.mStr) {
            return *this;
        }
        release(mStr);
        mStr = other.mStr;
        incrementRefCounter(mStr);
        return *this;
    }

    // Move assignment.
    constexpr ImmutableString &operator=(ImmutableString &&other) noexcept {
        std::swap(mStr, other.mStr);
        return *this;
    }

    // Conversion to 'const char *'
    constexpr operator const_pointer() const { return mStr; }

    // Operators overloading
    inline constexpr ImmutableString operator+(const_pointer str) const noexcept {
        return Algorithm::strcat(mStr, str);
    }

    inline constexpr ImmutableString &operator+=(const_pointer str) noexcept {
        auto p = ImmutableString::concat(mStr, str);
        if (mStr == p.mStr) {
            return *this;
        }
        release(mStr);
        mStr = p.mStr;
        incrementRefCounter(mStr);
        return *this;
    }

    inline constexpr ImmutableString &operator+=(const ImmutableString &str) noexcept {
        return *this += str.mStr;
    }

    // Return length of string.
    inline constexpr size_type size() const noexcept { return *(getPtrToLength(mStr)); }

    // Return length of string.
    inline constexpr size_type length() const noexcept { return *(getPtrToLength(mStr)); }

    // Test if string is empty.
    inline constexpr bool empty() const noexcept { return (length() == 0); }

    // Returns a reference to the character at specified location pos in range [0, length()].
    inline constexpr const_reference operator[](size_type pos) const noexcept { return mStr[pos]; }

    // Returns a reference to the character at specified location pos in range [0, length()].
    constexpr const_reference at(size_type pos) const {
        return (pos > length() ? throw std::out_of_range("cstring::at") : mStr[pos]);
    }

    // Get last character of the string.
    constexpr const_reference back() const {
        return (empty() ? throw std::out_of_range("cstring::back") : mStr[length() - 1]);
    }

    // Get first character of the string.
    constexpr const_reference front() const { return (empty() ? throw std::out_of_range("cstring::front") : mStr[0]); }

    // Returns a non-null pointer to a null-terminated character array.
    inline constexpr const_pointer data() const noexcept {
        assert(mStr != nullptr);
        return mStr;
    }

    // Returns a non-null pointer to a null-terminated character array.
    inline constexpr const_pointer c_str() const noexcept { return data(); }

    // Returns a string_view of content.
    inline constexpr basic_cstring_view view() const noexcept { return basic_cstring_view(mStr, length()); }

    // Const iterator to the beginning.
    constexpr const_iterator cbegin() const noexcept { return view().cbegin(); }

    // Const iterator to the end.
    constexpr const_iterator cend() const noexcept { return view().cend(); }

    // Const reverse iterator to the beginning.
    constexpr const_reverse_iterator crbegin() const noexcept { return view().crbegin(); }

    // Const reverse iterator to the end.
    constexpr const_reverse_iterator crend() const noexcept { return view().crend(); }

    // Exchanges the contents of the string with another.
    void swap(ImmutableString &other) noexcept { std::swap(mStr, other.mStr); }

    // Returns the substring [pos, pos+len).
    constexpr basic_cstring_view substr(size_type pos = 0, size_type len = npos) const {
        return view().substr(pos, len);
    }

    // Compare contents.
    int constexpr compare(const ImmutableString &other) const noexcept {
        return view().compare(other.view());
    }

    int constexpr compare(size_type pos, size_type len, const ImmutableString &other) const noexcept {
        return substr(pos, len).compare(other.view());
    }

    int constexpr
    compare(size_type pos1, size_type len1, const ImmutableString &other, size_type pos2, size_type len2 = npos) const {
        return substr(pos1, len1).compare(other.substr(pos2, len2));
    }

    int constexpr compare(const_pointer str) const {
        return view().compare(sanitize(str));
    }

    int constexpr compare(size_type pos, size_type len, const_pointer str) const {
        return substr(pos, len).compare(sanitize(str));
    }

    int constexpr compare(size_type pos, size_type len, const_pointer str, size_type len2) const {
        return substr(pos, len).compare(basic_cstring_view(sanitize(str), len2));
    }

    int constexpr compare(const basic_cstring_view other) const noexcept {
        return view().compare(other);
    }

    /*
     * Variadic template to dynamically receive a list of strings and concatenate
     * all of them in a single one.
     */
    template<typename... Args>
    static constexpr ImmutableString concat(Args... args) {
        size_type len = Algorithm::strlen(args...);
        auto data = new value_type[len + 1];
        Algorithm::strcat(data, args...);
        ImmutableString str(data);
        delete[] data;
        return str;
    }

    // Count contents
    int constexpr count(value_type c) const noexcept {
        return std::count(cbegin(), cend(), c);
    }

    int constexpr count(const_pointer str) const noexcept {
        return Algorithm::KMPSearch(str, mStr);
    }

    // Checks if the string view begins with the given prefix.
    bool constexpr starts_with(const ImmutableString &other) const noexcept {
        size_type len = other.length();
        return (compare(0, len, other) == 0);
    }

    bool constexpr starts_with(const basic_cstring_view sv) const noexcept {
        auto len = sv.length();
        return (compare(0, len, sv.data()) == 0);
    }

    bool constexpr starts_with(const_pointer str) const noexcept {
        return starts_with(basic_cstring_view(sanitize(str)));
    }

    // Checks if the string ends with the given suffix.
    bool constexpr ends_with(const ImmutableString &other) const noexcept {
        auto len1 = length();
        auto len2 = other.length();
        return (len1 >= len2 && compare(len1 - len2, len2, other) == 0);
    }

    bool constexpr ends_with(const basic_cstring_view sv) const noexcept {
        size_type len1 = length();
        size_type len2 = sv.length();
        return (len1 >= len2 && compare(len1 - len2, len2, sv.data()) == 0);
    }

    bool constexpr ends_with(const_pointer str) const noexcept {
        return ends_with(basic_cstring_view(sanitize(str)));
    }

    // Find the first ocurrence of a substring.
    auto constexpr find(const ImmutableString &other, size_type pos = 0) const noexcept {
        return view().find(other.view(), pos);
    }

    auto constexpr find(const_pointer str, size_type pos, size_type len) const {
        return view().find(sanitize(str), pos, len);
    }

    auto constexpr find(const_pointer str, size_type pos = 0) const {
        return view().find(sanitize(str), pos);
    }

    auto constexpr find(value_type c, size_type pos = 0) const noexcept {
        return view().find(c, pos);
    }

    // Find all ocurrences of a substring.
    auto constexpr find_all_of(const ImmutableString &other, size_type pos = 0) const noexcept {

        std::vector<size_type> entries{};
        size_type lastIdx = 0;

        for(auto idx = view().find(other.view(), pos); idx != std::string::npos; idx = view().find(other.view(), pos)) {
            entries.push_back(idx);
            pos = idx + 1;
        }

        return entries;
    }

    auto constexpr find_all_of(const_pointer str, size_type pos, size_type len) const {
        std::vector<size_type> entries{};
        size_type lastIdx = 0;

        for(auto idx = view().find(sanitize(str).view(), pos, len); idx != std::string::npos; idx = view().find(sanitize(str).view(), pos, len)) {
            entries.push_back(idx);
            pos = idx + 1;
        }

        std::vector<size_t> a(entries.begin(), entries.end());

        return entries;
    }

    auto constexpr find_all_of(const_pointer str, size_type pos = 0) const {
        std::vector<size_type> entries{};
        size_type lastIdx = 0;

        for(auto idx = view().find(sanitize(str).view(), pos); idx != std::string::npos; idx = view().find(sanitize(str).view(), pos)) {
            entries.push_back(idx);
            pos = idx + 1;
        }

        return entries;
    }

    auto constexpr find_all_of(value_type c, size_type pos = 0) const noexcept {
        std::vector<size_type> entries{};
        size_type lastIdx = 0;

        for(auto idx = view().find(c, pos); idx != std::string::npos; idx = view().find(c, pos)) {
            entries.push_back(idx);
            pos = idx + 1;
        }

        return entries;
    }

    // Find the last occurrence of a substring.
    auto constexpr rfind(const ImmutableString &other, size_type pos = npos) const noexcept {
        return view().rfind(other.view(), pos);
    }

    auto constexpr rfind(const_pointer str, size_type pos, size_type len) const {
        return view().rfind(sanitize(str), pos, len);
    }

    auto constexpr rfind(const_pointer str, size_type pos = npos) const {
        return view().rfind(sanitize(str), pos);
    }

    auto rfind(value_type c, size_type pos = npos) const noexcept {
        return view().rfind(c, pos);
    }

    // Finds the first character equal to one of the given characters.
    auto constexpr find_first_of(const ImmutableString &other, size_type pos = 0) const noexcept {
        return view().find_first_of(other.view(), pos);
    }

    auto constexpr find_first_of(const_pointer str, size_type pos, size_type len) const {
        return view().find_first_of(sanitize(str), pos, len);
    }

    auto constexpr find_first_of(const_pointer str, size_type pos = 0) const {
        return view().find_first_of(sanitize(str), pos);
    }

    auto constexpr find_first_of(value_type c, size_type pos = 0) const noexcept {
        return view().find_first_of(c, pos);
    }

    // Finds the first character equal to none of the given characters.
    auto constexpr find_first_not_of(const ImmutableString &other, size_type pos = 0) const noexcept {
        return view().find_first_not_of(other.view(), pos);
    }

    auto constexpr find_first_not_of(const_pointer str, size_type pos, size_type len) const {
        return view().find_first_not_of(sanitize(str), pos, len);
    }

    auto constexpr find_first_not_of(const_pointer str, size_type pos = 0) const {
        return view().find_first_not_of(sanitize(str), pos);
    }

    auto constexpr find_first_not_of(value_type c, size_type pos = 0) const noexcept {
        return view().find_first_not_of(c, pos);
    }

    // Finds the last character equal to one of given characters.
    auto constexpr find_last_of(const ImmutableString &other, size_type pos = npos) const noexcept {
        return view().find_last_of(other.view(), pos);
    }

    auto constexpr find_last_of(const_pointer str, size_type pos, size_type len) const {
        return view().find_last_of(sanitize(str), pos, len);
    }

    auto constexpr find_last_of(const_pointer str, size_type pos = npos) const {
        return view().find_last_of(sanitize(str), pos);
    }

    auto constexpr find_last_of(value_type c, size_type pos = npos) const noexcept {
        return view().find_last_of(c, pos);
    }

    // Finds the last character equal to none of the given characters.
    auto constexpr find_last_not_of(const ImmutableString &other, size_type pos = npos) const noexcept {
        return view().find_last_not_of(other.view(), pos);
    }

    auto constexpr find_last_not_of(const_pointer str, size_type pos, size_type len) const {
        return view().find_last_not_of(sanitize(str), pos, len);
    }

    auto constexpr find_last_not_of(const_pointer str, size_type pos = npos) const {
        return view().find_last_not_of(sanitize(str), pos);
    }

    auto constexpr find_last_not_of(value_type c, size_type pos = npos) const noexcept {
        return view().find_last_not_of(c, pos);
    }

    // Checks if the string contains the given substring.
    bool constexpr contains(basic_cstring_view sv) const noexcept {
        return (view().find(sv) != npos);
    }

    bool constexpr contains(value_type c) const noexcept {
        return (find(c) != npos);
    }

    bool constexpr contains(const_pointer str) const noexcept {
        return (find(str) != npos);
    }

    // Left trim spaces.
    constexpr basic_cstring_view ltrim() const {
        const_pointer ptr = mStr;
        while (std::isspace(*ptr)) ptr++;
        return basic_cstring_view(ptr);
    }

    // Right trim spaces.
    constexpr basic_cstring_view rtrim() const {
        const_pointer ptr = mStr + length() - 1;
        while (ptr >= mStr && std::isspace(*ptr)) ptr--;
        ptr++;
        return basic_cstring_view(mStr, static_cast<size_type>(ptr - mStr));
    }

    // Trim spaces.
    constexpr basic_cstring_view trim() const {
        const_pointer ptr1 = mStr;
        const_pointer ptr2 = mStr + length() - 1;
        while (std::isspace(*ptr1)) ptr1++;
        while (ptr2 >= ptr1 && std::isspace(*ptr2)) ptr2--;
        ptr2++;
        return basic_cstring_view(ptr1, static_cast<size_type>(ptr2 - ptr1));
    }

    // Comparison operators (between basic_cstring)
    friend inline constexpr bool operator==(const ImmutableString &lhs, const ImmutableString &rhs) noexcept {
        return (lhs.compare(rhs) == 0);
    }

    friend inline constexpr bool operator!=(const ImmutableString &lhs, const ImmutableString &rhs) noexcept {
        return (lhs.compare(rhs) != 0);
    }

    friend inline constexpr bool operator<(const ImmutableString &lhs, const ImmutableString &rhs) noexcept {
        return (lhs.compare(rhs) < 0);
    }

    friend inline constexpr bool operator<=(const ImmutableString &lhs, const ImmutableString &rhs) noexcept {
        return (lhs.compare(rhs) <= 0);
    }

    friend inline constexpr bool operator>(const ImmutableString &lhs, const ImmutableString &rhs) noexcept {
        return (lhs.compare(rhs) > 0);
    }

    friend inline constexpr bool operator>=(const ImmutableString &lhs, const ImmutableString &rhs) noexcept {
        return (lhs.compare(rhs) >= 0);
    }

    // Comparison operators (between basic_cstring and Char*)
    friend inline constexpr bool operator==(const ImmutableString &lhs, const Char *rhs) noexcept {
        return (lhs.compare(rhs) == 0);
    }

    friend inline constexpr bool operator!=(const ImmutableString &lhs, const Char *rhs) noexcept {
        return (lhs.compare(rhs) != 0);
    }

    friend inline constexpr bool operator<(const ImmutableString &lhs, const Char *rhs) noexcept {
        return (lhs.compare(rhs) < 0);
    }

    friend inline constexpr bool operator<=(const ImmutableString &lhs, const Char *rhs) noexcept {
        return (lhs.compare(rhs) <= 0);
    }

    friend inline constexpr bool operator>(const ImmutableString &lhs, const Char *rhs) noexcept {
        return (lhs.compare(rhs) > 0);
    }

    friend inline constexpr bool operator>=(const ImmutableString &lhs, const Char *rhs) noexcept {
        return (lhs.compare(rhs) >= 0);
    }

    // Comparison operators (between Char * and basic_cstring)
    friend inline constexpr bool
    operator==(const Char *lhs, const ImmutableString<Char, Traits, Allocator> &rhs) noexcept {
        return (rhs.compare(lhs) == 0);
    }

    friend constexpr bool operator!=(const Char *lhs, const ImmutableString<Char, Traits, Allocator> &rhs) noexcept {
        return (rhs.compare(lhs) != 0);
    }

    friend inline constexpr bool
    operator<(const Char *lhs, const ImmutableString<Char, Traits, Allocator> &rhs) noexcept {
        return (rhs.compare(lhs) > 0);
    }

    friend inline constexpr bool
    operator<=(const Char *lhs, const ImmutableString<Char, Traits, Allocator> &rhs) noexcept {
        return (rhs.compare(lhs) >= 0);
    }

    friend inline constexpr bool
    operator>(const Char *lhs, const ImmutableString<Char, Traits, Allocator> &rhs) noexcept {
        return (rhs.compare(lhs) < 0);
    }

    friend inline constexpr bool
    operator>=(const Char *lhs, const ImmutableString<Char, Traits, Allocator> &rhs) noexcept {
        return (rhs.compare(lhs) <= 0);
    }

    // Overloading the std::swap algorithm for std::basic_cstring.
    friend inline void swap(ImmutableString &lhs, ImmutableString &rhs) noexcept {
        lhs.swap(rhs);
    }

    // Performs stream output on basic_cstring.
    friend inline std::basic_ostream<Char, Traits> &
    operator<<(std::basic_ostream<Char, Traits> &os, const ImmutableString &str) {
        return operator<<(os, str.view());
    }
};

// Static variable declaration
template<typename Char, typename Traits, typename Allocator>
typename ImmutableString<Char, Traits, Allocator>::allocator_type ImmutableString<Char, Traits, Allocator>::mAllocator{};

// The template specializations of std::hash for ImmutableString<char>.
template<>
struct std::hash<ImmutableString<char>> {
    std::size_t operator()(const ImmutableString<char> &str) const {
        return std::hash<std::string_view>()(str.view());
    }
};

// The template specializations of std::hash for ImmutableString<wchar_t>.
template<>
struct std::hash<ImmutableString<wchar_t>> {
    std::size_t operator()(const ImmutableString<wchar_t> &str) const {
        return std::hash<std::wstring_view>()(str.view());
    }
};

// The template specializations of std::hash for ImmutableString<wchar_t>.
template<>
struct std::hash<ImmutableString<char8_t>> {
    std::size_t operator()(const ImmutableString<char8_t> &str) const {
        return std::hash<std::u8string_view>()(str.view());
    }
};

// The template specializations of std::hash for ImmutableString<wchar_t>.
template<>
struct std::hash<ImmutableString<char16_t>> {
    std::size_t operator()(const ImmutableString<char16_t> &str) const {
        return std::hash<std::u16string_view>()(str.view());
    }
};

// The template specializations of std::hash for ImmutableString<wchar_t>.
template<>
struct std::hash<ImmutableString<char32_t>> {
    std::size_t operator()(const ImmutableString<char32_t> &str) const {
        return std::hash<std::u32string_view>()(str.view());
    }
};

class String final {
private:

    ImmutableString<char> m_Data;

    static constexpr char Space = ' ';              // 0x0020
    static constexpr char FormFeed = '\f';          // 0x000c
    static constexpr char LineFeed = '\n';          // 0x000a
    static constexpr char CarriageReturn = '\r';    // 0x000d
    static constexpr char HorizontalTab = '\t';     // 0x0009
    static constexpr char VerticalTab = '\v';       // 0x000b

    //size_t InternalIndexOf(const wchar_t* c, int startIndex, int count, StringComparison options) const;
    //size_t InternalIndexOfAny(const wchar_t* array, int startIndex, int count) const;
    //size_t InternalLastIndexOf(const wchar_t* c, int startIndex, int count, StringComparison options) const;
    //size_t InternalLastIndexOfAny(const wchar_t* array, int startIndex, int count) const;
    //Array<String> InternalSplit(const wchar_t* c, int count, Array<size_t>& indices, StringSplitOptions options = StringSplitOptions::None) const noexcept;

    constexpr String(const ImmutableString<char> &imString) : m_Data(imString) {}

public:

    // Constructors
    constexpr String() noexcept: m_Data() {}

    constexpr String(const char *c) noexcept : m_Data(c) {}

    constexpr String(const char c, int count) noexcept : m_Data(c, count) {}

    constexpr String(const char *c, int startIndex, int length) noexcept : m_Data(c, startIndex, length) {}

    // TODO: Set as implicit when we implement the StringPool for shared allocation
    constexpr String(const String& other) noexcept = default;

    constexpr String(String&& other) noexcept = default;

    // Copy assignment.
    constexpr String &operator=(const String &other) noexcept = default;

    // Move Assignment.
    constexpr String& operator=(String&&other) noexcept = default;

    // TODO: Handle StringPool implementation
//    constexpr String &operator=(const char *c) noexcept {
//        m_Data = c;
//        return *this;
//    }

    inline constexpr String operator+(const char *c) const { return String::Concat(m_Data.c_str(), c); }

    inline constexpr String operator+(const String &s) const {
        return String::Concat(m_Data.c_str(), s.m_Data.c_str());
    }

    inline constexpr String &operator+=(const char *c) {
        m_Data += c;
        return *this;
    }

    inline constexpr String &operator+=(const String &s) {
        m_Data += s.m_Data;
        return *this;
    }

    inline constexpr Boolean operator==(const char *c) const noexcept { return m_Data == c; }

    inline constexpr Boolean operator==(const String &s) const noexcept { return m_Data == s.m_Data; }

    inline constexpr Boolean operator!=(const char *c) const noexcept { return !(*this == c); }

    inline constexpr Boolean operator!=(const String &s) const noexcept { return !(*this == s); }

    // Returns a reference to the character at specified location pos in range [0, length()].
    inline constexpr const char &operator[](int pos) const {
        if (pos > m_Data.length() - 1) throw std::out_of_range("Out of string boundaries");
        return m_Data[pos];
    }

    inline constexpr operator const char *() const noexcept { return m_Data.c_str(); }

    static constexpr String Concat(const char *a, const char *b) noexcept {
        return ImmutableString<char>::concat(a, b);
    }

    static constexpr String Concat(const char *a, const char *b, const char *c) noexcept {
        return ImmutableString<char>::concat(a, b, c);
    }

    static constexpr String Concat(const char *a, const char *b, const char *c, const char *d) noexcept {
        return ImmutableString<char>::concat(a, b, c, d);
    }

    static constexpr String Concat(const String &a, const String &b) noexcept {
        return String::Concat(a.m_Data.c_str(), b.m_Data.c_str());
    }

    static constexpr String Concat(const String &a, const String &b, const String &c) noexcept {
        return String::Concat(a.m_Data.c_str(), b.m_Data.c_str(), c.m_Data.c_str());
    }

    static constexpr String Concat(const String &a, const String &b, const String &c, const String &d) noexcept {
        return String::Concat(a.m_Data.c_str(), b.m_Data.c_str(), c.m_Data.c_str(), d.m_Data.c_str());
    }

    static constexpr String Concat(Array<String> &array) noexcept {
        size_t totalSize = 0;

        for (const auto &it: array) totalSize += it.GetLength();

        // Push what we already have
        char *ch = new char[totalSize + 1];

        for (size_t i = 0, offset = 0; i < array.GetLength(); ++i) {
            Algorithm::strcat(ch + offset, array[i].m_Data.data());
            offset += array[i].GetLength();
        }

        ch[totalSize] = '\0';
        String ret = ch;
        delete[] ch;
        return ret;
    }

    inline constexpr Boolean Contains(char c) const noexcept { return m_Data.contains(c); }

    inline constexpr Boolean Contains(const char *c) const noexcept { return m_Data.contains(c); }

    inline constexpr Boolean Contains(const String &s) const noexcept { return m_Data.contains(s.m_Data.c_str()); }

    constexpr size_t Count(char c) const noexcept { return m_Data.count(c); }

    constexpr size_t Count(const char *c) const noexcept { return m_Data.count(c); }

    constexpr size_t Count(const String &s) const noexcept { return m_Data.count(s.m_Data.c_str()); }

    static inline constexpr String Empty() noexcept { return nullptr; }

    inline constexpr Boolean EndsWith(const char c) const noexcept { char ptr[2]; ptr[0] = c; ptr[1] ='\0'; return m_Data.ends_with(ptr);}

    inline constexpr Boolean EndsWith(const char* c) const noexcept { return m_Data.ends_with(c);}

    inline constexpr Boolean EndsWith(const String& s) const noexcept { return m_Data.ends_with(s); }

    inline constexpr size_t GetLength() const noexcept { return m_Data.length(); }

    inline constexpr size_t IndexOf(const char c) const noexcept { return m_Data.find(c); }

    inline constexpr size_t IndexOf(const char c, int startIndex) const noexcept { return m_Data.find(c, startIndex);};

    inline constexpr size_t IndexOf(const char* c) const noexcept { return m_Data.find(c); }

    inline constexpr size_t IndexOf(const char* c, int startIndex) const noexcept { return m_Data.find(c, startIndex);};

    inline constexpr size_t IndexOfAny(const char c) const noexcept { return m_Data.find_first_of(c); }

    inline constexpr size_t IndexOfAny(const char c, int startIndex) const noexcept { return m_Data.find_first_of(c, startIndex);};

    inline constexpr size_t IndexOfAny(const char* c) const noexcept { return m_Data.find_first_of(c); }

    inline constexpr size_t IndexOfAny(const char* c, int startIndex) const noexcept { return m_Data.find_first_of(c, startIndex);};

    inline constexpr Array<size_t> IndicesOf(char c) const noexcept { auto ctn = m_Data.find_all_of(c); return {ctn.begin(), ctn.end()};}
    //
    //Array<size_t> IndicesOf(const wchar_t* c) const noexcept;
    //
    //String Insert(size_t index, wchar_t c) const;
    //
    //String Insert(size_t index, const wchar_t* c) const;

    inline constexpr bool IsEmpty() const noexcept { return (m_Data.length() == 0); }

    inline constexpr Boolean IsWhiteSpace() noexcept {
        if (GetLength() == 0) return true;

        for (size_t i = 0; i < GetLength(); ++i)
            if (m_Data[i] != ' ') return false;

        return true;
    }

    //static String Join(wchar_t separator, Array<String>& arrayString) noexcept;
    //
    //static String Join(wchar_t separator, Array<String>&& arrayString) noexcept;
    //
    //static String Join(const wchar_t* separator, Array<String>& arrayString) noexcept;
    //
    //static String Join(const wchar_t* separator, Array<String>&& arrayString) noexcept;
    //
    //inline ssize_t LastIndex() const noexcept { return GetLength() - 1; }
    //
    //size_t LastIndexOf(wchar_t c, StringComparison options = StringComparison::CaseSensitive) const noexcept;
    //
    //size_t LastIndexOf(wchar_t c, int startIndex, StringComparison options = StringComparison::CaseSensitive) const noexcept;
    //
    //size_t LastIndexOf(wchar_t c, int startIndex, int count, StringComparison options = StringComparison::CaseSensitive) const noexcept;
    //
    //size_t LastIndexOf(const wchar_t* c, StringComparison options = StringComparison::CaseSensitive) const noexcept;
    //
    //size_t LastIndexOf(const wchar_t* c, int startIndex, StringComparison options = StringComparison::CaseSensitive) const noexcept;
    //
    //size_t LastIndexOf(const wchar_t* c, int startIndex, int count, StringComparison options = StringComparison::CaseSensitive) const noexcept;
    //
    //size_t LastIndexOfAny(const wchar_t array[]) const noexcept;
    //
    //size_t LastIndexOfAny(const wchar_t array[], int startIndex) const noexcept;
    //
    //size_t LastIndexOfAny(const wchar_t array[], int startIndex, int count) const noexcept;
    //
    //String PadLeft(size_t width) const noexcept;
    //
    //String PadLeft(size_t width, wchar_t padding) const noexcept;
    //
    //String PadRight(size_t width) const noexcept;
    //
    //String PadRight(size_t width, wchar_t padding) const noexcept;
    //
    //String Remove(int startIndex) const;
    //
    //String Remove(int startIndex, int count) const;
    //
    //String Replace(wchar_t oldValue, wchar_t newValue) const noexcept;
    //
    //String Replace(const wchar_t* oldValue, const wchar_t* newValue) const noexcept;
    //
    //Array<String> Split(wchar_t c, int count);
    //
    //Array<String> Split(const wchar_t* c, int count);
    //
    //Array<String> Split(wchar_t c, StringSplitOptions options = StringSplitOptions::None) const noexcept;
    //
    //Array<String> Split(const wchar_t* delimiter, StringSplitOptions options = StringSplitOptions::None) const noexcept;
    //
    //Array<String> Split(wchar_t c, int count, StringSplitOptions options) const;
    //
    //Array<String> Split(const wchar_t* c, int count, StringSplitOptions options) const;
    //
    //Boolean StartsWith(const wchar_t* c, StringComparison options = StringComparison::CaseSensitive) const noexcept;
    //
    //String Substring(int startIndex) const;
    //
    //String Substring(int startIndex, int length) const;
    //
    //Array<Char> ToCharArray() const noexcept;
    //
    //String ToLower() const noexcept;
    //
    //String ToUpper() const noexcept;

    // Left trim spaces.
    //basic_cstring_view TrimStart() const {
    //	const_pointer ptr = mStr;
    //	while (std::isspace(*ptr)) ptr++;
    //	return basic_cstring_view(ptr);
    //	//return String(ptr);
    //}

    // Right trim spaces.
    //basic_cstring_view TrimEnd() const {
    //	const_pointer ptr = mStr + GetLength() - 1;
    //	while (ptr >= mStr && std::isspace(*ptr)) ptr--;
    //	ptr++;
    //	return basic_cstring_view(mStr, static_cast<size_type>(ptr - mStr));
    //	//return String(mStr, static_cast<size_type>(ptr - mStr));
    //}

    // Trim spaces.
    //basic_cstring_view Trim() const {
    //	const_pointer ptr1 = mStr;
    //	const_pointer ptr2 = mStr + GetLength() - 1;
    //	while (std::isspace(*ptr1)) ptr1++;
    //	while (ptr2 >= ptr1 && std::isspace(*ptr2)) ptr2--;
    //	ptr2++;
    //	return basic_cstring_view(ptr1, static_cast<size_type>(ptr2 - ptr1));
    //	//return String(ptr1, static_cast<size_type>(ptr2 - ptr1));
    //}

    //String Trim() const noexcept;

    //String Trim(wchar_t c) const noexcept;
    //
    //String Trim(const wchar_t* c) const noexcept;
    //
    //String TrimEnd() const noexcept;
    //
    //String TrimEnd(wchar_t c) const noexcept;
    //
    //String TrimEnd(const wchar_t* c) const noexcept;
    //
    //String TrimStart() const noexcept;
    //
    //String TrimStart(wchar_t c) const noexcept;
    //
    //String TrimStart(const wchar_t* c) const noexcept;
};

// The template specializations of std::hash
//template<>
//struct std::hash<String> {
//	std::size_t operator()(const String& str) const {
//		return std::hash<std::string_view>()(str.view());
//	}
//};

#endif //CPPDATASTRUCTURES_STRING_HPP