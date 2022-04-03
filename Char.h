//
// Created by bcfrutuozo on 31/03/2022.
//

#ifndef CPPDATASTRUCTURES_CHAR_H
#define CPPDATASTRUCTURES_CHAR_H

#include <cstdint>
#include <cassert>

#include "TypeValue.h"
#include "Boolean.h"
#include "Byte.h"
#include "Int32.h"
#include "UnicodeCategory.h"
#include "CharUnicodeInfo.h"

class Int16;
class Int32;
class Int64;
class Double;
class Float;
class SByte;
class String;
class UInt16;
class UInt32;
class UInt64;

/*
 * Wrapper to extend the char type
 * This wrapper suffers from a language limitation of string declaration.
 * When trying to declare const Char* (pointing to the wrapper), the compiler cannot
 * receive a const char* from primitives.
 * Char* c = "ABC" -> Fails
 *
 * To declare string, as we are strengthening the typing with Wrappers, we MUST declare
 * a string using ALWAYS the String class.
 */
class Char final {

private:

    char Value;

    // Define the whole Latin1 table based on Unicode category values from U+0000 to U+00FF
    static constexpr Byte CategoryForLatin1[256] = {
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,    // 0000 - 0007
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,    // 0008 - 000F
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,    // 0010 - 0017
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,    // 0018 - 001F
            (uint8_t) UnicodeCategory::SpaceSeparator, (uint8_t) UnicodeCategory::OtherPunctuation,
            (uint8_t) UnicodeCategory::OtherPunctuation, (uint8_t) UnicodeCategory::OtherPunctuation,
            (uint8_t) UnicodeCategory::CurrencySymbol, (uint8_t) UnicodeCategory::OtherPunctuation,
            (uint8_t) UnicodeCategory::OtherPunctuation, (uint8_t) UnicodeCategory::OtherPunctuation,    // 0020 - 0027
            (uint8_t) UnicodeCategory::OpenPunctuation, (uint8_t) UnicodeCategory::ClosePunctuation,
            (uint8_t) UnicodeCategory::OtherPunctuation, (uint8_t) UnicodeCategory::MathSymbol,
            (uint8_t) UnicodeCategory::OtherPunctuation, (uint8_t) UnicodeCategory::DashPunctuation,
            (uint8_t) UnicodeCategory::OtherPunctuation, (uint8_t) UnicodeCategory::OtherPunctuation,    // 0028 - 002F
            (uint8_t) UnicodeCategory::DecimalDigitNumber, (uint8_t) UnicodeCategory::DecimalDigitNumber,
            (uint8_t) UnicodeCategory::DecimalDigitNumber, (uint8_t) UnicodeCategory::DecimalDigitNumber,
            (uint8_t) UnicodeCategory::DecimalDigitNumber, (uint8_t) UnicodeCategory::DecimalDigitNumber,
            (uint8_t) UnicodeCategory::DecimalDigitNumber,
            (uint8_t) UnicodeCategory::DecimalDigitNumber,    // 0030 - 0037
            (uint8_t) UnicodeCategory::DecimalDigitNumber, (uint8_t) UnicodeCategory::DecimalDigitNumber,
            (uint8_t) UnicodeCategory::OtherPunctuation, (uint8_t) UnicodeCategory::OtherPunctuation,
            (uint8_t) UnicodeCategory::MathSymbol, (uint8_t) UnicodeCategory::MathSymbol,
            (uint8_t) UnicodeCategory::MathSymbol, (uint8_t) UnicodeCategory::OtherPunctuation,    // 0038 - 003F
            (uint8_t) UnicodeCategory::OtherPunctuation, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,    // 0040 - 0047
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,    // 0048 - 004F
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,    // 0050 - 0057
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::OpenPunctuation,
            (uint8_t) UnicodeCategory::OtherPunctuation, (uint8_t) UnicodeCategory::ClosePunctuation,
            (uint8_t) UnicodeCategory::ModifierSymbol,
            (uint8_t) UnicodeCategory::ConnectorPunctuation,    // 0058 - 005F
            (uint8_t) UnicodeCategory::ModifierSymbol, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,    // 0060 - 0067
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,    // 0068 - 006F
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,    // 0070 - 0077
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::OpenPunctuation,
            (uint8_t) UnicodeCategory::MathSymbol, (uint8_t) UnicodeCategory::ClosePunctuation,
            (uint8_t) UnicodeCategory::MathSymbol, (uint8_t) UnicodeCategory::Control,    // 0078 - 007F
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,    // 0080 - 0087
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,    // 0088 - 008F
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,    // 0090 - 0097
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,
            (uint8_t) UnicodeCategory::Control, (uint8_t) UnicodeCategory::Control,    // 0098 - 009F
            (uint8_t) UnicodeCategory::SpaceSeparator, (uint8_t) UnicodeCategory::OtherPunctuation,
            (uint8_t) UnicodeCategory::CurrencySymbol, (uint8_t) UnicodeCategory::CurrencySymbol,
            (uint8_t) UnicodeCategory::CurrencySymbol, (uint8_t) UnicodeCategory::CurrencySymbol,
            (uint8_t) UnicodeCategory::OtherSymbol, (uint8_t) UnicodeCategory::OtherSymbol,    // 00A0 - 00A7
            (uint8_t) UnicodeCategory::ModifierSymbol, (uint8_t) UnicodeCategory::OtherSymbol,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::InitialQuotePunctuation,
            (uint8_t) UnicodeCategory::MathSymbol, (uint8_t) UnicodeCategory::DashPunctuation,
            (uint8_t) UnicodeCategory::OtherSymbol, (uint8_t) UnicodeCategory::ModifierSymbol,    // 00A8 - 00AF
            (uint8_t) UnicodeCategory::OtherSymbol, (uint8_t) UnicodeCategory::MathSymbol,
            (uint8_t) UnicodeCategory::OtherNumber, (uint8_t) UnicodeCategory::OtherNumber,
            (uint8_t) UnicodeCategory::ModifierSymbol, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::OtherSymbol, (uint8_t) UnicodeCategory::OtherPunctuation,    // 00B0 - 00B7
            (uint8_t) UnicodeCategory::ModifierSymbol, (uint8_t) UnicodeCategory::OtherNumber,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::FinalQuotePunctuation,
            (uint8_t) UnicodeCategory::OtherNumber, (uint8_t) UnicodeCategory::OtherNumber,
            (uint8_t) UnicodeCategory::OtherNumber, (uint8_t) UnicodeCategory::OtherPunctuation,    // 00B8 - 00BF
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,    // 00C0 - 00C7
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,    // 00C8 - 00CF
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::MathSymbol,    // 00D0 - 00D7
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::UppercaseLetter,
            (uint8_t) UnicodeCategory::UppercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,    // 00D8 - 00DF
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,    // 00E0 - 00E7
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,    // 00E8 - 00EF
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::MathSymbol,    // 00F0 - 00F7
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,
            (uint8_t) UnicodeCategory::LowercaseLetter, (uint8_t) UnicodeCategory::LowercaseLetter,    // 00F8 - 00FF
    };

