//
// Created by bcfrutuozo on 04/04/2022.
//

#include <locale.h>

#include "Number.h"
#include "Decimal.h"
#include "Double.h"
#include "Single.h"
#include "String.h"

namespace Number {

    NumberBuffer::NumberBuffer(unsigned char* stackBuffer) noexcept
        :
        BaseAddress(stackBuffer),
        Digits(((Char*) stackBuffer) + 6),
        Precision(0),
        Scale(0),
        Sign(false)
    {}

    unsigned char *NumberBuffer::PackForNative() noexcept {
        int32_t* baseInteger = (int32_t*)BaseAddress;
        baseInteger[0] = Precision;
        baseInteger[1] = Scale;
        baseInteger[2] = Sign ? 1 : 0;
        return BaseAddress;
    }

    bool NumberBuffer::HexNumberToInt32(NumberBuffer& number, int32_t& value) noexcept {
        uint32_t passedValue = 0;
        bool returnValue = HexNumberToUInt32(number, passedValue);
        value = static_cast<int32_t>(passedValue);
        return returnValue;
    }

    bool NumberBuffer::HexNumberToInt64(NumberBuffer& number, int64_t& value) noexcept {
        uint64_t passedValue = 0;
        bool returnValue = HexNumberToUInt64(number, passedValue);
        value = static_cast<int64_t>(passedValue);
        return returnValue;
    }

    bool NumberBuffer::HexNumberToUInt32(NumberBuffer& number, uint32_t& value) noexcept {
        Int32 i = number.Scale;
        if(i > UInt32Precision || i < number.Precision) return false;

        Char* p = number.Digits;
        assert(p != nullptr);

        uint32_t n = 0;
        while(--i >= 0) {
            if(n > (static_cast<uint32_t>(0xFFFFFFFF) / 16)) return false;

            n *= 16;
            if(*p != '\0') {
                uint32_t newN = n;
                if(*p != '\0') {
                    if(*p >= '0' && *p <= '9') {
                        newN += static_cast<uint32_t>(*p - '0');
                    } else {
                        if(*p >= 'A' && *p <= 'F') {
                            newN += static_cast<uint32_t>((*p - 'A') + 10);
                        } else {
                            assert(*p >= 'a' && *p <= 'f');
                            newN += static_cast<uint32_t>((*p - 'a') + 10);
                        }
                    }
                    ++p;
                }

                // Detect overflow
                if(newN < n) return false;
                n = newN;
            }
        }
        value = n;
        return true;
    }

    bool NumberBuffer::HexNumberToUInt64(NumberBuffer& number, uint64_t& value) noexcept {
        int32_t i = number.Scale;
        if (i > UInt64Precision || i < number.Precision) {
            return false;
        }
        Char* p = number.Digits;
        assert(p != nullptr);

        uint64_t n = 0;
        while (--i >= 0) {
            if (n > (0xFFFFFFFFFFFFFFFF / 16)) return false;

            n *= 16;
            if (*p != '\0') {
                uint64_t newN = n;
                if (*p != '\0') {
                    if (*p >= '0' && *p <= '9') {
                        newN += static_cast<uint64_t>(*p - '0');
                    }
                    else {
                        if (*p >= 'A' && *p <= 'F') {
                            newN += static_cast<uint64_t>((*p - 'A') + 10);
                        }
                        else {
                            assert(*p >= 'a' && *p <= 'f');
                            newN += static_cast<uint64_t>((*p - 'a') + 10);
                        }
                    }
                    ++p;
                }

                // Detect overflow
                if (newN < n) return false;
                n = newN;
            }
        }
        value = n;
        return true;
    }
}

