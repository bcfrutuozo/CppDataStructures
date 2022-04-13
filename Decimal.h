//
// Created by bcfrutuozo on 4/9/22.
//

#ifndef CPPDATASTRUCTURES_DECIMAL_H
#define CPPDATASTRUCTURES_DECIMAL_H

#include <bit>

#include "Platform.h"
#include "BitConverter.h"
#include "MidPointRounding.hpp"

class Byte;
class Int16;
class Int32;
class Int64;
class Double;
class Single;
class SByte;
class String;
class UInt16;
class UInt32;
class UInt64;

/*
 * We must declare PowerOvfl outside the Decimal class scope, as we are using
 * it as constexpr inside of Decimal class.
 * That's the only reason it's completely private being private of Decimal class.
 * For that class is supposed to be accessed just for Decimal class
*/
class PowerOvfl
{
	friend class Decimal;

private:

	const unsigned int Hi;
	const unsigned long long MidLo;

	constexpr PowerOvfl(unsigned int hi, unsigned int mid, unsigned int lo)
		:
		Hi(hi),
		MidLo((static_cast<unsigned long long>(mid) << 32) + lo)
	{};
};

class Decimal
{

private:

	static constexpr int SignMask = static_cast<int>(0x80000000);
	static constexpr unsigned char DECIMAL_NEG = 0x80;
	static constexpr unsigned char DECIMAL_ADD = 0x00;

	/*
	 * Scale mask for the flags field.This byte in the flags field contains
	 * the power of 10 to divide the Decimal value by. The scale byte must
	 * contain a value between 0 and 28 inclusive.
	*/
	static constexpr int ScaleMask = 0x00FF0000;

	// Number of bits scale is shifted by
	static constexpr int ScaleShift = 16;

	// The maximum power of 10 that a 32 bit integer can store
	static constexpr int MaxInt32Scale = 9;

	// Fast access for 10^n where n is 0-9        
	static constexpr unsigned int Powers10[10] = {
		1,
		10,
		100,
		1000,
		10000,
		100000,
		1000000,
		10000000,
		100000000,
		1000000000
	};

	// Constant representing the Decimal value 0.
	static constexpr Decimal Zero() { return 0.0; }

	// Constant representing the Decimal value 1.
	static constexpr Decimal One() { return 1.0; }

	// Constant representing the Decimal value -1.
	static constexpr Decimal MinusOne() { return -1.0; }

	// Constant representing the largest possible Decimal value. The value of
	// this constant is 79,228,162,514,264,337,593,543,950,335.
	static constexpr Decimal MaxValue() { return 79228162514264337593543950335.0; }

	// Constant representing the smallest possible Decimal value. The value of
	// this constant is -79,228,162,514,264,337,593,543,950,335.
	static constexpr Decimal MinValue() { return -79228162514264337593543950335.0; }


	// Constant representing the negative number that is the closest possible
	// Decimal value to -0m.
	static constexpr Decimal NearNegativeZero() { return -0.000000000000000000000000001; }

	// Constant representing the positive number that is the closest possible
	// Decimal value to +0m.
	static constexpr Decimal NearPositiveZero() { +0.000000000000000000000000001; }

	/*
	 * The Lo, Mid, Hi, and Flags fields contain the representation of the
	 * Decimal value. The lo, mid, and hi fields contain the 96-bit integer
	 * part of the Decimal. Bits 0-15 (the lower word) of the flags field are
	 * unused and must be zero; bits 16-23 contain must contain a value between
	 * 0 and 28, indicating the power of 10 to divide the 96-bit integer part
	 * by to produce the Decimal value; bits 24-30 are unused and must be zero;
	 * and finally bit 31 indicates the sign of the Decimal value, 0 meaning
	 * positive and 1 meaning negative.
	 *
	 * NOTE: Do not change the order in which these fields are declared. The
	 * native methods in this class rely on this particular order.
	 */
	int Flags;
	int Hi;
	int Lo;
	int Mid;

	unsigned long long ULOMIDLE;

	inline constexpr bool IsNegative() const noexcept { return Flags < 0; }
	inline constexpr int Scale() const noexcept { return static_cast<unsigned char>(Flags >> ScaleShift); }

	static constexpr PowerOvfl PowerOvflValues[] =
	{
		// This is a table of the largest values that can be in the upper two
		// unsigned ints of a 96-bit number that will not overflow when multiplied
		// by a given power.  For the upper word, this is a table of
		// 2^32 / 10^n for 1 <= n <= 8.  For the lower word, this is the
		// remaining fraction part * 2^32.  2^32 = 4294967296.
		PowerOvfl(429496729, 2576980377, 2576980377),  // 10^1 remainder 0.6
		PowerOvfl(42949672, 4123168604, 687194767),   // 10^2 remainder 0.16
		PowerOvfl(4294967, 1271310319, 2645699854),  // 10^3 remainder 0.616
		PowerOvfl(429496, 3133608139, 694066715),   // 10^4 remainder 0.1616
		PowerOvfl(42949, 2890341191, 2216890319),  // 10^5 remainder 0.51616
		PowerOvfl(4294, 4154504685, 2369172679),  // 10^6 remainder 0.551616
		PowerOvfl(429, 2133437386, 4102387834),  // 10^7 remainder 0.9551616
		PowerOvfl(42, 4078814305, 410238783),   // 10^8 remainder 0.09991616
	};

	enum class RoundingMode
	{
		ToEven = 0,
		AwayFromZero = 1,
		Truncate = 2,
		Floor = 3,
		Ceiling = 4,
	};

	class Buf12
	{
	public:

		unsigned int U0;
		unsigned int U1;
		unsigned int U2;

		// We are declaring private fields after public ones to keep
		// the class structure for further bitwise operations
	private:

		unsigned long ulo64LE;
		unsigned long uhigh64LE;

	public:

		constexpr unsigned long Low64() const noexcept { return BitConverter::IsLittleEndian ? ulo64LE : static_cast<unsigned long>(U1 << 32) | U0; }
		constexpr void Low64(unsigned long value) noexcept
		{
			if(BitConverter::IsLittleEndian) ulo64LE = value;
			else
			{
				U1 = static_cast<int>(value >> 32);
				U0 = static_cast<int>(value);
			}
		}

		// U1-U2 combined (overlaps with Low64)
		constexpr unsigned long High64() const noexcept { return BitConverter::IsLittleEndian ? uhigh64LE : static_cast<unsigned long>(U2 << 32) | U1; }
		constexpr void High64(unsigned long value) noexcept
		{
			if(BitConverter::IsLittleEndian) uhigh64LE = value;
			else
			{
				U2 = static_cast<int>(value >> 32);
				U1 = static_cast<int>(value);
			}
		}
	};

	class Buf16
	{
	public:

		unsigned int U0;
		unsigned int U1;
		unsigned int U2;
		unsigned int U3;

	private:

		unsigned long ulo64LE;
		unsigned long uhigh64LE;

	public:

		constexpr unsigned long Low64() const noexcept { return BitConverter::IsLittleEndian ? ulo64LE : static_cast<unsigned long>(U1 << 32) | U0; }
		constexpr void Low64(unsigned long value) noexcept
		{
			if(BitConverter::IsLittleEndian) ulo64LE = value;
			else
			{
				U1 = static_cast<unsigned int>(value >> 32);
				U0 = static_cast<unsigned int>(value);
			}
		}

		constexpr unsigned long High64() const noexcept { return BitConverter::IsLittleEndian ? uhigh64LE : static_cast<long>(U3 << 32) | U2; }
		constexpr void High64(unsigned long value) noexcept
		{
			if(BitConverter::IsLittleEndian) uhigh64LE = value;
			else
			{
				U3 = static_cast<unsigned int>(value >> 32);
				U2 = static_cast<unsigned int>(value);
			}
		}
	};

	class Buf24
	{
	public:

		unsigned int U0;
		unsigned int U1;
		unsigned int U2;
		unsigned int U3;
		unsigned int U4;
		unsigned int U5;

	private:

		unsigned long ulo64LE;
		unsigned long umid64LE;
		unsigned long uhigh64LE;

	public:

		constexpr unsigned long Low64() const noexcept { return BitConverter::IsLittleEndian ? ulo64LE : static_cast<unsigned long>(U1 << 32) | U0; }
		constexpr void Low64(unsigned long value) noexcept
		{
			if(BitConverter::IsLittleEndian) ulo64LE = value;
			else
			{
				U1 = static_cast<unsigned int>(value >> 32);
				U0 = static_cast<unsigned int>(value);
			}
		}

		constexpr unsigned long Mid64() const noexcept { return BitConverter::IsLittleEndian ? umid64LE : static_cast<unsigned long>(U3 << 32) | U2; }
		constexpr void Mid64(unsigned long value) noexcept
		{
			if(BitConverter::IsLittleEndian) umid64LE = value;
			else
			{
				U3 = static_cast<unsigned int>(value >> 32);
				U2 = static_cast<unsigned int>(value);
			}
		}

		constexpr unsigned long High64() const noexcept { return BitConverter::IsLittleEndian ? uhigh64LE : static_cast<unsigned long>(U5 << 32) | U4; }
		constexpr void High64(unsigned long value) noexcept
		{
			if(BitConverter::IsLittleEndian) umid64LE = value;
			else
			{
				U5 = static_cast<unsigned int>(value >> 32);
				U4 = static_cast<unsigned int>(value);
			}
		}

		static constexpr int Length = 6;
	};

	struct Buf28
	{
		Buf24 Buf24;
		unsigned int U6;
		static constexpr int Length = 7;
	};

	/*
	 *  Class that contains all the mathematical calculations for decimal.Most of which have been ported from oleaut32.
	 *  All the logic from now on was taken from the mono framework: https://github.com/mono/mono/blob/main/mcs/class/corlib/corert/Decimal.cs
	 */
	class DecCalc
	{
		friend class Decimal;

	private:

		// NOTE: Do not change the offsets of these fields. This structure must have the same layout as Decimal.
		unsigned int uflags;
		unsigned int uhi;
		unsigned int ulo;
		unsigned int umid;

		/// The low and mid fields combined in little-endian order
		unsigned long ulomidLE;

		inline constexpr unsigned int High() const noexcept { return uhi; }
		inline constexpr void High(unsigned int value) noexcept { uhi = value; }
		inline constexpr unsigned int Mid() const noexcept { return umid; }
		inline constexpr void Mid(unsigned int value) noexcept { umid = value; }
		inline constexpr unsigned int Low() const noexcept { return ulo; }
		inline constexpr void Low(unsigned int value) noexcept { ulo = value; }
		inline constexpr bool IsNegative() const noexcept { return (static_cast<int>(uflags) < 0); }
		inline constexpr int Scale() const noexcept { return (unsigned char)(uflags >> ScaleShift); }

		// In our project, we are just handling LittleEndian format!
		// So there's no conversion to treat data as BigEndian
		constexpr unsigned long Low64() const noexcept { return ulomidLE; }
		constexpr void Low64(unsigned long value) noexcept { ulomidLE = value; }


		static constexpr unsigned int SignMask = 0x80000000;
		static constexpr unsigned int ScaleMask = 0x00FF0000;

		static constexpr int DEC_SCALE_MAX = 28;

		static constexpr unsigned int TenToPowerNine = 1000000000;
		static constexpr unsigned long TenToPowerEighteen = 1000000000000000000;

		// The maximum power of 10 that a 32 bit integer can store
		static constexpr int MaxInt32Scale = 9;
		// The maximum power of 10 that a 64 bit integer can store
		static constexpr int MaxInt64Scale = 19;

		// Fast access for 10^n where n is 0-9
		static constexpr unsigned int s_powers10[] = {
			1,
			10,
			100,
			1000,
			10000,
			100000,
			1000000,
			10000000,
			100000000,
			1000000000
		};

		// Fast access for 10^n where n is 1-19
		static constexpr unsigned long s_ulongPowers10[] = {
			10,
			100,
			1000,
			10000,
			100000,
			1000000,
			10000000,
			100000000,
			1000000000,
			10000000000,
			100000000000,
			1000000000000,
			10000000000000,
			100000000000000,
			1000000000000000,
			10000000000000000,
			100000000000000000,
			1000000000000000000,
			10000000000000000000,
		};

		static constexpr double s_doublePowers10[] =
		{
			1, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9,
				1e10, 1e11, 1e12, 1e13, 1e14, 1e15, 1e16, 1e17, 1e18, 1e19,
				1e20, 1e21, 1e22, 1e23, 1e24, 1e25, 1e26, 1e27, 1e28, 1e29,
				1e30, 1e31, 1e32, 1e33, 1e34, 1e35, 1e36, 1e37, 1e38, 1e39,
				1e40, 1e41, 1e42, 1e43, 1e44, 1e45, 1e46, 1e47, 1e48, 1e49,
				1e50, 1e51, 1e52, 1e53, 1e54, 1e55, 1e56, 1e57, 1e58, 1e59,
				1e60, 1e61, 1e62, 1e63, 1e64, 1e65, 1e66, 1e67, 1e68, 1e69,
				1e70, 1e71, 1e72, 1e73, 1e74, 1e75, 1e76, 1e77, 1e78, 1e79,
				1e80
		};

