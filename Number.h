//
// Created by bcfrutuozo on 03/04/2022.
//

#ifndef CPPDATASTRUCTURES_NUMBER_H
#define CPPDATASTRUCTURES_NUMBER_H

/* The Number class implements methods for formatting and parsing
 * numeric values. To format and parse numeric values, applications should
 * use the Format and Parse methods provided by the numeric
 * classes (Byte, Int16, Int32, Int64,
 * Single, Double, Currency, and Decimal). Those
 * Format and Parse methods share a common implementation
 * provided by this class, and are thus documented in detail here.
 *
 * Formatting
 *
 * The Format methods provided by the numeric classes are all the
 * form
 *
 *  public static String Format(XXX value, String format);
 *  public static String Format(XXX value, String format, NumberFormatInfo info);
 *
 * where XXX is the name of the particular numeric class. The methods convert
 * the numeric value to a string using the format string given by the
 * format parameter. If the format parameter is null or
 * an empty string, the number is formatted as if the string "G" (general
 * format) was specified. The info parameter specifies the
 * NumberFormatInfo instance to use when formatting the number. If the
 * info parameter is null or omitted, the numeric formatting information
 * is obtained from the current culture. The NumberFormatInfo supplies
 * such information as the characters to use for decimal and a thousand
 * separators, and the spelling and placement of currency symbols in monetary
 * values.
 *
 * Format strings fall into two categories: Standard format strings and
 * user-defined format strings. A format string consisting of a single
 * alphabetic character (A-Z or a-z), optionally followed by a sequence of
 * digits (0-9), is a standard format string. All other format strings are
 * used-defined format strings.
 *
 * A standard format string takes the form Axx, where A is an
 * alphabetic character called the format specifier and xx is a
 * sequence of digits called the precision specifier. The format
 * specifier controls the type of formatting applied to the number and the
 * precision specifier controls the number of significant digits or decimal
 * places of the formatting operation. The following table describes the
 * supported standard formats.
 *
 * C c - Currency format. The number is
 * converted to a string that represents a currency amount. The conversion is
 * controlled by the currency format information of the NumberFormatInfo
 * used to format the number. The precision specifier indicates the desired
 * number of decimal places. If the precision specifier is omitted, the default
 * currency precision given by the NumberFormatInfo is used.
 *
 * D d - Decimal format. This format is
 * supported for integral types only. The number is converted to a string of
 * decimal digits, prefixed by a minus sign if the number is negative. The
 * precision specifier indicates the minimum number of digits desired in the
 * resulting string. If required, the number will be left-padded with zeros to
 * produce the number of digits given by the precision specifier.
 *
 * E e Engineering (scientific) format.
 * The number is converted to a string of the form
 * "-d.ddd...E+ddd" or "-d.ddd...e+ddd", where each
 * 'd' indicates a digit (0-9). The string starts with a minus sign if the
 * number is negative, and one digit always precedes the decimal point. The
 * precision specifier indicates the desired number of digits after the decimal
 * point. If the precision specifier is omitted, a default of 6 digits after
 * the decimal point is used. The format specifier indicates whether to prefix
 * the exponent with an 'E' or an 'e'. The exponent is always consists of a
 * plus or minus sign and three digits.
 *
 * F f Fixed point format. The number is
 * converted to a string of the form "-ddd.ddd....", where each
 * 'd' indicates a digit (0-9). The string starts with a minus sign if the
 * number is negative. The precision specifier indicates the desired number of
 * decimal places. If the precision specifier is omitted, the default numeric
 * precision given by the NumberFormatInfo is used.
 *
 * G g - General format. The number is
 * converted to the shortest possible decimal representation using fixed point
 * or scientific format. The precision specifier determines the number of
 * significant digits in the resulting string. If the precision specifier is
 * omitted, the number of significant digits is determined by the type of the
 * number being converted (10 for int, 19 for long, 7 for
 * float, 15 for double, 19 for Currency, and 29 for
 * Decimal). Trailing zeros after the decimal point are removed, and the
 * resulting string contains a decimal point only if required. The resulting
 * string uses fixed point format if the exponent of the number is less than
 * the number of significant digits and greater than or equal to -4. Otherwise,
 * the resulting string uses scientific format, and the case of the format
 * specifier controls whether the exponent is prefixed with an 'E' or an
 * 'e'.
 *
 * N n Number format. The number is
 * converted to a string of the form "-d,ddd,ddd.ddd....", where
 * each 'd' indicates a digit (0-9). The string starts with a minus sign if the
 * number is negative. A thousand separators are inserted between each group of
 * three digits to the left of the decimal point. The precision specifier
 * indicates the desired number of decimal places. If the precision specifier
 * is omitted, the default numeric precision given by the
 * NumberFormatInfo is used.
 *
 * X x - Hexadecimal format. This format is
 * supported for integral types only. The number is converted to a string of
 * hexadecimal digits. The format specifier indicates whether to use upper or
 * lower case characters for the hexadecimal digits above 9 ('X' for 'ABCDEF',
 * and 'x' for 'abcdef'). The precision specifier indicates the minimum number
 * of digits desired in the resulting string. If required, the number will be
 * left-padded with zeros to produce the number of digits given by the
 * precision specifier.
 *
 * Some examples of standard format strings and their results are shown in the
 * table below. (The examples all assume a default NumberFormatInfo.)
 *
 * Value        Format  Result
 * 12345.6789   C       $12,345.68
 * -12345.6789  C       ($12,345.68)
 * 12345        D       12345
 * 12345        D8      00012345
 * 12345.6789   E       1.234568E+004
 * 12345.6789   E10     1.2345678900E+004
 * 12345.6789   e4      1.2346e+004
 * 12345.6789   F       12345.68
 * 12345.6789   F0      12346
 * 12345.6789   F6      12345.678900
 * 12345.6789   G       12345.6789
 * 12345.6789   G7      12345.68
 * 123456789    G7      1.234568E8
 * 12345.6789   N       12,345.68
 * 123456789    N4      123,456,789.0000
 * 0x2c45e      x       2c45e
 * 0x2c45e      X       2C45E
 * 0x2c45e      X8      0002C45E
 *
 * Format strings that do not start with an alphabetic character, or that start
 * with an alphabetic character followed by a non-digit, are called
 * user-defined format strings. The following table describes the formatting
 * characters that are supported in user defined format strings.
 *
 *
 * 0 - Digit placeholder. If the value being
 * formatted has a digit in the position where the '0' appears in the format
 * string, then that digit is copied to the output string. Otherwise, a '0' is
 * stored in that position in the output string. The position of the leftmost
 * '0' before the decimal point and the rightmost '0' after the decimal point
 * determines the range of digits that are always present in the output
 * string.
 *
 * # - Digit placeholder. If the value being
 * formatted has a digit in the position where the '#' appears in the format
 * string, then that digit is copied to the output string. Otherwise, nothing
 * is stored in that position in the output string.
 *
 * . - Decimal point. The first '.' character
 * in the format string determines the location of the decimal separator in the
 * formatted value; any additional '.' characters are ignored. The actual
 * character used as a decimal separator in the output string is given by
 * the NumberFormatInfo used to format the number.
 *
 * , - Thousand separator and number scaling.
 * The ',' character serves two purposes. First, if the format string contains
 * a ',' character between two digit placeholders (0 or #) and to the left of
 * the decimal point if one is present, then the output will have a thousand
 * separators inserted between each group of three digits to the left of the
 * decimal separator. The actual character used as a decimal separator in
 * the output string is given by the NumberFormatInfo used to format the
 * number. Second, if the format string contains one or more ',' characters
 * immediately to the left of the decimal point, or after the last digit
 * placeholder if there is no decimal point, then the number will be divided by
 * 1000 times the number of ',' characters before it is formatted. For example,
 * the format string '0,,' will represent 100 million as just 100. Use of the
 * ',' character to indicate scaling does not also cause the formatted number
 * to have a thousand separators. Thus, to scale a number by 1 million and insert
 * a thousand separators you would use the format string '#,##0,,'.
 *
 * % - Percentage placeholder. The presence of
 * a '%' character in the format string causes the number to be multiplied by
 * 100 before it is formatted. The '%' character itself is inserted in the
 * output string where it appears in the format string.
 *
 * E+ E- e+ e-   - Scientific notation.
 * If any of the strings 'E+', 'E-', 'e+', or 'e-' are present in the format
 * string and are immediately followed by at least one '0' character, then the
 * number is formatted using scientific notation with an 'E' or 'e' inserted
 * between the number and the exponent. The number of '0' characters following
 * the scientific notation indicator determines the minimum number of digits to
 * output for the exponent. The 'E+' and 'e+' formats indicate that a sign
 * character (plus or minus) should always precede the exponent. The 'E-' and
 * 'e-' formats indicate that a sign character should only precede negative
 * exponents.
 *
 * \ - Literal character. A backslash character
 * causes the next character in the format string to be copied to the output
 * string as-is. The backslash itself isn't copied, so to place a backslash
 * character in the output string, use two backslashes (\\) in the format
 * string.
 *
 * 'ABC' "ABC" - Literal string. Characters
 * enclosed in single or double quotation marks are copied to the output string
 * as-is and do not affect formatting.
 *
 * ; - Section separator. The ';' character is
 * used to separate sections for positive, negative, and zero numbers in the
 * format string.
 *
 * Other - All other characters are copied to
 * the output string in the position they appear.
 *
 * For fixed point formats (formats not containing an 'E+', 'E-', 'e+', or
 * 'e-'), the number is rounded to as many decimal places as there are digit
 * placeholders to the right of the decimal point. If the format string does
 * not contain a decimal point, the number is rounded to the nearest
 * integer. If the number has more digits than there are digit placeholders to
 * the left of the decimal point, the extra digits are copied to the output
 * string immediately before the first digit placeholder.
 *
 * For scientific formats, the number is rounded to as many significant digits
 * as there are digit placeholders in the format string.
 *
 * To allow for different formatting of positive, negative, and zero values, a
 * user-defined format string may contain up to three sections separated by
 * semicolons. The results of having one, two, or three sections in the format
 * string are described in the table below.
 *
 * Sections:
 *
 * One - The format string applies to all values.
 *
 * Two - The first section applies to positive values
 * and zeros, and the second section applies to negative values. If the number
 * to be formatted is negative, but becomes zero after rounding according to
 * the format in the second section, then the resulting zero is formatted
 * according to the first section.
 *
 * Three - The first section applies to positive
 * values, the second section applies to negative values, and the third section
 * applies to zero. The second section may be left empty (by having no
 * characters between the semicolons), in which case the first section applies
 * to all non-zero values. If the number to be formatted is non-zero, but
 * becomes zero after rounding according to the format in the first or second
 * section, then the resulting zero is formatted according to the third
 * section.
 *
 * For both standard and user-defined formatting operations on values of type
 * float and double, if the value being formatted is a NaN (Not
 * a Number) or a positive or negative infinity, then regardless of the format
 * string, the resulting string is given by the NaNSymbol,
 * PositiveInfinitySymbol, or NegativeInfinitySymbol property of
 * the NumberFormatInfo used to format the number.
 *
 * Parsing
 *
 * The Parse methods provided by the numeric classes are all the form
 *
 *  public static XXX Parse(String s);
 *  public static XXX Parse(String s, int style);
 *  public static XXX Parse(String s, int style, NumberFormatInfo info);
 *
 * where XXX is the name of the particular numeric class. The methods convert a
 * string to a numeric value. The optional style parameter specifies the
 * permitted style of the numeric string. It must be a combination of bit flags
 * from the NumberStyles enumeration. The optional info parameter
 * specifies the NumberFormatInfo instance to use when parsing the
 * string. If the info parameter is null or omitted, the numeric
 * formatting information is obtained from the current culture.
 *
 * Numeric strings produced by the Format methods using the Currency,
 * Decimal, Engineering, Fixed point, General, or Number standard formats
 * (the C, D, E, F, G, and N format specifiers) are guaranteed to be parseable
 * by the Parse methods if the NumberStyles.Any style is
 * specified. Note, however, that the Parse methods do not accept
 * NaNs or Infinities.
 */

