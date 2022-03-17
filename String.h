//
// Created by bcfrutuozo on 12/03/2022.
//

#ifndef LNXCPPLEARNING_STRING_H
#define LNXCPPLEARNING_STRING_H

#include "Array.h"

#include <iostream>
#include <cstring>

class String {

private:

    size_t m_Length;
    char* m_Data;

    constexpr char* GetPointer() const { return m_Data; }

public:

    String() noexcept;
    String(const char* c) noexcept;
    String(const String& s) noexcept;
    String(String&& s) noexcept;
    ~String();

    String operator=(const char* c);
    String operator=(const String& s);
    String operator+(const char* c);
    String operator+(const String& s);

    char operator[](size_t index);

    inline bool operator==(const char* c)
    {
        if(m_Length != strlen(c))
            return false;

        for(size_t i = 0; i < m_Length; ++i)
        {
            if(m_Data[i] != c[i])
                return false;
        }

        return true;
    }

    inline bool operator==(const String& rhs)
    {
        return *this == rhs.m_Data;
    }

    bool Contains(const char c) const;
    bool Contains(const char* c) const;
    bool Contains(const String& s) const;
    constexpr size_t GetLength() const { return m_Length; }
    void Copy(char c[], size_t length, size_t pos);
    Array<String> Split(const char* delimiter);

    friend std::ostream& operator<<(std::ostream& os, const String& s);
};

inline std::ostream& operator<<(std::ostream& os, const String& s)
{
    os << s.GetPointer();
    return os;
}

#endif //LNXCPPLEARNING_STRING_H