		static inline constexpr unsigned int GetExponent(float f) noexcept
		{
			return static_cast<unsigned char>(*reinterpret_cast<unsigned int*>(&f) >> 23);
		}

		static inline constexpr unsigned int GetExponent(double d) noexcept
		{
			return static_cast<unsigned int>(*reinterpret_cast<unsigned long*>(&d) >> 52) & 0x7FFu;
		}

		static inline constexpr unsigned long unsigned UInt32x32To64(unsigned int a, unsigned int b) noexcept
		{
			return static_cast<unsigned long>(a) * static_cast<unsigned long>(b);
		}

		static constexpr void UInt64x64To128(unsigned long a, unsigned long b, DecCalc& result)
		{
			unsigned long low = UInt32x32To64(static_cast<unsigned int>(a), static_cast<unsigned int>(b)); // lo partial prod
			unsigned long mid = UInt32x32To64(static_cast<unsigned int>(a), static_cast<unsigned int>(b >> 32)); // mid 1 partial prod
			unsigned long high = UInt32x32To64(static_cast<unsigned int>(a >> 32), static_cast<unsigned int>(b >> 32));
			high += mid >> 32;
			low += mid <<= 32;
			if(low < mid)  // test for carry
				++high;

			mid = UInt32x32To64(static_cast<unsigned int>(a >> 32), static_cast<unsigned int>(b));
			high += mid >> 32;
			low += mid <<= 32;
			if(low < mid)  // test for carry
				++high;

			if(high > UINTMAX_MAX) throw std::overflow_error("Decimal");
			result.Low64(low);
			result.High(static_cast<unsigned int>(high));
		}

		static unsigned int Div96By32(Buf12& bufNum, unsigned int den)
		{
			// TODO: https://github.com/dotnet/coreclr/issues/3439
			unsigned long tmp, div;
			if(bufNum.U2 != 0)
			{
				tmp = bufNum.High64();
				div = tmp / den;
				bufNum.High64(div);
				tmp = ((tmp - static_cast<unsigned int>(div) * den) << 32) | bufNum.U0;
				if(tmp == 0) return 0;
				unsigned int div32 = static_cast<unsigned int>(tmp / den);
				bufNum.U0 = div32;
				return static_cast<unsigned int>(tmp - div32 * den);
			}

			tmp = bufNum.Low64();
			if(tmp == 0) return 0;
			div = tmp / den;
			bufNum.Low64(div);
			return static_cast<unsigned int>(tmp - div * den);
		}

		static bool Div96ByConst(unsigned long& high64, unsigned int& low, unsigned int pow)
		{
		#ifdef ENVIRONMENT64
			unsigned long div64 = high64 / pow;
			unsigned int div = static_cast<unsigned int>((((high64 - div64 * pow) << 32) + low) / pow);
			if(low == div * pow)
			{
				high64 = div64;
				low = div;
				return true;
			}
		#else
			assert(pow <= UINT16_MAX);
			unsigned int num, mid32, low16, div;
			if(high64 <= UINT_MAX)
			{
				num = static_cast<unsigned int>(high64);
				mid32 = num / pow;
				num = (num - mid32 * pow) << 16;

				num += low >> 16;
				low16 = num / pow;
				num = (num - low16 * pow) << 16;

				num += static_cast<unsigned short>(low);
				div = num / pow;
				if(num == div * pow)
				{
					high64 = mid32;
					low = (low16 << 16) + div;
					return true;
				}
			}
			else
			{
				num = static_cast<unsigned int>(high64 >> 32);
				unsigned int high32 = num / pow;
				num = (num - high32 * pow) << 16;

				num += static_cast<unsigned int>(high64 >> 16);
				mid32 = num / pow;
				num = (num - mid32 * pow) << 16;

				num += static_cast<unsigned short>(high64);
				div = num / pow;
				num = (num - div * pow) << 16;
				mid32 = div + (mid32 << 16);

				num += low >> 16;
				low16 = num / pow;
				num = (num - low16 * pow) << 16;

				num += static_cast<unsigned short>(low);
				div = num / pow;
				if(num == div * pow)
				{
					high64 = (static_cast<unsigned long>(high32) << 32) | mid32;
					low = (low16 << 16) + div;
					return true;
				}
			}
		#endif
			return false;
		}

		/// Normalize (unscale) the number by trying to divide out 10^8, 10^4, 10^2, and 10^1.
		/// If a division by one of these powers returns a zero remainder, then we keep the quotient.
		static constexpr void Unscale(unsigned int& low, unsigned long& high64, int& scale)
		{
			// Since 10 = 2 * 5, there must be a factor of 2 for every power of 10 we can extract.
			// We use this as a quick test on whether to try a given power.

		#ifdef ENVIRONMENT64
			while(static_cast<unsigned char>(low) == 0 && scale >= 8 && Div96ByConst(high64, low, 100000000))
				scale -= 8;

			if((low & 0xF) == 0 && scale >= 4 && Div96ByConst(high64, low, 10000))
				scale -= 4;
		#else
			while((low & 0xF) == 0 && scale >= 4 && Div96ByConst(high64, low, 10000))
				scale -= 4;
		#endif

			if((low & 3) == 0 && scale >= 2 && Div96ByConst(high64, low, 100))
				scale -= 2;

			if((low & 1) == 0 && scale >= 1 && Div96ByConst(high64, low, 10))
				scale--;
		}

		/// Do partial divide, yielding 32-bit result and 64-bit remainder.
		/// Divisor must be larger than upper 64 bits of dividend.
		static unsigned int Div96By64(Buf12& bufNum, unsigned long den)
		{
			assert(den > bufNum.High64());
			unsigned int quo;
			unsigned long num;
			unsigned int num2 = bufNum.U2;
			if(num2 == 0)
			{
				num = bufNum.Low64();
				if(num < den)
					// Result is zero.  Entire dividend is remainder.
					return 0;

				quo = static_cast<unsigned int>(num / den);
				num -= quo * den; // remainder
				bufNum.Low64(num);
				return quo;
			}

			unsigned int denHigh32 = static_cast<unsigned int>(den >> 32);
			if(num2 >= denHigh32)
			{
				// Divide would overflow.  Assume a quotient of 2^32, and set
				// up remainder accordingly.
				//
				num = bufNum.Low64();
				num -= den << 32;
				quo = 0;

				// Remainder went negative.  Add divisor back in until it's positive,
				// a max of 2 times.
				//
				do
				{
					quo--;
					num += den;
				} while(num >= den);

				bufNum.Low64(num);
				return quo;
			}

			// Hardware divide won't overflow
			unsigned long num64 = bufNum.High64();
			if(num64 < denHigh32)
				// Result is zero.  Entire dividend is remainder.
				//
				return 0;

			quo = static_cast<unsigned int>(num64 / denHigh32);
			num = bufNum.U0 | ((num64 - quo * denHigh32) << 32); // remainder

			// Compute full remainder, rem = dividend - (quo * divisor).
			unsigned long prod = UInt32x32To64(quo, static_cast<unsigned int>(den)); // quo * lo divisor
			num -= prod;

			if(num > ~prod)
			{
				// Remainder went negative.  Add divisor back in until it's positive,
				// a max of 2 times.
				do
				{
					quo--;
					num += den;
				} while(num >= den);
			}

			bufNum.Low64(num);
			return quo;
		}

		/// Do partial divide, yielding 32-bit result and 96-bit remainder.
		/// Top divisor unsigned int must be larger than top dividend unsigned int. This is
		/// assured in the initial call because the divisor is normalized
		/// and the dividend can't be. In subsequent calls, the remainder
		/// is multiplied by 10^9 (max), so it can be no more than 1/4 of
		/// the divisor which is effectively multiplied by 2^32 (4 * 10^9).
		static unsigned int Div128By96(Buf16& bufNum, Buf12& bufDen)
		{
			assert(bufDen.U2 > bufNum.U3);
			unsigned long dividend = bufNum.High64();
			unsigned int den = bufDen.U2;
			if(dividend < den)
				// Result is zero.  Entire dividend is remainder.
				return 0;

			unsigned int quo = static_cast<unsigned int>(dividend / den);
			unsigned int remainder = static_cast<unsigned int>(dividend - quo * den);

			// Compute full remainder, rem = dividend - (quo * divisor).
			unsigned long prod1 = UInt32x32To64(quo, bufDen.U0); // quo * lo divisor
			unsigned long prod2 = UInt32x32To64(quo, bufDen.U1); // quo * mid divisor
			prod2 += prod1 >> 32;
			prod1 = (unsigned int)prod1 | (prod2 << 32);
			prod2 >>= 32;

			unsigned long num = bufNum.Low64();
			num -= prod1;
			remainder -= static_cast<unsigned int>(prod2);

			// Propagate carries
			if(num > ~prod1)
			{
				remainder--;
				if(remainder < ~static_cast<unsigned int>(prod2))
					goto PosRem;
			}
			else if(remainder <= ~static_cast<unsigned int>(prod2))
				goto PosRem;
			{
				// Remainder went negative.  Add divisor back in until it's positive,
				// a max of 2 times.
				prod1 = bufDen.Low64();

				for(;;)
				{
					quo--;
					num += prod1;
					remainder += den;

					if(num < prod1)
					{
						// Detected carry. Check for carry out of top
						// before adding it in.
						if(remainder++ < den)
							break;
					}
					if(remainder < den)
						break; // detected carry
				}
			}
		PosRem:

			bufNum.Low64(num);
			bufNum.U2 = remainder;
			return quo;
		}

		/// Multiply the two numbers. The low 96 bits of the result overwrite
		/// the input. The last 32 bits of the product are the return value.
		static unsigned int IncreaseScale(Buf12& bufNum, unsigned int power)
		{
			unsigned long tmp = UInt32x32To64(bufNum.U0, power);
			bufNum.U0 = static_cast<unsigned int>(tmp);
			tmp >>= 32;
			tmp += UInt32x32To64(bufNum.U1, power);
			bufNum.U1 = static_cast<unsigned int>(tmp);
			tmp >>= 32;
			tmp += UInt32x32To64(bufNum.U2, power);
			bufNum.U2 = static_cast<unsigned int>(tmp);
			return static_cast<unsigned int>(tmp >> 32);
		}

		static void IncreaseScale64(Buf12& bufNum, unsigned int power)
		{
			unsigned long tmp = UInt32x32To64(bufNum.U0, power);
			bufNum.U0 = static_cast<unsigned int>(tmp);
			tmp >>= 32;
			tmp += UInt32x32To64(bufNum.U1, power);
			bufNum.High64(tmp);
		}

		static unsigned int DivByConst(unsigned int* result, unsigned int hiRes, unsigned int& quotient, unsigned int& remainder, unsigned int power)
		{
			unsigned int high = result[hiRes];
			remainder = high - (quotient = high / power) * power;
			for(unsigned int i = hiRes - 1; (int)i >= 0; i--)
			{
			#ifdef ENVIRONMENT64
				unsigned long num = result[i] + ((unsigned long)remainder << 32);
				remainder = static_cast<unsigned int>(num) - (result[i] = static_cast<unsigned int>(num / power)) * power;
			#else
				// 32-bit RyuJIT doesn't convert 64-bit division by constant into multiplication by reciprocal. Do half-width divisions instead.
				assert(power <= ushort.MaxValue);
				int low16 = BitConverter::IsLittleEndian ? 0 : 2, high16 = BitConverter::IsLittleEndian ? 2 : 0;
				unsigned int num = *reinterpret_cast<unsigned short*>((unsigned char*)result + i * 4 + high16) + (remainder << 16);
				unsigned int div = num / power;
				remainder = num - div * power;
				*reinterpret_cast<unsigned short>((unsigned char*)result + i * 4 + high16) = static_cast<unsigned short>(div);

				num = *reinterpret_cast<unsigned short*>((unsigned char*)result + i * 4 + low16) + (remainder << 16);
				div = num / power;
				remainder = num - div * power;
				*reinterpret_cast<unsigned short*>((unsigned char*)result + i * 4 + low16) = static_cast<unsigned short>(div);
			#endif
			}
			return power;
		}

		static int LeadingZeroCount(unsigned int value)
		{
			assert(value > 0);
			int c = 1;
			if((value & 0xFFFF0000) == 0)
			{
				value <<= 16;
				c += 16;
			}
			if((value & 0xFF000000) == 0)
			{
				value <<= 8;
				c += 8;
			}
			if((value & 0xF0000000) == 0)
			{
				value <<= 4;
				c += 4;
			}
			if((value & 0xC0000000) == 0)
			{
				value <<= 2;
				c += 2;
			}
			return c + (static_cast<int>(value) >> 31);
		}

