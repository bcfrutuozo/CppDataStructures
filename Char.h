//
// Created by bcfrutuozo on 31/03/2022.
//

#ifndef CPPDATASTRUCTURES_CHAR_H
#define CPPDATASTRUCTURES_CHAR_H

#include <cstdint>
#include <cassert>
#include <type_traits>

#include "TypeValue.h"
#include "UnicodeCategory.h"
#include "CharUnicodeInfo.h"

class Char {

private:

    char Value;

    // Define the whole Latin1 table based on Unicode category values from U+0000 to U+00FF
    static constexpr uint8_t CategoryForLatin1[256] = {
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,    // 0000 - 0007
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,    // 0008 - 000F
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,    // 0010 - 0017
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,    // 0018 - 001F
            (uint8_t) UnicodeCategory::SpaceSeparator, (uint8_t) UnicodeCategory::OtherPunctuation,
            (uint8_t) UnicodeCategory::OtherPunctuation, (uint8_t) UnicodeCategory::OtherPunctuation,
            (uint8_t) UnicodeCategory::CurrencySymbol, (uint8_t) UnicodeCategory::OtherPunctuation,
            (uint8_t) UnicodeCategory::OtherPunctuation, (uint8_t) UnicodeCategory::OtherPunctuation,    // 0020 - 0027
            (uint8_t) UnicodeCategory::OpenPunctuation, (uint8_t) UnicodeCategory::ClosePunctuation,
            (uint8_t) UnicodeCategory::OtherPunctuation, (uint8_t) UnicodeCategory::MathSymbol,
            (uint8_t) UnicodeCategory::OtherPunctuation, (uint8_t) UnicodeCategory::DashPunctuation,
            (uint8_t) UnicodeCategory::OtherPunctuation, (uint8_t) UnicodeCategory::OtherPunctuation,    // 0028 - 002F
            (uint8_t) UnicodeCategory::DecimalDigitNumber, (uint8_t) UnicodeCategory::DecimalDigitNumber,
            (uint8_t) UnicodeCategory::DecimalDigitNumber, (uint8_t) UnicodeCategory::DecimalDigitNumber,
            (uint8_t) UnicodeCategory::DecimalDigitNumber, (uint8_t) UnicodeCategory::DecimalDigitNumber,
            (uint8_t) UnicodeCategory::DecimalDigitNumber,
            (uint8_t) UnicodeCategory::DecimalDigitNumber,    // 0030 - 0037
            (uint8_t) UnicodeCategory::DecimalDigitNumber, (uint8_t) UnicodeCategory::DecimalDigitNumber,
            (uint8_t) UnicodeCategory::OtherPunctuation, (uint8_t) UnicodeCategory::OtherPunctuation,
            (uint8_t) UnicodeCategory::MathSymbol, (uint8_t) UnicodeCategory::MathSymbol,
            (uint8_t) UnicodeCategory::MathSymbol, (uint8_t) UnicodeCategory::OtherPunctuation,    // 0038 - 003F
            (uint8_t) UnicodeCategory::OtherPunctuation, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,    // 0040 - 0047
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,    // 0048 - 004F
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,    // 0050 - 0057
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::OpenPunctuation,
            (uint8_t) UnicodeCategory::OtherPunctuation, (uint8_t) UnicodeCategory::ClosePunctuation,
            (uint8_t) UnicodeCategory::ModifierSymbol,
            (uint8_t) UnicodeCategory::ConnectorPunctuation,    // 0058 - 005F
            (uint8_t) UnicodeCategory::ModifierSymbol, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,    // 0060 - 0067
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,    // 0068 - 006F
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,    // 0070 - 0077
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::OpenPunctuation,
            (uint8_t) UnicodeCategory::MathSymbol, (uint8_t) UnicodeCategory::ClosePunctuation,
            (uint8_t) UnicodeCategory::MathSymbol, (uint8_t) UnicodeCategory::Control,    // 0078 - 007F
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,    // 0080 - 0087
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,    // 0088 - 008F
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,    // 0090 - 0097
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,    // 0098 - 009F
            (uint8_t) UnicodeCategory::SpaceSeparator, (uint8_t) UnicodeCategory::OtherPunctuation,
            (uint8_t) UnicodeCategory::CurrencySymbol, (uint8_t) UnicodeCategory::CurrencySymbol,
            (uint8_t) UnicodeCategory::CurrencySymbol, (uint8_t) UnicodeCategory::CurrencySymbol,
            (uint8_t) UnicodeCategory::OtherSymbol, (uint8_t) UnicodeCategory::OtherSymbol,    // 00A0 - 00A7
            (uint8_t) UnicodeCategory::ModifierSymbol, (uint8_t) UnicodeCategory::OtherSymbol,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::InitialQuotePunctuation,
            (uint8_t) UnicodeCategory::MathSymbol, (uint8_t) UnicodeCategory::DashPunctuation,
            (uint8_t) UnicodeCategory::OtherSymbol, (uint8_t) UnicodeCategory::ModifierSymbol,    // 00A8 - 00AF
            (uint8_t) UnicodeCategory::OtherSymbol, (uint8_t) UnicodeCategory::MathSymbol,
            (uint8_t) UnicodeCategory::OtherNumber, (uint8_t) UnicodeCategory::OtherNumber,
            (uint8_t) UnicodeCategory::ModifierSymbol, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::OtherSymbol, (uint8_t) UnicodeCategory::OtherPunctuation,    // 00B0 - 00B7
            (uint8_t) UnicodeCategory::ModifierSymbol, (uint8_t) UnicodeCategory::OtherNumber,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::FinalQuotePunctuation,
            (uint8_t) UnicodeCategory::OtherNumber, (uint8_t) UnicodeCategory::OtherNumber,
            (uint8_t) UnicodeCategory::OtherNumber, (uint8_t) UnicodeCategory::OtherPunctuation,    // 00B8 - 00BF
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,    // 00C0 - 00C7
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,    // 00C8 - 00CF
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::MathSymbol,    // 00D0 - 00D7
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,    // 00D8 - 00DF
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,    // 00E0 - 00E7
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,    // 00E8 - 00EF
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::MathSymbol,    // 00F0 - 00F7
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,    // 00F8 - 00FF
    };

