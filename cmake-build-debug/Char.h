//
// Created by bcfrutuozo on 13/03/2022.
//

#ifndef LNXCPPLEARNING_CHAR_H
#define LNXCPPLEARNING_CHAR_H

#include "CharUnicodeInfo.h"

class Char {

private:

    char m_Value;

    static constexpr bool IsLatin1(char ch) { return (ch <= '\x00ff');}
    static constexpr bool IsAscii(char ch) { return (ch <= '\x007f');}

public:

    int GetHashCode()
    {
        return (int)m_Value | ((int)m_Value << 16);
    }

    static constexpr bool IsDigit(char c)
    {
        if(IsLatin1(c))
            return (c >= '0' && c <= '9');

        //return CharUnicodeInfo::GetUnicodeCategory(c) == UnicodeCategory::DecimalDigitNumber;
    }

    static constexpr char MaxValue = 0xFFFF;
    static constexpr char MinValue = 0x00;
};


#endif //LNXCPPLEARNING_CHAR_H