		/// See if we need to scale the result to fit it in 96 bits.
		/// Perform needed scaling. Adjust scale factor accordingly.
		static int ScaleResult(Buf24* bufRes, unsigned int hiRes, int scale)
		{
			assert(hiRes < bufRes->Length);
			unsigned int* result = (unsigned int*)(bufRes);

			// See if we need to scale the result.  The combined scale must
			// be <= DEC_SCALE_MAX and the upper 96 bits must be zero.
			//
			// Start by figuring a lower bound on the scaling needed to make
			// the upper 96 bits zero.  hiRes is the index into result[]
			// of the highest non-zero unsigned int.
			//
			int newScale = 0;
			if(hiRes > 2)
			{
				newScale = (int)hiRes * 32 - 64 - 1;
				newScale -= LeadingZeroCount(result[hiRes]);

				// Multiply bit position by log10(2) to figure it's power of 10.
				// We scale the log by 256.  log(2) = .30103, * 256 = 77.  Doing this
				// with a multiply saves a 96-byte lookup table.  The power returned
				// is <= the power of the number, so we must add one power of 10
				// to make it's integer part zero after dividing by 256.
				//
				// Note: the result of this multiplication by an approximation of
				// log10(2) have been exhaustively checked to verify it gives the
				// correct result.  (There were only 95 to check...)
				newScale = ((newScale * 77) >> 8) + 1;

				// newScale = min scale factor to make high 96 bits zero, 0 - 29.
				// This reduces the scale factor of the result.  If it exceeds the
				// current scale of the result, we'll overflow.
				if(newScale > scale)
					goto ThrowOverflow;
			}

			// Make sure we scale by enough to bring the current scale factor
			// into valid range.
			if(newScale < scale - DEC_SCALE_MAX)
				newScale = scale - DEC_SCALE_MAX;

			if(newScale != 0)
			{
				// Scale by the power of 10 given by newScale.  Note that this is
				// NOT guaranteed to bring the number within 96 bits -- it could
				// be 1 power of 10 short.
				scale -= newScale;
				unsigned int sticky = 0;
				unsigned int quotient, remainder = 0;

				for(;;)
				{
					sticky |= remainder; // record remainder as sticky bit

					unsigned int power;
					// Scaling loop specialized for each power of 10 because division by constant is an order of magnitude faster (especially for 64-bit division that's actually done by 128bit DIV on x64)
					switch(newScale)
					{
						case 1:
							power = DivByConst(result, hiRes, quotient, remainder, 10);
							break;
						case 2:
							power = DivByConst(result, hiRes, quotient, remainder, 100);
							break;
						case 3:
							power = DivByConst(result, hiRes, quotient, remainder, 1000);
							break;
						case 4:
							power = DivByConst(result, hiRes, quotient, remainder, 10000);
							break;
						#ifdef ENVIRONMENT64
						case 5:
							power = DivByConst(result, hiRes, quotient, remainder, 100000);
							break;
						case 6:
							power = DivByConst(result, hiRes, quotient, remainder, 1000000);
							break;
						case 7:
							power = DivByConst(result, hiRes, quotient, remainder, 10000000);
							break;
						case 8:
							power = DivByConst(result, hiRes, quotient, remainder, 100000000);
							break;
						default:
							power = DivByConst(result, hiRes, quotient, remainder, TenToPowerNine);
							break;
						#else
						default:
							goto case 4;
						#endif
					}
					result[hiRes] = quotient;
					// If first quotient was 0, update hiRes.
					//
					if(quotient == 0 && hiRes != 0)
						hiRes--;

				#ifdef ENVIRONMENT64
					newScale -= MaxInt32Scale;
				#else
					newScale -= 4;
				#endif
					if(newScale > 0) continue; // scale some more

					// If we scaled enough, hiRes would be 2 or less.  If not,
					// divide by 10 more.
					if(hiRes > 2)
					{
						if(scale == 0)
							goto ThrowOverflow;
						newScale = 1;
						scale--;
						continue; // scale by 10
					}

					// Round final result.  See if remainder >= 1/2 of divisor.
					// If remainder == 1/2 divisor, round up if odd or sticky bit set.
					power >>= 1;  // power of 10 always even
					if(power <= remainder && (power < remainder || ((result[0] & 1) | sticky) != 0) && ++result[0] == 0)
					{
						unsigned int cur = 0;
						do
						{
							assert(cur + 1 < bufRes->Length);
						} while(++result[++cur] == 0);

						if(cur > 2)
						{
							// The rounding caused us to carry beyond 96 bits.
							// Scale by 10 more.
							if(scale == 0) goto ThrowOverflow;
							hiRes = cur;
							sticky = 0;    // no sticky bit
							remainder = 0; // or remainder
							newScale = 1;
							scale--;
							continue; // scale by 10
						}
					}

					break;
				}
			}
			return scale;

		ThrowOverflow:
			throw std::overflow_error("Decimal");
		}

		/// Add a 32-bit unsigned int to an array of 3 unsigned ints representing a 96-bit integer.
		static bool Add32To96(Buf12& bufNum, unsigned int value)
		{
			unsigned long low64 = bufNum.Low64();
			bufNum.Low64(low64 += value);
			if(bufNum.Low64() < value)
			{
				if(++bufNum.U2 == 0)
					return false;
			}
			return true;
		}

		/// Adjust the quotient to deal with an overflow.
		/// We need to divide by 10, feed in the high bit to undo the overflow and then round as required.
		static int OverflowUnscale(Buf12& bufQuo, int scale, bool sticky)
		{
			if(--scale < 0) throw std::overflow_error("Decimal");
			assert(bufQuo.U2 == 0);

			// We have overflown, so load the high bit with a one.
			const unsigned long highbit = 1UL << 32;
			bufQuo.U2 = static_cast<unsigned int>(highbit / 10);
			unsigned long tmp = ((highbit % 10) << 32) + bufQuo.U1;
			unsigned int div = static_cast<unsigned int>(tmp / 10);
			bufQuo.U1 = div;
			tmp = ((tmp - div * 10) << 32) + bufQuo.U0;
			div = static_cast<unsigned int>(tmp / 10);
			bufQuo.U0 = div;
			unsigned int remainder = static_cast<unsigned int>(tmp - div * 10);
			// The remainder is the last digit that does not fit, so we can use it to work out if we need to round up
			if(remainder > 5 || remainder == 5 && (sticky || (bufQuo.U0 & 1) != 0))
				Add32To96(bufQuo, 1);
			return scale;
		}

		/// Determine the max power of 10, &lt;= 9, that the quotient can be scaled
		/// up by and still fit in 96 bits.
		static int SearchScale(Buf12& bufQuo, int scale)
		{
			static constexpr unsigned int OVFL_MAX_9_HI = 4;
			static constexpr unsigned int OVFL_MAX_8_HI = 42;
			static constexpr unsigned int OVFL_MAX_7_HI = 429;
			static constexpr unsigned int OVFL_MAX_6_HI = 4294;
			static constexpr unsigned int OVFL_MAX_5_HI = 42949;
			static constexpr unsigned int OVFL_MAX_4_HI = 429496;
			static constexpr unsigned int OVFL_MAX_3_HI = 4294967;
			static constexpr unsigned int OVFL_MAX_2_HI = 42949672;
			static constexpr unsigned int OVFL_MAX_1_HI = 429496729;
			static constexpr unsigned long OVFL_MAX_9_MIDLO = 5441186219426131129;

			unsigned int resHi = bufQuo.U2;
			unsigned long resMidLo = bufQuo.Low64();
			int curScale = 0;
			auto powerOvfl = PowerOvflValues;

			// Quick check to stop us from trying to scale any more.
			//
			if(resHi > OVFL_MAX_1_HI)
			{
				goto HaveScale;
			}

			if(scale > DEC_SCALE_MAX - 9)
			{
				// We can't scale by 10^9 without exceeding the max scale factor.
				// See if we can scale to the max.  If not, we'll fall into
				// standard search for scale factor.
				//
				curScale = DEC_SCALE_MAX - scale;
				if(resHi < powerOvfl[curScale - 1].Hi)
					goto HaveScale;
			}
			else if(resHi < OVFL_MAX_9_HI || resHi == OVFL_MAX_9_HI && resMidLo <= OVFL_MAX_9_MIDLO)
				return 9;

			// Search for a power to scale by < 9.  Do a binary search.
			//
			if(resHi > OVFL_MAX_5_HI)
			{
				if(resHi > OVFL_MAX_3_HI)
				{
					curScale = 2;
					if(resHi > OVFL_MAX_2_HI)
						curScale--;
				}
				else
				{
					curScale = 4;
					if(resHi > OVFL_MAX_4_HI)
						curScale--;
				}
			}
			else
			{
				if(resHi > OVFL_MAX_7_HI)
				{
					curScale = 6;
					if(resHi > OVFL_MAX_6_HI)
						curScale--;
				}
				else
				{
					curScale = 8;
					if(resHi > OVFL_MAX_8_HI)
						curScale--;
				}
			}

			// In all cases, we already found we could not use the power one larger.
			// So if we can use this power, it is the biggest, and we're done.  If
			// we can't use this power, the one below it is correct for all cases
			// unless it's 10^1 -- we might have to go to 10^0 (no scaling).
			if(resHi == powerOvfl[curScale - 1].Hi && resMidLo > powerOvfl[curScale - 1].MidLo)
				curScale--;

		HaveScale:
			// curScale = largest power of 10 we can scale by without overflow,
			// curScale < 9.  See if this is enough to make scale factor
			// positive if it isn't already.
			if(curScale + scale < 0) throw std::overflow_error("Decimal");

			return curScale;
		}