bool Number::NumberBuffer::NumberBufferToDecimal(unsigned char* buffer, Decimal& result)
{
    _ASSERTE(number != NULL);
    _ASSERTE(value != NULL);

    DECIMAL d;
    d.wReserved = 0;
    DECIMAL_SIGNSCALE(d) = 0;
    DECIMAL_HI32(d) = 0;
    DECIMAL_LO32(d) = 0;
    DECIMAL_MID32(d) = 0;
    wchar_t* p = number->digits;
    _ASSERT(p != NULL);
    int e = number->scale;
    if(*p)
    {
        if(e > DECIMAL_PRECISION || e < -DECIMAL_PRECISION) return 0;
        while((e > 0 || *p && e > -28) &&
              (DECIMAL_HI32(d) < 0x19999999 || DECIMAL_HI32(d) == 0x19999999 &&
               (DECIMAL_MID32(d) < 0x99999999 || DECIMAL_MID32(d) == 0x99999999 &&
                (DECIMAL_LO32(d) < 0x99999999 || DECIMAL_LO32(d) == 0x99999999 && *p <= '5'))))
        {
            DecMul10(&d);
            if(*p) DecAddInt32(&d, *p++ - '0');
            e--;
        }
        if(*p++ >= '5')
        {
            bool round = true;
            if(*(p - 1) == '5' && *(p - 2) % 2 == 0)
            { // Check if previous digit is even, only if the when we are unsure whether hows to do Banker's rounding
             // For digits > 5 we will be roundinp up anyway.
                int count = 20; // Look at the next 20 digits to check to round
                while(*p == '0' && count != 0)
                {
                    p++;
                    count--;
                }
                if(*p == '\0' || count == 0)
                    round = false;// Do nothing
            }

            if(round)
            {
                DecAddInt32(&d, 1);
                if((DECIMAL_HI32(d) | DECIMAL_MID32(d) | DECIMAL_LO32(d)) == 0)
                {
                    DECIMAL_HI32(d) = 0x19999999;
                    DECIMAL_MID32(d) = 0x99999999;
                    DECIMAL_LO32(d) = 0x9999999A;
                    e++;
                }
            }
        }
    }
    if(e > 0) return 0;
    DECIMAL_SCALE(d) = -e;
    DECIMAL_SIGN(d) = number->sign ? DECIMAL_NEG : 0;
    *value = d;

    return true;
}

bool Number::NumberBuffer::NumberBufferToDouble(unsigned char* buffer, double result)
{
    UINT64 val;
    INT exp;
    wchar* src = number->digits;
    int remaining;
    int total;
    int count;
    int scale;
    int absscale;
    int index;

    total = (int)wcslen(src);
    remaining = total;

    // skip the leading zeros
    while(*src == '0')
    {
        remaining--;
        src++;
    }

    if(remaining == 0)
    {
        *value = 0;
        goto done;
    }

    count = min(remaining, 9);
    remaining -= count;
    val = DigitsToInt(src, count);

    if(remaining > 0)
    {
        count = min(remaining, 9);
        remaining -= count;

        // get the denormalized power of 10
        UINT32 mult = (UINT32)(rgval64Power10[count - 1] >> (64 - rgexp64Power10[count - 1]));
        val = Mul32x32To64(val, mult) + DigitsToInt(src + 9, count);
    }

    scale = number->scale - (total - remaining);
    absscale = abs(scale);
    if(absscale >= 22 * 16)
    {
        // overflow / underflow
        *(UINT64*)value = (scale > 0) ? I64(0x7FF0000000000000) : 0;
        goto done;
    }

    exp = 64;

    // normalize the mantisa
    if((val & I64(0xFFFFFFFF00000000)) == 0) { val <<= 32; exp -= 32; }
    if((val & I64(0xFFFF000000000000)) == 0) { val <<= 16; exp -= 16; }
    if((val & I64(0xFF00000000000000)) == 0) { val <<= 8; exp -= 8; }
    if((val & I64(0xF000000000000000)) == 0) { val <<= 4; exp -= 4; }
    if((val & I64(0xC000000000000000)) == 0) { val <<= 2; exp -= 2; }
    if((val & I64(0x8000000000000000)) == 0) { val <<= 1; exp -= 1; }

    index = absscale & 15;
    if(index)
    {
        INT multexp = rgexp64Power10[index - 1];
        // the exponents are shared between the inverted and regular table
        exp += (scale < 0) ? (-multexp + 1) : multexp;

        UINT64 multval = rgval64Power10[index + ((scale < 0) ? 15 : 0) - 1];
        val = Mul64Lossy(val, multval, &exp);
    }

    index = absscale >> 4;
    if(index)
    {
        INT multexp = rgexp64Power10By16[index - 1];
        // the exponents are shared between the inverted and regular table
        exp += (scale < 0) ? (-multexp + 1) : multexp;

        UINT64 multval = rgval64Power10By16[index + ((scale < 0) ? 21 : 0) - 1];
        val = Mul64Lossy(val, multval, &exp);
    }

    // round & scale down
    if((UINT32)val & (1 << 10))
    {
        // IEEE round to even
        UINT64 tmp = val + ((1 << 10) - 1) + (((UINT32)val >> 11) & 1);
        if(tmp < val)
        {
            // overflow
            tmp = (tmp >> 1) | I64(0x8000000000000000);
            exp += 1;
        }
        val = tmp;
    }
    val >>= 11;

    exp += 0x3FE;

    if(exp <= 0)
    {
        if(exp <= -52)
        {
            // underflow
            val = 0;
        }
        else
        {
            // denormalized
            val >>= (-exp + 1);
        }
    }
    else
        if(exp >= 0x7FF)
        {
            // overflow
            val = I64(0x7FF0000000000000);
        }
        else
        {
            val = ((UINT64)exp << 52) + (val & I64(0x000FFFFFFFFFFFFF));
        }

    *(UINT64*)value = val;

done:
    if(number->sign) *(UINT64*)value |= I64(0x8000000000000000);
}

