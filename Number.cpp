//
// Created by bcfrutuozo on 04/04/2022.
//

#include "Number.h"
#include "Boolean.h"
#include "Char.h"
#include "Int64.h"
#include "UInt32.h"
#include "UInt64.h"

namespace Number {

    NumberBuffer::NumberBuffer(Byte* stackBuffer) noexcept
        :
        BaseAddress(stackBuffer),
        Digits(((Char*) stackBuffer) + 6),
        Precision(0),
        Scale(0),
        Sign(false)
    {}

    Byte *NumberBuffer::PackForNative() noexcept {
        Int32* baseInteger = (Int32*) BaseAddress;
        baseInteger[0] = Precision;
        baseInteger[1] = Scale;
        baseInteger[2] = Sign ? 1 : 0;
        return BaseAddress;
    }

    Boolean NumberBuffer::HexNumberToInt32(NumberBuffer const& number, Int32& value) noexcept {
        UInt32 passedValue = 0;
        Boolean returnValue = HexNumberToUInt32(number, passedValue);
        value = static_cast<Int32>(passedValue);
        return returnValue;
    }

    Boolean NumberBuffer::HexNumberToInt64(NumberBuffer const& number, Int64& value) noexcept {
        UInt64 passedValue = 0;
        Boolean returnValue = HexNumberToUInt64(number, passedValue);
        value = static_cast<Int64>(passedValue);
        return returnValue;
    }

    Boolean NumberBuffer::HexNumberToUInt32(NumberBuffer const& number, UInt32& value) noexcept {
        Int32 i = number.Scale;
        if(i > UInt32Precision || i < number.Precision) return false;

        Char* p = number.Digits;
        assert(p != nullptr);

        UInt32 n = 0;
        while(--i >= 0) {
            if(n > ((UInt32)0xFFFFFFFF / 16)) return false;

            n *= 16;
            if(*p != '\0') {
                UInt32 newN = n;
                if(*p != '\0') {
                    if(*p >= '0' && *p <= '9') {
                        newN += static_cast<UInt32>(*p - '0');
                    } else {
                        if(*p >= 'A' && *p <= 'F') {
                            newN += static_cast<UInt32>((*p - 'A') + 10);
                        } else {
                            assert(*p >= 'a' && *p <= 'f');
                            newN += static_cast<UInt32>((*p - 'a') + 10);
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

    Boolean NumberBuffer::HexNumberToUInt64(NumberBuffer const& number, UInt64& value) noexcept {
        Int32 i = number.Scale;
        if (i > UInt64Precision || i < number.Precision) {
            return false;
        }
        Char* p = number.Digits;
        assert(p != nullptr);

        UInt64 n = 0;
        while (--i >= 0) {
            if (n > (0xFFFFFFFFFFFFFFFF / 16)) return false;

            n *= 16;
            if (*p != '\0') {
                UInt64 newN = n;
                if (*p != '\0') {
                    if (*p >= '0' && *p <= '9') {
                        newN += static_cast<UInt64>(*p - '0');
                    }
                    else {
                        if (*p >= 'A' && *p <= 'F') {
                            newN += static_cast<UInt64>((*p - 'A') + 10);
                        }
                        else {
                            assert(*p >= 'a' && *p <= 'f');
                            newN += static_cast<UInt64>((*p - 'a') + 10);
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
