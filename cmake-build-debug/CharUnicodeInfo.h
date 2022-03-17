//
// Created by bcfrutuozo on 13/03/2022.
//

#ifndef LNXCPPLEARNING_CHARUNICODEINFO_H
#define LNXCPPLEARNING_CHARUNICODEINFO_H

#include "UnicodeCategory.h"

class CharUnicodeInfo
{
private:

    class UnicodeDataHeader
    {
    public:

        char TableName;
        unsigned short Version;
        unsigned int OffsetToCategoriesIndex;
        unsigned int OffsetToCategoriesValue;
        unsigned int OffsetToNumericIndex;
        unsigned int OffsetToDigitValue;
        unsigned int OffsetToNumericValue;
    };

    class DigitValues
    {
    public:

        short DecimalDigit;
        short Digit;
    };

public:

    static constexpr char HIGH_SURROGATE_START = 0xD800;
    static constexpr char HIGH_SURROGATE_END = 0xDBFF;
    static constexpr char LOW_SURROGATE_START = 0xDC00;
    static constexpr char LOW_SURROGATE_END = 0xDFFF;

    static constexpr int UNICODE_CATEGORY_OFFSET = 0;
    static constexpr int BIDI_CATEGORY_OFFSET = 1;
};

#endif //LNXCPPLEARNING_CHARUNICODEINFO_H
