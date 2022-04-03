//
// Created by bcfrutuozo on 02/04/2022.
//

#ifndef CPPDATASTRUCTURES_UINT16_H
#define CPPDATASTRUCTURES_UINT16_H

#include <cstdint>

#include "TypeValue.h"
#include "Boolean.h"

class Byte;
class Char;
class Int16;
class Int32;
class Int64;
class Double;
class Float;
class SByte;
class UInt32;
class UInt64;

class UInt16 {

private:

    uint16_t Value;
    
public:

    //<editor-fold desc="Primitive abstraction section">

    using value_type = uint16_t;

    constexpr uint16_t const& GetValue() const noexcept { return Value; }

    constexpr UInt16() : Value() {};

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr UInt16(T value) noexcept requires(is_promotion_primitive<T>::value) : Value((value)) {}

    /*
     * Constructor which receives another Wrapper
     * It's implicit because if you pass another wrapper without setting it, it'll cast to primitive
     * by its operator T() function
     */
    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr explicit UInt16(T const& wrapper) noexcept requires(is_promotion_wrapper<T>::value) : Value(wrapper) {}

    constexpr UInt16(UInt16 const &) = default;

    constexpr UInt16(UInt16 &&) = default;

    constexpr UInt16 &operator=(UInt16 const &) = default;

    constexpr UInt16 &operator=(UInt16 &&) = default;

    /*
     * Operator= (Assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr UInt16 operator=(T const& value) noexcept requires(is_promotion_primitive<T>::value) { return Value = value; };

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr UInt16& operator=(T const& wrapper) noexcept requires(is_promotion_wrapper<T>::value) { Value = wrapper.GetValue(); return *this; };

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
    constexpr UInt16 const& operator+() const noexcept {
        return *this;
    }

    /*
     * Operator- (Unary Minus -> Changes the sign of value)
     */
    constexpr UInt16 operator-() const noexcept {
        return UInt16(-Value);
    }

