//
// Created by bcfrutuozo on 03/04/2022.
//

#include "Char.hpp"
#include "Int32.hpp"
#include "String.hpp"

String Char::ConvertFromUTF32(int utf32) noexcept {

    // For UTF32 values from U+00D800 ~ U+00DFFF, we should throw.  They
    // are considered as irregular code unit sequence, but they are not illegal.
    if ((utf32 < 0 || utf32 > UNICODE_PLANE16_END) || (utf32 >= HIGH_SURROGATE_START && utf32 <= LOW_SURROGATE_END)) {
        throw std::out_of_range("utf32");
    }

    if (utf32 < UNICODE_PLANE01_START) {
        // This is a BMP character.
        return (Char::ToString((char) utf32));
    }

    // This is a sumplementary character.  Convert it to a surrogate pair in UTF-16.
    utf32 -= UNICODE_PLANE01_START;
    char surrogate[2];
    surrogate[0] = (char) ((utf32 / 0x400) + (int) CharUnicodeInfo::HIGH_SURROGATE_START);
    surrogate[1] = (char) ((utf32 % 0x400) + (int) CharUnicodeInfo::LOW_SURROGATE_START);
    return String(surrogate);
}

Int32 Char::ConvertToUTF32(Char highSurrogate, Char lowSurrogate) noexcept {
    if (!Char::IsHighSurrogate(highSurrogate)) {
        throw std::out_of_range("highSurrogate");
    }
    if (!Char::IsLowSurrogate(lowSurrogate)) {
        throw std::out_of_range("lowSurrogate");
    }

    return (((highSurrogate - CharUnicodeInfo::HIGH_SURROGATE_START) * 0x400) +
            (lowSurrogate - CharUnicodeInfo::LOW_SURROGATE_START) + UNICODE_PLANE01_START);
}

Int32 Char::ConvertToUTF32(String &s, int index) {
    if (index < 0 && index >= s.GetLength()) throw std::out_of_range("index");

    // Check if the character at index is a high surrogate.
    int temp1 = s[index] - CharUnicodeInfo::HIGH_SURROGATE_START;
    if (temp1 >= 0 && temp1 <= 0x7ff) {
        // Found a surrogate char.
        if (temp1 <= 0x3ff) {
            // Found a high surrogate.
            if (index < s.GetLength() - 1) {
                int temp2 = s[index + 1] - CharUnicodeInfo::LOW_SURROGATE_START;
                if (temp2 >= 0 && temp2 <= 0x3ff) {
                    // Found a low surrogate.
                    return ((temp1 * 0x400) + temp2 + UNICODE_PLANE01_START);
                } else {
                    throw std::invalid_argument("InvalidHighSurrogate");
                }
            } else {
                // Found a high surrogate at the end of the string.
                throw std::invalid_argument("InvalidHighSurrogate");
            }
        } else {
            // Find a low surrogate at the character pointed by index.
            throw std::invalid_argument("InvalidLowSurrogate");
        }
    }
    // Not a high-surrogate or low-surrogate. Genereate the UTF32 value for the BMP characters.
    return s[index];
}

Int32 Char::GetHashCode() const noexcept {
    return (int) Value | ((int) Value << 16);
}

Boolean Char::IsHighSurrogate(String &s, int index) {
    if (index < 0 || index >= s.GetLength()) throw std::out_of_range("index");

    return Char::IsHighSurrogate(s[index]);
}

Boolean Char::IsLowSurrogate(String &s, int index) {
    if (index < 0 || index >= s.GetLength()) throw std::out_of_range("index");

    return Char::IsLowSurrogate(s[index]);
}

Boolean Char::IsSurrogatePair(String &s, int index) {
    if (index < 0 || index >= s.GetLength()) throw std::out_of_range("index");
    if (index + 1 < s.GetLength()) return Char::IsSurrogatePair(s[index], s[index + 1]);

    return false;
}

Boolean Char::IsLower(Char c) {
    if (IsLatin1(c)) {
        if (IsASCII(c)) return (c >= 'a' && c <= 'z');
        return (GetLatin1UnicodeCategory(c) == UnicodeCategory::LowercaseLetter);
    }
    return (CharUnicodeInfo::GetUnicodeCategory(c) == UnicodeCategory::LowercaseLetter);
}

Boolean Char::IsPunctuation(Char c) {
    if (IsLatin1(c)) return (CheckPunctuation(GetLatin1UnicodeCategory(c)));
    return (CheckPunctuation(CharUnicodeInfo::GetUnicodeCategory(c)));
}

Boolean Char::IsUpper(Char c) noexcept {
    if (IsLatin1(c)) {
        if (IsASCII(c)) return (c >= 'A' && c <= 'Z');
        return GetLatin1UnicodeCategory(c) == UnicodeCategory::UppercaseLetter;
    }
    return CharUnicodeInfo::GetUnicodeCategory(c) == UnicodeCategory::UppercaseLetter;
}

Boolean Char::IsWhiteSpace(Char c) noexcept {
    if (IsLatin1(c)) return IsWhiteSpaceLatin1(c);
    return CharUnicodeInfo::IsWhiteSpace(c);
}

Char Char::Parse(String &s) {
    if (s.GetLength() != 1) throw std::invalid_argument("Need single character to parse String to Char");

    return s[0];
}

String Char::ToString() const noexcept {
    return Char::ToString(Value);
}

String Char::ToString(Char c) noexcept {
    return String(c, 1);
}

Boolean Char::TryParse(String &s, Char &result) noexcept {
    result = '\0';

    if (s.GetLength() != 1) return false;

    result = s[0];
    return true;
}
