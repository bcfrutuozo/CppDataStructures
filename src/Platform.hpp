#ifndef CPPDATASTRUCTURES_PLATFORM_HPP
#define CPPDATASTRUCTURES_PLATFORM_HPP

#define _SILENCE_CXX20_ATOMIC_INIT_DEPRECATION_WARNING

#include <climits>
#include <cstddef>
#include <cinttypes>
#include <cstdint>
#include <string_view>
#include <type_traits>

#if defined(__linux) || defined(__linux__) || defined(linux)
# define LINUX
#elif defined(__APPLE__)
# define MACOS
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
# define WINDOWS
#endif

#if _WIN64 | __x86_x64__ || __ppc64__
#define ENVIRONMENT64
#elif
#define ENVIRONMENT32
#endif

#if _WIN32
typedef long long ssize_t;  /* Windows */
#define SSIZE_MIN  LLONG_MIN
#define SSIZE_MAX  LLONG_MAX
#define strcasestr(c, check) strstri(c, check)
#define wcscasestr(c, check) wcsstri(c, check)
#elif __linux__
typedef long ssize_t;       /* Linux */
#define SSIZE_MIN  LONG_MIN
#define SSIZE_MAX  LONG_MAX
#endif

#include <stdio.h>
#include <cstring>
#include <string>

#define ArraySize(array) (sizeof(array)/sizeof(array[0]))

// Compare function to handle with const char*
// Char* must always be compared with strcmp() function
template<typename T>
static inline constexpr typename std::enable_if<std::is_same<T, const char*>::value, bool>::type Equals(const T& a, const T& b) noexcept
{
    return (strcmp(a, b) == 0);
}

template<typename T>
static inline constexpr typename std::enable_if<std::is_same<T, const wchar_t*>::value, bool>::type Equals(const T& a, const T& b) noexcept
{
    return (wcscmp(a, b) == 0);
}

// Compare function for primitive and classes which contain implementation of operator==()
template <typename T>
static inline constexpr typename std::enable_if<!std::is_same<T, const char*>::value, bool>::type Equals(const T& a, const T& b) noexcept
{
    return (a == b);
}

//template <typename T>
//static inline constexpr typename std::enable_if<!std::is_same<T, const wchar_t*>::value, bool>::type Equals(const T& a, const T& b) noexcept
//{
//    return (a == b);
//}

/* Auxiliar c string functions to handle String class abstraction
 * Find the first occurrence of needle in haystack, where the search is limited to the
 * first length characters of haystack.
 */
static char *strnstr(const char *haystack, const char *needle, size_t length) {
    char nC, hC;

    if ((nC = *needle++) != '\0') {
        const size_t needleLength = strlen(needle);
        do {
            do {
                if (length-- < 1 || (hC = *haystack++) == '\0')
                    return nullptr;
            } while (hC != nC);
            if (needleLength > length)
                return nullptr;
        } while (strncmp(haystack, needle, needleLength) != 0);
        --haystack;
    }
    return ((char *) haystack);
}

static wchar_t* wcsnstr(const wchar_t* haystack, const wchar_t* needle, size_t length) {
    wchar_t nC, hC;

    if ((nC = *needle++) != '\0') {
        const size_t needleLength = wcslen(needle);
        do {
            do {
                if (length-- < 1 || (hC = *haystack++) == '\0')
                    return nullptr;
            } while (hC != nC);
            if (needleLength > length)
                return nullptr;
        } while (wcsncmp(haystack, needle, needleLength) != 0);
        --haystack;
    }
    return ((wchar_t*)haystack);
}

// Case-sensitive
static char *strnrstr(const char *str, const char *sub, int len) {
    const char *pend = str + len;
    const char *pstr;
    const int sl = strlen(sub);
    for (pstr = pend - sl; pstr >= str; pstr--) {
        if (!strncmp(pstr, sub, sl))
            return (char *) pstr;
    }
    return nullptr;
}

static wchar_t* wcstrnrstr(const wchar_t* str, const wchar_t* sub, int len) {
    const wchar_t* pend = str + len;
    const wchar_t* pstr;
    const int sl = wcslen(sub);
    for (pstr = pend - sl; pstr >= str; pstr--) {
        if (!wcsncmp(pstr, sub, sl))
            return (wchar_t*)pstr;
    }
    return nullptr;
}

static char* strrstr(const char *str, const char *sub) { return strnrstr(str, sub, strlen(str)); }
static wchar_t* wcsrstr(const wchar_t* str, const wchar_t* sub) { return wcstrnrstr(str, sub, wcslen(str)); }

// Case-insensitive
#ifdef __linux__
static int strnicmp(char const *s1, char const *s2, size_t len) {
    unsigned char c1 = '\0';
    unsigned char c2 = '\0';
    if (len > 0) {
        do {
            c1 = *s1;
            c2 = *s2;
            s1++;
            s2++;
            if (!c1)
                break;
            if (!c2)
                break;
            if (c1 == c2)
                continue;
            c1 = tolower(c1);
            c2 = tolower(c2);
            if (c1 != c2)
                break;
        } while (--len);
    }
    return (int) c1 - (int) c2;
}
#endif

static char *strnrstri(const char *str, const char *sub, int len) {
    const char *pend = str + len;
    const char *pstr;
    int sl = strlen(sub);
    for (pstr = pend - sl; pstr >= str; pstr--) {
        if (!strnicmp(pstr, sub, sl))
            return (char *) pstr;
    }
    return nullptr;
}

static wchar_t* wcsnrstri(const wchar_t* str, const wchar_t* sub, int len) {
    const wchar_t* pend = str + len;
    const wchar_t* pstr;
    int sl = wcslen(sub);
    for (pstr = pend - sl; pstr >= str; pstr--) {
        if (!wcsnicmp(pstr, sub, sl))
            return (wchar_t*)pstr;
    }
    return nullptr;
}

static char* strrstri(const char *str, const char *sub) { return strnrstri(str, sub, strlen(str)); }
static wchar_t* wcsrstri(const wchar_t* str, const wchar_t* sub) { return wcsnrstri(str, sub, wcslen(str)); }

static char *strnstri(const char *str, const char *sub, int len) {
    const char *pend = str + len;
    const char *pstr;
    int sl = strlen(sub);
    for (pstr = str; pstr <= pend - sl; pstr++) {
        if (!strnicmp(pstr, sub, sl))
            return (char *) pstr;
    }
    return nullptr;
}

static wchar_t* wcsnstri(const wchar_t* str, const wchar_t* sub, int len) {
    const wchar_t* pend = str + len;
    const wchar_t* pstr;
    int sl = wcslen(sub);
    for (pstr = str; pstr <= pend - sl; pstr++) {
        if (!wcsnicmp(pstr, sub, sl))
            return (wchar_t*)pstr;
    }
    return nullptr;
}

static char* strstri(const char* str, const char* sub) { return strnstri(str, sub, strlen(str)); }
static wchar_t* wcsstri(const wchar_t* str, const wchar_t* sub) { return wcsnstri(str, sub, wcslen(str)); }

#endif // CPPDATASTRUCTURES_PLATFORM_HPP