    static constexpr Boolean CheckLetter(UnicodeCategory uc) noexcept {
        switch (uc) {
            case UnicodeCategory::UppercaseLetter:
            case UnicodeCategory::LowercaseLetter:
            case UnicodeCategory::TitlecaseLetter:
            case UnicodeCategory::ModifierLetter:
            case UnicodeCategory::OtherLetter:
                return true;
        }
        return false;
    }

    static constexpr Boolean CheckLetterOrDigit(UnicodeCategory uc) {
        switch (uc) {
            case UnicodeCategory::UppercaseLetter:
            case UnicodeCategory::LowercaseLetter:
            case UnicodeCategory::TitlecaseLetter:
            case UnicodeCategory::ModifierLetter:
            case UnicodeCategory::OtherLetter:
            case UnicodeCategory::DecimalDigitNumber:
                return true;
        }

        return false;
    }

    static constexpr Boolean CheckPunctuation(UnicodeCategory uc) {
        switch (uc) {
            case UnicodeCategory::ConnectorPunctuation:
            case UnicodeCategory::DashPunctuation:
            case UnicodeCategory::OpenPunctuation:
            case UnicodeCategory::ClosePunctuation:
            case UnicodeCategory::InitialQuotePunctuation:
            case UnicodeCategory::FinalQuotePunctuation:
            case UnicodeCategory::OtherPunctuation:
                return true;
        }
        return false;
    }

    static constexpr UnicodeCategory GetLatin1UnicodeCategory(char ch) noexcept {
        assert(IsLatin1(ch) == true);
        return static_cast<UnicodeCategory>(CategoryForLatin1[(int) ch].GetValue());
    }

