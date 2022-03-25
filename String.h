//
// Created by bcfrutuozo on 12/03/2022.
//

#ifndef CPPDATASTRUCTURES_STRING_H
#define CPPDATASTRUCTURES_STRING_H

#include "Platform.h"
#include "Container.hpp"
#include "Array.h"

#include <iostream>
#include <cstring>

class String : Container<const char *> {

private:

    size_t m_Length;
    char *m_Data;

    inline constexpr char *GetPointer() const noexcept { return m_Data; }

public:

    String() noexcept;

    String(const char *c) noexcept;

    String(const String &s) noexcept;

    String(String &&s) noexcept;

    ~String() noexcept;

    String &operator=(const char *c) noexcept;

    String &operator=(const String &other) noexcept;

    String &operator=(String &&s) noexcept;

    String operator+(const char *c) noexcept;

    String operator+(const String &s) noexcept;

    char operator[](size_t index);

    bool operator==(const char *c) const noexcept;

    inline bool operator==(const String &rhs) const noexcept;

    bool Contains(char c) const noexcept;

    bool Contains(const char *c) const noexcept;

    bool Contains(const String &s) const noexcept;

    constexpr size_t GetLength() const noexcept { return m_Length; }

    void Copy(char c[], size_t length, size_t pos);

    size_t Count(char c) const noexcept;

    size_t Count(const char *c) const noexcept;

    size_t Count(const String &s) const noexcept;

    size_t IndexOf(char c) const noexcept;

    size_t IndexOf(const char *c) const noexcept;

    size_t IndexOf(const String &s) const noexcept;

    Array<size_t> IndicesOf(char c) const noexcept;

    Array<size_t> IndicesOf(const char *c) const noexcept;

    Array<size_t> IndicesOf(const String &s) const noexcept;

    size_t LastIndexOf(char c) const noexcept;

    size_t LastIndexOf(const char *c) const noexcept;

    size_t LastIndexOf(const String &s) const noexcept;

    Array<String> Split(const char *delimiter) const noexcept;

    friend std::ostream &operator<<(std::ostream &os, const String &s);
};

inline std::ostream &operator<<(std::ostream &os, const String &s) {
    os << s.GetPointer();
    return os;
};

#endif //CPPDATASTRUCTURES_STRING_H
