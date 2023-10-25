#include "BitConverter.h"

namespace BitConverter
{
	String ToString(unsigned char* value, int startIndex, int length)
	{
		if(value == nullptr) throw std::invalid_argument("value is null");
		if(length < 0) throw std::invalid_argument("length is 0");

		int size = ArraySize(value); // Declared as int to remove the necessity of casting size_t to ssize_t below

		// Don't throw for a 0 length array
		if(startIndex < 0 || (startIndex > 0 && startIndex >= size)) throw std::out_of_range("startIndex is out of range");
		if(startIndex > size - length) throw std::invalid_argument("ArrayPlusOffTooSmall");

		if(length == 0) return "";
		if(length > (INT_MAX / 3))
		{
			// (Int32.MaxValue / 3) == 715,827,882 Bytes == 699 MB
			throw std::out_of_range("Length is too large");
		}

		int chArrayLength = length * 3;
		// As String can easily occupy more than the Stack size,
		// we will be using the Heap for it
		char* chArray = new char[chArrayLength];
		int index = startIndex;
		for(size_t i = 0; i < chArrayLength; i += 3)
		{
			unsigned char b = value[index++];
			chArray[i] = GetHexValue(b / 16);
			chArray[i + 1] = GetHexValue(b % 16);

			// Push the '-' char until the last time.
			// If don't do this, we will occupy a lot more memory to instantiate a second string
			// just to remove the last char from it
			if(i < (chArrayLength - 1))
				chArray[i + 2] = '-';
		}

		String ret(chArray);
		delete[] chArray;
		return ret;
	}

	String ToString(unsigned char* value)
	{
		if(value == nullptr) throw std::invalid_argument("value is null");
		return ToString(value, 0, ArraySize(value));
	}

	String ToString(unsigned char* value, int startIndex)
	{
		if(value == nullptr) throw std::invalid_argument("value is null");
		return ToString(value, startIndex, ArraySize(value) - startIndex);
	}
}