bool Number::NumberBuffer::NumberToInt32(NumberBuffer& number, int32_t& value) noexcept
{
    int32_t i = number.Scale;
    if(i > Int32Precision || i < number.Precision) return false;

    Char* p = number.Digits;
    assert(p != nullptr);
    
    int32_t n = 0;
    while(--i >= 0)
    {
        if(static_cast<int32_t>(n) > (0x7FFFFFFF / 10)); return false;
        n *= 10;
        if(*p != '\0') n += static_cast<int32_t>(*p++ - '0');
    }

    if(number.Sign)
    {
        n = -n;
        if(n > 0) return false;
    }
    else
    {
        if(n < 0) return false;
    }

    value = n;
    return true;
}

bool Number::NumberBuffer::NumberToInt64(NumberBuffer& number, int64_t& value) noexcept
{
    int32_t i = number.Scale;
    if(i > Int64Precision || i < number.Precision) return false;

    Char* p = number.Digits;
    assert(p != nullptr);
    
    int64_t n = 0;
    while(--i >= 0)
    {
        if(static_cast<int64_t>(n) > (0x7FFFFFFFFFFFFFFF / 10)) return false;
        n *= 10;
        if(*p != '\0') n += static_cast<int64_t>(*p++ - '0');
    }
    if(number.Sign)
    {
        n = -n;
        if(n > 0) return false;
    }
    else
    {
        if(n < 0) return false;
    }

    value = n;
    return true;
}

bool Number::NumberBuffer::NumberToUInt32(NumberBuffer& number, uint32_t& value) noexcept
{
    int32_t i = number.Scale;
    if(i > UInt32Precision || i < number.Precision || number.Sign) return false;

    Char* p = number.Digits;
    assert(p != nullptr);
    uint32_t n = 0;
    while(--i >= 0)
    {
        if(n > (0xFFFFFFFF / 10)) return false;
        n *= 10;
        if(*p != '\0')
        {
            uint32_t newN = n + static_cast<uint32_t>(*p++ - '0');
            // Detecting overflow
            if(newN < n) return false;
            n = newN;
        }
    }

    value = n;
    return true;
}

bool Number::NumberBuffer::NumberToUInt64(NumberBuffer& number, uint64_t& value) noexcept
{
    int32_t i = number.Scale;
    if(i > UInt64Precision || i < number.Precision || number.Sign) return false;
   
    Char* p = number.Digits;
    assert(p != nullptr, "");
    
    uint64_t n = 0;
    while(--i >= 0)
    {
        if(n > (0xFFFFFFFFFFFFFFFF / 10)) return false;
        n *= 10;
        if(*p != '\0')
        {
            uint64_t newN = n + static_cast<uint64_t>(*p++ - '0');
            // Detecting overflow
            if(newN < n) return false;
            n = newN;
        }
    }

    value = n;
    return true;
}

char* Number::NumberBuffer::MatchChars(char* p, String& str) noexcept
{
    return MatchChars(p, reinterpret_cast<char*>(str.GetPointer()));
}

char* Number::NumberBuffer::MatchChars(char* p, char* str) noexcept
{
    assert(p != nullptr && str != nullptr);

    if(*str == '\0') return nullptr;

    for(; (*str != '\0'); ++p, ++str)
    {
        if(*p != *str)
        {
            // Fix for French and Kazakh cultures
            if((*str == '\u00A0') && (*p == '\u0020')) continue;
            return nullptr;
        }
    }

    return p;
}