    static constexpr bool CheckLetter(UnicodeCategory uc) noexcept {
        switch (uc) {
            case UnicodeCategory::UppercaseLetter:
            case UnicodeCategory::LowercaseLetter:
            case UnicodeCategory::TitlecaseLetter:
            case UnicodeCategory::ModifierLetter:
            case UnicodeCategory::OtherLetter:
                return true;
        }
        return false;
    }

    static constexpr bool CheckLetterOrDigit(UnicodeCategory uc) {
        switch (uc) {
            case UnicodeCategory::UppercaseLetter:
            case UnicodeCategory::LowercaseLetter:
            case UnicodeCategory::TitlecaseLetter:
            case UnicodeCategory::ModifierLetter:
            case UnicodeCategory::OtherLetter:
            case UnicodeCategory::DecimalDigitNumber:
                return true;
        }
        return false;
    }

    static constexpr bool CheckPunctuation(UnicodeCategory uc) {
        switch (uc) {
            case UnicodeCategory::ConnectorPunctuation:
            case UnicodeCategory::DashPunctuation:
            case UnicodeCategory::OpenPunctuation:
            case UnicodeCategory::ClosePunctuation:
            case UnicodeCategory::InitialQuotePunctuation:
            case UnicodeCategory::FinalQuotePunctuation:
            case UnicodeCategory::OtherPunctuation:
                return true;
        }
        return false;
    }

    static constexpr UnicodeCategory GetLatin1UnicodeCategory(char ch) noexcept {
        assert(IsLatin1(ch) == true);
        return static_cast<UnicodeCategory>(CategoryForLatin1[(int) ch]);
    }

    static constexpr bool IsLatin1(char ch) noexcept {
        return (ch <= '\x00FF');
    }

    static constexpr bool IsASCII(char ch) noexcept {
        return (ch <= '\x007F');
    }