    /*
     * Operator~ (One's Complement)
     */
    constexpr UInt16 operator~() const noexcept {
        return UInt16(~Value);
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
    constexpr UInt16& operator++() noexcept {
        ++Value;
        return *this;
    }

    /*
     * Operator++ (Postfix increment)
     */
    constexpr UInt16 operator++(int) noexcept {
        return UInt16(Value++);
    }

    /*
     * Operator-- (Prefix decrement)
     */
    constexpr UInt16& operator--() noexcept {
        --Value;
        return *this;
    }

    /*
     * Operator-- (Postfix decrement)
     */
    constexpr UInt16 operator--(int) noexcept {
        return UInt16(Value--);
    }

    /*
     * Operator+= (Addition assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr UInt16& operator+=(T const& other) noexcept requires(is_promotion_primitive<T>::value) {
        Value += other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr UInt16& operator+=(T const& other) noexcept requires(is_promotion_wrapper<T>::value) {
        Value += other.GetValue();
        return *this;
    }


    /*
     * Operator-= (Subtraction assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr UInt16& operator-=(T const& other) noexcept requires(is_promotion_primitive<T>::value)  {
        Value -= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr UInt16& operator-=(T const& other) noexcept requires(is_promotion_wrapper<T>::value) {
        Value -= other.GetValue();
        return *this;
    }

    /*
     * Operator*= (Multiplication assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr UInt16& operator *=(T const& other) noexcept requires(is_promotion_primitive<T>::value) {
        Value *= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr UInt16& operator*=(T const& other) noexcept requires(is_promotion_wrapper<T>::value) {
        Value *= other.GetValue();
        return *this;
    }

    /*
     * Operator/= (Division assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr UInt16& operator /=(T const& other) noexcept requires(is_promotion_primitive<T>::value) {
        Value /= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr UInt16& operator/=(T const& other) noexcept requires(is_promotion_wrapper<T>::value)  {
        Value /= other.GetValue();
        return *this;
    }

    /*
     * Operator%= (Modulo assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    constexpr UInt16& operator %=(T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        Value %= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    constexpr UInt16& operator %=(T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        Value %= other.GetValue();
        return *this;
    }

    /*
     * Operator<<= (Shift-Left assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    constexpr UInt16& operator <<=(T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)  {
        Value <<= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    constexpr UInt16& operator <<=(T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        Value <<= other.GetValue();
        return *this;
    }

    /*
     * Operator>>= (Shift-Right assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    constexpr UInt16& operator >>=(T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        Value >>= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    constexpr UInt16& operator >>=(T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        Value >>= other.GetValue();
        return *this;
    }

    /*
     * Operator&= (Logical AND assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    constexpr UInt16& operator &=(T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        Value &= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    constexpr UInt16& operator &=(T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        Value &= other.GetValue();
        return *this;
    }

    /*
     * Operator|= (Logical OR assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    constexpr UInt16& operator |=(T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        Value |= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    constexpr UInt16& operator |=(T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        Value |= other.GetValue();
        return *this;
    }

    /*
     * Operator^= (Logical XOR assignment)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    constexpr UInt16& operator ^=(T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        Value ^= other;
        return *this;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    constexpr UInt16& operator ^=(T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        Value ^= other.GetValue();
        return *this;
    }

    /*
     * Operator+ (Addition)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr UInt16 operator+(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value + rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr UInt16 operator+(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value + rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr UInt16 operator+(T const& lhs, UInt16 const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs + rhs.Value; }

    /*
     * Operator- (Subtraction)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr UInt16 operator-(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value - rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr UInt16 operator-(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value - rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr UInt16 operator-(T const& lhs, UInt16 const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs - rhs.Value; }

    /*
    * Operator* (Multiplication)
    */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr UInt16 operator*(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value * rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr UInt16 operator*(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value * rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr UInt16 operator*(T const& lhs, UInt16 const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs * rhs.Value; }

    /*
    * Operator/ (Division)
    */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr UInt16 operator/(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value / rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr UInt16 operator/(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value / rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr UInt16 operator/(T const& lhs, UInt16 const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs / rhs.Value; }

    /*
     * Operator% (Modulo)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr UInt16 operator%(UInt16 const& lhs, T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        return lhs.Value % other;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    friend inline constexpr UInt16 operator%(UInt16 const& lhs, T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        return lhs.Value % other.GetValue();
    }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr UInt16 operator%(T const& lhs, UInt16 const& rhs) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)
    {
        return lhs % rhs.Value;
    }

    /*
     * Operator& (Logical AND)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr UInt16 operator&(UInt16 const& lhs, T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        return lhs.Value & other;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    friend inline constexpr UInt16 operator&(UInt16 const& lhs, T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        return lhs.Value & other.GetValue();
    }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr UInt16 operator&(T const& lhs, UInt16 const& rhs) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)
    {
        return lhs & rhs.Value;
    }

    /*
     * Operator| (Logical OR)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr UInt16 operator|(UInt16 const& lhs, T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        return lhs.Value | other;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    friend inline constexpr UInt16 operator|(UInt16 const& lhs, T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        return lhs.Value | other.GetValue();
    }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr UInt16 operator|(T const& lhs, UInt16 const& rhs) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)
    {
        return lhs | rhs.Value;
    }

    /*
     * Operator^ (Logical XOR)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr UInt16 operator^(UInt16 const& lhs, T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        return lhs.Value ^ other;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    friend inline constexpr UInt16 operator^(UInt16 const& lhs, T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        return lhs.Value ^ other.GetValue();
    }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr UInt16 operator^(T const& lhs, UInt16 const& rhs) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)
    {
        return lhs ^ rhs.Value;
    }

    /*
     * Operator<< (Shift-Left)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr UInt16 operator<<(UInt16 const& lhs, T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        return lhs.Value << other;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    friend inline constexpr UInt16 operator<<(UInt16 const& lhs, T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        return lhs.Value << other.GetValue();
    }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr UInt16 operator<<(T const& lhs, UInt16 const& rhs) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)
    {
        return lhs << rhs.Value;
    }

    /*
     * Operator>> (Shift-Right)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr UInt16 operator>>(UInt16 const& lhs, T const& other) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value) {
        return lhs.Value >> other;
    }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value, bool> = true>
    friend inline constexpr UInt16 operator>>(UInt16 const& lhs, T const& other) noexcept requires(is_promotion_wrapper<T>::value && is_wrapper_integral<T>::value) {
        return lhs.Value >> other.GetValue();
    }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value && std::is_integral<T>::value, bool> = true>
    friend inline constexpr UInt16 operator>>(T const& lhs, UInt16 const& rhs) noexcept requires(is_promotion_primitive<T>::value && std::is_integral<T>::value)
    {
        return lhs >> rhs.Value;
    }

    /*
     * Operator== (Equality)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator==(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value == rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator==(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value == rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator==(T const& lhs, UInt16 const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs == rhs.Value; }

    /*
     * Operator!= (Inequality)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator!=(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return !(lhs.Value == rhs); }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator!=(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return !(lhs.Value == rhs.GetValue()); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator!=(T const& lhs, UInt16 const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return !(lhs == rhs.Value); }

    /*
     * Operator< (Less Than)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator<(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value < rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator<(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value < rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator<(T const& lhs, UInt16 const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs < rhs.Value; }

    /*
     * Operator<= (Less Than or Equal to )
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator<=(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value <= rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator<=(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value <= rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator<=(T const& lhs, UInt16 const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs <= rhs.Value; }

    /*
     * Operator> (Greater than)
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator>(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value > rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator>(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value > rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator>(T const& lhs, UInt16 const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs > rhs.Value; }

    /*
     * Operator>= (Greater Than or Equal to )
     */
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator>=(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value >= rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr Boolean operator>=(UInt16 const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value >= rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr Boolean operator>=(T const& lhs, UInt16 const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs >= rhs.Value; }

    /*
     * Operator<< (Stream extraction)
     */
    friend inline std::istream& operator>>(std::istream& lhs, UInt16 & rhs) {
        return lhs >> rhs.Value;
    }

    /*
     * Operator<< (Stream insertion)
     */
    friend inline std::ostream& operator<<(std::ostream& lhs, UInt16 const& rhs) {
        return lhs << rhs.Value;
    }

    //</editor-fold>
};

#endif //CPPDATASTRUCTURES_UINT16_H