		/// Adds or subtracts two decimal values.
		/// On return, d1 contains the result of the operation and d2 is trashed.
		static void DecAddSub(DecCalc& d1, DecCalc& d2, bool sign)
		{
			unsigned long low64 = d1.Low64();
			unsigned int high = d1.High(), flags = d1.uflags, d2flags = d2.uflags;

			unsigned int xorflags = d2flags ^ flags;
			sign ^= (xorflags & SignMask) != 0;

			if((xorflags & ScaleMask) == 0)
			{
				// Scale factors are equal, no alignment necessary.
				goto AlignedAdd;
			}
			else
			{
				// Scale factors are not equal.  Assume that a larger scale
				// factor (more decimal places) is likely to mean that number
				// is smaller.  Start by guessing that the right operand has
				// the larger scale factor.  The result will have the larger
				// scale factor.
				unsigned int d1flags = flags;
				flags = d2flags & ScaleMask | flags & SignMask; // scale factor of "smaller",  but sign of "larger"
				int scale = static_cast<int>(flags - d1flags) >> ScaleShift;

				if(scale < 0)
				{
					// Guessed scale factor wrong. Swap operands.
					//
					scale = -scale;
					flags = d1flags;
					if(sign)
						flags ^= SignMask;
					low64 = d2.Low64();
					high = d2.High();
					d2 = d1;
				}

				unsigned int power;
				unsigned long tmp64, tmpLow;

				// d1 will need to be multiplied by 10^scale so
				// it will have the same scale as d2.  We could be
				// extending it to up to 192 bits of precision.

				// Scan for zeros in the upper words.
				if(high == 0)
				{
					if(low64 <= UINT_MAX)
					{
						if(static_cast<unsigned int>(low64) == 0)
						{
							// Left arg is zero, return right.
							//
							unsigned int signFlags = flags & SignMask;
							if(sign)
								signFlags ^= SignMask;
							d1 = d2;
							d1.uflags = d2.uflags & ScaleMask | signFlags;
							return;
						}

						do
						{
							if(scale <= MaxInt32Scale)
							{
								low64 = UInt32x32To64(static_cast<unsigned int>(low64), s_powers10[scale]);
								goto AlignedAdd;
							}
							scale -= MaxInt32Scale;
							low64 = UInt32x32To64(static_cast<unsigned int>(low64), TenToPowerNine);
						} while(low64 <= UINT_MAX);
					}

					do
					{
						power = TenToPowerNine;
						if(scale < MaxInt32Scale)
							power = s_powers10[scale];
						tmpLow = UInt32x32To64(static_cast<unsigned int>(low64), power);
						tmp64 = UInt32x32To64(static_cast<unsigned int>(low64 >> 32), power) + (tmpLow >> 32);
						low64 = static_cast<unsigned int>(tmpLow) + (tmp64 << 32);
						high = static_cast<unsigned int>(tmp64 >> 32);
						if((scale -= MaxInt32Scale) <= 0)
							goto AlignedAdd;
					} while(high == 0);
				}

				while(true)
				{
					// Scaling won't make it larger than 4 unsigned ints
					power = TenToPowerNine;
					if(scale < MaxInt32Scale)
						power = s_powers10[scale];
					tmpLow = UInt32x32To64(static_cast<unsigned int>(low64), power);
					tmp64 = UInt32x32To64(static_cast<unsigned int>(low64 >> 32), power) + (tmpLow >> 32);
					low64 = static_cast<unsigned int>(tmpLow) + (tmp64 << 32);
					tmp64 >>= 32;
					tmp64 += UInt32x32To64(high, power);

					scale -= MaxInt32Scale;
					if(tmp64 > UINT_MAX)
						break;

					high = static_cast<unsigned int>(tmp64);
					// Result fits in 96 bits.  Use standard aligned add.
					if(scale <= 0)
						goto AlignedAdd;
				}

				// Have to scale by a bunch. Move the number to a buffer where it has room to grow as it's scaled.
				Buf24 bufNum;
				bufNum.Low64(low64);
				bufNum.Mid64(tmp64);
				unsigned int hiProd = 3;

				// Scaling loop, up to 10^9 at a time. hiProd stays updated with index of highest non-zero unsigned int.
				for(; scale > 0; scale -= MaxInt32Scale)
				{
					power = TenToPowerNine;
					if(scale < MaxInt32Scale)
						power = s_powers10[scale];
					tmp64 = 0;
					unsigned int* rgulNum = reinterpret_cast<unsigned int*>(&bufNum);
					for(unsigned int cur = 0; ;)
					{
						assert(cur < bufNum.Length);
						tmp64 += UInt32x32To64(rgulNum[cur], power);
						rgulNum[cur] = static_cast<unsigned int>(tmp64);
						cur++;
						tmp64 >>= 32;
						if(cur > hiProd)
							break;
					}

					if((unsigned int)tmp64 != 0)
					{
						// We're extending the result by another unsigned int.
						assert(hiProd + 1 < bufNum.Length);
						rgulNum[++hiProd] = static_cast<unsigned int>(tmp64);
					}
				}

				// Scaling complete, do the add.  Could be subtract if signs differ.
				tmp64 = bufNum.Low64();
				low64 = d2.Low64();
				unsigned int tmpHigh = bufNum.U2;
				high = d2.High();

				if(sign)
				{
					// Signs differ, subtract.
					low64 = tmp64 - low64;
					high = tmpHigh - high;

					// Propagate carry
					if(low64 > tmp64)
					{
						high--;
						if(high < tmpHigh)
							goto NoCarry;
					}
					else if(high <= tmpHigh)
						goto NoCarry;

					// Carry the subtraction into the higher bits.
					unsigned int* number = reinterpret_cast<unsigned int*>(&bufNum);
					unsigned int cur = 3;
					do
					{
						assert(cur < bufNum.Length);
					} while(number[cur++]-- == 0);

					assert(hiProd < bufNum.Length);
					if(number[hiProd] == 0 && --hiProd <= 2)
						goto ReturnResult;
				}
				else
				{
					// Signs the same, add.
					low64 += tmp64;
					high += tmpHigh;

					// Propagate carry
					if(low64 < tmp64)
					{
						high++;
						if(high > tmpHigh)
							goto NoCarry;
					}
					else if(high >= tmpHigh)
						goto NoCarry;

					unsigned int* number = reinterpret_cast<unsigned int*>(&bufNum);
					for(unsigned int cur = 3; ++number[cur++] == 0;)
					{
						assert(cur < bufNum.Length);
						if(hiProd < cur)
						{
							number[cur] = 1;
							hiProd = cur;
							break;
						}
					}
				}
			NoCarry:

				bufNum.Low64(low64);
				bufNum.U2 = high;
				scale = ScaleResult(&bufNum, hiProd, static_cast<unsigned char>(flags >> ScaleShift));
				flags = (flags & ~ScaleMask) | ((unsigned int)scale << ScaleShift);
				low64 = bufNum.Low64();
				high = bufNum.U2;
				goto ReturnResult;
			}

		SignFlip:
			{
				// Got negative result.  Flip its sign.
				flags ^= SignMask;
				high = ~high;
				low64 = (unsigned long)-(long)low64;
				if(low64 == 0)
					high++;
				goto ReturnResult;
			}

		AlignedScale:
			{
				// The addition carried above 96 bits.
				// Divide the value by 10, dropping the scale factor.
				if((flags & ScaleMask) == 0) throw std::overflow_error("Decimal");
				flags -= 1 << ScaleShift;

				const unsigned int den = 10;
				unsigned long num = high + (1UL << 32);
				high = static_cast<unsigned int>(num / den);
				num = ((num - high * den) << 32) + (low64 >> 32);
				unsigned int div = static_cast<unsigned int>(num / den);
				num = ((num - div * den) << 32) + static_cast<unsigned int>(low64);
				low64 = div;
				low64 <<= 32;
				div = static_cast<unsigned int>(num / den);
				low64 += div;
				div = static_cast<unsigned int>(num - div * den);

				// See if we need to round up.
				if(div >= 5 && (div > 5 || (low64 & 1) != 0))
				{
					if(++low64 == 0)
						high++;
				}
				goto ReturnResult;
			}

		AlignedAdd:
			{
				unsigned long d1Low64 = low64;
				unsigned int d1High = high;
				if(sign)
				{
					// Signs differ - subtract
					low64 = d1Low64 - d2.Low64();
					high = d1High - d2.High();

					// Propagate carry
					//
					if(low64 > d1Low64)
					{
						high--;
						if(high >= d1High)
							goto SignFlip;
					}
					else if(high > d1High)
						goto SignFlip;
				}
				else
				{
					// Signs are the same - add
					low64 = d1Low64 + d2.Low64();
					high = d1High + d2.High();

					// Propagate carry
					if(low64 < d1Low64)
					{
						high++;
						if(high <= d1High)
							goto AlignedScale;
					}
					else if(high < d1High)
						goto AlignedScale;
				}
				goto ReturnResult;
			}

		ReturnResult:
			d1.uflags = flags;
			d1.High(high);
			d1.Low64(low64);
			return;
		}

		/// Does an in-place round by the specified scale
		static void InternalRound(DecCalc& d, unsigned int scale, RoundingMode mode) noexcept
		{
			// the scale becomes the desired decimal count
			d.uflags -= scale << ScaleShift;

			unsigned int remainder, sticky = 0, power;
			// First divide the value by constant 10^9 up to three times
			while(scale >= MaxInt32Scale)
			{
				scale -= MaxInt32Scale;

				const unsigned int divisor = TenToPowerNine;
				unsigned int n = d.uhi;
				if(n == 0)
				{
					unsigned long tmp = d.Low64();
					unsigned long div = tmp / divisor;
					d.Low64(div);
					remainder = static_cast<unsigned int>(tmp - div * divisor);
				}
				else
				{
					unsigned int q;
					d.uhi = q = n / divisor;
					remainder = n - q * divisor;
					n = d.umid;
					if((n | remainder) != 0)
					{
						d.umid = q = static_cast<int>(((static_cast<unsigned long>(remainder) << 32) | n) / divisor);
						remainder = n - q * divisor;
					}
					n = d.ulo;
					if((n | remainder) != 0)
					{
						d.ulo = q = static_cast<int>(((static_cast<unsigned long>(remainder) << 32) | n) / divisor);
						remainder = n - q * divisor;
					}
				}
				power = divisor;
				if(scale == 0)
					goto checkRemainder;
				sticky |= remainder;
			}

			{
				power = s_powers10[scale];
				unsigned int n = d.uhi;
				if(n == 0)
				{
					unsigned long tmp = d.Low64();
					if(tmp == 0)
					{
						if(mode <= RoundingMode::Truncate)
							return;
						remainder = 0;
						goto checkRemainder;
					}
					unsigned long div = tmp / power;
					d.Low64(div);
					remainder = static_cast<unsigned int>(tmp - div * power);
				}
				else
				{
					unsigned int q;
					d.uhi = q = n / power;
					remainder = n - q * power;
					n = d.umid;
					if((n | remainder) != 0)
					{
						d.umid = q = static_cast<unsigned int>(((static_cast<unsigned long>(remainder) << 32) | n) / power);
						remainder = n - q * power;
					}
					n = d.ulo;
					if((n | remainder) != 0)
					{
						d.ulo = q = static_cast<unsigned int>(((static_cast<unsigned long>(remainder) << 32) | n) / power);
						remainder = n - q * power;
					}
				}
			}

		checkRemainder:
			if(mode == RoundingMode::Truncate)
				return;
			else if(mode == RoundingMode::ToEven)
			{
				// To do IEEE rounding, we add LSB of result to sticky bits so either causes round up if remainder * 2 == last divisor.
				remainder <<= 1;
				if((sticky | d.ulo & 1) != 0)
					remainder++;
				if(power >= remainder)
					return;
			}
			else if(mode == RoundingMode::AwayFromZero)
			{
				// Round away from zero at the mid point.
				remainder <<= 1;
				if(power > remainder)
					return;
			}
			else if(mode == RoundingMode::Floor)
			{
				// Round toward -infinity if we have chopped off a non-zero amount from a negative value.
				if((remainder | sticky) == 0 || !d.IsNegative())
					return;
			}
			else
			{
				assert(mode == RoundingMode::Ceiling);
				// Round toward infinity if we have chopped off a non-zero amount from a positive value.
				if((remainder | sticky) == 0 || d.IsNegative())
					return;
			}

			unsigned long low64 = d.Low64();
			d.Low(++low64);
			if(d.Low64() == 0)
				d.uhi++;
			return;
		}

		static unsigned int DecDivMod1E9(DecCalc& value)
		{
			unsigned long high64 = (static_cast<unsigned long>(value.uhi) << 32) + value.umid;
			unsigned long div64 = high64 / TenToPowerNine;
			value.uhi = static_cast<unsigned int>(div64 >> 32);
			value.umid = static_cast<unsigned int>(div64);

			unsigned long num = ((high64 - static_cast<unsigned int>(div64) * TenToPowerNine) << 32) + value.ulo;
			unsigned int div = static_cast<unsigned int>(num / TenToPowerNine);
			value.ulo = div;
			return static_cast<unsigned int>(num) - div * TenToPowerNine;
		}

		// Convert Decimal to Currency (similar to OleAut32 api.)
		static long VarCyFromDec(DecCalc& pdecIn)
		{
			long value;

			int scale = pdecIn.Scale() - 4;
			// Need to scale to get 4 decimal places.  -4 <= scale <= 24.
			if(scale < 0)
			{
				if(pdecIn.High() != 0)
					goto ThrowOverflow;
				unsigned int pwr = s_powers10[-scale];
				unsigned long high = UInt32x32To64(pwr, pdecIn.Mid());
				if(high > UINT_MAX)
					goto ThrowOverflow;
				unsigned long low = UInt32x32To64(pwr, pdecIn.Low());
				low += high <<= 32;
				if(low < high)
					goto ThrowOverflow;
				value = static_cast<long>(low);
			}
			else
			{
				if(scale != 0)
					InternalRound(pdecIn, static_cast<unsigned int>(scale), RoundingMode::ToEven);
				if(pdecIn.High() != 0)
					goto ThrowOverflow;
				value = static_cast<long>(pdecIn.Low64());
			}

			if(value < 0 && (value != LONG_MIN || !pdecIn.IsNegative()))
				goto ThrowOverflow;

			if(pdecIn.IsNegative())
				value = -value;

			return value;

		ThrowOverflow:
			throw std::overflow_error("Currency");
		}

		static int VarDecCmpSub(Decimal const& d1, Decimal const& d2)
		{
			int flags = d2.Flags;
			int sign = (flags >> 31) | 1;
			int scale = flags - d1.Flags;

			unsigned long low64 = BitConverter::IsLittleEndian ? static_cast<unsigned long>(d1.Lo) : static_cast<unsigned long>(d1.Mid) << 32 | d1.Lo;
			unsigned int high = d1.Hi;

			unsigned long d2Low64 = BitConverter::IsLittleEndian ? static_cast<unsigned long>(d2.Lo) : static_cast<unsigned long>(d2.Mid) << 32 | d2.Lo;
			unsigned int d2High = d2.Hi;

			if(scale != 0)
			{
				scale >>= ScaleShift;

				// Scale factors are not equal. Assume that a larger scale factor (more decimal places) is likely to mean that number is smaller.
				// Start by guessing that the right operand has the larger scale factor.
				if(scale < 0)
				{
					// Guessed scale factor wrong. Swap operands.
					scale = -scale;
					sign = -sign;

					unsigned long tmp64 = low64;
					low64 = d2Low64;
					d2Low64 = tmp64;

					unsigned int tmp = high;
					high = d2High;
					d2High = tmp;
				}

				// d1 will need to be multiplied by 10^scale so it will have the same scale as d2.
				// Scaling loop, up to 10^9 at a time.
				do
				{
					unsigned int power = scale >= MaxInt32Scale ? TenToPowerNine : s_powers10[scale];
					unsigned long tmpLow = UInt32x32To64((unsigned int)low64, power);
					unsigned long tmp = UInt32x32To64((unsigned int)(low64 >> 32), power) + (tmpLow >> 32);
					low64 = (unsigned int)tmpLow + (tmp << 32);
					tmp >>= 32;
					tmp += UInt32x32To64(high, power);
					// If the scaled value has more than 96 significant bits then it's greater than d2
					if(tmp > UINT_MAX) return sign;
					high = static_cast<unsigned int>(tmp);
				} while((scale -= MaxInt32Scale) > 0);
			}

			unsigned int cmpHigh = high - d2High;
			if(cmpHigh != 0)
			{
				// check for overflow
				if(cmpHigh > high)
					sign = -sign;
				return sign;
			}

			unsigned long cmpLow64 = low64 - d2Low64;
			if(cmpLow64 == 0)
				sign = 0;
			// check for overflow
			else if(cmpLow64 > low64)
				sign = -sign;
			return sign;
		}

