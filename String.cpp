//
// Created by bcfrutuozo on 12/03/2022.
//

#include "String.h"
#include "Queue.h"

#include <iostream>
#include <string>
#include <cstdio>

String::String() noexcept
        :
        m_Data(nullptr),
        m_Length(0) {
    m_Data = new char[1];
    m_Data[0] = '\0';
}

String::String(const char *c) noexcept
        :
        m_Data(nullptr) {
    if (c == nullptr) {
        m_Data = new char[1];
        m_Data[0] = '\0';
        m_Length = 0;
    } else {
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

String::~String() noexcept {
    delete[] m_Data;
    m_Data = nullptr;
}

String &String::operator=(const char *c) noexcept {
    if (&m_Data == &c) {
        return *this;
    }

    delete[] m_Data;
    size_t newSize = strlen(c);
    m_Data = new char[newSize + 1];
    strcpy(m_Data, c);
    m_Length = newSize;
    return *this;
}

String &String::operator=(const String &s) noexcept {
    if (this == &s) {
        return *this;
    }

    delete[] m_Data;
    size_t newSize = strlen(s.m_Data);
    m_Data = new char[newSize + 1];
    strcpy(m_Data, s.m_Data);
    m_Length = newSize;
    return *this;
}

String &String::operator=(String &&other) noexcept {

    // Self-assignment detection
    if (&other == this) return *this;

    delete[] m_Data;

    size_t newSize = other.m_Length;
    m_Data = other.m_Data;

    other.m_Length = 0;
    m_Data = nullptr;

    return *this;
}

String String::operator+(const char *c) noexcept {
    size_t newSize = m_Length + strlen(c);
    char *buffer = new char[newSize + 1];
    strcpy(buffer, m_Data);
    strcat(buffer, c);
    buffer[newSize] = '\0';
    String temp{buffer};
    delete[] buffer;
    return temp;
}

String String::operator+(const String &s) noexcept {
    size_t newSize = m_Length + s.m_Length;
    char *buffer = new char[newSize + 1];
    strcpy(buffer, m_Data);
    strcat(buffer, s.m_Data);
    buffer[newSize] = '\0';
    String temp{buffer};
    delete[] buffer;
    return temp;
}

char String::operator[](size_t index) {
    if (index > m_Length - 1) throw std::out_of_range("Out of string boundaries");
    return m_Data[index];
}

bool String::operator==(const char *c) const noexcept {
    if (m_Length != strlen(c))
        return false;

    for (size_t i = 0; i < m_Length; ++i) {
        if (m_Data[i] != c[i])
            return false;
    }

    return true;
}

inline bool String::operator==(const String &rhs) const noexcept {
    return *this == rhs.m_Data;
}

bool String::Contains(const char c) const noexcept {
    for (size_t i = 0; i < m_Length; ++i)
        if (*(m_Data + i) == c)
            return true;

    return false;
}

bool String::Contains(const char *c) const noexcept {

    size_t cSize = strlen(c);

    if (cSize > m_Length) return false;

    auto lastBlock = reinterpret_cast<size_t>(m_Data + m_Length);

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

void String::Copy(char *c, size_t length, size_t pos) {
    for (size_t i = 0; i < length; ++i) {
        c[i] = m_Data[pos + i];
    }
    c[length] = '\0';
}

size_t String::Count(char c) const noexcept {
    if (GetLength() == 0) return 0;

    auto p = m_Data;
    size_t count = 0;
    while (*p != '\0') {
        if (*p == c) ++count;
        ++p;
    }

    return count;
}

size_t String::Count(const char *c) const noexcept {
    return IndicesOf(c).GetLength();
}

size_t String::IndexOf(const char c) const noexcept {
    return (size_t) (strchr(m_Data, c) - m_Data);
}

size_t String::IndexOf(const char *c) const noexcept {
    return (size_t) (strstr(m_Data, c) - m_Data);
}

Array<size_t> String::IndicesOf(const char c) const noexcept {
    if (GetLength() == 0) return Array<size_t>{};

    Queue<size_t> q;
    auto lastIndex = (size_t) m_Data;
    while (lastIndex != 0) {
        size_t a = (strchr((char *) lastIndex, c) - m_Data);
        if (a != 0) q.Enqueue(a);
        lastIndex = a + 1;
    }

    return q.ToArray();
}

Array<size_t> String::IndicesOf(const char *c) const noexcept {
    if (GetLength() == 0) return Array<size_t>{};

    Queue<size_t> q;
    size_t subSize = strlen(c);
    for (size_t i = 0; i < GetLength();) {
        size_t j = 0;
        size_t subCount = 0;
        while (m_Data[i] == c[j]) {
            ++subCount;
            ++i;
            ++j;
        }
        if (subCount == subSize) q.Enqueue(i - subSize);
        else ++i;
    }

    return q.ToArray();
}

size_t String::LastIndexOf(const char c) const noexcept {
    return (size_t) (strrchr(m_Data, c) - m_Data);
}

size_t String::LastIndexOf(const char *c) const noexcept {
    char *haystack;
    char *r = nullptr;

    if (!c[0])
        return (size_t) (haystack + strlen(haystack));
    while (true) {
        char *p = strstr(haystack, c);
        if (!p)
            return (size_t) (r - m_Data);
        r = p;
        haystack = p + 1;
    }
}

Array<String> String::Split(char c, StringSplitOptions options) const noexcept {

}

Array<String> String::Split(const char *delimiter, StringSplitOptions options) const noexcept {

    Array<String> arrayStr{};
    if (GetLength() == 0) arrayStr;
    if (GetLength() == 1) {
        if(strcmp(m_Data, delimiter) == 0)
            return Array<String>{m_Data};
        else arrayStr;
    }

    auto array = IndicesOf(delimiter);
    size_t length = strlen(delimiter);
    Array<String>::Resize(arrayStr, array.GetLength());
    for (ssize_t i = -1, j = 0; i < (ssize_t) arrayStr.GetLength(); ++i, ++j) {
        auto start = i >= 0 ? length + array[i] : 0;
        size_t end;

        if (array.GetLength() - 1 == i) {
            end = GetLength();
        } else {
            end = array[i + 1];
        }

        size_t charSize = end - start;
        char buffer[charSize];
        std::copy(m_Data + start, m_Data + end, buffer);
        *(buffer + charSize) = '\0';
        arrayStr[j] = buffer;
    }

    return arrayStr;
}

String String::TrimStart() const noexcept{
    TrimStart(Space);
}

String String::TrimStart(char c) const noexcept{
    auto p = m_Data;
    size_t start = 0;

    while(*p == c){
        ++start;
    }

    return m_Data + start;
}

String String::TrimStart(const char* c) const noexcept{
    auto index = strstr(m_Data, c) - m_Data;
    return m_Data + index;

    String s;
}

String String::TrimEnd() const noexcept{
    TrimEnd(Space);
}

String String::TrimEnd(char c) const noexcept{
    auto p = (m_Data + GetLength() - 2); // 1 for \0 and 1 for index
    size_t end = 0;

    while(*p == c){
        --end;
    }

    char buffer[end + 1];
    std::copy(m_Data, m_Data + end - 1, buffer);
    buffer[end] = '\0';

    return buffer;
}

String String::TrimEnd(const char* c) const noexcept{

}
