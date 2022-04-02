//
// Created by bcfrutuozo on 01/04/2022.
//

#ifndef CPPDATASTRUCTURES_BOOLEAN_H
#define CPPDATASTRUCTURES_BOOLEAN_H

#include "TypeValue.h"

class Boolean {

    friend class Byte;
    friend class Char;
    friend class Int16;
    friend class Int32;
    friend class Int64;
    friend class Double;
    friend class Float;
    friend class SByte;
    friend class UInt16;
    friend class UInt32;
    friend class UInt64;

private:

    bool Value;

public:

    //<editor-fold desc="Primitive abstraction section">
    constexpr bool const& GetValue() const noexcept { return Value; }

    constexpr Boolean() : Value() {};

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Boolean(T value) noexcept requires(is_promotion_primitive<T>::value) : Value((value)) {}

    /*
     * Constructor which receives another Wrapper
     * It's implicit because if you pass another wrapper without setting it, it'll cast to primitive
     * by its operator T() function
     */
    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr explicit Boolean(T const& wrapper) noexcept requires(is_promotion_wrapper<T>::value) : Value(wrapper) {}

    constexpr Boolean(Boolean const &) = default;

    constexpr Boolean(Boolean &&) = default;

    constexpr Boolean &operator=(Boolean const &) = default;

    constexpr Boolean &operator=(Boolean &&) = default;

    /*
     * Operator= (Assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Boolean operator=(T const& value) noexcept requires(is_promotion_primitive<T>::value) { return Value = value; };

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr Boolean& operator=(T const& wrapper) noexcept requires(is_promotion_wrapper<T>::value) { Value = wrapper.GetValue(); return *this; };

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
    constexpr Boolean const& operator+() const noexcept {
        return *this;
    }

    /*
     * Operator- (Unary Minus -> Changes the sign of value)
     */
    constexpr Boolean operator-() const noexcept {
        return Boolean(-Value);
    }

    /*
     * Operator~ (One's Complement)
     */
    constexpr Boolean operator~() const noexcept {
        return Boolean(~Value);
    }

    /*
     * Operator! (Logical NOT)
     */
    constexpr bool operator!() const noexcept {
        return !Value;
    }

    /*
     * According to C++ 17 standards onwards, Boolean type
     * does not implement Prefix and Postfix increment/decrement
     */