		/// Decimal Compare updated to return values similar to ICompareTo
		static int VarDecCmp(Decimal const& d1, Decimal const& d2)
		{
			if((d2.Lo | d2.Mid | d2.Hi) == 0)
			{
				if((d1.Lo | d1.Mid | d1.Hi) == 0) return 0;
				return (d1.Flags >> 31) | 1;
			}
			if((d1.Lo | d1.Mid | d1.Hi) == 0) return -((d2.Flags >> 31) | 1);

			int sign = (d1.Flags >> 31) - (d2.Flags >> 31);
			if(sign != 0)
				return sign;
			return VarDecCmpSub(d1, d2);
		}

		/// Decimal Multiply
		static void VarDecMul(DecCalc& d1, DecCalc& d2)
		{
			int scale = static_cast<unsigned char>(d1.uflags + d2.uflags >> ScaleShift);

			unsigned long tmp;
			unsigned int hiProd;
			Buf24 bufProd;
			unsigned int* product = reinterpret_cast<unsigned int*>(&bufProd);

			if((d1.High() | d1.Mid()) == 0)
			{
				if((d2.High() | d2.Mid()) == 0)
				{
					// Upper 64 bits are zero.
					unsigned long low64 = UInt32x32To64(d1.Low(), d2.Low());
					if(scale > DEC_SCALE_MAX)
					{
						// Result scale is too big.  Divide result by power of 10 to reduce it.
						// If the amount to divide by is > 19 the result is guaranteed
						// less than 1/2.  [max value in 64 bits = 1.84E19]
						if(scale > DEC_SCALE_MAX + MaxInt64Scale)
							goto ReturnZero;

						scale -= DEC_SCALE_MAX + 1;
						unsigned long power = s_ulongPowers10[scale];

						tmp = low64 / power;
						unsigned long remainder = low64 - tmp * power;
						low64 = tmp;

						// Round result.  See if remainder >= 1/2 of divisor.
						// Divisor is a power of 10, so it is always even.
						power >>= 1;
						if(remainder >= power && (remainder > power || (static_cast<unsigned int>(low64) & 1) > 0))
							low64++;

						scale = DEC_SCALE_MAX;
					}
					d1.Low64(low64);
					d1.uflags = ((d2.uflags ^ d1.uflags) & SignMask) | ((unsigned int)scale << ScaleShift);
					return;
				}
				else
				{
					// Left value is 32-bit, result fits in 4 unsigned ints
					tmp = UInt32x32To64(d1.Low(), d2.Low());
					bufProd.U0 = static_cast<unsigned int>(tmp);

					tmp = UInt32x32To64(d1.Low(), d2.Mid()) + (tmp >> 32);
					bufProd.U1 = static_cast<unsigned int>(tmp);
					tmp >>= 32;

					if(d2.High() != 0)
					{
						tmp += UInt32x32To64(d1.Low(), d2.High());
						if(tmp > UINT_MAX)
						{
							bufProd.Mid64(tmp);
							hiProd = 3;
							goto SkipScan;
						}
					}
					if((unsigned int)tmp != 0)
					{
						bufProd.U2 = (unsigned int)tmp;
						hiProd = 2;
						goto SkipScan;
					}
					hiProd = 1;
				}
			}
			else if((d2.High() | d2.Mid()) == 0)
			{
				// Right value is 32-bit, result fits in 4 unsigned ints
				tmp = UInt32x32To64(d2.Low(), d1.Low());
				bufProd.U0 = static_cast<unsigned int>(tmp);

				tmp = UInt32x32To64(d2.Low(), d1.Mid()) + (tmp >> 32);
				bufProd.U1 = static_cast<unsigned int>(tmp);
				tmp >>= 32;

				if(d1.High() != 0)
				{
					tmp += UInt32x32To64(d2.Low(), d1.High());
					if(tmp > UINT_MAX)
					{
						bufProd.Mid64(tmp);
						hiProd = 3;
						goto SkipScan;
					}
				}
				if(static_cast<unsigned int>(tmp) != 0)
				{
					bufProd.U2 = static_cast<unsigned int>(tmp);
					hiProd = 2;
					goto SkipScan;
				}
				hiProd = 1;
			}
			else
			{
				// Both operands have bits set in the upper 64 bits.
				//
				// Compute and accumulate the 9 partial products into a
				// 192-bit (24-byte) result.
				//
				//        [l-h][l-m][l-l]      left high, middle, low
				//         x    [r-h][r-m][r-l]      right high, middle, low
				// ------------------------------
				//
				//             [0-h][0-l]      l-l * r-l
				//        [1ah][1al]      l-l * r-m
				//        [1bh][1bl]      l-m * r-l
				//       [2ah][2al]          l-m * r-m
				//       [2bh][2bl]          l-l * r-h
				//       [2ch][2cl]          l-h * r-l
				//      [3ah][3al]          l-m * r-h
				//      [3bh][3bl]          l-h * r-m
				// [4-h][4-l]              l-h * r-h
				// ------------------------------
				// [p-5][p-4][p-3][p-2][p-1][p-0]      prod[] array
				//

				tmp = UInt32x32To64(d1.Low(), d2.Low());
				bufProd.U0 = (unsigned int)tmp;

				unsigned long tmp2 = UInt32x32To64(d1.Low(), d2.Mid()) + (tmp >> 32);

				tmp = UInt32x32To64(d1.Mid(), d2.Low());
				tmp += tmp2; // this could generate carry
				bufProd.U1 = static_cast<unsigned int>(tmp);
				if(tmp < tmp2) // detect carry
					tmp2 = (tmp >> 32) | (1UL << 32);
				else
					tmp2 = tmp >> 32;

				tmp = UInt32x32To64(d1.Mid(), d2.Mid()) + tmp2;

				if((d1.High() | d2.High()) > 0)
				{
					// Highest 32 bits is non-zero.     Calculate 5 more partial products.
					tmp2 = UInt32x32To64(d1.Low(), d2.High());
					tmp += tmp2; // this could generate carry
					unsigned int tmp3 = 0;
					if(tmp < tmp2) // detect carry
						tmp3 = 1;

					tmp2 = UInt32x32To64(d1.High(), d2.Low());
					tmp += tmp2; // this could generate carry
					bufProd.U2 = static_cast<unsigned int>(tmp);
					if(tmp < tmp2) // detect carry
						tmp3++;
					tmp2 = (static_cast<unsigned long>(tmp3) << 32) | (tmp >> 32);

					tmp = UInt32x32To64(d1.Mid(), d2.High());
					tmp += tmp2; // this could generate carry
					tmp3 = 0;
					if(tmp < tmp2) // detect carry
						tmp3 = 1;

					tmp2 = UInt32x32To64(d1.High(), d2.Mid());
					tmp += tmp2; // this could generate carry
					bufProd.U3 = (unsigned int)tmp;
					if(tmp < tmp2) // detect carry
						tmp3++;
					tmp = (static_cast<unsigned long>(tmp3) << 32) | (tmp >> 32);

					bufProd.High64(UInt32x32To64(d1.High(), d2.High()) + tmp);

					hiProd = 5;
				}
				else if(tmp != 0)
				{
					bufProd.Mid64(tmp);
					hiProd = 3;
				}
				else
					hiProd = 1;
			}

			// Check for leading zero unsigned ints on the product
			while(product[(int)hiProd] == 0)
			{
				if(hiProd == 0)
					goto ReturnZero;
				hiProd--;
			}

		SkipScan:
			if(hiProd > 2 || scale > DEC_SCALE_MAX)
			{
				scale = ScaleResult(&bufProd, hiProd, scale);
			}

			d1.Low64(bufProd.Low64());
			d1.High(bufProd.U2);
			d1.uflags = ((d2.uflags ^ d1.uflags) & SignMask) | (static_cast<unsigned int>(scale) << ScaleShift);
			return;

		ReturnZero:
			d1.Low64(0);
			d1.Mid(0);
			d1.High(0);
		}

		/// Convert float to Decimal
		static constexpr void VarDecFromR4(float input, DecCalc& result)
		{
			result = DecCalc();

			// The most we can scale by is 10^28, which is just slightly more
			// than 2^93.  So a float with an exponent of -94 could just
			// barely reach 0.5, but smaller exponents will always round to zero.
			const unsigned int SNGBIAS = 126;
			int exp = static_cast<int>(GetExponent(input) - SNGBIAS);
			if(exp < -94)
				return; // result should be zeroed out

			if(exp > 96) throw std::overflow_error("Decimal");

			unsigned int flags = 0;
			if(input < 0)
			{
				input = -input;
				flags = SignMask;
			}

			// Round the input to a 7-digit integer.  The R4 format has
			// only 7 digits of precision, and we want to keep garbage digits
			// out of the Decimal were making.
			//
			// Calculate max power of 10 input value could have by multiplying
			// the exponent by log10(2).  Using scaled integer multiplcation,
			// log10(2) * 2 ^ 16 = .30103 * 65536 = 19728.3.
			double dbl = input;
			int power = 6 - ((exp * 19728) >> 16);
			// power is between -22 and 35

			if(power >= 0)
			{
				// We have less than 7 digits, scale input up.
				//
				if(power > DEC_SCALE_MAX)
					power = DEC_SCALE_MAX;

				dbl *= s_doublePowers10[power];
			}
			else
			{
				if(power != -1 || dbl >= 1E7)
					dbl /= s_doublePowers10[-power];
				else
					power = 0; // didn't scale it
			}

			assert(dbl < 1E7);
			if(dbl < 1E6 && power < DEC_SCALE_MAX)
			{
				dbl *= 10;
				power++;
				assert(dbl >= 1E6);
			}

			// Round to integer
			unsigned int mant;
			mant = static_cast<unsigned int>(static_cast<int>(dbl));
			dbl -= static_cast<int>(mant);  // difference between input & integer
			if(dbl > 0.5 || dbl == 0.5 && (mant & 1) != 0)
				mant++;
			if(mant == 0)
				return;  // result should be zeroed out

			if(power < 0)
			{
				// Add -power factors of 10, -power <= (29 - 7) = 22.
				power = -power;
				if(power < 10)
				{
					result.Low64(UInt32x32To64(mant, s_powers10[power]));
				}
				else
				{
					// Have a big power of 10.
					if(power > 18)
					{
						unsigned long low64 = UInt32x32To64(mant, s_powers10[power - 18]);
						UInt64x64To128(low64, TenToPowerEighteen, result);
					}
					else
					{
						unsigned long low64 = UInt32x32To64(mant, s_powers10[power - 9]);
						unsigned long hi64 = UInt32x32To64(TenToPowerNine, static_cast<unsigned int>(low64) >> 32);
						low64 = UInt32x32To64(TenToPowerNine, static_cast<unsigned int>(low64));
						result.Low(static_cast<unsigned int>(low64));
						hi64 += low64 >> 32;
						result.Mid(static_cast<unsigned int>(hi64));
						hi64 >>= 32;
						result.High(static_cast<unsigned int>(hi64));
					}
				}
			}
			else
			{
				// Factor out powers of 10 to reduce the scale, if possible.
				// The maximum number we could factor out would be 6.  This
				// comes from the fact we have a 7-digit number, and the
				// MSD must be non-zero -- but the lower 6 digits could be
				// zero.  Note also the scale factor is never negative, so
				// we can't scale by any more than the power we used to
				// get the integer.
				int lmax = power;
				if(lmax > 6)
					lmax = 6;

				if((mant & 0xF) == 0 && lmax >= 4)
				{
					const unsigned int den = 10000;
					unsigned int div = mant / den;
					if(mant == div * den)
					{
						mant = div;
						power -= 4;
						lmax -= 4;
					}
				}

				if((mant & 3) == 0 && lmax >= 2)
				{
					const unsigned int den = 100;
					unsigned int div = mant / den;
					if(mant == div * den)
					{
						mant = div;
						power -= 2;
						lmax -= 2;
					}
				}

				if((mant & 1) == 0 && lmax >= 1)
				{
					const unsigned int den = 10;
					unsigned int div = mant / den;
					if(mant == div * den)
					{
						mant = div;
						power--;
					}
				}

				flags |= static_cast<unsigned int>(power) << ScaleShift;
				result.Low(mant);
			}

			result.uflags = flags;
		}