#include "NumberStyles.h"

#include <sstream>


class String;

class Number final
{
	friend class Boolean;
	friend class Byte;
	friend class Char;
	friend class Decimal;
	friend class Double;
	friend class Int16;
	friend class Int32;
	friend class Int64;
	friend class SByte;
	friend class Single;
	friend class String;
	friend class UInt16;
	friend class UInt32;
	friend class UInt64;

public:

	// Constants used by number parsing
	static constexpr uint8_t DecimalNeg = static_cast<uint8_t>(0x80);
	static constexpr uint32_t DecimalPrecision = 29;
	static constexpr uint32_t NumberMaxDigits = 50;
	static constexpr uint32_t Int32Precision = 10;
	static constexpr uint32_t UInt32Precision = Int32Precision;
	static constexpr uint32_t Int64Precision = 19;
	static constexpr uint32_t UInt64Precision = 20;

private:


	/*
	 * NumberBuffer is a partial wrapper around a stack pointer that maps on to
	 * the native NUMBER struct so that it can be passed to native directly. It
	 * must be initialized with a stack Byte * of size NumberBufferBytes.
	 * For performance, this structure should attempt to be completely inlined.
	 *
	 * It should always be initialized like so:
	 *
	 * Byte * numberBufferBytes = stackalloc Byte[NumberBuffer.NumberBufferBytes];
	 * NumberBuffer number = new NumberBuffer(numberBufferBytes);
	 *
	 * For performance, when working on the buffer in managed we use the values in this
	 * structure, except for the digits, and pack those values into the byte buffer
	 * if called out to manage.
	*/
	class NumberBuffer
	{

