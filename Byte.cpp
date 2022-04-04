//
// Created by bcfrutuozo on 03/04/2022.
//

#include "Byte.h"
#include "Int32.h"
#include "String.h"

Int32 Byte::GetHashCode() const noexcept {
    return Value;
}

Byte Byte::Parse(String &s) {
    Parse(s, NumberStyles::Integer);
}

Byte Byte::Parse(String& s, NumberStyles style) {
    // Validate number style
    if((style & Byte::InvalidNumberStyle) != 0) throw std::invalid_argument("InvalidNumberStyle");
    if((style & NumberStyles::AllowHexSpecifier) != 0)
        if((style & ~NumberStyles::HexNumber) != 0) throw std::invalid_argument("InvalidHexStyle");

    int i = 0;

}