    /*
     * Operator+= (Addition assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Boolean& operator+=(T const& other) noexcept requires(is_promotion_primitive<T>::value) {
        Value += other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr Boolean& operator+=(T const& other) noexcept requires(is_promotion_wrapper<T>::value) {
        Value += other.GetValue();
        return *this;
    }


    /*
     * Operator-= (Subtraction assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Boolean& operator-=(T const& other) noexcept requires(is_promotion_primitive<T>::value)  {
        Value -= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr Boolean& operator-=(T const& other) noexcept requires(is_promotion_wrapper<T>::value) {
        Value -= other.GetValue();
        return *this;
    }

    /*
     * Operator*= (Multiplication assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Boolean& operator *=(T const& other) noexcept requires(is_promotion_primitive<T>::value) {
        Value *= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr Boolean& operator*=(T const& other) noexcept requires(is_promotion_wrapper<T>::value) {
        Value *= other.GetValue();
        return *this;
    }

    /*
     * Operator/= (Division assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Boolean& operator /=(T const& other) noexcept requires(is_promotion_primitive<T>::value) {
        Value /= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr Boolean& operator/=(T const& other) noexcept requires(is_promotion_wrapper<T>::value)  {
        Value /= other.GetValue();
        return *this;
    }

    /*
     * Operator%= (Modulo assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    constexpr Boolean& operator %=(T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        Value %= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    constexpr Boolean& operator %=(T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        Value %= other.GetValue();
        return *this;
    }

    /*
     * Operator<<= (Shift-Left assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    constexpr Boolean& operator <<=(T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)  {
        Value <<= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    constexpr Boolean& operator <<=(T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        Value <<= other.GetValue();
        return *this;
    }

    /*
     * Operator>>= (Shift-Right assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    constexpr Boolean& operator >>=(T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        Value >>= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    constexpr Boolean& operator >>=(T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        Value >>= other.GetValue();
        return *this;
    }

    /*
     * Operator&= (Logical AND assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    constexpr Boolean& operator &=(T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        Value &= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    constexpr Boolean& operator &=(T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        Value &= other.GetValue();
        return *this;
    }

    /*
     * Operator|= (Logical OR assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    constexpr Boolean& operator |=(T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        Value |= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    constexpr Boolean& operator |=(T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        Value |= other.GetValue();
        return *this;
    }

    /*
     * Operator^= (Logical XOR assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    constexpr Boolean& operator ^=(T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        Value ^= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    constexpr Boolean& operator ^=(T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        Value ^= other.GetValue();
        return *this;
    }

    /*
     * Operator+ (Addition)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator+(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value + rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator+(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value + rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator+(T const& lhs, Boolean const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs + rhs.Value; }

    /*
     * Operator- (Subtraction)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator-(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value - rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator-(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value - rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator-(T const& lhs, Boolean const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs - rhs.Value; }

    /*
    * Operator* (Multiplication)
    */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator*(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value * rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator*(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value * rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator*(T const& lhs, Boolean const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs * rhs.Value; }

    /*
    * Operator/ (Division)
    */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator/(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value / rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator/(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value / rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator/(T const& lhs, Boolean const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs / rhs.Value; }

    /*
     * Operator% (Modulo)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Boolean operator%(Boolean const& lhs, T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        return lhs.Value %= other;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    friend inline constexpr Boolean operator%(Boolean const& lhs, T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        return lhs.Value %= other.GetValue();
    }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Boolean operator%(T const& lhs, Boolean const& rhs) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)
    {
        return lhs % rhs.Value;
    }

    /*
     * Operator& (Logical AND)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Boolean operator&(Boolean const& lhs, T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        return lhs.Value & other;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    friend inline constexpr Boolean operator&(Boolean const& lhs, T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        return lhs.Value & other.GetValue();
    }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Boolean operator&(T const& lhs, Boolean const& rhs) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)
    {
        return lhs & rhs.Value;
    }

    /*
     * Operator| (Logical OR)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Boolean operator|(Boolean const& lhs, T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        return lhs.Value | other;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    friend inline constexpr Boolean operator|(Boolean const& lhs, T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        return lhs.Value | other.GetValue();
    }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Boolean operator|(T const& lhs, Boolean const& rhs) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)
    {
        return lhs | rhs.Value;
    }

    /*
     * Operator^ (Logical XOR)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Boolean operator^(Boolean const& lhs, T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        return lhs.Value ^ other;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    friend inline constexpr Boolean operator^(Boolean const& lhs, T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        return lhs.Value ^ other.GetValue();
    }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Boolean operator^(T const& lhs, Boolean const& rhs) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)
    {
        return lhs ^ rhs.Value;
    }

    /*
     * Operator<< (Shift-Left)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Boolean operator<<(Boolean const& lhs, T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        return lhs.Value << other;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    friend inline constexpr Boolean operator<<(Boolean const& lhs, T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        return lhs.Value << other.GetValue();
    }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Boolean operator<<(T const& lhs, Boolean const& rhs) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)
    {
        return lhs << rhs.Value;
    }

    /*
     * Operator>> (Shift-Right)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Boolean operator>>(Boolean const& lhs, T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        return lhs.Value >> other;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    friend inline constexpr Boolean operator>>(Boolean const& lhs, T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        return lhs.Value >> other.GetValue();
    }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr Boolean operator>>(T const& lhs, Boolean const& rhs) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)
    {
        return lhs >> rhs.Value;
    }

    /*
     * Operator== (Equality)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator==(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value == rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator==(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value == rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator==(T const& lhs, Boolean const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs == rhs.Value; }

    /*
     * Operator!= (Inequality)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator!=(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return !(lhs.Value == rhs); }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator!=(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return !(lhs.Value == rhs.GetValue()); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator!=(T const& lhs, Boolean const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return !(lhs == rhs.Value); }

    /*
     * Operator< (Less Than)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator<(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value < rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator<(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value < rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator<(T const& lhs, Boolean const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs < rhs.Value; }

    /*
     * Operator<= (Less Than or Equal to )
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator<=(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value <= rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator<=(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value <= rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator<=(T const& lhs, Boolean const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs <= rhs.Value; }

    /*
     * Operator> (Greater than)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator>(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value > rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator>(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value > rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator>(T const& lhs, Boolean const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs > rhs.Value; }

    /*
     * Operator>= (Greater Than or Equal to )
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator>=(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value >= rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator>=(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value >= rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator>=(T const& lhs, Boolean const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs >= rhs.Value; }

    /*
     * Operator<< (Stream extraction)
     */
    friend inline std::istream& operator>>(std::istream& lhs, Boolean & rhs) {
        return lhs >> rhs.Value;
    }

    /*
     * Operator<< (Stream insertion)
     */
    friend inline std::ostream& operator<<(std::ostream& lhs, Boolean & rhs) {
        return lhs << rhs.Value;
    }

    /*
     * Operator&& (AND) -> Boolean exclusive
     */
    friend inline constexpr Boolean operator&&(Boolean const& lhs, bool const& rhs) noexcept {
        return lhs.GetValue() && rhs;
    }
    friend inline constexpr Boolean operator&&(bool const& lhs, Boolean const& rhs) noexcept {
        return lhs && rhs.GetValue();
    }

    friend inline constexpr Boolean operator&&(Boolean const& lhs, Boolean const& rhs) noexcept {
        return lhs.Value && rhs.Value;
    }

    /*
     * Operator|| (OR) -> Boolean exclusive
     */
    friend inline constexpr Boolean operator||(Boolean const& lhs, bool const& rhs) noexcept {
        return lhs.GetValue() || rhs;
    }
    friend inline constexpr Boolean operator||(bool const& lhs, Boolean const& rhs) noexcept {
        return lhs || rhs.GetValue();
    }

    friend inline constexpr Boolean operator||(Boolean const& lhs, Boolean const& rhs) noexcept {
        return lhs.Value || rhs.Value;
    }
    //</editor-fold>
};

#endif //CPPDATASTRUCTURES_BOOLEAN_H