	private:

		unsigned char* BaseAddress;

	public:

		char* Digits;
		int32_t Precision;
		int32_t Scale;
		bool Sign;

		constexpr NumberBuffer(uint8_t* data) noexcept;

		static constexpr size_t NumberBufferBytes = 12 + ((NumberMaxDigits + 1) * 2) + sizeof(uintptr_t);
	};

	static constexpr uint64_t rgval64Power10[] =
	{	// Powers of 10
		/*1*/  0xa000000000000000l,
		/*2*/  0xc800000000000000l,
		/*3*/  0xfa00000000000000l,
		/*4*/  0x9c40000000000000l,
		/*5*/  0xc350000000000000l,
		/*6*/  0xf424000000000000l,
		/*7*/  0x9896800000000000l,
		/*8*/  0xbebc200000000000l,
		/*9*/  0xee6b280000000000l,
		/*10*/ 0x9502f90000000000l,
		/*11*/ 0xba43b74000000000l,
		/*12*/ 0xe8d4a51000000000l,
		/*13*/ 0x9184e72a00000000l,
		/*14*/ 0xb5e620f480000000l,
		/*15*/ 0xe35fa931a0000000l,

		// Powers of 0.1
		/*1*/  0xcccccccccccccccdl,
		/*2*/  0xa3d70a3d70a3d70bl,
		/*3*/  0x83126e978d4fdf3cl,
		/*4*/  0xd1b71758e219652el,
		/*5*/  0xa7c5ac471b478425l,
		/*6*/  0x8637bd05af6c69b7l,
		/*7*/  0xd6bf94d5e57a42bel,
		/*8*/  0xabcc77118461ceffl,
		/*9*/  0x89705f4136b4a599l,
		/*10*/ 0xdbe6fecebdedd5c2l,
		/*11*/ 0xafebff0bcb24ab02l,
		/*12*/ 0x8cbccc096f5088cfl,
		/*13*/ 0xe12e13424bb40e18l,
		/*14*/ 0xb424dc35095cd813l,
		/*15*/ 0x901d7cf73ab0acdcl
	};

