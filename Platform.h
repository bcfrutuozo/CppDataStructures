#ifndef CPPDATASTRUCTURES_PLATFORM_H
#define CPPDATASTRUCTURES_PLATFORM_H

#include <climits>
#include <cstddef>
#include <cinttypes>
#include <cstdint>
#include <string_view>

#if SIZE_MAX == UINT_MAX
typedef int ssize_t;        /* common 32 bit case */
#define SSIZE_MIN  INT_MIN
#define SSIZE_MAX  INT_MAX
#elif SIZE_MAX == ULONG_MAX
typedef long ssize_t;       /* linux 64 bits */
#define SSIZE_MIN  LONG_MIN
#define SSIZE_MAX  LONG_MAX
#elif SIZE_MAX == ULLONG_MAX
typedef long long ssize_t;  /* windows 64 bits */
#define SSIZE_MIN  LLONG_MIN
#define SSIZE_MAX  LLONG_MAX
#elif SIZE_MAX == USHRT_MAX
typedef short ssize_t;      /* is this even possible? */
#define SSIZE_MIN  SHRT_MIN
#define SSIZE_MAX  SHRT_MAX
#elif SIZE_MAX == UINTMAX_MAX
typedef intmax_t ssize_t;  /* last resort, chux suggestion */
#define SSIZE_MIN  INTMAX_MIN
#define SSIZE_MAX  INTMAX_MAX
#else
#error platform has exotic SIZE_MAX
#endif

#include <stdio.h>
#include <cstring>
#include <string>

/* Auxiliar c string functions to handle String class abstraction
 * Find the first occurrence of needle in haystack, where the search is limited to the
 * first length characters of haystack.
 */
static constexpr char *strnstr(const char *haystack, const char *needle, size_t length) {
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

// Case sensitive
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

static char *strrstr(const char *str, const char *sub) { return strnrstr(str, sub, strlen(str)); }

//case Insensitive
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

static char *strrstri(const char *str, const char *sub) { return strnrstri(str, sub, strlen(str)); }

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

static char *strstri(const char *str, const char *sub) { return strnstri(str, sub, strlen(str)); }

#endif // CPPDATASTRUCTURES_PLATFORM_H