		/// Convert double to Decimal
		static void VarDecFromR8(double input, DecCalc& result)
		{
			result = DecCalc();

			// The most we can scale by is 10^28, which is just slightly more
			// than 2^93.  So a float with an exponent of -94 could just
			// barely reach 0.5, but smaller exponents will always round to zero.
			const unsigned int DBLBIAS = 1022;
			int exp = static_cast<int>(GetExponent(input) - DBLBIAS);
			if(exp < -94)
				return; // result should be zeroed out

			if(exp > 96) throw std::overflow_error("Decimal");

			unsigned int flags = 0;
			if(input < 0)
			{
				input = -input;
				flags = SignMask;
			}

			// Round the input to a 15-digit integer.  The R8 format has
			// only 15 digits of precision, and we want to keep garbage digits
			// out of the Decimal were making.
			//
			// Calculate max power of 10 input value could have by multiplying
			// the exponent by log10(2).  Using scaled integer multiplcation,
			// log10(2) * 2 ^ 16 = .30103 * 65536 = 19728.3.
			double dbl = input;
			int power = 14 - ((exp * 19728) >> 16);
			// power is between -14 and 43

			if(power >= 0)
			{
				// We have less than 15 digits, scale input up.
				//
				if(power > DEC_SCALE_MAX)
					power = DEC_SCALE_MAX;

				dbl *= s_doublePowers10[power];
			}
			else
			{
				if(power != -1 || dbl >= 1E15)
					dbl /= s_doublePowers10[-power];
				else
					power = 0; // didn't scale it
			}

			assert(dbl < 1E15);
			if(dbl < 1E14 && power < DEC_SCALE_MAX)
			{
				dbl *= 10;
				power++;
				assert(dbl >= 1E14);
			}

			// Round to int64
			unsigned long mant;
			mant = static_cast<unsigned long>(static_cast<long>(dbl));
			dbl -= (long)mant;  // difference between input & integer
			if(dbl > 0.5 || dbl == 0.5 && (mant & 1) != 0)
				mant++;

			if(mant == 0)
				return;  // result should be zeroed out

			if(power < 0)
			{
				// Add -power factors of 10, -power <= (29 - 15) = 14.
				power = -power;
				if(power < 10)
				{
					auto pow10 = s_powers10[power];
					unsigned long low64 = UInt32x32To64((unsigned int)mant, pow10);
					unsigned long hi64 = UInt32x32To64((unsigned int)(mant >> 32), pow10);
					result.Low(static_cast<unsigned int>(low64));
					hi64 += low64 >> 32;
					result.Mid(static_cast<unsigned int>(hi64));
					hi64 >>= 32;
					result.High(static_cast<unsigned int>(hi64));
				}
				else
				{
					// Have a big power of 10.
					assert(power <= 14);
					UInt64x64To128(mant, s_ulongPowers10[power - 1], result);
				}
			}
			else
			{
				// Factor out powers of 10 to reduce the scale, if possible.
				// The maximum number we could factor out would be 14.  This
				// comes from the fact we have a 15-digit number, and the
				// MSD must be non-zero -- but the lower 14 digits could be
				// zero.  Note also the scale factor is never negative, so
				// we can't scale by any more than the power we used to
				// get the integer.
				int lmax = power;
				if(lmax > 14)
					lmax = 14;

				if(static_cast<unsigned char>(mant) == 0 && lmax >= 8)
				{
					const unsigned int den = 100000000;
					unsigned long div = mant / den;
					if(static_cast<unsigned int>(mant) == static_cast<unsigned int>(div * den))
					{
						mant = div;
						power -= 8;
						lmax -= 8;
					}
				}

				if((static_cast<unsigned int>(mant) & 0xF) == 0 && lmax >= 4)
				{
					const unsigned int den = 10000;
					unsigned long div = mant / den;
					if(static_cast<unsigned int>(mant) == static_cast<unsigned int>(div * den))
					{
						mant = div;
						power -= 4;
						lmax -= 4;
					}
				}

				if((static_cast<unsigned int>(mant) & 3) == 0 && lmax >= 2)
				{
					const unsigned int den = 100;
					unsigned long div = mant / den;
					if(static_cast<unsigned int>(mant) == static_cast<unsigned int>(div * den))
					{
						mant = div;
						power -= 2;
						lmax -= 2;
					}
				}

				if((static_cast<unsigned int>(mant) & 1) == 0 && lmax >= 1)
				{
					const unsigned int den = 10;
					unsigned long div = mant / den;
					if(static_cast<unsigned int>(mant) == static_cast<unsigned int>(div * den))
					{
						mant = div;
						power--;
					}
				}

				flags |= static_cast<unsigned int>(power) << ScaleShift;
				result.Low64(mant);
			}

			result.uflags = flags;
		}

		/// Convert Decimal to float
		static float VarR4FromDec(Decimal const& value)
		{
			return static_cast<float>(VarR8FromDec(value));
		}

		/// Convert Decimal to double
		static double VarR8FromDec(Decimal const& value)
		{
			// Value taken via reverse engineering the double that corresponds to 2^64. (oleaut32 has ds2to64 = DEFDS(0, 0, DBLBIAS + 65, 0))
			const double ds2to64 = 1.8446744073709552e+019;

			double dbl = (static_cast<double>(value.Lo) +
						  static_cast<double>(value.Hi) * ds2to64) / s_doublePowers10[value.Scale()];

			if(value.IsNegative())
				dbl = -dbl;

			return dbl;
		}

		static constexpr int GetHashCode(Decimal const& d)
		{
			if((d.Lo | d.Mid | d.Hi) == 0)return 0;

			unsigned int flags = static_cast<unsigned int>(d.Flags);
			if((flags & ScaleMask) == 0 || (d.Lo & 1) != 0)
				return static_cast<int>(flags ^ d.Hi ^ d.Mid ^ d.Lo);

			int scale = static_cast<unsigned char>(flags >> ScaleShift);
			unsigned int low = d.Lo;
			unsigned long high64 = (static_cast<unsigned long>(d.Hi) << 32) | d.Mid;

			Unscale(low, high64, scale);

			flags = ((flags) & ~ScaleMask) | static_cast<unsigned int>(scale) << ScaleShift;
			return static_cast<int>(flags ^ static_cast<unsigned int>(high64 >> 32) ^ static_cast<unsigned int>(high64) ^ low);
		}

		/// Divides two decimal values.
		/// On return, d1 contains the result of the operation.
		static void VarDecDiv(DecCalc& d1, DecCalc& d2)
		{
			Buf12 bufQuo;
			unsigned int power;
			int curScale;

			int scale = static_cast<signed char>(d1.uflags - d2.uflags >> ScaleShift);
			bool unscale = false;
			unsigned int tmp;

			if((d2.High() | d2.Mid()) == 0)
			{
				// Divisor is only 32 bits.  Easy divide.
				unsigned int den = d2.Low();
				if(den == 0) throw std::overflow_error("DivideByZero");

				bufQuo.Low64(d1.Low64());
				bufQuo.U2 = d1.High();
				unsigned int remainder = Div96By32(bufQuo, den);

				for(;;)
				{
					if(remainder == 0)
					{
						if(scale < 0)
						{
							curScale = std::min(9, -scale);
							goto HaveScale;
						}
						break;
					}

					// We need to unscale if and only if we have a non-zero remainder
					unscale = true;

					// We have computed a quotient based on the natural scale
					// ( <dividend scale> - <divisor scale> ).  We have a non-zero
					// remainder, so now we should increase the scale if possible to
					// include more quotient bits.
					//
					// If it doesn't cause overflow, we'll loop scaling by 10^9 and
					// computing more quotient bits as long as the remainder stays
					// non-zero.  If scaling by that much would cause overflow, we'll
					// drop out of the loop and scale by as much as we can.
					//
					// Scaling by 10^9 will overflow if bufQuo[2].bufQuo[1] >= 2^32 / 10^9
					// = 4.294 967 296.  So the upper limit is bufQuo[2] == 4 and
					// bufQuo[1] == 0.294 967 296 * 2^32 = 1,266,874,889.7+.  Since
					// quotient bits in bufQuo[0] could be all 1's, then 1,266,874,888
					// is the largest value in bufQuo[1] (when bufQuo[2] == 4) that is
					// assured not to overflow.
					if(scale == DEC_SCALE_MAX || (curScale = SearchScale(bufQuo, scale)) == 0)
					{
						// No more scaling to be done, but remainder is non-zero.
						// Round quotient.
						//
						tmp = remainder << 1;
						if(tmp < remainder || tmp >= den && (tmp > den || (bufQuo.U0 & 1) != 0))
							goto RoundUp;
						break;
					}

				HaveScale:
					power = s_powers10[curScale];
					scale += curScale;

					if(IncreaseScale(bufQuo, power) != 0)
						goto ThrowOverflow;

					unsigned long num = UInt32x32To64(remainder, power);
					unsigned int div = static_cast<unsigned int>(num / den);
					remainder = (unsigned int)num - div * den;

					if(!Add32To96(bufQuo, div))
					{
						scale = OverflowUnscale(bufQuo, scale, remainder != 0);
						break;
					}
				} // for (;;)
			}
			else
			{
				// Divisor has bits set in the upper 64 bits.
				//
				// Divisor must be fully normalized (shifted so bit 31 of the most
				// significant unsigned int is 1).  Locate the MSB so we know how much to
				// normalize by.  The dividend will be shifted by the same amount so
				// the quotient is not changed.
				tmp = d2.High();
				if(tmp == 0)
					tmp = d2.Mid();

				curScale = LeadingZeroCount(tmp);

				// Shift both dividend and divisor left by curScale.
				Buf16 bufRem;
				bufRem.Low64(d1.Low64() << curScale);
				bufRem.High64(d1.Mid() + (static_cast<unsigned long>(d1.High()) << 32) >> (32 - curScale));

				unsigned long divisor = d2.Low64() << curScale;

				if(d2.High() == 0)
				{
					// Have a 64-bit divisor in sdlDivisor.  The remainder
					// (currently 96 bits spread over 4 unsigned ints) will be < divisor.
					bufQuo.U1 = Div96By64(*reinterpret_cast<Buf12*>(&bufRem.U1), divisor);
					bufQuo.U0 = Div96By64(*reinterpret_cast<Buf12*>(&bufRem), divisor);

					for(;;)
					{
						if(bufRem.Low64() == 0)
						{
							if(scale < 0)
							{
								curScale = std::min(9, -scale);
								goto HaveScale64;
							}
							break;
						}

						// We need to unscale if and only if we have a non-zero remainder
						unscale = true;

						// Remainder is non-zero.  Scale up quotient and remainder by
						// powers of 10 so we can compute more significant bits.
						if(scale == DEC_SCALE_MAX || (curScale = SearchScale(bufQuo, scale)) == 0)
						{
							// No more scaling to be done, but remainder is non-zero.
							// Round quotient.
							unsigned long tmp64 = bufRem.Low64();
							if(static_cast<long>(tmp64) < 0 || (tmp64 <<= 1) > divisor ||
							   (tmp64 == divisor && (bufQuo.U0 & 1) != 0))
								goto RoundUp;
							break;
						}

					HaveScale64:
						power = s_powers10[curScale];
						scale += curScale;

						if(IncreaseScale(bufQuo, power) != 0)
							goto ThrowOverflow;

						IncreaseScale64(*reinterpret_cast<Buf12*>(&bufRem), power);
						tmp = Div96By64(*reinterpret_cast<Buf12*>(&bufRem), divisor);
						if(!Add32To96(bufQuo, tmp))
						{
							scale = OverflowUnscale(bufQuo, scale, bufRem.Low64() != 0);
							break;
						}
					} // for (;;)
				}
				else
				{
					// Have a 96-bit divisor in bufDivisor.
					//
					// Start by finishing the shift left by curScale.
					Buf12 bufDivisor;
					bufDivisor.Low64(divisor);
					bufDivisor.U2 = static_cast<unsigned int>((d2.Mid() + (static_cast<unsigned long>(d2.High()) << 32)) >> (32 - curScale));

					// The remainder (currently 96 bits spread over 4 unsigned ints) will be < divisor.
					//
					bufQuo.Low64(Div128By96(bufRem, bufDivisor));

					for(;;)
					{
						if((bufRem.Low64() | bufRem.U2) == 0)
						{
							if(scale < 0)
							{
								curScale = std::min(9, -scale);
								goto HaveScale96;
							}
							break;
						}

						// We need to unscale if and only if we have a non-zero remainder
						unscale = true;

						// Remainder is non-zero.  Scale up quotient and remainder by
						// powers of 10 so we can compute more significant bits.
						//
						if(scale == DEC_SCALE_MAX || (curScale = SearchScale(bufQuo, scale)) == 0)
						{
							// No more scaling to be done, but remainder is non-zero.
							// Round quotient.
							//
							if((int)bufRem.U2 < 0)
							{
								goto RoundUp;
							}

							tmp = bufRem.U1 >> 31;
							bufRem.Low64(bufRem.Low64() << 1);		// Same as <<=
							bufRem.U2 = (bufRem.U2 << 1) + tmp;

							if(bufRem.U2 > bufDivisor.U2 || bufRem.U2 == bufDivisor.U2 &&
							   (bufRem.Low64() > bufDivisor.Low64() || bufRem.Low64() == bufDivisor.Low64() && (bufQuo.U0 & 1) != 0))
								goto RoundUp;
							break;
						}

					HaveScale96:
						power = s_powers10[curScale];
						scale += curScale;

						if(IncreaseScale(bufQuo, power) != 0)
							goto ThrowOverflow;

						bufRem.U3 = IncreaseScale(*reinterpret_cast<Buf12*>(&bufRem), power);
						tmp = Div128By96(bufRem, bufDivisor);
						if(!Add32To96(bufQuo, tmp))
						{
							scale = OverflowUnscale(bufQuo, scale, (bufRem.Low64() | bufRem.High64()) != 0);
							break;
						}
					} // for (;;)
				}
			}

		Unscale:
			if(unscale)
			{
				unsigned int low = bufQuo.U0;
				unsigned long high64 = bufQuo.High64();
				Unscale(low, high64, scale);
				d1.Low(low);
				d1.Mid(static_cast<unsigned int>(high64));
				d1.High(static_cast<unsigned int>(high64 >> 32));
			}
			else
			{
				d1.Low64(bufQuo.Low64());
				d1.High(bufQuo.U2);
			}

			d1.uflags = ((d1.uflags ^ d2.uflags) & SignMask) | (static_cast<unsigned int>(scale) << ScaleShift);
			return;

		RoundUp:
			{
				auto actual = bufQuo.Low64() + 1;
				bufQuo.Low64(actual);
				if(bufQuo.Low64() == 0 && ++bufQuo.U2 == 0)
				{
					scale = OverflowUnscale(bufQuo, scale, true);
				}
				goto Unscale;
			}

		ThrowOverflow:
			throw std::overflow_error("Decimal");
		}