	static constexpr int8_t rgexp64Power10[] = {
		// Exponents for both powers of 10 and 0.1
		/*1*/   4,
		/*2*/   7,
		/*3*/  10,
		/*4*/  14,
		/*5*/  17,
		/*6*/  20,
		/*7*/  24,
		/*8*/  27,
		/*9*/  30,
		/*10*/ 34,
		/*11*/ 37,
		/*12*/ 40,
		/*13*/ 44,
		/*14*/ 47,
		/*15*/ 50,
	};

	static constexpr uint64_t rgval64Power10By16[] = {
		// Powers of 10^16
		/*1*/  0x8e1bc9bf04000000l,
		/*2*/  0x9dc5ada82b70b59el,
		/*3*/  0xaf298d050e4395d6l,
		/*4*/  0xc2781f49ffcfa6d4l,
		/*5*/  0xd7e77a8f87daf7fal,
		/*6*/  0xefb3ab16c59b14a0l,
		/*7*/  0x850fadc09923329cl,
		/*8*/  0x93ba47c980e98cdel,
		/*9*/  0xa402b9c5a8d3a6e6l,
		/*10*/ 0xb616a12b7fe617a8l,
		/*11*/ 0xca28a291859bbf90l,
		/*12*/ 0xe070f78d39275566l,
		/*13*/ 0xf92e0c3537826140l,
		/*14*/ 0x8a5296ffe33cc92cl,
		/*15*/ 0x9991a6f3d6bf1762l,
		/*16*/ 0xaa7eebfb9df9de8al,
		/*17*/ 0xbd49d14aa79dbc7el,
		/*18*/ 0xd226fc195c6a2f88l,
		/*19*/ 0xe950df20247c83f8l,
		/*20*/ 0x81842f29f2cce373l,
		/*21*/ 0x8fcac257558ee4e2l,

		// Powers of 0.1^16
		/*1*/  0xe69594bec44de160l,
		/*2*/  0xcfb11ead453994c3l,
		/*3*/  0xbb127c53b17ec165l,
		/*4*/  0xa87fea27a539e9b3l,
		/*5*/  0x97c560ba6b0919b5l,
		/*6*/  0x88b402f7fd7553abl,
		/*7*/  0xf64335bcf065d3a0l,
		/*8*/  0xddd0467c64bce4c4l,
		/*9*/  0xc7caba6e7c5382edl,
		/*10*/ 0xb3f4e093db73a0b7l,
		/*11*/ 0xa21727db38cb0053l,
		/*12*/ 0x91ff83775423cc29l,
		/*13*/ 0x8380dea93da4bc82l,
		/*14*/ 0xece53cec4a314f00l,
		/*15*/ 0xd5605fcdcf32e217l,
		/*16*/ 0xc0314325637a1978l,
		/*17*/ 0xad1c8eab5ee43ba2l,
		/*18*/ 0x9becce62836ac5b0l,
		/*19*/ 0x8c71dcd9ba0b495cl,
		/*20*/ 0xfd00b89747823938l,
		/*21*/ 0xe3e27a444d8d991al,
	};

