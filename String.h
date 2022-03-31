//
// Created by bcfrutuozo on 12/03/2022.
//

#ifndef CPPDATASTRUCTURES_STRING_H
#define CPPDATASTRUCTURES_STRING_H

#include "Platform.h"
#include "Container.hpp"
#include "Array.h"
#include "StringSplitOptions.h"
#include "StringComparison.h"

#include <iostream>
#include <cstring>

class String : Container<const char *> {

private:

    //<editor-fold desc="Iterators implementation">
    struct Iterator
    {
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = char;
        using pointer = char*;  // or also value_type*
        using reference = char&;  // or also value_type&

        // Pointer field representation
        pointer pElement = nullptr;

        constexpr Iterator(pointer ptr) noexcept : pElement(ptr) {}

        constexpr reference operator*() const { return *pElement; }

        constexpr pointer operator->() const { return pElement; }

        // Prefix increment
        constexpr Iterator& operator++()
        {
            this->pElement++;
            return *this;
        }

        // Postfix increment
        constexpr Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        // Prefix decrement
        constexpr Iterator& operator--()
        {
            this->pElement--;
            return *this;
        }

        // Postfix decrement
        constexpr Iterator operator--(int)
        {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        inline constexpr friend bool operator==(const Iterator& a, const Iterator& b) noexcept
        {
            return a.pElement == b.pElement;
        };

        inline constexpr friend bool operator!=(const Iterator& a, const Iterator& b) noexcept
        {
            return !(a == b);
        };
    };

    struct ConstIterator
    {
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const char;
        using pointer = const char*;  // or also value_type*
        using reference = const char&;  // or also value_type&

        // Pointer field representation
        pointer pElement = nullptr;

        constexpr ConstIterator(pointer ptr) noexcept : pElement(ptr) {}

        constexpr reference operator*() const { return *pElement; }

        constexpr pointer operator->() const { return pElement; }

        // Prefix increment
        constexpr ConstIterator& operator++()
        {
            this->pElement++;
            return *this;
        }

        // Postfix increment
        constexpr ConstIterator operator++(int)
        {
            ConstIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        // Prefix decrement
        constexpr ConstIterator& operator--()
        {
            this->pElement--;
            return *this;
        }

        // Postfix decrement
        constexpr ConstIterator operator--(int)
        {
            ConstIterator tmp = *this;
            --(*this);
            return tmp;
        }

        inline constexpr friend bool operator==(const ConstIterator& a, const ConstIterator& b) noexcept
        {
            return a.pElement == b.pElement;
        };

        inline constexpr friend bool operator!=(const ConstIterator& a, const ConstIterator& b) noexcept
        {
            return !(a == b);
        };
    };

    struct ReverseIterator
    {
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = char;
        using pointer = char*;  // or also value_type*
        using reference = char&;  // or also value_type&

        // Pointer field representation
        pointer pElement = nullptr;

        constexpr ReverseIterator(pointer ptr) noexcept : pElement(ptr) {}

        constexpr reference operator*() const { return *pElement; }

        constexpr pointer operator->() const { return pElement; }

        // Prefix increment
        constexpr ReverseIterator& operator++()
        {
            this->pElement--;
            return *this;
        }

        // Postfix increment
        constexpr ReverseIterator operator++(int)
        {
            ReverseIterator tmp = *this;
            --(*this);
            return tmp;
        }

        // Prefix decrement
        constexpr ReverseIterator& operator--()
        {
            this->pElement++;
            return *this;
        }

        // Postfix decrement
        constexpr ReverseIterator operator--(int)
        {
            ReverseIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        inline constexpr friend bool operator==(const ReverseIterator& a, const ReverseIterator& b) noexcept
        {
            return a.pElement ==  b.pElement;
        };

        inline constexpr friend bool operator!=(const ReverseIterator& a, const ReverseIterator& b) noexcept
        {
            return !(a == b);
        };
    };

    struct ConstReverseIterator
    {
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const char;
        using pointer = const char*;  // or also value_type*
        using reference = const char&;  // or also value_type&

        constexpr reference operator*() const { return *pElement; }

        constexpr pointer operator->() const { return pElement; }

