//
// Created by bcfru on 10/24/2023.
//

#ifndef CPPDATASTRUCTURES_ALGORITHM_HPP
#define CPPDATASTRUCTURES_ALGORITHM_HPP

#include <cstdint>
#include <string>
#include <type_traits>
#include <string_view>

namespace Algorithm {


    // base template with 1 argument (which will be called from the variadic one).
    template<typename Char = char,
            typename Allocator = std::allocator<Char>,
            typename Arg>
    static constexpr std::allocator_traits<Allocator>::size_type strlen(Arg arg) noexcept {
        typename std::allocator_traits<Allocator>::const_pointer s;
        for (s = arg; *s; ++s);
        return (s - arg);
    }


    template<typename Char = char,
            typename Allocator = std::allocator<Char>,
            typename First, typename... Args>
    static constexpr std::allocator_traits<Allocator>::size_type strlen(First first, Args... args) noexcept {
        typename std::allocator_traits<Allocator>::const_pointer s;
        for (s = first; *s; ++s);
        return (s - first) + strlen(args...);
    }

    template<typename Char = char,
            typename Allocator = std::allocator<Char>,
            typename Arg>
    static constexpr typename std::allocator_traits<Allocator>::const_pointer
    strcat(typename std::allocator_traits<Allocator>::pointer to, Arg arg) noexcept {
        for (; (*to = *arg) != '\0'; ++arg, ++to);
        *to = Char();
        return to;
    }


    template<typename Char = char,
            typename Allocator = std::allocator<Char>,
            typename First, typename... Args>
    static constexpr typename std::allocator_traits<Allocator>::const_pointer
    strcat(typename std::allocator_traits<Allocator>::pointer to, First first, Args... args) noexcept {
        typename std::allocator_traits<Allocator>::const_pointer save = to;
        for (; (*to = *first) != '\0'; ++first, ++to);
        strcat(to, args...);
        return save;
    }


    constexpr void LPSArray(const char* pattern, size_t M, int *lps) {
        int len = 0;
        lps[0] = 0;
        int i = 1;
        while (i < M) {
            if (pattern[i] == pattern[len]) {
                ++len;
                lps[i] = len;
                ++i;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    ++i;
                }
            }
        }
    }

    constexpr int KMPSearch(const char* pattern, const char* str) {
        auto M = Algorithm::strlen(pattern);
        auto N = Algorithm::strlen(str);

        int lps[M];
        int ret = 0;

        LPSArray(pattern, M, lps);

        int i = 0;
        int j = 0;
        while ((N - i) >= (M - j)) {
            if (pattern[j] == str[i]) {
                ++j;
                ++i;
            }

            if (j == M) {
                // Found it!
                ++ret;
                j = lps[j - 1];
            } else if (i < N && pattern[j] != str[i]) {
                if (j != 0)
                    j = lps[j - 1];
                else
                    i += 1;
            }
        }

        return ret;
    }
}

#endif //CPPDATASTRUCTURES_ALGORITHM_HPP