	static constexpr int16_t rgexp64Power10By16[] = {
		// Exponents for both powers of 10^16 and 0.1^16
		/*1*/    54,
		/*2*/   107,
		/*3*/   160,
		/*4*/   213,
		/*5*/   266,
		/*6*/   319,
		/*7*/   373,
		/*8*/   426,
		/*9*/   479,
		/*10*/  532,
		/*11*/  585,
		/*12*/  638,
		/*13*/  691,
		/*14*/  745,
		/*15*/  798,
		/*16*/  851,
		/*17*/  904,
		/*18*/  957,
		/*19*/ 1010,
		/*20*/ 1064,
		/*21*/ 1117,
	};

	static constexpr uint32_t DigitsToInt(char* p, int count)
	{
		assert(count >= 1 && count <= 9);
		char* end = p + count;
		uint32_t res = *p - '0';
		for(p = p + 1; p < end; ++p) res = (10 * res) + *p - '0';
		return res;
	}

	static constexpr uint64_t Mul32x32To64(uint32_t a, uint32_t b) noexcept { return static_cast<uint64_t>(a) * static_cast<uint64_t>(b); }

	static constexpr uint64_t Mul64Lossy(uint64_t a, uint64_t b, int32_t* pexp) noexcept
	{
		// it's ok to losse some precision here - Mul64 will be called
		// at most twice during the conversion, so the error won't propagate
		// to any of the 53 significant bits of the result
		uint64_t val = Mul32x32To64(a >> 32, b >> 32) +
			(Mul32x32To64(a >> 32, b) >> 32) +
			(Mul32x32To64(a, b >> 32) >> 32);

		// normalize
		if((val & static_cast<int64_t>(0x8000000000000000)) == 0) { val <<= 1; *pexp -= 1; }

		return val;
	}