		static void VarDecModFull(DecCalc& d1, DecCalc& d2, int scale)
		{
			// Divisor has bits set in the upper 64 bits.
			//
			// Divisor must be fully normalized (shifted so bit 31 of the most significant unsigned int is 1). 
			// Locate the MSB so we know how much to normalize by. 
			// The dividend will be shifted by the same amount so the quotient is not changed.
			unsigned int tmp = d2.High();
			if(tmp == 0)
				tmp = d2.Mid();
			int shift = LeadingZeroCount(tmp);

			Buf28 b;
			b.Buf24.Low64(d1.Low64() << shift);
			b.Buf24.Mid64(d1.Mid() + (static_cast<unsigned long>(d1.High()) << 32) >> (32 - shift));

			// The dividend might need to be scaled up to 221 significant bits.
			// Maximum scaling is required when the divisor is 2^64 with scale 28 and is left shifted 31 bits
			// and the dividend is decimal.MaxValue: (2^96 - 1) * 10^28 << 31 = 221 bits.
			unsigned int high = 3;
			while(scale < 0)
			{
				unsigned int power = scale <= -MaxInt32Scale ? TenToPowerNine : s_powers10[-scale];
				unsigned int* buf = (unsigned int*)&b;
				unsigned long tmp64 = UInt32x32To64(b.Buf24.U0, power);
				b.Buf24.U0 = static_cast<unsigned int>(tmp64);
				for(int i = 1; i <= high; i++)
				{
					tmp64 >>= 32;
					tmp64 += UInt32x32To64(buf[i], power);
					buf[i] = static_cast<unsigned int>(tmp64);
				}
				// The high bit of the dividend must not be set.
				if(tmp64 > INT_MAX)
				{
					assert(high + 1 < b.Length);
					buf[++high] = static_cast<unsigned int>(tmp64 >> 32);
				}

				scale += MaxInt32Scale;
			}

			if(d2.High() == 0)
			{
				unsigned long divisor = d2.Low64() << shift;
				switch(high)
				{
					case 6:
						Div96By64(*reinterpret_cast<Buf12*>(&b.Buf24.U4), divisor);
						Div96By64(*reinterpret_cast<Buf12*>(&b.Buf24.U3), divisor);
						Div96By64(*reinterpret_cast<Buf12*>(&b.Buf24.U2), divisor);
					case 5:
						Div96By64(*reinterpret_cast<Buf12*>(&b.Buf24.U3), divisor);
						Div96By64(*reinterpret_cast<Buf12*>(&b.Buf24.U2), divisor);
					case 4:
						Div96By64(*reinterpret_cast<Buf12*>(&b.Buf24.U2), divisor);
						break;
				}
				Div96By64(*reinterpret_cast<Buf12*>(&b.Buf24.U1), divisor);
				Div96By64(*reinterpret_cast<Buf12*>(&b), divisor);

				d1.Low64(b.Buf24.Low64() >> shift);
				d1.High(0);
			}
			else
			{
				Buf12 bufDivisor;
				bufDivisor.Low64(d2.Low64() << shift);
				bufDivisor.U2 = static_cast<unsigned int>((d2.Mid() + (static_cast<unsigned long>(d2.High()) << 32)) >> (32 - shift));

				switch(high)
				{
					case 6:
						Div128By96(*reinterpret_cast<Buf16*>(&b.Buf24.U3), bufDivisor);
						Div128By96(*reinterpret_cast<Buf16*>(&b.Buf24.U2), bufDivisor);
						Div128By96(*reinterpret_cast<Buf16*>(&b.Buf24.U1), bufDivisor);
					case 5:
						Div128By96(*reinterpret_cast<Buf16*>(&b.Buf24.U2), bufDivisor);
						Div128By96(*reinterpret_cast<Buf16*>(&b.Buf24.U1), bufDivisor);
					case 4:
						Div128By96(*reinterpret_cast<Buf16*>(&b.Buf24.U1), bufDivisor);
						break;
				}
				Div128By96(*reinterpret_cast<Buf16*>(&b), bufDivisor);

				d1.Low64((b.Buf24.Low64() >> shift) + static_cast<unsigned long>(b.Buf24.U2) << (32 - shift) << 32);
				d1.High(b.Buf24.U2 >> shift);
			}
		}

		/// Computes the remainder between two decimals.
		/// On return, d1 contains the result of the operation and d2 is trashed.
		static void VarDecMod(DecCalc& d1, DecCalc& d2)
		{
			if((d2.ulo | d2.umid | d2.uhi) == 0) throw std::overflow_error("DivideByZero");

			if((d1.ulo | d1.umid | d1.uhi) == 0)
				return;

			// In the operation x % y the sign of y does not matter. Result will have the sign of x.
			d2.uflags = (d2.uflags & ~SignMask) | (d1.uflags & SignMask);

			int cmp = VarDecCmpSub(*reinterpret_cast<Decimal*>(&d1), *reinterpret_cast<Decimal*>(&d2));
			if(cmp == 0)
			{
				d1.ulo = 0;
				d1.umid = 0;
				d1.uhi = 0;
				if(d2.uflags > d1.uflags)
					d1.uflags = d2.uflags;
				return;
			}
			if((cmp ^ static_cast<int>(d1.uflags & SignMask)) < 0)
				return;

			// The divisor is smaller than the dividend and both are non-zero. Calculate the integer remainder using the larger scaling factor. 
			int scale = static_cast<signed char>(d1.uflags - d2.uflags >> ScaleShift);
			if(scale > 0)
			{
				// Divisor scale can always be increased to dividend scale for remainder calculation.
				do
				{
					unsigned int power = scale >= MaxInt32Scale ? TenToPowerNine : s_powers10[scale];
					unsigned long tmp = UInt32x32To64(d2.Low(), power);
					d2.Low(static_cast<unsigned int>(tmp));
					tmp >>= 32;
					tmp += (d2.Mid() + (static_cast<unsigned long>(d2.High()) << 32)) * power;
					d2.Mid(static_cast<unsigned int>(tmp));
					d2.High(static_cast<unsigned int>(tmp >> 32));
				} while((scale -= MaxInt32Scale) > 0);
				scale = 0;
			}

			do
			{
				if(scale < 0)
				{
					d1.uflags = d2.uflags;
					// Try to scale up dividend to match divisor.
					Buf12 bufQuo;
					bufQuo.Low64(d1.Low64());
					bufQuo.U2 = d1.High();
					do
					{
						int iCurScale = SearchScale(bufQuo, DEC_SCALE_MAX + scale);
						if(iCurScale == 0)
							break;
						unsigned int power = iCurScale >= MaxInt32Scale ? TenToPowerNine : s_powers10[iCurScale];
						scale += iCurScale;
						unsigned long tmp = UInt32x32To64(bufQuo.U0, power);
						bufQuo.U0 = static_cast<unsigned int>(tmp);
						tmp >>= 32;
						bufQuo.High64(tmp + bufQuo.High64() * power);
						if(power != TenToPowerNine)
							break;
					} while(scale < 0);
					d1.Low64(bufQuo.Low64());
					d1.High(bufQuo.U2);
				}

				if(d1.High() == 0)
				{
					assert(d2.High() == 0);
					assert(scale == 0);
					d1.Low64(d1.Low64() % d2.Low64());
					return;
				}
				else if((d2.High() | d2.Mid()) == 0)
				{
					unsigned int den = d2.Low();
					unsigned long tmp = (static_cast<unsigned long>(d1.High()) << 32) | d1.Mid();
					tmp = ((tmp % den) << 32) | d1.Low();
					d1.Low64(tmp % den);
					d1.High(0);
				}
				else
				{
					VarDecModFull(d1, d2, scale);
					return;
				}
			} while(scale < 0);
		}
	};

	constexpr Decimal(int lo, int mid, int hi, int flags)
	{
		if(IsValid(flags))
		{
			ULOMIDLE = 0;

			Lo = lo;
			Mid = mid;
			Hi = hi;
			Flags = flags;
			return;
		}

		throw std::invalid_argument("DecBitCtor");
	}

	static inline constexpr DecCalc& AsMutable(Decimal& d) noexcept { return *reinterpret_cast<DecCalc*>(&d); }

	static inline constexpr Decimal Abs(Decimal d) { return Decimal(d.Lo, d.Mid, d.Hi, d.Flags & ~SignMask); }

	static constexpr void GetBytes(Decimal& d, unsigned char buffer[]) noexcept
	{
		assert(buffer != nullptr && ArraySize(buffer) >= 16);
		buffer[0] = static_cast<unsigned char>(d.Lo);
		buffer[1] = static_cast<unsigned char>(d.Lo >> 8);
		buffer[2] = static_cast<unsigned char>(d.Lo >> 16);
		buffer[3] = static_cast<unsigned char>(d.Lo >> 24);
		buffer[4] = static_cast<unsigned char>(d.Mid);
		buffer[5] = static_cast<unsigned char>(d.Mid >> 8);
		buffer[6] = static_cast<unsigned char>(d.Mid >> 16);
		buffer[7] = static_cast<unsigned char>(d.Mid >> 24);
		buffer[8] = static_cast<unsigned char>(d.Hi);
		buffer[9] = static_cast<unsigned char>(d.Hi >> 8);
		buffer[10] = static_cast<unsigned char>(d.Hi >> 16);
		buffer[11] = static_cast<unsigned char>(d.Hi >> 24);
		buffer[12] = static_cast<unsigned char>(d.Flags);
		buffer[13] = static_cast<unsigned char>(d.Flags >> 8);
		buffer[14] = static_cast<unsigned char>(d.Flags >> 16);
		buffer[15] = static_cast<unsigned char>(d.Flags >> 24);
	}

	/*
	 * This method does a 'raw' and 'unchecked' addition of a UInt32 to a Decimal in place.
	 * 'raw' means that it operates on the internal 96-bit unsigned integer value and
	 * ingores the sign and scale. This means that it is not equivalent to just adding
	 * that number, as the sign and scale are effectively applied to the UInt32 value also.
	 * 'unchecked' means that it does not fail if you overflow the 96 bit value.
	 */
	static void InternalAddUInt32RawUnchecked(Decimal& value, unsigned int i)
	{
		unsigned int v;
		unsigned int sum;
		v = static_cast<unsigned int>(value.Lo);
		sum = v + i;
		value.Lo = static_cast<unsigned int>(sum);
		if(sum < v || sum < i)
		{
			v = static_cast<unsigned int>(value.Mid);
			sum = v + 1;
			value.Mid = static_cast<unsigned int>(sum);
			if(sum < v || sum < 1)
			{
				value.Hi = static_cast<int>(static_cast<unsigned int>(value.Hi) + 1);
			}
		}
	}

	static inline constexpr bool IsValid(int flags) noexcept
	{
		return (flags & ~(SignMask | ScaleMask)) == 0 && (static_cast<unsigned int>(flags & ScaleMask) <= (28 << ScaleShift));
	}

	inline constexpr unsigned long Low64() noexcept { return BitConverter::IsLittleEndian ? static_cast<unsigned long long>(ULOMIDLE) : (static_cast<unsigned long long>(Mid) << 32) | Lo; }

	static Decimal PrivateRound(Decimal& d, int decimals, MidPointRounding mode)
	{
		if(static_cast<unsigned int>(decimals) > 28) throw std::invalid_argument("Scale should not be larger than 28");

		int scale = d.Scale() - decimals;
		if(scale > 0) DecCalc::InternalRound(AsMutable(d), static_cast<unsigned int>(scale), static_cast<RoundingMode>(mode));
		return d;
	}

	constexpr void SetBits(int bits[])
	{
		if(bits == nullptr) throw std::invalid_argument("bits");

		auto arraySize = (sizeof(bits) / sizeof(bits[0]));

		if(arraySize == 4)
		{
			int f = bits[3];
			if(IsValid(f))
			{
				Lo = bits[0];
				Mid = bits[1];
				Hi = bits[2];
				Flags = f;
				return;
			}
		}

		throw std::invalid_argument("bits must contain the size of 4 ints");
	}

	static constexpr void TruncateSelf(Decimal& d) noexcept
	{
		int flags = d.Flags;
		if((flags & ScaleMask) != 0)
			DecCalc::InternalRound(AsMutable(d), static_cast<unsigned char>(flags >> ScaleShift), RoundingMode::Truncate);
	}

public:

	constexpr Decimal() noexcept
		:
		Lo(0),
		Mid(0),
		Hi(0),
		Flags(0)
	{}

	constexpr Decimal(int value) noexcept
		:
		Mid(0),
		Hi(0)
	{
		int value_copy = value;
		if(value_copy >= 0)
		{
			Flags = 0;
		}
		else
		{
			Flags = SignMask;
			value_copy = -value_copy;
		}
		Lo = value_copy;
	}