        // Pointer field representation
        pointer pElement = nullptr;

        constexpr ConstReverseIterator(pointer ptr) noexcept : pElement(ptr) {}

        // Prefix increment
        constexpr ConstReverseIterator& operator++()
        {
            this->pElement--;
            return *this;
        }

        // Postfix increment
        constexpr ConstReverseIterator operator++(int)
        {
            ConstReverseIterator tmp = *this;
            --(*this);
            return tmp;
        }

        // Prefix increment
        constexpr ConstReverseIterator& operator--()
        {
            this->pElement++;
            return *this;
        }

        // Postfix increment
        constexpr ConstReverseIterator operator--(int)
        {
            ConstReverseIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        inline constexpr friend bool operator==(const ConstReverseIterator& a, const ConstReverseIterator& b) noexcept
        {
            return a.pElement == b.pElement;
        };

        inline constexpr friend bool operator!=(const ConstReverseIterator& a, const ConstReverseIterator& b) noexcept
        {
            return !(a == b);
        };
    };
    //</editor-fold>

    size_t m_Length;
    char *m_Data;

    inline constexpr char *GetPointer() const noexcept { return m_Data; }

    static constexpr char Space = ' ';              // 0x20
    static constexpr char FormFeed = '\f';          // 0x0c
    static constexpr char LineFeed = '\n';          // 0x0a
    static constexpr char CarriageReturn = '\r';    // 0x0d
    static constexpr char HorizontalTab = '\t';     // 0x09
    static constexpr char VerticalTab = '\v';       // 0x0b

    ssize_t InternalIndexOf(const char* c, int startIndex, int count) const noexcept;
    ssize_t InternalIndexOfAny(const char array[], int startIndex, int count) const noexcept;
    ssize_t InternalLastIndexOf(const char* c, int startIndex, int count) const noexcept;
    ssize_t InternalLastIndexOfAny(const char array[], int startIndex, int count) const noexcept;
    Array<String> InternalSplit(const char* c, int count, Array<size_t>& indices, StringSplitOptions options = StringSplitOptions::None) const noexcept;

public:

    String() noexcept;

    String(const char *c) noexcept;

    String(const String &s) noexcept;

    String(String &&s) noexcept;

    ~String() noexcept;

    String &operator=(const char *c) noexcept;

    String &operator=(const String &other) noexcept;

    String &operator=(String &&s) noexcept;

    String operator+(const char *c) noexcept;

    String operator+(const String &s) noexcept;

    String& operator+=(const char* c) noexcept;

    inline String& operator+=(const String& rhs) noexcept;

    char& operator[](size_t index);

    bool operator==(const char *c) const noexcept;

    inline bool operator==(const String &rhs) const noexcept;

    inline bool operator!=(const char* c) const noexcept;

    inline bool operator!=(const String &rhs) const noexcept;

    bool Contains(char c) const noexcept;

    bool Contains(const char *c) const noexcept;

    constexpr size_t GetLength() const noexcept { return m_Length; }

    static String Concat(String& a, String& b) noexcept;

    String Concat(Array<String>& array) const noexcept;

    void Copy(char c[], size_t length, size_t pos);

    size_t Count(char c) const noexcept;

    size_t Count(const char *c) const noexcept;

    bool EndsWith(const char* c, StringComparison options = StringComparison::CaseSensitive) const noexcept;

    ssize_t IndexOf(char c) const noexcept;

    ssize_t IndexOf(char c, int startIndex) const noexcept;

    ssize_t IndexOf(char c, int startIndex, int count) const noexcept;

    ssize_t IndexOf(const char *c) const noexcept;

    ssize_t IndexOf(const char *c, int startIndex) const noexcept;

    ssize_t IndexOf(const char *c, int startIndex, int count) const noexcept;

    ssize_t IndexOfAny(const char array[]) const noexcept;

    ssize_t IndexOfAny(const char array[], int startIndex) const noexcept;

    ssize_t IndexOfAny(const char array[], int startIndex, int count) const noexcept;

    Array<size_t> IndicesOf(char c) const noexcept;

    Array<size_t> IndicesOf(const char *c) const noexcept;