	static bool HexNumberToInt32(NumberBuffer& number, int32_t& value) noexcept;
	static bool HexNumberToInt64(NumberBuffer& number, int64_t& value) noexcept;
	static bool HexNumberToUInt32(NumberBuffer& number, uint32_t& value) noexcept;
	static bool HexNumberToUInt64(NumberBuffer& number, uint64_t& value) noexcept;

	static bool IsWhite(char ch) noexcept
	{
		return ((ch == 0x20) || ((ch >= 0x09) && (ch <= 0x0d)));
	}

	// Implemented from COMM source...
	static bool NumberBufferToDecimal(NumberBuffer& buffer, Decimal& result);
	static bool NumberBufferToDouble(NumberBuffer& buffer, double* result);

	static bool NumberToInt32(NumberBuffer& number, int32_t& value) noexcept;
	static bool NumberToInt64(NumberBuffer& number, int64_t& value) noexcept;
	static bool NumberToUInt32(NumberBuffer& number, uint32_t& value) noexcept;
	static bool NumberToUInt64(NumberBuffer& number, uint64_t& value) noexcept;

	static char* MatchChars(char* p, String& str) noexcept;
	static char* MatchChars(char* p, char* str) noexcept;

	static Decimal ParseDecimal(String& value, NumberStyles options);
	static double ParseDouble(String& value, NumberStyles options);
	static int32_t ParseInt32(String& value, NumberStyles options);
	static int64_t ParseInt64(String& value, NumberStyles options);
	static bool ParseNumber(const char* str, NumberStyles options, NumberBuffer& number, std::ostringstream* sb, bool parseDecimal);
	static float ParseSingle(String& value, NumberStyles options);
	static uint32_t ParseUInt32(String& value, NumberStyles options);
	static uint64_t ParseUInt64(String& value, NumberStyles options);
	static void StringToNumber(String& value, NumberStyles options, NumberBuffer& number, bool parseDecimal);
	static bool TrailingZeros(String& value, int32_t index) noexcept;
	static bool TryParseDecimal(String& value, NumberStyles options, Decimal& result) noexcept;
	static bool TryParseDouble(String& value, NumberStyles options, double& result) noexcept;
	static bool TryParseInt32(String& value, NumberStyles options, int32_t& result) noexcept;
	static bool TryParseInt64(String& value, NumberStyles options, int64_t& result) noexcept;
	static bool TryParseSingle(String& value, NumberStyles options, float& result) noexcept;
	static bool TryParseUInt32(String& value, NumberStyles options, uint32_t& result) noexcept;
	static bool TryParseUInt64(String& value, NumberStyles options, uint64_t& result) noexcept;
	static bool TryStringToNumber(String& value, NumberStyles options, NumberBuffer& number, bool parseDecimal) noexcept;
	static bool TryStringToNumber(String& value, NumberStyles options, NumberBuffer& number, std::ostringstream* sb, bool parseDecimal) noexcept;
};

#endif //CPPDATASTRUCTURES_NUMBER_H
