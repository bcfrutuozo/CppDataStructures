#ifndef CPPDATASTRUCTURES_NUMBERFORMATTER_H
#define CPPDATASTRUCTURES_NUMBERFORMATTER_H

#include <cassert>

#include "BitConverter.h"
#include "String.h"

class NumberFormatter final
{

private:

	static constexpr int32_t INT32_PRECISION = 10;
	static constexpr int32_t UINT32_PRECISION = INT32_PRECISION;
	static constexpr int32_t INT64_PRECISION = 19;
	static constexpr int32_t UINT64_PRECISION = 20;
	static constexpr int32_t FLOAT_PRECISION = 7;
	static constexpr int32_t DOUBLE_PRECISION = 15;
	static constexpr int32_t LARGE_BUFFER_SIZE = 600;
	static constexpr int32_t MIN_BUFFER_SIZE = 105;

	static constexpr int32_t SCALE_NAN = 0x80000000;
	static constexpr int32_t SCALE_INF = 0x7FFFFFFF;

	struct FPSINGLE
	{
	#if BitConverter::IsLittleEndian() == 0
		uint32_t sign : 1;
		uint32_t exp : 8;
		uint32_t mant : 23;
	#else
		uint32_t mant : 23;
		uint32_t exp : 8;
		uint32_t sign : 1;
	#endif
	};

	struct FPDOUBLE
	{
	#if BitConverter::IsLittleEndian() == 0
		unsigned int sign : 1;
		unsigned int exp : 11;
		unsigned int mantHi : 20;
		unsigned int mantLo;
	#else
		unsigned int mantLo;
		unsigned int mantHi : 20;
		unsigned int exp : 11;
		unsigned int sign : 1;
	#endif
	};

	static constexpr const char* const posCurrencyFormats[] = {
		"$#", "#$", "$ #", "# $" };

	static constexpr const char* const negCurrencyFormats[] = {
			"($#)", "-$#", "$-#", "$#-",
				"(#$)", "-#$", "#-$", "#$-",
				"-# $", "-$ #", "# $-", "$ #-",
				"$ -#", "#- $", "($ #)", "(# $)" };

	static constexpr const char* const posPercentFormats[] = {
				"# %", "#%", "%#", "% #"
	};

	static constexpr const char* const negPercentFormats[] = {
		"-# %", "-#%", "-%#",
			"%-#", "%#-",
			"#-%", "#%-",
			"-% #", "# %-", "% #-",
			"% -#", "#- %"
	};

	static constexpr const char* const negNumberFormats[] = {
				"(#)", "-#", "- #", "#-", "# -",
	};

	static constexpr const char posNumberFormat[] = "#";

	static char ParseFormatSpecifier(String& value, int* digits) noexcept
	{
		assert(digits != nullptr);
		if(value.IsEmpty())
		{
			*digits = -1;
			return 'G';
		}

		const char* p = reinterpret_cast<const char*>(value.GetPointer());
		char ch = *p;
		if(ch != 0)
		{
			if(ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z')
			{
				++p;
				int n = -1;
				if(*p >= '0' && *p <= '9')
				{
					n = *p++ - '0';
					while(*p >= '0' && *p <= '9')
					{
						n = n * 10 + *p++ - '0';
						if(n > 10) break;
					}
				}
				if(*p == 0)
				{
					*digits = n;
					return ch;
				}
			}

			return 0;
		}
	}

public:

	static constexpr String FormatDouble(double& value, String& format)
	{
		// We are purposely using stack for this
		uint8_t numberBufferByte[Number::NumberBuffer::NumberBufferBytes];
		Number::NumberBuffer number(numberBufferByte);
		
		int32_t digits;
		double test;
		char fmt = ParseFormatSpecifier(format, &digits);
		char val = (fmt & 0xFFDF);
		int precision = DOUBLE_PRECISION;

		switch(val)
		{
			case 'R':
				/* In order to give numbers that are both friendly to display and round-trippable,
				 * we parse the number using 15 digits and then determine if it round trips to the same
				 * value.  If it does, we convert that NUMBER to a string, otherwise we reparse using 17 digits
				 * and display that.
				 */

				DoubleToNumber(value, DOUBLE_PRECISION, &number);

				if(number.Scale == SCALE_NAN) goto lExit;
				if(number.Scale == SCALE_INF) goto lExit;
				
				Number::NumberBufferToDouble(number, &test);

				if(test == value)
				{
					return NumberToString(&number, 'G', DOUBLE_PRECISION);
					goto lExit;
				}

				DoubleToNumber(value, 17, &number);
				return NumberToString(&number, 'G', 17);
		}
	}

};

#endif //CPPDATASTRUCTURES_NUMBERFORMATTER_H