    String Insert(size_t index, char c) const;

    String Insert(size_t index, const char* c) const;

    inline constexpr bool IsEmpty() const noexcept { return GetLength() == 0; }

    constexpr bool IsWhiteSpace() const noexcept {
        if(GetLength() == 0) return true;

        for(size_t i = 0; i < GetLength(); ++i)
            if(m_Data[i] != ' ') return false;

        return true;
    }

    static String Join(char separator, Array<String>& arrayString) noexcept;

    static String Join(char separator, Array<String>&& arrayString) noexcept;

    static String Join(const char* separator, Array<String>& arrayString) noexcept;

    static String Join(const char* separator, Array<String>&& arrayString) noexcept;

    inline constexpr ssize_t LastIndex() const noexcept { return m_Length - 1; }

    ssize_t LastIndexOf(char c) const noexcept;

    ssize_t LastIndexOf(char c, int startIndex) const noexcept;

    ssize_t LastIndexOf(char c, int startIndex, int count) const noexcept;

    ssize_t LastIndexOf(const char *c) const noexcept;

    ssize_t LastIndexOf(const char *c, int startIndex) const noexcept;

    ssize_t LastIndexOf(const char *c, int startIndex, int count) const noexcept;

    ssize_t LastIndexOfAny(const char array[]) const noexcept;

    ssize_t LastIndexOfAny(const char array[], int startIndex) const noexcept;

    ssize_t LastIndexOfAny(const char array[], int startIndex, int count) const noexcept;

    String PadLeft(size_t width) const noexcept;

    String PadLeft(size_t width, char padding) const noexcept;

    String PadRight(size_t width) const noexcept;

    String PadRight(size_t width, char padding) const noexcept;

    String Remove(int startIndex) const noexcept;

    String Remove(int startIndex, int count) const noexcept;

    String Replace(char oldValue, char newValue) const noexcept;

    String Replace(const char* oldValue, const char* newValue) const noexcept;

    Array<String> Split(char c, int count);

    Array<String> Split(const char* c, int count);

    Array<String> Split(char c, StringSplitOptions options = StringSplitOptions::None) const noexcept;

    Array<String> Split(const char *delimiter, StringSplitOptions options = StringSplitOptions::None) const noexcept;

    Array<String> Split(char c, int count, StringSplitOptions options) const;

    Array<String> Split(const char* c, int count, StringSplitOptions options) const;

    bool StartsWith(const char* c, StringComparison options = StringComparison::CaseSensitive) const noexcept;

    String Substring(int startIndex) const;

    String Substring(int startIndex, int length) const;

    Array<char> ToCharArray() const noexcept;

    // We are not dealing yet with UTF8. This will come at the future
    String ToLower() const noexcept;

    // We are not dealing yet with UTF8. This will come at the future
    String ToUpper() const noexcept;

    String Trim() const noexcept;

    String Trim(char c) const noexcept;

    String Trim(const char* c) const noexcept;

    String TrimEnd() const noexcept;

    String TrimEnd(char c) const noexcept;

    String TrimEnd(const char* c) const noexcept;

    String TrimStart() const noexcept;

    String TrimStart(char c) const noexcept;

    String TrimStart(const char* c) const noexcept;

    friend std::ostream &operator<<(std::ostream &os, const String &s);

    constexpr Iterator begin() noexcept { return m_Data; }

    constexpr Iterator end() noexcept { return m_Data + m_Length; }

    constexpr ConstIterator cbegin() const noexcept { return m_Data; }

    constexpr ConstIterator cend() const noexcept { return m_Data + m_Length; }

    constexpr ReverseIterator rbegin() noexcept { return m_Data + LastIndex(); }

    constexpr ReverseIterator rend() noexcept { return m_Data - 1; }

    constexpr ConstReverseIterator crbegin() const noexcept { return m_Data + LastIndex(); }

    constexpr ConstReverseIterator crend() const noexcept { return m_Data - 1; }
};

inline std::ostream &operator<<(std::ostream &os, const String &s) {
    os << s.GetPointer();
    return os;
};

#endif //CPPDATASTRUCTURES_STRING_H
