//
// Created by bcfrutuozo on 09/04/2022.
//

#ifndef CPPDATASTRUCTURES_BITCONVERTER_H
#define CPPDATASTRUCTURES_BITCONVERTER_H

#include <bit>
#include <cassert>

#include "Array.h"

class String;

namespace BitConverter
{
	static constexpr bool IsLittleEndian = std::endian::native == std::endian::little ? true : false;

	static inline constexpr Array<unsigned char> GetBytes(bool value) noexcept
	{
		return Array<unsigned char>{value ? static_cast<unsigned char>(true) : static_cast<unsigned char>(false)};
	}

	template<typename T, typename = std::enable_if_t<std::is_integral<T>::value && !std::is_same<T, bool>::value>>
	static constexpr Array<unsigned char> GetBytes(T value) noexcept
	{
		Array<unsigned char> bytes(sizeof(T));
		for(size_t i = 0; i < sizeof(T); ++i) { bytes[i] = (value >> (2 * i)) & 0xFF; }
		return bytes;
	}

	static constexpr Array<unsigned char> GetBytes(float value) noexcept
	{
		return GetBytes(*reinterpret_cast<int*>(&value));
	}

	static constexpr Array<unsigned char> GetBytes(double value) noexcept
	{
		return GetBytes(*reinterpret_cast<long*>(&value));
	}

	static constexpr short ToInt16(unsigned char value[], int startIndex)
	{
		if(value == nullptr) throw std::invalid_argument("value is null");
		
		int size = ArraySize(value); // Declared as int to remove the necessity of casting size_t to ssize_t below
		if(static_cast<unsigned int>(startIndex) >= size) throw std::out_of_range("startIndex is out of range");
		if(startIndex > size - sizeof(short)) throw std::invalid_argument("ArrayPlusOffTooSmall");

		unsigned char* pByte = &value[startIndex];
		if(startIndex % 2 == 0)	// Data is aligned
		{
			return *reinterpret_cast<short*>(pByte);
		}
		else
		{
			if(IsLittleEndian) return static_cast<short>((*pByte) | (*(pByte + 1) << 8));
			else return static_cast<short>((*pByte << 8) | (*(pByte + 1)));
		}
	}

	static inline constexpr char ToChar(unsigned char value[], int startIndex)
	{
		return static_cast<char>(ToInt16(value, startIndex));
	}

	static constexpr int ToInt32(unsigned char value[], int startIndex)
	{
		if(value == nullptr) throw std::invalid_argument("value is null");

		int size = ArraySize(value); // Declared as int to remove the necessity of casting size_t to ssize_t below
		if(static_cast<unsigned int>(startIndex) >= size) throw std::out_of_range("startIndex is out of range");
		if(startIndex > size - sizeof(int)) throw std::invalid_argument("ArrayPlusOffTooSmall");

		unsigned char* pByte = &value[startIndex];
		if(startIndex % 4 == 0)	// Data is aligned
		{
			return *reinterpret_cast<int*>(pByte);
		}
		else
		{
			if(IsLittleEndian) return (*pByte) | (*(pByte + 1) << 8) | (*(pByte + 2) << 16) | (*(pByte + 3) << 24);
			else return (*pByte) | (*(pByte + 1) << 8) | (*(pByte + 2) << 16) | (*(pByte + 3) << 24);
		}
	}

	static constexpr int ToInt64(unsigned char value[], int startIndex)
	{
		if(value == nullptr) throw std::invalid_argument("value is null");

		int size = ArraySize(value); // Declared as int to remove the necessity of casting size_t to ssize_t below
		if(static_cast<unsigned int>(startIndex) >= size) throw std::out_of_range("startIndex is out of range");
		if(startIndex > size - sizeof(long)) throw std::invalid_argument("ArrayPlusOffTooSmall");

		unsigned char* pByte = &value[startIndex];
		if(startIndex % 8 == 0)	// Data is aligned
		{
			return *reinterpret_cast<long*>(pByte);
		}
		else
		{
			if(IsLittleEndian)
			{
				int i1 = (*pByte) | (*(pByte + 1) << 8) | (*(pByte + 2) << 16) | (*(pByte + 3) << 24);
				int i2 = (*(pByte + 4)) | (*(pByte + 5) << 8) | (*(pByte + 6) << 16) | (*(pByte + 7) << 24);
				return static_cast<unsigned int>(i1) | (static_cast<long>(i2) << 32);
			}
			else
			{
				int i1 = (*pByte << 24) | (*(pByte + 1) << 16) | (*(pByte + 2) << 8) | (*(pByte + 3));
				int i2 = (*(pByte + 4) << 24) | (*(pByte + 5) << 16) | (*(pByte + 6) << 8) | (*(pByte + 7));
				return static_cast<unsigned int>(i2) | (static_cast<long>(i1) << 32);
			}
		}
	}

	static constexpr unsigned short ToUInt16(unsigned char value[], int startIndex)
	{
		return static_cast<unsigned short>(ToInt16(value, startIndex));
	}

	static constexpr unsigned int ToUInt32(unsigned char value[], int startIndex)
	{
		return static_cast<unsigned int>(ToInt32(value, startIndex));
	}

	static constexpr unsigned long ToUInt64(unsigned char value[], int startIndex)
	{
		return static_cast<unsigned long>(ToInt64(value, startIndex));
	}

	static float ToSingle(unsigned char value[], int startIndex)
	{
		int temp = ToInt32(value, startIndex);
		return *reinterpret_cast<float*>(&temp);
	}

	static float ToDouble(unsigned char value[], int startIndex)
	{
		int temp = ToInt32(value, startIndex);
		return *reinterpret_cast<double*>(&temp);
	}

	static char GetHexValue(int i) noexcept
	{
		assert(i >= 0 && i < 16);
		if(i < 10) return static_cast<char>(i + '0');
		return static_cast<char>(i - 10 + 'A');
	}

	static String ToString(unsigned char value[], int startIndex, int length);

	static String ToString(unsigned char value[]);

	static String ToString(unsigned char value[], int startIndex);

	static constexpr bool ToBoolean(unsigned char value[], int startIndex)
	{
		if(value == nullptr) throw std::invalid_argument("value is null");

		int size = ArraySize(value); // Declared as int to remove the necessity of casting size_t to ssize_t below

		if(startIndex < 0) throw std::out_of_range("startIndex is out of range");
		if(startIndex > size - 1) throw std::invalid_argument("ArrayPlusOffTooSmall");

		return (value[startIndex] == 0) ? false : true;
	}

	static long DoubleToInt64Bits(double value) noexcept
	{
		// This method is implemented assuming little endian with an ambiguous spec
		assert(IsLittleEndian);
		return *reinterpret_cast<long*>(&value);
	}

	static double Int64BitsToDouble(long value) noexcept
	{
		// This method is implemented assuming little endian with an ambiguous spec
		assert(IsLittleEndian);
		return *reinterpret_cast<double*>(&value);
	}
};

#endif //CPPDATASTRUCTURES_BITCONVERTER_H