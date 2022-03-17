//
// Created by bcfrutuozo on 12/03/2022.
//

#include "String.h"

#include <malloc.h>
#include <iostream>
#include <string>

String::String() noexcept
    :
    m_Data(nullptr),
    m_Length(0)
    {
    m_Data = new char[1];
    m_Data[0] = '\0';
}

String::String(const char *c) noexcept
    :
    m_Data(nullptr)
    {
    if(c == nullptr){
        m_Data = new char[1];
        m_Data[0] = '\0';
        m_Length = 0;
    }
    else{
        size_t size = strlen(c);
        m_Data = new char[size + 1];
        strcpy(m_Data, c);
        m_Data[size] = '\0';
        m_Length = size;
    }
}

String::String(const String &s) noexcept {
    size_t size = strlen(s.m_Data);
    m_Data = new char[size + 1];
    strcpy(m_Data, s.m_Data);
    m_Data[size] = '\0';
    m_Length = size;
}

String::String(String &&s) noexcept {
    m_Data = s.m_Data;
    m_Length = s.m_Length;
    s.m_Data = nullptr;
}

String::~String() {
    delete[] m_Data;
}

String String::operator=(const char *c) {
    if(&m_Data == &c){
        return *this;
    }

    delete[] m_Data;
    size_t newSize = strlen(c);
    m_Data = new char[newSize + 1];
    strcpy(m_Data, c);
    m_Length = newSize;
    return *this;
}

String String::operator=(const String &s) {
    if(this == &s){
        return *this;
    }

    delete[] m_Data;
    size_t newSize = strlen(s.m_Data);
    m_Data = new char[newSize + 1];
    strcpy(m_Data, s.m_Data);
    m_Length = newSize;
    return *this;
}

String String::operator+(const char *c) {
    size_t newSize = m_Length + strlen(c);
    char* buffer = new char[newSize + 1];
    strcpy(buffer, m_Data);
    strcat(buffer, c);
    buffer[newSize] = '\0';
    String temp { buffer };
    delete[] buffer;
    return temp;
}

String String::operator+(const String& s) {
    size_t newSize = m_Length + s.m_Length;
    char* buffer = new char[newSize + 1];
    strcpy(buffer, m_Data);
    strcat(buffer, s.m_Data);
    buffer[newSize] = '\0';
    String temp { buffer };
    delete[] buffer;
    return temp;
}

bool String::Contains(const char c) const {

    for (size_t i = 0; i < m_Length; ++i)
        if (*(m_Data + i) == c)
            return true;

    return false;
}

bool String::Contains(const char *c) const {

    size_t cSize = strlen(c);

    if (cSize > m_Length) return false;

    size_t lastBlock = reinterpret_cast<size_t>(m_Data + m_Length);

    for (size_t i = 0; i < m_Length && reinterpret_cast<size_t>(m_Data + i) <= lastBlock; ++i) {

//ifdef IS_DEBUG
        std::cout << "Comparing ";

        for (size_t start = i; start < i + cSize; ++start)
            std::cout << *(m_Data + start);

        std::cout << " with " << c << std::endl;
//#endif

        if (memcmp((m_Data + i), c, cSize) == 0)
            return true;
    }

    return false;
}

bool String::Contains(const String &s) const {
    return this->Contains(s.m_Data);
}

void String::Copy(char *c, size_t length, size_t pos) {
    for(size_t i = 0; i < length; ++i){
        c[i] = m_Data[pos + i];
    }
    c[length] = '\0';
}

char String::operator[](size_t index) {
    if(index > m_Length - 1)
        std::out_of_range("Out of string boundaries");

    return m_Data[index];
}