    static constexpr Boolean IsLatin1(char ch) noexcept {
        return (ch <= '\x00FF');
    }

    static constexpr Boolean IsASCII(char ch) noexcept {
        return (ch <= '\x007F');
    }

    static Boolean IsWhiteSpaceLatin1(char ch) noexcept {
        /*
         * There are characters which belong to UnicodeCategory.Control but are considered as white spaces.
         * We use code point comparisons for these characters here as a temporary fix.
         * U+0009 = <control> HORIZONTAL TAB
         * U+000a = <control> LINE FEED
         * U+000b = <control> VERTICAL TAB
         * U+000c = <control> FORM FEED
         * U+000d = <control> CARRIAGE RETURN
         * U+0085 = <control> NEXT LINE
         * U+00a0 = NO-BREAK SPACE
         */
        if ((ch == ' ') || (ch >= '\x0009' && ch <= -'\x000d') || ch == '\x00a0' || ch == '\x0085')
            return true;
        return false;
    }

public:

    //<editor-fold desc="Primitive abstraction section">

    using value_type = char;

    constexpr char const& GetValue() const noexcept { return Value; }

    constexpr Char() : Value() {};

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Char(T value) noexcept requires(is_promotion_primitive<T>::value) : Value((value)) {}

    /*
     * Constructor which receives another Wrapper
     * It's implicit because if you pass another wrapper without setting it, it'll cast to primitive
     * by its operator T() function
     */
    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr explicit Char(T const& wrapper) noexcept requires(is_promotion_wrapper<T>::value) : Value(wrapper) {}

    constexpr Char(Char const &) = default;

    constexpr Char(Char &&) = default;

    constexpr Char &operator=(Char const &) = default;

    constexpr Char &operator=(Char &&) = default;

    /*
     * Operator= (Assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Char& operator=(T const& value) noexcept requires(is_promotion_primitive<T>::value) { Value = value; return *this; };

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr Char& operator=(T const& wrapper) noexcept requires(is_promotion_wrapper<T>::value) { Value = wrapper.GetValue(); return *this; };

    /*
     * Implicit use of between Primitive and Wrapper
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr operator T() noexcept requires(is_promotion_primitive<T>::value) { return Value; };

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr operator T() noexcept requires(is_promotion_wrapper<T>::value) { return Value; };

    /*
     * Operator+ (Unary Plus -> Does not change value)
     */
    constexpr Char const& operator+() const noexcept {
        return *this;
    }

    /*
     * Operator- (Unary Minus -> Changes the sign of value)
     */
    constexpr Char operator-() const noexcept {
        return Char(-Value);
    }

    /*
     * Operator~ (One's Complement)
     */
    constexpr Char operator~() const noexcept {
        return Char(~Value);
    }

    /*
     * Operator! (Logical NOT)
     * Not applicable for int. However, C++ allows its usage
     */
    constexpr Boolean operator!() const noexcept {
        return !Value;
    }

    /*
     * Operator++ (Prefix increment)
     */
    constexpr Char& operator++() noexcept {
        ++Value;
        return *this;
    }

    /*
     * Operator++ (Postfix increment)
     */
    constexpr Char operator++(int) noexcept {
        return Char(Value++);
    }

    /*
     * Operator-- (Prefix decrement)
     */
    constexpr Char& operator--() noexcept {
        --Value;
        return *this;
    }

    /*
     * Operator-- (Postfix decrement)
     */
    constexpr Char operator--(int) noexcept {
        return Char(Value--);
    }

