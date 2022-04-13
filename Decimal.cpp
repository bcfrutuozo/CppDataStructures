//
// Created by bcfrutuozo on 4/9/22.
//

#include "Decimal.h"
#include "Byte.h"
#include "SByte.h"
#include "Double.h"
#include "Float.h"
#include "Int16.h"
#include "Int32.h"
#include "Int64.h"
#include "UInt16.h"
#include "UInt32.h"
#include "UInt64.h"
#include "String.h"
#include "Number.h"
#include "NumberFormatter.hpp"

Decimal Decimal::Parse(String s)
{
	if(s.IsEmpty()) throw std::invalid_argument("String is empty");
	return Number::ParseDecimal(s, NumberStyles::Number);
}

Decimal Decimal::Parse(String s, NumberStyles style)
{
	if(s.IsEmpty()) throw std::invalid_argument("String is empty");
	return Number::ParseDecimal(s, style);
}

uint8_t Decimal::ToByte(Decimal value)
{
	unsigned int temp;
	
	try
	{
		temp = ToUInt32(value);
	}
	catch(const std::overflow_error& ex)
	{
		throw std::overflow_error(ex);
	}

	if(temp != static_cast<unsigned char>(temp)) throw std::overflow_error("Byte");
	return static_cast<unsigned char>(temp);
}

double Decimal::ToDouble(Decimal value)
{
	return DecCalc::VarR8FromDec(value);
}

float Decimal::ToFloat(Decimal value)
{
	return DecCalc::VarR4FromDec(value);
}

int16_t Decimal::ToInt16(Decimal value)
{
	int temp;
	try
	{
		temp = ToInt32(value);
	}
	catch(const std::overflow_error& ex)
	{
		throw std::overflow_error(ex);
	}
	if(temp != static_cast<short>(temp)) throw std::overflow_error("Int16");
	return static_cast<short>(temp);
}

int32_t Decimal::ToInt32(Decimal value)
{
	TruncateSelf(value);

	if((value.Hi | value.Mid) == 0)
	{
		int i = value.Lo;
		if(!value.IsNegative())
		{
			if(i >= 0) return i;
		}
		else
		{
			i = -i;
			if(i <= 0) return i;
		}
	}

	throw std::overflow_error("Int32");
}

int64_t Decimal::ToInt64(Decimal value)
{
	TruncateSelf(value);

	if(value.Hi == 0)
	{
		long long l = static_cast<long long>(value.Low64());
		if(!value.IsNegative())
		{
			if(l >= 0) return l;
		}
		else
		{
			l = -l;
			if(l <= 0) return l;
		}
	}

	throw std::overflow_error("Int64");
}

int8_t Decimal::ToSByte(Decimal value)
{
	int temp;
	try
	{
		temp = ToInt32(value);
	}
	catch(const std::overflow_error& ex)
	{
		throw std::overflow_error(ex);
	}
	if(temp != static_cast<signed char>(temp)) throw std::overflow_error("SByte");
	return static_cast<signed char>(temp);
}

String Decimal::ToString()
{
	return Number::FormatDecimal(*this, "");
}

String Decimal::ToString(String const& format)
{
	return Number::FormatDecimal(*this, format);
}

uint16_t Decimal::ToUInt16(Decimal value)
{
	unsigned int temp;
	try
	{
		temp = ToInt32(value);
	}
	catch(const std::overflow_error& ex)
	{
		throw std::overflow_error(ex);
	}
	if(temp != static_cast<unsigned short>(temp)) throw std::overflow_error("UInt16");
	return static_cast<unsigned short>(temp);
}

uint32_t Decimal::ToUInt32(Decimal value)
{
	TruncateSelf(value);

	if((value.Hi | value.Mid) == 0)
	{
		unsigned int i = value.Lo;
		if(!value.IsNegative() || i == 0) return i;
	}

	throw std::overflow_error("UInt32");
}

uint64_t Decimal::ToUInt64(Decimal value)
{
	TruncateSelf(value);

	if(value.Hi == 0)
	{
		unsigned long long l = value.Low64();
		if(!value.IsNegative() || l == 0) return l;
	}

	throw std::overflow_error("UInt64");
}

bool Decimal::TryParse(String s, Decimal& result)
{
	if(s.IsEmpty()) return false;
	return Number::TryParseDecimal(s, NumberStyles::Number, result);
}

bool Decimal::TryParse(String s, NumberStyles style, Decimal& result)
{
	if(s.IsEmpty()) return false;
	return Number::TryParseDecimal(s, style, result);
}