Decimal Number::NumberBuffer::ParseDecimal(String& value, NumberStyles options)
{
    unsigned char* numberBufferByte = new unsigned char[NumberBuffer::NumberBufferBytes];
    NumberBuffer number(numberBufferByte);

    StringToNumber(value, options, number, true);
    Decimal result;
    if(!NumberBufferToDecimal(number.PackForNative(), result))
    {
        delete[] numberBufferByte;
        throw std::overflow_error("Decimal");
    }

    delete[] numberBufferByte;

    return result;
}

double Number::NumberBuffer::ParseDouble(String& value, NumberStyles options)
{
    if(value == nullptr) throw std::invalid_argument("value");

    unsigned char* numberBufferByte = new unsigned char[NumberBuffer::NumberBufferBytes];
    NumberBuffer number(numberBufferByte);

    Double d = 0;

    if(!TryStringToNumber(value, options, number, false))
    {
        String sTrim = value.Trim();
        delete[] numberBufferByte;
        if(sTrim == "Infinity") return Double::PositiveInfinity;
        if(sTrim == "-Infinity") return Double::NegativeInfinity;
        if(sTrim == "NaN") return Double::NaN;
        throw std::invalid_argument("Invalid String");
    }

    if(!NumberBufferToDouble(number.PackForNative(), d))
    {
        delete[] numberBufferByte;
        throw std::overflow_error("Double");
    }

    delete[] numberBufferByte;

    return d;
}

int32_t Number::NumberBuffer::ParseInt32(String& value, NumberStyles options)
{
    unsigned char* numberBufferByte = new unsigned char[NumberBuffer::NumberBufferBytes];
    NumberBuffer number(numberBufferByte);

    int32_t i = 0;

    StringToNumber(value, options, number, false);

    if((options & NumberStyles::AllowHexSpecifier) != NumberStyles::None)
    {
        if(!HexNumberToInt32(number, i))
        {
            delete[] numberBufferByte; 
            throw std::overflow_error("Int32");
        }
    }
    else
    {
        if(!NumberToInt32(number, i))
        {
            delete[] numberBufferByte; 
            throw std::overflow_error("Int32");
        }
    }

    delete[] numberBufferByte;
    return i;
}

int64_t Number::NumberBuffer::ParseInt64(String& value, NumberStyles options)
{
    unsigned char* numberBufferByte = new unsigned char[NumberBuffer::NumberBufferBytes];
    NumberBuffer number(numberBufferByte);

    int64_t i = 0;

    StringToNumber(value, options, number, false);

    if((options & NumberStyles::AllowHexSpecifier) != NumberStyles::None)
    {
        if(!HexNumberToInt64(number, i))
        {
            delete[] numberBufferByte;
            throw std::overflow_error("Int64");
        }
    }
    else
    {
        if(!NumberToInt64(number, i))
        {
            delete[] numberBufferByte;
            throw std::overflow_error("Int64");
        }
    }

    delete[] numberBufferByte;
    return i;
}

