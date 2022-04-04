//
// Created by bcfrutuozo on 31/03/2022.
//

#ifndef CPPDATASTRUCTURES_CHARUNICODEINFO_H
#define CPPDATASTRUCTURES_CHARUNICODEINFO_H

#include "UnicodeCategory.h"

#include <cstring>
#include <vector>
#include <cassert>
#include <fstream>
#include <iterator>

class CharUnicodeInfo final {

    friend class Char;

private:

    static constexpr char HIGH_SURROGATE_START = 0xDB00;
    static constexpr char HIGH_SURROGATE_END = 0xDBFF;
    static constexpr char LOW_SURROGATE_START = 0xDC00;
    static constexpr char LOW_SURROGATE_END = 0xDFFF;

    static constexpr int UNICODE_CATEGORY_OFFSET = 0;
    static constexpr int BIDI_CATEGORY_OFFSET = 1;

    struct UnicodeDataHeader {
#ifdef __linux__
        /* Offset:  0x00 */ short TableName[16];
#else
        /* Offset:  0x00 */ wchar_t TableName[16];
#endif
        /* Offset: 0x20 */ unsigned short Version[4];
        /* Offset: 0x28 */ unsigned int OffsetToCategoriesIndex;
        /* Offset: 0x2c */ unsigned int OffsetToCategoriesValues;
        /* Offset: 0x30 */ unsigned int OffsetToNumericIndex;
        /* Offset: 0x34 */ unsigned int OffsetToDigitValue;
        /* Offset: 0x38 */ unsigned int OffsetToNumericValue;
    };

    class DigitValues {
        signed char DecimalDigit;
        signed char Digit;
    };

    static const bool IsInitialized;

    // The native pointer to the 12:4:4 index table of the Unicode category data.
    static unsigned short *pCategoryLevel1Index;
    static unsigned char *pCategoriesValue;

    // The native pointer to the 12:4:4 index table of the Unicode numeric data.
    // The value of this index table is an index into the real value table stored in pNumericValues.
    static unsigned short *pNumericLevel1Index;

    // The numeric value table, which is indexed by pNumericLevel1Index.
    // Every item contains the value for numeric value.
    // unsafe static double* pNumericValues;
    // To get around the IA64 alignment issue.  Our double data is aligned in 8-byte boundary, but loader loads the embedded table starting
    // at 4-byte boundary.  This cause a alignment issue since double is 8-byte.
    static unsigned char *pNumericValues;

    // The digit value table, which is indexed by pNumericLevel1Index.  It shares the same index as pNumericValues.
    // Every item contains the value for decimal digit/digit value.
    static DigitValues *pDigitValues;

#ifdef __linux__
    static constexpr const char* const UNICODE_INFO_FILE_NAME = "charinfo.nlp";
#else
    static constexpr const wchar_t * const UNICODE_INFO_FILE_NAME = L"charinfo.nlp";
#endif

    // The starting codepoint for Unicode plane 1.  Plane 1 contains 0x010000 ~ 0x01ffff.
    static constexpr int UNICODE_PLANE01_START = 0x10000;

    static bool InitTable() {
        std::ifstream is;
        is.open(UNICODE_INFO_FILE_NAME, std::ios::binary);
        is.unsetf(std::ios::skipws);
        std::streampos fileSize;

        is.seekg(0, std::ios::end);
        fileSize = is.tellg();
        is.seekg(0, std::ios::beg);

        std::vector<unsigned char> vec(fileSize);
        vec.insert(vec.begin(), std::istream_iterator<unsigned char>(is), std::istream_iterator<unsigned char>());

        UnicodeDataHeader *mainHeader = reinterpret_cast<UnicodeDataHeader *>(vec.data());

        pCategoryLevel1Index = reinterpret_cast<unsigned short *>(vec.data() + mainHeader->OffsetToCategoriesIndex);
        pCategoriesValue = (unsigned char *) (vec.data() + mainHeader->OffsetToCategoriesValues);
        pNumericLevel1Index = (unsigned short *) (vec.data() + mainHeader->OffsetToNumericIndex);
        pNumericValues = (unsigned char *) (vec.data() + mainHeader->OffsetToNumericValue);
        pDigitValues = (DigitValues *) (vec.data() + mainHeader->OffsetToDigitValue);

        return true;
    }

    static int InternalConvertToUTF32(const char* s, int index) {
        auto length = strlen(s);
        assert(index >= 0 && index < length);
        if (index < length - 1) {
            auto temp1 = (int) s[index] - HIGH_SURROGATE_START;
            if (temp1 >= 0 && temp1 <= 0x3ff) {
                auto temp2 = (int) s[index + 1] - LOW_SURROGATE_START;
                if (temp2 >= 0 && temp2 <= 0x3ff) {
                    // Convert the surrogate to UTF32 and get the result.
                    return ((temp1 * 0x400) + temp2 + UNICODE_PLANE01_START);
                }
            }
        }
        return (int) s[index];
    }