	constexpr Decimal(unsigned int value) noexcept
		:
		Lo(static_cast<int>(value)),
		Mid(0),
		Hi(0),
		Flags(0)
	{}

	constexpr Decimal(long value) noexcept
		:
		Hi(0)
	{
		long value_copy = value;
		if(value_copy >= 0)
		{
			Flags = 0;
		}
		else
		{
			Flags = SignMask;
			value_copy = -value_copy;
		}
		Lo = static_cast<int>(value_copy);
		Mid = static_cast<int>(value_copy >> 32);
	}

	constexpr Decimal(unsigned long value) noexcept
		:
		Flags(0),
		Lo(static_cast<int>(value)),
		Mid(static_cast<int>(value) >> 32),
		Hi(0)
	{}

	constexpr Decimal(float value) noexcept
	{
		DecCalc::VarDecFromR4(value, AsMutable(*this));
	}

	constexpr Decimal(double value) noexcept
	{
		DecCalc::VarDecFromR8(value, AsMutable(*this));
	}

	/*
	 * Constructs a Decimal from an integer array containing a binary
	 * representation. The bits argument must be a non-null integer
	 * array with four elements. bits[0], bits[1], and
	 * bits[2] contain the low, middle, and high 32 bits of the 96-bit
	 * integer part of the Decimal. bits[3] contains the scale factor
	 * and sign of the Decimal: bits 0-15 (the lower word) are unused and must
	 * be zero; bits 16-23 must contain a value between 0 and 28, indicating
	 * the power of 10 to divide the 96-bit integer part by to produce the
	 * Decimal value; bits 24-30 are unused and must be zero; and finally bit
	 * 31 indicates the sign of the Decimal value, 0 meaning positive and 1
	 * meaning negative.
	 *
	 * Note that there are several possible binary representations for the
	 * same numeric value. For example, the value 1 can be represented as {1,
	 * 0, 0, 0} (integer value 1 with a scale factor of 0) and equally well as
	 * {1000, 0, 0, 0x30000} (integer value 1000 with a scale factor of 3).
	 * The possible binary representations of a particular value are all
	 * equally valid, and all are numerically equivalent.
	*/
	constexpr Decimal(int bits[]) noexcept
		:
		Lo(0),
		Mid(0),
		Hi(0),
		Flags(0)
	{
		SetBits(bits);
	}

	constexpr Decimal(int lo, int mid, int hi, bool isNegative, unsigned char scale) noexcept
	{
		if(scale > 28) throw std::out_of_range("scale cannot be large than 28");
		Lo = lo;
		Mid = mid;
		Hi = hi;
		Flags = static_cast<int>(scale) << 16;
		if(isNegative) Flags |= SignMask;
	}

	constexpr operator unsigned char() const { return ToByte(*this); }
	constexpr operator signed char() const { return ToSByte(*this); }
	constexpr operator char() const
	{
		unsigned short temp;
		try
		{
			temp = ToUInt16(*this);
		}
		catch(const std::overflow_error& ex)
		{
			throw std::overflow_error(ex);
		}

		return static_cast<char>(temp);
	}

	constexpr operator short() const { return ToInt16(*this); }
	constexpr operator unsigned short() const { return ToUInt16(*this); }
	constexpr operator int() const { return ToInt32(*this); }
	constexpr operator unsigned int() const { return ToUInt32(*this); }
	constexpr operator long long() const { return ToInt64(*this); }
	constexpr operator unsigned long long() const { return ToUInt64(*this); }
	constexpr operator float() const { return ToFloat(*this); }
	constexpr operator double() const { return ToDouble(*this); }

	/*
	 * Operator+ (Unary Plus -> Does not change value)
	 */
	constexpr Decimal const& operator+() const noexcept
	{
		return *this;
	}

	/*
	 * Operator- (Unary Minus -> Changes the sign of value)
	 */
	constexpr Decimal operator-() const noexcept
	{
		return Decimal(Lo, Mid, Hi, Flags ^ SignMask);
	}

	/*
	 * Operator++ (Prefix increment)
	 */
	constexpr Decimal& operator++() noexcept
	{
		auto ret = Decimal::Add(*this, Decimal::One());

		Lo = ret.Lo;
		Mid = ret.Mid;
		Hi = ret.Hi;
		Flags = ret.Flags;

		return *this;
	}

	/*
	 * Operator-- (Prefix decrement)
	 */
	constexpr Decimal& operator--() noexcept
	{
		auto ret = Decimal::Subtract(*this, Decimal::One());

		Lo = ret.Lo;
		Mid = ret.Mid;
		Hi = ret.Hi;
		Flags = ret.Flags;

		return *this;
	}

	/*
 * Operator+= (Addition assignment)
 */
	constexpr Decimal& operator+=(Decimal& other)
	{
		DecCalc::DecAddSub(AsMutable(*this), AsMutable(other), false);
		return *this;
	}

	/*
	 * Operator-= (Subtraction assignment)
	 */
	constexpr Decimal& operator-=(Decimal& other)
	{
		DecCalc::DecAddSub(AsMutable(*this), AsMutable(other), true);
		return *this;
	}

	/*
	 * Operator*= (Multiplication assignment)
	 */
	constexpr Decimal& operator*=(Decimal& other)
	{
		DecCalc::VarDecMul(AsMutable(*this), AsMutable(other));
		return *this;
	}

	/*
	 * Operator/= (Division assignment)
	 */
	constexpr Decimal& operator/=(Decimal& other)
	{
		DecCalc::VarDecDiv(AsMutable(*this), AsMutable(other));
		return *this;
	}

	/*
	 * Operator%= (Modulo assignment)
	 */
	constexpr Decimal& operator%=(Decimal& other)
	{
		DecCalc::VarDecMod(AsMutable(*this), AsMutable(other));
		return *this;
	}

	/*
	 * Operator+ (Addition)
	 */
	constexpr Decimal operator+(Decimal& other) noexcept
	{
		Decimal lhs = *this;
		DecCalc::DecAddSub(AsMutable(lhs), AsMutable(other), false);
		return lhs;
	}

	/*
	 * Operator- (Subtraction)
	 */
	constexpr Decimal operator-(Decimal& other) noexcept
	{
		Decimal lhs = *this;
		DecCalc::DecAddSub(AsMutable(lhs), AsMutable(other), true);
		return lhs;
	}

	/*
	* Operator* (Multiplication)
	*/
	constexpr Decimal operator*(Decimal& other) noexcept
	{
		Decimal lhs = *this;
		DecCalc::VarDecMul(AsMutable(lhs), AsMutable(other));
		return lhs;
	}

	/*
	* Operator/ (Division)
	*/
	constexpr Decimal operator/(Decimal& other)
	{
		Decimal lhs = *this;
		DecCalc::VarDecDiv(AsMutable(lhs), AsMutable(other));
		return lhs;
	}

	/*
	 * Operator% (Modulo)
	 */
	constexpr Decimal operator%(Decimal& other)
	{
		Decimal lhs = *this;
		DecCalc::VarDecMod(AsMutable(lhs), AsMutable(other));
		return lhs;
	}

	/*
	 * Operator== (Equality)
	 */
	inline constexpr bool operator==(Decimal& other) const noexcept { return DecCalc::VarDecCmp(*this, other) == 0; }

	/*
	 * Operator!= (Inequality)
	 */
	inline constexpr bool operator!=(Decimal& other) const noexcept { return !(*this == other); }

	/*
	 * Operator< (Less Than)
	 */
	inline constexpr bool operator<(Decimal& other) const noexcept { return DecCalc::VarDecCmp(*this, other) < 0; }

	/*
	 * Operator<= (Less Than or Equal to )
	 */
	inline constexpr bool operator<=(Decimal& other) const noexcept { return DecCalc::VarDecCmp(*this, other) <= 0; }

	/*
	 * Operator> (Greater than)
	 */
	inline constexpr bool operator>(Decimal& other) const noexcept { return DecCalc::VarDecCmp(*this, other) > 0; }

	/*
	 * Operator>= (Greater Than or Equal to )
	 */
	inline constexpr bool operator>=(Decimal& other) const noexcept { return DecCalc::VarDecCmp(*this, other) >= 0; }


	static constexpr Decimal Add(Decimal d1, Decimal d2)
	{
		DecCalc::DecAddSub(AsMutable(d1), AsMutable(d2), false);
		return d1;
	}

	static constexpr Decimal Ceiling(Decimal d)
	{
		int flags = d.Flags;
		if((flags & ScaleMask) != 0) DecCalc::InternalRound(AsMutable(d), static_cast<unsigned char>(flags >> ScaleShift), RoundingMode::Ceiling);
		return d;
	}

	static constexpr Decimal Divide(Decimal d1, Decimal d2)
	{
		DecCalc::VarDecDiv(AsMutable(d1), AsMutable(d2));
		return d1;
	}

	static constexpr Array<int> GetBits(Decimal& d) noexcept { return { d.Lo, d.Mid, d.Hi, d.Flags }; }

	constexpr int GetHashCode() const noexcept { return DecCalc::GetHashCode(*this); }

	static constexpr Decimal Floor(Decimal d)
	{
		int flags = d.Flags;
		if((flags & ScaleMask) != 0) DecCalc::InternalRound(AsMutable(d), static_cast<unsigned char>(flags >> ScaleShift), RoundingMode::Floor);
		return d;
	}

	static constexpr Decimal& Max(Decimal& d1, Decimal& d2) noexcept
	{
		return DecCalc::VarDecCmp(d1, d2) > 0 ? d1 : d2;
	}

	static constexpr Decimal& Min(Decimal& d1, Decimal& d2) noexcept
	{
		return DecCalc::VarDecCmp(d1, d2) < 0 ? d1 : d2;
	}

	static constexpr Decimal Multiply(Decimal d1, Decimal d2) noexcept
	{
		DecCalc::VarDecMul(AsMutable(d1), AsMutable(d2));
		return d1;
	}

	static constexpr Decimal Negate(Decimal& d)
	{
		return Decimal(d.Lo, d.Mid, d.Hi, d.Flags ^ SignMask);
	}

	static constexpr Decimal Remainder(Decimal d1, Decimal d2)
	{
		DecCalc::VarDecMod(AsMutable(d1), AsMutable(d2));
		return d1;
	}

	static constexpr Decimal Round(Decimal d) { return PrivateRound(d, 0, MidPointRounding::ToEven); }
	static constexpr Decimal Round(Decimal d, int decimals) { return PrivateRound(d, decimals, MidPointRounding::ToEven); }
	static constexpr Decimal Round(Decimal d, MidPointRounding mode) { return PrivateRound(d, 0, mode); }
	static constexpr Decimal Round(Decimal d, int decimals, MidPointRounding mode) { return PrivateRound(d, decimals, mode); }

	static constexpr int Sign(Decimal const& d) noexcept { return (d.Lo | d.Mid | d.Hi) == 0 ? 0 : (d.Flags >> 31) | 1; }

	static constexpr Decimal Subtract(Decimal d1, Decimal d2)
	{
		DecCalc::DecAddSub(AsMutable(d1), AsMutable(d2), true);
		return d1;
	}

	static Decimal Parse(String s);
	static Decimal Parse(String s, NumberStyles style);
	static Byte	ToByte(Decimal value);

	static Decimal ToDecimal(const unsigned char buffer[])
	{
		assert(buffer != nullptr && ArraySize(buffer) >= 16);

		int lo = static_cast<int>(buffer[0]) | static_cast<int>(buffer[1]) << 8 | static_cast<int>(buffer[2]) << 16 | static_cast<int>(buffer[3]) << 24;
		int mid = static_cast<int>(buffer[4]) | static_cast<int>(buffer[5]) << 8 | static_cast<int>(buffer[6]) << 16 | static_cast<int>(buffer[7]) << 24;
		int hi = static_cast<int>(buffer[8]) | static_cast<int>(buffer[9]) << 8 | static_cast<int>(buffer[10]) << 16 | static_cast<int>(buffer[11]) << 24;
		int flags = static_cast<int>(buffer[12]) | static_cast<int>(buffer[13]) << 8 | static_cast<int>(buffer[14]) << 16 | static_cast<int>(buffer[15]) << 24;

		return Decimal(lo, mid, hi, flags);
	}

	static Double ToDouble(Decimal value);
	static Single ToFloat(Decimal value);
	static Int16 ToInt16(Decimal value);
	static Int32 ToInt32(Decimal value);
	static Int64 ToInt64(Decimal value);
	static SByte ToSByte(Decimal value);
	String ToString();
	String ToString(String const& format);
	static UInt16 ToUInt16(Decimal value);
	static UInt32 ToUInt32(Decimal value);
	static UInt64 ToUInt64(Decimal value);

	static constexpr Decimal Truncate(Decimal value) noexcept
	{
		TruncateSelf(value);
		return value;
	}

	static Boolean TryParse(String s, Decimal& result);
	static Boolean TryParse(String s, NumberStyles style, Decimal& result);
};

typedef Decimal decimal;

#endif //CPPDATASTRUCTURES_DECIMAL_H