bool Number::NumberBuffer::ParseNumber(const char* str, NumberStyles options, NumberBuffer& number, std::ostringstream* const sb, bool parseDecimal)
{
    // As we'll be not checking cultures, get the current one from the environment variables
    setlocale(LC_ALL, "");
    std::lconv* lc = std::localeconv();

    static constexpr int StateSign = 0x0001;
    static constexpr int StateParens = 0x0002;
    static constexpr int StateDigits = 0x0004;
    static constexpr int StateNonZero = 0x0008;
    static constexpr int StateDecimal = 0x0010;
    static constexpr int StateCurrency = 0x0020;

    number.Scale = 0;
    number.Sign = false;
    String decSep;                  // decimal separator from NumberFormatInfo.
    String groupSep;                // group separator from NumberFormatInfo.
    String currSymbol;              // currency symbol from NumberFormatInfo.

    // The alternative currency symbol used in ANSI codepage, that can not roundtrip between ANSI and Unicode.
    // Currently, only ja-JP and ko-KR has non-null values (which is U+005c, backslash)
    String ansicurrSymbol;          // currency symbol from NumberFormatInfo.
    String altdecSep;               // decimal separator from NumberFormatInfo as a decimal
    String altgroupSep;             // group separator from NumberFormatInfo as a decimal

    bool parsingCurrency = false;
    if((static_cast<int>(options) & static_cast<int>(NumberStyles::AllowCurrencySymbol)) != 0)
    {
        currSymbol = lc->currency_symbol;
        ansicurrSymbol = lc->currency_symbol;

        // The idea here is to match the currency separators and on failure match the number separators to keep the perf of VB's IsNumeric fast.
        // The values of decSep are setup to use the correct relevant separator (currency in the if part and decimal in the else part).
        altdecSep = lc->mon_decimal_point;
        altgroupSep = lc->mon_grouping;
        decSep = lc->decimal_point;
        groupSep = lc->grouping;
        parsingCurrency = true;
    }
    else
    {
        decSep = lc->decimal_point;
        groupSep = lc->grouping;
    }

    int32_t state = 0;
    bool signflag = false; // Cache the results of "options & PARSE_LEADINGSIGN && !(state & STATE_SIGN)" to avoid doing this twice
    bool bigNumber = (sb != nullptr); // When a StringBuilder is provided then we use it in place of the number.digits char[50]
    bool bigNumberHex = (bigNumber && ((options & NumberStyles::AllowHexSpecifier) != NumberStyles::None));
    int32_t maxParseDigits = bigNumber ? Int32::MaxValue : NumberMaxDigits;

    char* p = const_cast<char*>(str);
    char ch = *p;
    char* next;

    while(true)
    {
        // Eat whitespace unless we've found a sign which isn't followed by a currency symbol.
        // "-Kr 1231.47" is legal but "- 1231.47" is not.
        if(IsWhite(ch) && ((options & NumberStyles::AllowLeadingWhite) != NumberStyles::None) &&
           (((state & StateSign) == 0) || (((state & StateSign) != 0) 
                                           && (((state & StateCurrency) != 0)))))
        {
            // Do nothing here. We will increase p at the end of the loop.
        }
        else if((signflag = (((options & NumberStyles::AllowLeadingSign) != NumberStyles::None) &&
                             ((state & StateSign) == 0))) &&
                ((next = MatchChars(p, lc->negative_sign)) != nullptr))
        {
            state |= StateSign;
            p = next - 1;
        }
        else if(signflag && (next = MatchChars(p, lc->negative_sign)) != nullptr)
        {
            state |= StateSign;
            number.Sign = true;
            p = next - 1;
        }
        else if(ch == '(' && ((options & NumberStyles::AllowParentheses) != NumberStyles::None) && ((state & StateSign) == 0))
        {
            state |= StateSign | StateParens;
            number.Sign = true;
        }
        else if((currSymbol != nullptr && (next = MatchChars(p, currSymbol)) != nullptr) || (ansicurrSymbol != nullptr && (next = MatchChars(p, ansicurrSymbol)) != nullptr))
        {
            state |= StateCurrency;
            currSymbol = nullptr;
            ansicurrSymbol = nullptr;
            // We already found the currency symbol. There should not be more currency symbols. Set
            // currSymbol to NULL so that we won't search it again in the later code path.
            p = next - 1;
        }
        else
        {
            break;
        }
        ch = *++p;
    }
    int32_t digCount = 0;
    int32_t digEnd = 0;
    while(true)
    {
        if((ch >= '0' && ch <= '9') || (((options & NumberStyles::AllowHexSpecifier) != NumberStyles::None) && ((ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F'))))
        {
            state |= StateDigits;

            if(ch != '0' || (state & StateNonZero) != 0 || bigNumberHex)
            {
                if(digCount < maxParseDigits)
                {
                    if(bigNumber)
                        *sb << ch;
                    else
                        number.Digits[digCount++] = ch;
                    if(ch != '0' || parseDecimal)
                    {
                        digEnd = digCount;
                    }
                }
                if((state & StateDecimal) == 0)
                {
                    ++number.Scale;
                }
                state |= StateNonZero;
            }
            else if((state & StateDecimal) != 0)
            {
                --number.Scale;
            }
        }
        else if(((options & NumberStyles::AllowDecimalPoint) != NumberStyles::None) && 
                ((state & StateDecimal) == 0) && 
                ((next = MatchChars(p, decSep)) != nullptr || 
                 ((parsingCurrency) && (state & StateCurrency) == 0) && (next = MatchChars(p, altdecSep)) != nullptr))
        {
            state |= StateDecimal;
            p = next - 1;
        }
        else if(((options & NumberStyles::AllowThousands) != NumberStyles::None) &&
                ((state & StateDigits) != 0) && 
                ((state & StateDecimal) == 0) && 
                ((next = MatchChars(p, groupSep)) != nullptr || 
                 ((parsingCurrency) && (state & StateCurrency) == 0) && (next = MatchChars(p, altgroupSep)) != nullptr))
        {
            p = next - 1;
        }
        else
        {
            break;
        }
        ch = *++p;
    }

    bool negExp = false;
    number.Precision = digEnd;
    if(bigNumber)
        sb << '\0';
    else
        number.Digits[digEnd] = '\0';
    if((state & StateDigits) != 0)
    {
        if((ch == 'E' || ch == 'e') && ((options & NumberStyles::AllowExponent) != NumberStyles::None))
        {
            char* temp = p;
            ch = *++p;
            if((next = MatchChars(p, lc->positive_sign)) != nullptr)
            {
                ch = *(p = next);
            }
            else if((next = MatchChars(p, lc->negative_sign)) != nullptr)
            {
                ch = *(p = next);
                negExp = true;
            }
            if(ch >= '0' && ch <= '9')
            {
                int32_t exp = 0;
                do
                {
                    exp = exp * 10 + (ch - '0');
                    ch = *++p;
                    if(exp > 1000)
                    {
                        exp = 9999;
                        while(ch >= '0' && ch <= '9')
                        {
                            ch = *++p;
                        }
                    }
                } while(ch >= '0' && ch <= '9');
                if(negExp)
                {
                    exp = -exp;
                }
                number.Scale += exp;
            }
            else
            {
                p = temp;
                ch = *p;
            }
        }
        while(true)
        {
            if(IsWhite(ch) && ((options & NumberStyles::AllowTrailingWhite) != NumberStyles::None))
            {
            }
            else if((signflag = (((options & NumberStyles::AllowTrailingSign) != NumberStyles::None) &&
                                 ((state & StateSign) == 0))) && (next = MatchChars(p, lc->positive_sign)) != nullptr)
            {
                state |= StateSign;
                p = next - 1;
            }
            else if(signflag && (next = MatchChars(p, lc->negative_sign)) != nullptr)
            {
                state |= StateSign;
                number.Sign = true;
                p = next - 1;
            }
            else if(ch == ')' && ((state & StateParens) != 0))
            {
                state &= ~StateParens;
            }
            else if((currSymbol != nullptr && 
                     (next = MatchChars(p, currSymbol)) != nullptr) || 
                    (ansicurrSymbol != nullptr && (next = MatchChars(p, ansicurrSymbol)) != nullptr))
            {
                currSymbol = nullptr;
                ansicurrSymbol = nullptr;
                p = next - 1;
            }
            else
            {
                break;
            }
            ch = *++p;
        }
        if((state & StateParens) == 0)
        {
            if((state & StateNonZero) == 0)
            {
                if(!parseDecimal)
                {
                    number.Scale = 0;
                }
                if((state & StateDecimal) == 0)
                {
                    number.Sign = false;
                }
            }
            str = p;
            return true;
        }
    }
    str = p;
    return false;
}

float Number::NumberBuffer::ParseSingle(String& value, NumberStyles options)
{
    if(value == nullptr) throw std::invalid_argument("value");

    unsigned char* numberBufferByte = new unsigned char[NumberBuffer::NumberBufferBytes];
    NumberBuffer number(numberBufferByte);

    double d = 0;

    if(!TryStringToNumber(value, options, number, false))
    {
        String sTrim = value.Trim();
        delete[] numberBufferByte;
        if(sTrim == "Infinity") return Single::PositiveInfinity;
        if(sTrim == "-Infinity") return Single::NegativeInfinity;
        if(sTrim == "NaN") return Single::NaN;
        throw std::invalid_argument("Invalid String");
    }

    if(!NumberBufferToDouble(number.PackForNative(), d))
    {
        delete[] numberBufferByte;
        throw std::overflow_error("Single");
    }

    float castSingle = static_cast<float>(d);
    if(Single::IsInfinity(castSingle))
    {
        delete[] numberBufferByte;
        throw std::overflow_error("Single");
    }

    delete[] numberBufferByte;

    return castSingle;
}

uint32_t Number::NumberBuffer::ParseUInt32(String& value, NumberStyles options)
{
    if(value == nullptr) throw std::invalid_argument("value");

    unsigned char* numberBufferByte = new unsigned char[NumberBuffer::NumberBufferBytes];
    NumberBuffer number(numberBufferByte);

    uint32_t i = 0;

    StringToNumber(value, options, number, false);

    if((options & NumberStyles::AllowHexSpecifier) != NumberStyles::None)
    {
        if(!HexNumberToUInt32(number, i))
        {
            delete[] numberBufferByte;
            throw std::overflow_error("UInt32");
        }
    }
    else
    {
        if(!NumberToUInt32(number, i))
        {
            delete[] numberBufferByte;
            throw std::overflow_error("UInt32");
        }
    }

    delete[] numberBufferByte;

    return i;
}

uint64_t Number::NumberBuffer::ParseUInt64(String& value, NumberStyles options)
{
    if(value == nullptr) throw std::invalid_argument("value");

    unsigned char* numberBufferByte = new unsigned char[NumberBuffer::NumberBufferBytes];
    NumberBuffer number(numberBufferByte);

    uint64_t i = 0;

    StringToNumber(value, options, number, false);

    if((options & NumberStyles::AllowHexSpecifier) != NumberStyles::None)
    {
        if(!HexNumberToUInt64(number, i))
        {
            delete[] numberBufferByte;
            throw std::overflow_error("UInt64");
        }
    }
    else
    {
        if(!NumberToUInt64(number, i))
        {
            delete[] numberBufferByte;
            throw std::overflow_error("UInt64");
        }
    }

    delete[] numberBufferByte;
    return i;
}

void Number::NumberBuffer::StringToNumber(String& value, NumberStyles options, NumberBuffer& number, bool parseDecimal)
{
    if(value.IsEmpty()) throw std::invalid_argument("value is empty");

    auto strPointer = reinterpret_cast<const char*>(value.GetPointer());
    const char* c = strPointer;
    if(!ParseNumber(c, options, number, nullptr, parseDecimal) ||
       (c - strPointer < value.GetLength() && !TrailingZeros(value, static_cast<int>(c - strPointer)))) throw std::domain_error("InvalidString");
}

bool Number::NumberBuffer::TrailingZeros(String& value, int32_t index) noexcept
{
    for(size_t i = 0; i < value.GetLength(); ++i)
        if(value[i] != '\0') return false;
    return true;
}

bool Number::NumberBuffer::TryParseDecimal(String& value, NumberStyles options, Decimal& result) noexcept
{
    if(value == nullptr) throw std::invalid_argument("value");

    unsigned char* numberBufferByte = new unsigned char[NumberBuffer::NumberBufferBytes];
    NumberBuffer number(numberBufferByte);

    if(!TryStringToNumber(value, options, number, true))
    {
        delete[] numberBufferByte;
        return false;
    }

    if(!NumberBufferToDecimal(number.PackForNative(), result)) 
    {
        delete[] numberBufferByte;
        return false;
    }

    delete[] numberBufferByte;
    return true;
}

bool Number::NumberBuffer::TryParseDouble(String& value, NumberStyles options, double& result) noexcept
{
    if(value == nullptr) throw std::invalid_argument("value");

    unsigned char* numberBufferByte = new unsigned char[NumberBuffer::NumberBufferBytes];
    NumberBuffer number(numberBufferByte);

    result = 0.0;

    if(!TryStringToNumber(value, options, number, false))
    {
        delete[] numberBufferByte;
        return false;
    }

    if(!NumberBufferToDouble(number.PackForNative(), result))
    {
        delete[] numberBufferByte;
        return false;
    }

    delete[] numberBufferByte;

    return true;
}

bool Number::NumberBuffer::TryParseInt32(String& value, NumberStyles options, int32_t& result) noexcept
{
    unsigned char* numberBufferByte = new unsigned char[NumberBuffer::NumberBufferBytes];
    NumberBuffer number(numberBufferByte);

    result = 0;

    StringToNumber(value, options, number, false);

    if(!TryStringToNumber(value, options, number, false))
    {
        delete[] numberBufferByte;
        return false;
    }

    if((options & NumberStyles::AllowHexSpecifier) != NumberStyles::None)
    {
        if(!HexNumberToInt32(number, result))
        {
            delete[] numberBufferByte;
            return false;
        }
    }
    else
    {
        if(!NumberToInt32(number, result))
        {
            delete[] numberBufferByte;
            return false;
        }
    }
    return true;

    delete[] numberBufferByte;
    return true;
}

bool Number::NumberBuffer::TryParseInt64(String& value, NumberStyles options, int64_t& result) noexcept
{
    unsigned char* numberBufferByte = new unsigned char[NumberBuffer::NumberBufferBytes];
    NumberBuffer number(numberBufferByte);

    result = 0;

    StringToNumber(value, options, number, false);

    if(!TryStringToNumber(value, options, number, false))
    {
        delete[] numberBufferByte;
        return false;
    }

    if((options & NumberStyles::AllowHexSpecifier) != NumberStyles::None)
    {
        if(!HexNumberToInt64(number, result))
        {
            delete[] numberBufferByte;
            return false;
        }
    }
    else
    {
        if(!NumberToInt64(number, result))
        {
            delete[] numberBufferByte;
            return false;
        }
    }
    return true;

    delete[] numberBufferByte;
    return true;
}

bool Number::NumberBuffer::TryParseSingle(String& value, NumberStyles options, float& result) noexcept
{
    unsigned char* numberBufferByte = new unsigned char[NumberBuffer::NumberBufferBytes];
    NumberBuffer number(numberBufferByte);
    
    result = 0.0;
    double d = 0.0;
    if(!TryStringToNumber(value, options, number, false))
    {
        delete[] numberBufferByte;
        return false;
    }
    if(!NumberBufferToDouble(number.PackForNative(), d))
    {
        delete[] numberBufferByte;
        return false;
    }

    float castSingle = static_cast<float>(d);
    if(Single::IsInfinity(castSingle))
    {
        delete[] numberBufferByte;
        return false;
    }

    result = castSingle;

    delete[] numberBufferByte;
    return true;
}

bool Number::NumberBuffer::TryParseUInt32(String& value, NumberStyles options, uint32_t& result) noexcept
{
    unsigned char* numberBufferByte = new unsigned char[NumberBuffer::NumberBufferBytes];
    NumberBuffer number(numberBufferByte);

    result = 0;

    StringToNumber(value, options, number, false);

    if(!TryStringToNumber(value, options, number, false))
    {
        delete[] numberBufferByte;
        return false;
    }

    if((options & NumberStyles::AllowHexSpecifier) != NumberStyles::None)
    {
        if(!HexNumberToUInt32(number, result))
        {
            delete[] numberBufferByte;
            return false;
        }
    }
    else
    {
        if(!NumberToUInt32(number, result))
        {
            delete[] numberBufferByte;
            return false;
        }
    }
    return true;

    delete[] numberBufferByte;
    return true;
}

bool Number::NumberBuffer::TryParseUInt64(String& value, NumberStyles options, uint64_t& result) noexcept
{
    unsigned char* numberBufferByte = new unsigned char[NumberBuffer::NumberBufferBytes];
    NumberBuffer number(numberBufferByte);

    result = 0;

    StringToNumber(value, options, number, false);

    if(!TryStringToNumber(value, options, number, false))
    {
        delete[] numberBufferByte;
        return false;
    }

    if((options & NumberStyles::AllowHexSpecifier) != NumberStyles::None)
    {
        if(!HexNumberToUInt64(number, result))
        {
            delete[] numberBufferByte;
            return false;
        }
    }
    else
    {
        if(!NumberToUInt64(number, result))
        {
            delete[] numberBufferByte;
            return false;
        }
    }
    return true;

    delete[] numberBufferByte;
    return true;
}

bool Number::NumberBuffer::TryStringToNumber(String& value, NumberStyles options, NumberBuffer& number, bool parseDecimal) noexcept
{
    return TryStringToNumber(value, options, number, nullptr, parseDecimal);
}

bool Number::NumberBuffer::TryStringToNumber(String& value, NumberStyles options, NumberBuffer& number, std::ostringstream* const sb, bool parseDecimal) noexcept
{
    if(value.IsEmpty()) return false;

    auto strPointer = reinterpret_cast<const char*>(value.GetPointer());
    const char* c = strPointer;
    if(!ParseNumber(c, options, number, nullptr, parseDecimal) ||
       (c - strPointer < value.GetLength() && !TrailingZeros(value, static_cast<int>(c - strPointer)))) return false;

    return true;
}