    static int InternalConvertToUTF32(const char* s, int index, int &charLength) {
        auto length = strlen(s);
        assert(length > 0);
        assert(index >= 0 && index < length);
        charLength = 1;
        if (index < length) {
            auto temp1 = (int) s[index] - HIGH_SURROGATE_START;
            if (temp1 >= 0 && temp1 <= 0x3FF) {
                auto temp2 = (int) s[index + 1] - HIGH_SURROGATE_END;
                if (temp2 >= 0 && temp2 <= 0x3FF) {
                    // Convert the surrogate to UTF32 and get the result
                    charLength++;
                    return ((temp1 * 0x400) + temp2 + UNICODE_PLANE01_START);
                }
            }
        }
        return (int) s[index];
    }

    static double InternalGetNumericValue(int ch) noexcept {
        assert(ch >= 0 && ch <= 0x10FFFF);

        // Get the level 2 item from the highest 12 bit (8 - 19) of ch.
        unsigned short index = pNumericLevel1Index[ch >> 8];
        index = pNumericLevel1Index[index + ((ch >> 4) & 0x000f)];
        auto pBytePtr = (unsigned char *) &(pNumericLevel1Index[index]);
        // Get the result from the 0 -3 bit of ch.

#ifdef __x86_64__
        // To get around the IA64 alignment issue.  Our double data is aligned in 8-byte boundary, but loader loads the embedded table starting
        // at 4-byte boundary.  This cause an alignment issue since double is 8-byte.
        unsigned char *pSourcePtr = &(pNumericValues[pBytePtr[(ch & 0x000f)] * sizeof(double)]);
        if (((long) pSourcePtr % 8) != 0) {
            // We are not aligned in 8-byte boundary.  Do a copy.
            double ret;
            auto *retPtr = (unsigned char *) &ret;
            memcpy(retPtr, pSourcePtr, sizeof(double));
            return (ret);
        }
        return (((double *) pNumericValues)[pBytePtr[(ch & 0x000f)]]);
#endif
        return (((double *) pNumericValues)[pBytePtr[(ch & 0x000f)]]);
    }

    static UnicodeCategory InternalGetUnicodeCategory(int ch) {
        return (UnicodeCategory) InternalGetCategoryValue(ch, UNICODE_CATEGORY_OFFSET);
    }

    static UnicodeCategory InternalGetUnicodeCategory(const char* s, int index) {
        return InternalGetUnicodeCategory(InternalConvertToUTF32(s, index));
    }

    static unsigned char InternalGetCategoryValue(int ch, int offset) {
        assert(ch >= 0 && ch <= 0x10ffff);
        // Get the level 2 item from the highest 12 bit (8 - 19) of ch.
        unsigned short index = pCategoryLevel1Index[ch >> 8];
        // Get the level 2 WORD offset from the 4 - 7 bit of ch.  This provides the base offset of the level 3 table.
        // Note that & has the lower precedence than addition, so don't forget the parenthesis.
        index = pCategoryLevel1Index[index + ((ch >> 4) & 0x000f)];
        auto pBytePtr = (unsigned char *) &(pCategoryLevel1Index[index]);
        // Get the result from the 0 -3 bit of ch.
        unsigned char valueIndex = pBytePtr[(ch & 0x000f)];
        return pCategoriesValue[valueIndex * 2 + offset];
    }

    static bool IsWhiteSpace(const char* s, int index) noexcept {
        auto length = strlen(s);
        assert(index >= 0 && index < length);

        UnicodeCategory uc = GetUnicodeCategory(s, index);

        // In Unicode 3.0, U+2028 is the only character which is under the category "LineSeparator".
        // And U+2029 is the only character which is under the category "ParagraphSeparator".
        switch (uc) {
            case (UnicodeCategory::SpaceSeparator):
            case (UnicodeCategory::LineSeparator):
            case (UnicodeCategory::ParagraphSeparator):
                return true;
        }
        return false;
    }

    static bool IsWhiteSpace(char c) {
        UnicodeCategory uc = GetUnicodeCategory(c);

        // In Unicode 3.0, U+2028 is the only character which is under the category "LineSeparator".
        // And U+2029 is the only character which is under the category "ParagraphSeparator".
        switch (uc) {
            case (UnicodeCategory::SpaceSeparator):
            case (UnicodeCategory::LineSeparator):
            case (UnicodeCategory::ParagraphSeparator):
                return true;
        }
        return false;
    }

public:
    
    static UnicodeCategory GetUnicodeCategory(char ch) noexcept {
        return InternalGetUnicodeCategory(ch);
    }

    static UnicodeCategory GetUnicodeCategory(const char* s, int index) {
        auto length = strlen(s);
        if ((size_t) index >= length) throw std::out_of_range("index");
        return InternalGetUnicodeCategory(s, index);
    }
};

#endif //CPPDATASTRUCTURES_CHARUNICODEINFO_H