    /*
     * Operator+= (Addition assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Char& operator+=(T const& other) noexcept requires(is_promotion_primitive<T>::value) {
        Value += other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr Char& operator+=(T const& other) noexcept requires(is_promotion_wrapper<T>::value) {
        Value += other.GetValue();
        return *this;
    }


    /*
     * Operator-= (Subtraction assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Char& operator-=(T const& other) noexcept requires(is_promotion_primitive<T>::value)  {
        Value -= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr Char& operator-=(T const& other) noexcept requires(is_promotion_wrapper<T>::value) {
        Value -= other.GetValue();
        return *this;
    }

    /*
     * Operator*= (Multiplication assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Char& operator *=(T const& other) noexcept requires(is_promotion_primitive<T>::value) {
        Value *= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr Char& operator*=(T const& other) noexcept requires(is_promotion_wrapper<T>::value) {
        Value *= other.GetValue();
        return *this;
    }

    /*
     * Operator/= (Division assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Char& operator /=(T const& other) noexcept requires(is_promotion_primitive<T>::value) {
        Value /= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr Char& operator/=(T const& other) noexcept requires(is_promotion_wrapper<T>::value)  {
        Value /= other.GetValue();
        return *this;
    }

    /*
     * Operator%= (Modulo assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    constexpr Char& operator %=(T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        Value %= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    constexpr Char& operator %=(T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        Value %= other.GetValue();
        return *this;
    }

    /*
     * Operator<<= (Shift-Left assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    constexpr Char& operator <<=(T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)  {
        Value <<= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    constexpr Char& operator <<=(T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        Value <<= other.GetValue();
        return *this;
    }

    /*
     * Operator>>= (Shift-Right assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    constexpr Char& operator >>=(T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        Value >>= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    constexpr Char& operator >>=(T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        Value >>= other.GetValue();
        return *this;
    }

    /*
     * Operator&= (Logical AND assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    constexpr Char& operator &=(T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        Value &= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    constexpr Char& operator &=(T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        Value &= other.GetValue();
        return *this;
    }

    /*
     * Operator|= (Logical OR assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    constexpr Char& operator |=(T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        Value |= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    constexpr Char& operator |=(T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        Value |= other.GetValue();
        return *this;
    }

    /*
     * Operator^= (Logical XOR assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    constexpr Char& operator ^=(T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        Value ^= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    constexpr Char& operator ^=(T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        Value ^= other.GetValue();
        return *this;
    }

    /*
     * Operator+ (Addition)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Char operator+(Char const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value + rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Char operator+(Char const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value + rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Char operator+(T const& lhs, Char const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs + rhs.Value; }

    /*
     * Operator- (Subtraction)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Char operator-(Char const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value - rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Char operator-(Char const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value - rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Char operator-(T const& lhs, Char const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs - rhs.Value; }

    /*
    * Operator* (Multiplication)
    */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Char operator*(Char const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value * rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Char operator*(Char const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value * rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Char operator*(T const& lhs, Char const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs * rhs.Value; }

    /*
    * Operator/ (Division)
    */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Char operator/(Char const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value / rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Char operator/(Char const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value / rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Char operator/(T const& lhs, Char const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs / rhs.Value; }

    /*
     * Operator% (Modulo)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Char operator%(Char const& lhs, T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        return lhs.Value % other;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    friend inline constexpr Char operator%(Char const& lhs, T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        return lhs.Value % other.GetValue();
    }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Char operator%(T const& lhs, Char const& rhs) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)
    {
        return lhs % rhs.Value;
    }

    /*
     * Operator& (Logical AND)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Char operator&(Char const& lhs, T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        return lhs.Value & other;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    friend inline constexpr Char operator&(Char const& lhs, T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        return lhs.Value & other.GetValue();
    }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Char operator&(T const& lhs, Char const& rhs) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)
    {
        return lhs & rhs.Value;
    }

    /*
     * Operator| (Logical OR)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Char operator|(Char const& lhs, T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        return lhs.Value | other;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    friend inline constexpr Char operator|(Char const& lhs, T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        return lhs.Value | other.GetValue();
    }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Char operator|(T const& lhs, Char const& rhs) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)
    {
        return lhs | rhs.Value;
    }

    /*
     * Operator^ (Logical XOR)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Char operator^(Char const& lhs, T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        return lhs.Value ^ other;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    friend inline constexpr Char operator^(Char const& lhs, T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        return lhs.Value ^ other.GetValue();
    }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Char operator^(T const& lhs, Char const& rhs) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)
    {
        return lhs ^ rhs.Value;
    }

    /*
     * Operator<< (Shift-Left)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Char operator<<(Char const& lhs, T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        return lhs.Value << other;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    friend inline constexpr Char operator<<(Char const& lhs, T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        return lhs.Value << other.GetValue();
    }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Char operator<<(T const& lhs, Char const& rhs) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)
    {
        return lhs << rhs.Value;
    }

    /*
     * Operator>> (Shift-Right)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Char operator>>(Char const& lhs, T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        return lhs.Value >> other;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    friend inline constexpr Char operator>>(Char const& lhs, T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        return lhs.Value >> other.GetValue();
    }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Char operator>>(T const& lhs, Char const& rhs) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)
    {
        return lhs >> rhs.Value;
    }

    /*
     * Operator== (Equality)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator==(Char const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value == rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator==(Char const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value == rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator==(T const& lhs, Char const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs == rhs.Value; }

    /*
     * Operator!= (Inequality)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator!=(Char const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return !(lhs.Value == rhs); }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator!=(Char const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return !(lhs.Value == rhs.GetValue()); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator!=(T const& lhs, Char const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return !(lhs == rhs.Value); }

    /*
     * Operator< (Less Than)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator<(Char const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value < rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator<(Char const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value < rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator<(T const& lhs, Char const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs < rhs.Value; }

    /*
     * Operator<= (Less Than or Equal to )
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator<=(Char const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value <= rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator<=(Char const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value <= rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator<=(T const& lhs, Char const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs <= rhs.Value; }

    /*
     * Operator> (Greater than)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator>(Char const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value > rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator>(Char const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value > rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator>(T const& lhs, Char const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs > rhs.Value; }

    /*
     * Operator>= (Greater Than or Equal to )
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator>=(Char const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value >= rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator>=(Char const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value >= rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator>=(T const& lhs, Char const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs >= rhs.Value; }

    /*
     * Operator<< (Stream extraction)
     */
    friend inline std::istream& operator>>(std::istream& lhs, Char & rhs) {
        return lhs >> rhs.Value;
    }

    /*
     * Operator<< (Stream insertion)
     */
    friend inline std::ostream& operator<<(std::ostream& lhs, Char const& rhs) {
        return lhs << rhs.Value;
    }

    //</editor-fold>

    constexpr Int32 GetHashCode() const noexcept { return (int) Value | ((int) Value << 16); }

    static constexpr Boolean IsDigit(char c) {
        if (IsLatin1(c)) {
            return (c >= '0' && c <= '9');
        }
        return (CharUnicodeInfo::GetUnicodeCategory(c) == UnicodeCategory::DecimalDigitNumber);
    };

    static constexpr Boolean IsControl(char c) noexcept {
        if(IsLatin1(c)) return GetLatin1UnicodeCategory(c) == UnicodeCategory::Control;
        return CharUnicodeInfo::GetUnicodeCategory(c) == UnicodeCategory::Control;
    }

    static constexpr Boolean IsLetter(char c) noexcept {
        if (IsLatin1(c)) {
            if (IsASCII(c)) {
                c |= static_cast<char>(0x20);
                return ((c >= 'a' && c <= 'z'));
            }
            return CheckLetter(GetLatin1UnicodeCategory(c));
        }
        return CheckLetter(CharUnicodeInfo::GetUnicodeCategory(c));
    }

    static constexpr Boolean IsLetterOrDigit(char c) {
        if (IsLatin1(c)) return (CheckLetterOrDigit(GetLatin1UnicodeCategory(c)));
        return (CheckLetterOrDigit(CharUnicodeInfo::GetUnicodeCategory(c)));
    }

    static constexpr Boolean IsLower(char c) {
        if (IsLatin1(c)) {
            if (IsASCII(c)) return (c >= 'a' && c <= 'z');
            return (GetLatin1UnicodeCategory(c) == UnicodeCategory::LowercaseLetter);
        }
        return (CharUnicodeInfo::GetUnicodeCategory(c) == UnicodeCategory::LowercaseLetter);
    }

    static constexpr Boolean IsPunctuation(char c) {
        if (IsLatin1(c)) return (CheckPunctuation(GetLatin1UnicodeCategory(c)));
        return (CheckPunctuation(CharUnicodeInfo::GetUnicodeCategory(c)));
    }

    static constexpr Boolean IsUpper(char c) noexcept {
        if (IsLatin1(c)) {
            if (IsASCII(c)) return (c >= 'A' && c <= 'Z');
            return GetLatin1UnicodeCategory(c) == UnicodeCategory::UppercaseLetter;
        }
        return CharUnicodeInfo::GetUnicodeCategory(c) == UnicodeCategory::UppercaseLetter;
    }

    static Boolean IsWhiteSpace(char c) noexcept {
        if (IsLatin1(c)) return IsWhiteSpaceLatin1(c);
        return CharUnicodeInfo::IsWhiteSpace(c);
    }


    static constexpr Char MaxValue() { return static_cast<Char>(0xFFFF); }
    static constexpr Char MinValue() { return static_cast<Char>(0x00); }
};

#endif //CPPDATASTRUCTURES_CHAR_H