    static bool IsWhiteSpaceLatin1(char ch) noexcept {
        /*
         * There are characters which belong to UnicodeCategory.Control but are considered as white spaces.
         * We use code point comparisons for these characters here as a temporary fix.
         * U+0009 = <control> HORIZONTAL TAB
         * U+000a = <control> LINE FEED
         * U+000b = <control> VERTICAL TAB
         * U+000c = <control> FORM FEED
         * U+000d = <control> CARRIAGE RETURN
         * U+0085 = <control> NEXT LINE
         * U+00a0 = NO-BREAK SPACE
         */
        if ((ch == ' ') || (ch >= '\x0009' && ch <= -'\x000d') || ch == '\x00a0' || ch == '\x0085')
            return true;
        return false;
    }

public:

    constexpr Char() : Value() {};

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Char(T value) noexcept requires(is_promotion_primitive<T>::value) : Value((value)) {}

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr explicit Char(T value) noexcept requires(is_promotion_wrapper<T>::value) : Value((value)) {}

    Char(Char const &) = default;

    Char(Char &&) = default;

    Char &operator=(Char const &) = default;

    Char &operator=(Char &&) = default;

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Char operator=(T value) noexcept requires(is_promotion_primitive<T>::value) { return Value = value; };

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr Char operator=(T value) noexcept requires(is_promotion_wrapper<T>::value) { return Value = value; };

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr operator T() noexcept requires(is_promotion_primitive<T>::value) { return Value; };

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr operator T() noexcept requires(is_promotion_wrapper<T>::value) { return Value; };

    constexpr int GetHashCode() const noexcept { return (int) Value | ((int) Value << 16); }

    static constexpr bool IsDigit(char c) {
        if (IsLatin1(c)) {
            return (c >= '0' && c <= '9');
        }
        return (CharUnicodeInfo::GetUnicodeCategory(c) == UnicodeCategory::DecimalDigitNumber);
    };

    static constexpr bool IsLetter(char c) noexcept {
        if (IsLatin1(c)) {
            if (IsASCII(c)) {
                c |= static_cast<char>(0x20);
                return ((c >= 'a' && c <= 'z'));
            }
            return CheckLetter(GetLatin1UnicodeCategory(c));
        }
        return CheckLetter(CharUnicodeInfo::GetUnicodeCategory(c));
    }

    static constexpr bool IsLetterOrDigit(char c) {
        if (IsLatin1(c)) return (CheckLetterOrDigit(GetLatin1UnicodeCategory(c)));
        return (CheckLetterOrDigit(CharUnicodeInfo::GetUnicodeCategory(c)));
    }

    static constexpr bool IsLower(char c) {
        if (IsLatin1(c)) {
            if (IsASCII(c)) return (c >= 'a' && c <= 'z');
            return (GetLatin1UnicodeCategory(c) == UnicodeCategory::LowercaseLetter);
        }
        return (CharUnicodeInfo::GetUnicodeCategory(c) == UnicodeCategory::LowercaseLetter);
    }

    static constexpr bool IsPunctuation(char c) {
        if (IsLatin1(c)) return (CheckPunctuation(GetLatin1UnicodeCategory(c)));
        return (CheckPunctuation(CharUnicodeInfo::GetUnicodeCategory(c)));
    }

    static constexpr bool IsUpper(char c) noexcept {
        if (IsLatin1(c)) {
            if (IsASCII(c)) return (c >= 'A' && c <= 'Z');
            return GetLatin1UnicodeCategory(c) == UnicodeCategory::UppercaseLetter;
        }
        return CharUnicodeInfo::GetUnicodeCategory(c) == UnicodeCategory::UppercaseLetter;
    }

    static bool IsWhiteSpace(char c) noexcept {
        if (IsLatin1(c)) return IsWhiteSpaceLatin1(c);
        return CharUnicodeInfo::IsWhiteSpace(c);
    }


    static constexpr char MaxValue = (char) 0xFFFF;
    static constexpr char MinValue = (char) 0x00;
};

//#define char Char;

#endif //CPPDATASTRUCTURES_CHAR_H
