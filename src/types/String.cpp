////
//// Created by bcfrutuozo on 12/03/2022.
////
//
//#include "String.h"
//#include "Queue.h"
//
//#include <iostream>
//#include <cstdio>
//#include <string.h>
//#include <cctype>      // std::tolower
//#include <algorithm>   // std::equal
//
//// Static variable declaration
//typename String::allocator_type String::mAllocator{};
//// 
//// 
////String::String(char c) noexcept
////	:
////	String(c, 1)
////{}
////
////String::String(wchar_t c) noexcept
////	:
////	String(c, 1)
////{}
////
////String::String(Char c) noexcept
////	:
////	String(c, 1)
////{}
////
////String::String(char c, int count) noexcept
////{
////	size_t i = 0;
////	wchar_t retChar[2];
////	mbstowcs_s(&i, retChar, 2, &c, 1);
////	wchar_t wc = retChar[0];
////	wchar_t* data = new wchar_t[count + 1];
////	for (size_t i = 0; i < count; ++i)
////		data[i] = wc;
////	data[count] = '\0';
////	mStr = data;
////	delete[] data;
////}
////
////String::String(wchar_t c, int count) noexcept
////{
////	wchar_t* data = new wchar_t[count + 1];
////
////	for (size_t i = 0; i < count; ++i)
////		data[i] = c;
////	data[count] = '\0';
////
////	mStr = data;
////
////	delete[] data;
////}
////
////String::String(Char c, int count) noexcept
////	:
////	String(c.GetValue(), count)
////{
////
////}
////
////String::String(const char* c) noexcept
////{
////	size_t i = strlen(c);
////	wchar_t* wString = new wchar_t[i + 1];
////	mbstowcs_s(&i, wString, i + 1, c, i);
////	mStr = wString;
////	delete[] wString; // Cleaning here to avoid leak
////}
////
////String::String(const wchar_t* c) noexcept
////	:
////	mStr(c)
////{
////
////}
////
////String::String(const Char* c) noexcept
////	:
////	mStr(reinterpret_cast<const wchar_t*>(c))
////{
////
////}
//
//String& String::operator=(const String& s) noexcept
//{
//	mStr = s.mStr;
//	return *this;
//}
//
//String& String::operator=(String&& other) noexcept
//{
//	// Self-assignment detection
//	if (&other == this) return *this;
//
//	mStr = other.mStr;
//	other.mStr = nullptr;
//
//	return *this;
//}
//
//String String::operator+(const char* c) noexcept
//{
//	//size_t newSize = strlen(c);
//	//size_t oldSize = GetLength();
//	//
//	//wchar_t* wString = new wchar_t[newSize + 1];
//	//mbstowcs_s(&newSize, wString, newSize + 1, c, newSize);
//	//
//	//wchar_t* nString = new wchar_t[oldSize + newSize + 1];
//	//wcscpy_s(nString, oldSize + 1, mStr);
//	//wcscat_s(nString, oldSize + newSize + 1, wString);
//	//
//	//String s = nString;
//	//
//	//delete[] wString;
//	//delete[] nString;
//
//	//return s;
//}
//
//String String::operator+(const wchar_t* c) noexcept
//{
//	size_t newSize = wcslen(c);
//	size_t oldSize = GetLength();
//	wchar_t* nString = new wchar_t[newSize + oldSize + 1];
//
//	wcscpy_s(nString, oldSize + 1, mStr.data());
//	wcscat_s(nString, oldSize + newSize + 1, c);
//
//	String s = nString;
//	delete[] nString;
//
//	return s;
//}
//
//String String::operator+(const String& s) noexcept
//{
//	size_t newSize = s.GetLength();
//	size_t oldSize = GetLength();
//	wchar_t* nString = new wchar_t[newSize + oldSize + 1];
//
//	wcscpy_s(nString, oldSize + 1, mStr.data());
//	wcscat_s(nString, oldSize + newSize + 1, s.mStr.data());
//
//	String s2 = nString;
//	delete[] nString;
//
//	return s2;
//}
//
//String& String::operator+=(const char* c) noexcept
//{
//	return *this;
//}
//
//String& String::operator+=(const wchar_t* c) noexcept
//{
//	String s = *this + c;
//	mStr = s.mStr;
//	return *this;
//}
//
//String& String::operator+=(String& s) noexcept
//{
//	String s2 = *this + s;
//	mStr = s2.mStr;
//	return *this;
//}
//
//Boolean String::String::operator==(const char* c) const noexcept
//{
//	size_t i = strlen(c);
//	wchar_t* wString = new wchar_t[i + 1];
//	mbstowcs_s(&i, wString, i + 1, c, i);
//	int cmp = (mStr.compare(wString) == 0);
//	delete[] wString;
//	return cmp;
//}
//
//Boolean String::operator==(const wchar_t* c) const noexcept
//{
//	return mStr == c;
//}
//
//Boolean String::operator==(const String& rhs) const noexcept {
//	return mStr == rhs.mStr;
//}
//
//Boolean String::String::operator!=(const char* c) const noexcept
//{
//	return !(*this == c);
//}
//
//Boolean String::operator!=(const wchar_t* c) const noexcept {
//	return !(*this == c);
//}
//
//Boolean String::operator!=(const String& rhs) const noexcept {
//	return !(*this == rhs);
//}
//
//Boolean String::Contains(char c) const noexcept
//{
//	size_t i = 0;
//	wchar_t retChar[2];
//	mbstowcs_s(&i, retChar, 2, &c, 1);
//	wchar_t wc = retChar[0];
//	return mStr.contains(wc);
//}
//
//Boolean String::Contains(wchar_t c) const noexcept {
//	return mStr.contains(c);
//}
//
//Boolean String::Contains(const char* c) const noexcept
//{
//	size_t i = strlen(c);
//	wchar_t* wString = new wchar_t[i + 1];
//	mbstowcs_s(&i, wString, i + 1, c, i);
//	int ctn = mStr.contains(wString);
//	delete[] wString; // Cleaning here to avoid leak
//	return ctn;
//}
//
//Boolean String::Contains(const wchar_t* c) const noexcept {
//	return mStr.contains(c);
//}
//
//String String::Concat(String& a, String& b) noexcept
//{
//	return a + b;
//}
//
//String String::Concat(Array<String>& a) const noexcept {
//
//	size_t oldSize = GetLength();
//	size_t totalSize = oldSize;
//	for (auto it = a.cbegin(); it != a.cend(); ++it) totalSize += it->GetLength();
//
//	// Push what we already have
//	wchar_t* ch = new wchar_t[totalSize + 1];
//	wcscpy_s(ch, oldSize + 1, mStr.data());
//
//	for (size_t i = 0; i < a.GetLength(); ++i)
//	{
//		wcscat_s(ch, totalSize + 1, a[i].mStr);
//	}
//
//	String ret = ch;
//	delete[] ch;
//	return ret;
//}
//
//size_t String::Count(char c) const noexcept
//{
//	size_t count = 0;
//	size_t i = 0;
//	wchar_t retChar[2];
//	mbstowcs_s(&i, retChar, 2, &c, 1);
//	wchar_t wc = retChar[0];
//
//	for (size_t i = 0; i < GetLength(); ++i)
//	{
//		if (mStr[i] == wc) ++count;
//	}
//
//	return count;
//}
//
//size_t String::Count(wchar_t c) const noexcept
//{
//	size_t count = 0;
//	for (size_t i = 0; i < GetLength(); ++i)
//	{
//		if (mStr[i] == c) ++count;
//	}
//
//	return count;
//}
//
//size_t String::Count(Char c) const noexcept
//{
//	return Count(c.GetValue());
//}
//
//size_t String::Count(const char* c) const noexcept {
//	if (GetLength() == 0) return 0;
//
//	size_t i = strlen(c);
//	wchar_t* wString = new wchar_t[i + 1];
//	mbstowcs_s(&i, wString, i + 1, c, i);
//	int cnt = IndicesOf(wString).GetLength();
//	delete[] wString; // Cleaning here to avoid leak
//	return cnt;
//}
//
//size_t String::Count(const wchar_t* c) const noexcept {
//	if (GetLength() == 0) return 0;
//	return IndicesOf(c).GetLength();
//}
//
//size_t String::Count(const Char* c) const noexcept
//{
//	return Count(reinterpret_cast<const wchar_t*>(c));
//}
//
//Boolean String::EndsWith(const char* c, StringComparison options) const noexcept
//{
//	size_t i = strlen(c);
//	wchar_t* wString = new wchar_t[i + 1];
//	mbstowcs_s(&i, wString, i + 1, c, i);
//	int flg = EndsWith(wString, options);
//	delete[] wString; // Cleaning here to avoid leak
//	return flg;
//}
//
//Boolean String::EndsWith(const wchar_t* c, StringComparison options) const noexcept
//{
//	size_t s = wcslen(c);
//	switch (options)
//	{
//	case StringComparison::CaseSensitive:
//		if (wcsncmp(mStr.data() + GetLength() - s, c, s) == 0) return true;
//		break;
//	case StringComparison::CaseInsensitive:
//		if (wcsnicmp(mStr.data() + GetLength() - s, c, s) == 0) return true;
//		break;
//	}
//	return false;
//}
//
//Boolean String::EndsWith(const Char* c, StringComparison options) const noexcept
//{
//	return EndsWith(reinterpret_cast<const wchar_t*>(c), options);
//}
//
//size_t String::IndexOf(char c, StringComparison options) const noexcept {
//	size_t i = 0;
//	wchar_t retChar[2];
//	mbstowcs_s(&i, retChar, 2, &c, 1);
//	return InternalIndexOf(retChar, 0, 0, options);
//}
//
//size_t String::IndexOf(wchar_t c, StringComparison options) const noexcept {
//	wchar_t temp[2] = { c, '\0' };
//	return InternalIndexOf(temp, 0, 0, options);
//}
//
//size_t String::IndexOf(Char c, StringComparison options) const noexcept {
//	return IndexOf(c.GetValue(), options);
//}
//
//size_t String::IndexOf(char c, int startIndex, StringComparison options) const noexcept {
//	size_t i = 0;
//	wchar_t retChar[2];
//	mbstowcs_s(&i, retChar, 2, &c, 1);
//	return InternalIndexOf(retChar, startIndex, 0, options);
//}
//
//size_t String::IndexOf(wchar_t c, int startIndex, StringComparison options) const noexcept {
//	wchar_t temp[2] = { c, '\0' };
//	return InternalIndexOf(temp, startIndex, 0, options);
//}
//
//size_t String::IndexOf(Char c, int startIndex, StringComparison options) const noexcept {
//	wchar_t temp[2] = { c.GetValue(), '\0' };
//	return InternalIndexOf(temp, startIndex, 0, options);
//}
//
//size_t String::IndexOf(wchar_t c, int startIndex, int count, StringComparison options) const noexcept {
//	wchar_t temp[2] = { c, '\0' };
//	return InternalIndexOf(temp, startIndex, count, options);
//}
//
//size_t String::IndexOf(const char* c, StringComparison options) const noexcept {
//	size_t i = strlen(c);
//	wchar_t* wString = new wchar_t[i + 1];
//	mbstowcs_s(&i, wString, i + 1, c, i);
//	size_t idx = InternalIndexOf(wString, 0, 0, options);
//	delete[] wString;
//	return idx;
//}
//
//size_t String::IndexOf(const wchar_t* c, StringComparison options) const noexcept {
//	return InternalIndexOf(c, 0, 0, options);
//}
//
//size_t String::IndexOf(const Char* c, StringComparison options) const noexcept {
//	return InternalIndexOf(reinterpret_cast<const wchar_t*>(c), 0, 0, options);
//}
//
//size_t String::IndexOf(const char* c, int startIndex, StringComparison options) const noexcept {
//	size_t i = strlen(c);
//	wchar_t* wString = new wchar_t[i + 1];
//	mbstowcs_s(&i, wString, i + 1, c, i);
//	size_t idx = InternalIndexOf(wString, startIndex, 0, options);
//	delete[] wString;
//	return idx;
//}
//
//size_t String::IndexOf(const wchar_t* c, int startIndex, StringComparison options) const noexcept {
//	return InternalIndexOf(c, startIndex, 0, options);
//}
//
//size_t String::IndexOf(const Char* c, int startIndex, StringComparison options) const noexcept {
//	return InternalIndexOf(reinterpret_cast<const wchar_t*>(c), startIndex, 0, options);
//}
//
//size_t String::IndexOf(const char* c, int startIndex, int count, StringComparison options) const noexcept {
//	size_t i = strlen(c);
//	wchar_t* wString = new wchar_t[i + 1];
//	mbstowcs_s(&i, wString, i + 1, c, i);
//	size_t idx = InternalIndexOf(wString, startIndex, count, options);
//	delete[] wString;
//	return idx;
//}
//
//size_t String::IndexOf(const wchar_t* c, int startIndex, int count, StringComparison options) const noexcept {
//	return InternalIndexOf(c, startIndex, count, options);
//}
//
//size_t String::IndexOf(const Char* c, int startIndex, int count, StringComparison options) const noexcept {
//	return InternalIndexOf(reinterpret_cast<const wchar_t*>(c), startIndex, count, options);
//}
//
//size_t String::IndexOfAny(const wchar_t* array) const noexcept {
//	return InternalIndexOfAny(array, 0, GetLength());
//}
//
//size_t String::IndexOfAny(const wchar_t* array, int startIndex) const noexcept {
//	return InternalIndexOfAny(array, startIndex, 0);
//}
//
//size_t String::IndexOfAny(const wchar_t* array, int startIndex, int count) const noexcept {
//	return InternalIndexOfAny(array, startIndex, count);
//}
//
//Array<size_t> String::IndicesOf(const wchar_t c) const noexcept
//{
//	if (GetLength() == 0) return Array<size_t>{};
//
//	Queue<size_t> q;
//	for (size_t i = 0;; ++i)
//	{
//		auto a = (wcsrchr(mStr + i, c));
//		if (a != nullptr) {
//			auto idx = a - mStr;
//			q.Enqueue(idx);
//			i = idx;
//		}
//		else break;
//	}
//
//	return q.ToArray();
//}
//
//Array<size_t> String::IndicesOf(const wchar_t* c) const noexcept {
//	if (GetLength() == 0) return Array<size_t>{};
//
//	Queue<size_t> q;
//	size_t inc = wcslen(c);
//	for (auto p = wcsstr(mStr, c); p != nullptr; p = wcsstr(p + inc, c))
//		q.Enqueue(p - mStr);
//
//	return q.ToArray();
//}
//
//String String::Insert(size_t index, wchar_t c) const {
//	wchar_t temp[2] = { c, '\0' };
//	return Insert(index, temp);
//}
//
//String String::Insert(size_t index, const wchar_t* c) const
//{
//	size_t oldSize = GetLength();
//	if (index > oldSize) throw std::out_of_range("index");
//
//	size_t length = wcslen(c);
//	wchar_t* ch = new wchar_t[oldSize + length + 1];
//
//	if (index == 0)
//	{
//		wcscpy_s(ch, oldSize + 1, c);
//		wcscpy_s(ch + oldSize, oldSize + length + 1, mStr.data());
//	}
//	else if (index == GetLength())
//	{
//		wcscpy_s(ch, oldSize + 1, mStr.data());
//		wcscpy_s(ch + oldSize, oldSize + length + 1, c);
//	}
//	else
//	{
//		wcsncpy_s(ch, oldSize + 1, mStr.data(), index);
//		wcscpy_s(ch + oldSize, oldSize + length + 1, c);
//		wcscpy_s(ch + oldSize + index, oldSize + length + 1, c);
//	}
//
//	String ret = ch;
//	delete[] ch;
//	return ret;
//}
//
//size_t String::InternalIndexOf(const wchar_t* c, int startIndex, int count, StringComparison options) const
//{
//	if (startIndex > LastIndex()) throw std::out_of_range("startIndex");
//	if (GetLength() == 0) return -1;
//
//	const wchar_t* ret;
//	if (count == 0)
//	{
//		ret = options == StringComparison::CaseSensitive ? wcsstr(mStr.data() + startIndex, c) : wcscasestr(mStr.data() + startIndex, c);
//	}
//	else
//	{
//		ret = options == StringComparison::CaseSensitive ? wcsnstr(mStr.data() + startIndex, c, count) : wcsnstri(mStr.data() + startIndex, c, count);
//	}
//
//	if (ret == nullptr) return -1;
//	else return ret - mStr.data();
//
//	return 1;
//}
//
//size_t String::InternalIndexOfAny(const wchar_t* array, int startIndex, int count) const
//{
//	if (startIndex > LastIndex()) throw std::out_of_range("startIndex");
//	
//	size_t arrLength = wcslen(array);
//	if (arrLength == 0 || GetLength() == 0) return -1;
//	
//	size_t ret = -1;
//	for (size_t i = 0; i < arrLength; ++i) {
//		const wchar_t* p;
//		if (count == 0) p = wcschr(mStr.data() + startIndex, *(array + i));
//		else p = (wchar_t*)memchr(mStr + startIndex, *(array + i), count);
//	
//		size_t newFound = p - mStr.data();
//		if (p != nullptr && newFound < ret) ret = newFound;
//	}
//	
//	return 1;
//}
//
//size_t String::InternalLastIndexOf(const wchar_t* c, int startIndex, int count, StringComparison options) const
//{
//	if (startIndex > LastIndex()) throw std::out_of_range("startIndex");
//	if (GetLength() == 0) return -1;
//
//	// To avoid wrong pointer operation
//	if (count > GetLength()) {
//		count = GetLength() - startIndex;
//	}
//
//	size_t end = GetLength() - startIndex;
//	size_t start = count > end ? 0 : end - count;
//
//	if (start == 0 && end == GetLength())
//	{
//		auto ch = options == StringComparison::CaseSensitive ? wcsrstr(mStr.data(), c) : wcsrstri(mStr.data(), c);
//		if (ch != nullptr) return ch - mStr.data();
//	}
//	else
//	{
//		wchar_t* ch = new wchar_t[end - start];
//		for (size_t i = 0, j = start; j < end; ++i, ++j) {
//			ch[i] = mStr[j];
//		}
//
//		size_t ret = 0;
//		auto pos = options == StringComparison::CaseSensitive ? wcsrstr(ch, c) : wcsrstri(mStr.data(), c);
//		if (pos != nullptr) {
//			ret = pos - ch + (GetLength() - startIndex - count);
//			delete[] ch;
//			return ret;
//		}
//		delete[] ch;
//	}
//
//	return -1;
//}
//
//size_t String::InternalLastIndexOfAny(const wchar_t* array, int startIndex, int count) const
//{
//	if (startIndex > LastIndex()) throw std::out_of_range("startIndex");
//	size_t arrayLength = wcslen(array);
//	if (GetLength() == 0 || arrayLength == 0) return -1;
//
//	// To avoid wrong pointer operation
//	if (count > GetLength()) {
//		count = GetLength() - startIndex;
//	}
//
//	size_t end = GetLength() - startIndex;
//	size_t start = count > end ? 0 : end - count;
//
//	if (start == 0 && end == GetLength())
//	{
//		for (size_t i = 0; i < arrayLength; ++i)
//		{
//			auto ch = wcsrchr(mStr.data(), *(array + i));
//			if (ch != nullptr) return ch - mStr.data();
//		}
//	}
//	else
//	{
//		wchar_t* ch = new wchar_t[end - start];
//		for (size_t i = 0, j = start; j < end; ++i, ++j)
//		{
//			ch[i] = mStr[j];
//		}
//
//		size_t ret = 0;
//
//		for (size_t i = 0; i < arrayLength; ++i)
//		{
//			auto pos = wcsrchr(ch, *(array + i));
//			if (pos != nullptr) {
//				ret = pos - ch + (GetLength() - startIndex - count);
//				delete[] ch;
//				return ret;
//			}
//		}
//
//		delete[] ch;
//	}
//
//	return -1;
//}
//
//Array<String> String::InternalSplit(const wchar_t* c, int count, Array<size_t>& array, StringSplitOptions options) const noexcept {
//
//	if (count > array.GetLength()) count = array.GetLength();
//
//	size_t length = wcslen(c);
//
//	//Handle the special case of no replaces and special count.
//	if (array.GetLength() == 0) 
//	{
//		return Array<String>{mStr.data()};
//	}
//
//	Queue<String> q;
//
//	size_t start = 0;
//	size_t end;
//	size_t charSize;
//
//	switch (options) {
//	case StringSplitOptions::RemoveEmptyEntries:
//		if (array[0] != 0) {
//			if (count > 1)
//				end = array[0] - 1;
//			else
//				end = GetLength();
//			charSize = end - start;
//			wchar_t* buffer = new wchar_t[charSize + 1];
//			std::copy(mStr.data() + start, mStr.data() + end + 1, buffer);
//			*(buffer + charSize + 1) = '\0';
//			q.Enqueue(buffer);
//			delete[] buffer;
//		}
//
//		for (size_t i = 0; i < count; ++i) {
//
//			start = array[i] + length;
//
//			if (count - 1 > i)
//				end = array[i + 1] - 1;
//			else
//				end = GetLength();
//
//			if (start <= end) {
//				charSize = end - start;
//				wchar_t* buffer = new wchar_t[charSize + 1];
//				std::copy(mStr.data() + start, mStr.data() + end + 1, buffer);
//				*(buffer + charSize + 1) = '\0';
//				q.Enqueue(buffer);
//				delete[] buffer;
//			}
//		}
//
//		break;
//	default:
//
//		if (array[0] == 0)
//			q.Enqueue(String{});
//		else {
//			if (count > 1)
//				end = array[0] - 1;
//			else
//				end = GetLength();
//			charSize = end - start;
//			wchar_t* buffer = new wchar_t[charSize + 1];
//			std::copy(mStr.data() + start, mStr.data() + end + 1, buffer);
//			*(buffer + charSize + 1) = '\0';
//			q.Enqueue(buffer);
//			delete[] buffer;
//		}
//
//		for (size_t i = 0; i < count; ++i) {
//
//			start = array[i] + length;
//
//			if (count - 1 > i)
//				end = array[i + 1] - 1;
//			else
//				end = GetLength();
//
//			if (start > end) q.Enqueue(String{});
//			else {
//				charSize = end - start;
//				wchar_t* buffer = new wchar_t[charSize + 1];
//				std::copy(mStr.data() + start, mStr.data() + end + 1, buffer);
//				*(buffer + charSize + 1) = '\0';
//				q.Enqueue(buffer);
//				delete[] buffer;
//			}
//		}
//
//		break;
//	}
//
//	return Array<String>();
//}
//
//String String::Join(wchar_t separator, Array<String>& arrayString) noexcept {
//	wchar_t temp[2] = { separator, '\0' };
//	return String::Join(temp, arrayString);
//}
//
//String String::Join(wchar_t separator, Array<String>&& arrayString) noexcept {
//	wchar_t temp[2] = { separator, '\0' };
//	return String::Join(temp, arrayString);
//}
//
//String String::Join(const wchar_t* separator, Array<String>& arrayString) noexcept {
//
//	if (arrayString.GetLength() == 0) return String{};
//
//	size_t totalSize = 0;
//	for (const auto& x : arrayString)
//		totalSize += x.GetLength();
//
//	totalSize += arrayString.GetLength();
//
//	wchar_t* buffer = new wchar_t[totalSize];
//	size_t start = 0;
//	size_t end = 0;
//	size_t length = wcslen(separator);
//
//	for (size_t i = 0; i < arrayString.GetLength(); ++i) 
//	{
//		String stg = arrayString[i];
//		start = i == 0 ? 0 : end + length;
//		end = i == 0 ? stg.GetLength() : start + stg.GetLength();
//
//		std::copy(stg.mStr.data(), stg.mStr.data() + stg.GetLength(), buffer + start);
//
//		if (i == arrayString.GetLength() - 1)
//			*(buffer + end) = '\0';
//		else
//			std::copy(separator, separator + length, buffer + end);
//	}
//
//	String cat = buffer;
//	delete[] buffer;
//
//	return cat;
//}
//
//String String::Join(const wchar_t* separator, Array<String>&& arrayString) noexcept {
//	return String::Join(separator, arrayString);
//}
//
//size_t String::LastIndexOf(wchar_t c, StringComparison options) const noexcept {
//	wchar_t temp[2] = { c, '\0' };
//	return InternalLastIndexOf(temp, 0, GetLength(), options);
//}
//
//size_t String::LastIndexOf(wchar_t c, int startIndex, StringComparison options) const noexcept {
//	wchar_t temp[2] = { c, '\0' };
//	return InternalLastIndexOf(temp, startIndex, GetLength(), options);
//}
//
//size_t String::LastIndexOf(wchar_t c, int startIndex, int count, StringComparison options) const noexcept {
//	wchar_t temp[2] = { c, '\0' };
//	return InternalLastIndexOf(temp, startIndex, count, options);
//}
//
//size_t String::LastIndexOf(const wchar_t* c, StringComparison options) const noexcept {
//	return InternalLastIndexOf(c, 0, GetLength(), options);
//}
//
//size_t String::LastIndexOf(const wchar_t* c, int startIndex, StringComparison options) const noexcept {
//	return InternalLastIndexOf(c, startIndex, GetLength(), options);
//}
//
//size_t String::LastIndexOf(const wchar_t* c, int startIndex, int count, StringComparison options) const noexcept {
//	return InternalLastIndexOf(c, startIndex, count, options);
//}
//
//size_t String::LastIndexOfAny(const wchar_t array[]) const noexcept {
//	return InternalLastIndexOfAny(array, 0, GetLength());
//}
//
//size_t String::LastIndexOfAny(const wchar_t array[], int startIndex) const noexcept {
//	return InternalLastIndexOfAny(array, startIndex, GetLength());
//}
//
//size_t String::LastIndexOfAny(const wchar_t array[], int startIndex, int count) const noexcept {
//	return InternalLastIndexOfAny(array, startIndex, count);
//}
//
//Array<String> String::Split(wchar_t delimiter, int count) {
//	if (count < 0) throw std::invalid_argument("count");
//
//	if ((GetLength() == 0)) {
//		return Array<String>{mStr.data()};
//	}
//
//	auto array = IndicesOf(delimiter);
//	wchar_t temp[2] = { delimiter, '\0' };
//	return InternalSplit(temp, count, array);
//
//	return Array<String>();
//}
//
//String String::PadLeft(size_t width) const noexcept {
//	return PadLeft(width, ' ');
//}
//
//String String::PadLeft(size_t width, wchar_t padding) const noexcept {
//
//	// Avoids the user to push \0 at the beginning of the string
//	if (padding == '\0') padding = '0';
//
//	if (width <= GetLength()) return mStr.data();
//	wchar_t* c = new wchar_t[width];
//	for (size_t i = 0; i < width - GetLength(); ++i) c[i] = padding;
//	for (size_t i = 0; i < GetLength(); ++i) c[i + width - GetLength()] = mStr[i];
//	String ret = c;
//	delete[] c;
//	return ret;
//
//	return L"";
//}
//
//String String::PadRight(size_t width) const noexcept {
//	return PadRight(width, ' ');
//}
//
//String String::PadRight(size_t width, wchar_t padding) const noexcept {
//	// Avoids the user to push \0 at the end of the string
//	if (padding == '\0') padding = '0';
//
//	if (width <= GetLength()) return mStr.data();
//	wchar_t* c = new wchar_t[width];
//	for (size_t i = 0; i < GetLength(); ++i) c[i] = mStr[i];
//	for (size_t i = 0; i < width - GetLength(); ++i) c[i + GetLength()] = padding;
//	String ret = c;
//	delete[] c;
//	return ret;
//}
//
//String String::Remove(int startIndex) const {
//	return Remove(startIndex, startIndex);
//}
//
//String String::Remove(int startIndex, int count) const {
//	if (startIndex < 0) throw std::invalid_argument("startIndex");
//	if (count < 0) throw std::invalid_argument("count");
//	if (count == 0) return mStr.data();
//	if (count > GetLength() - startIndex) count = GetLength() - startIndex;
//
//	if (count == GetLength() && startIndex == 0) return L"";
//
//	size_t newSize = GetLength() - count;
//	wchar_t* ch = new wchar_t[newSize];
//	for (size_t i = 0; i < startIndex; ++i)
//		ch[i] = mStr[i];
//
//	for (size_t i = startIndex + count, j = startIndex; j < newSize; ++i, ++j)
//		ch[j] = mStr[i];
//
//	ch[newSize] = '\0';
//
//	String ret = ch;
//	delete[] ch;
//	return ret;
//}
//
//String String::Replace(wchar_t oldValue, wchar_t newValue) const noexcept 
//{
//	wchar_t* newStr = new wchar_t[GetLength() + 1];
//
//	for (size_t i = 0; i < GetLength(); ++i)
//	{
//		if (mStr[i] == oldValue) newStr[i] = newValue;
//		else newStr[i] = mStr[i];
//	}
//
//	newStr[GetLength()] = '\0';
//
//	String ret = newStr;
//	delete[] newStr;
//	return ret;
//}
//
//String String::Replace(const wchar_t* oldValue, const wchar_t* newValue) const noexcept 
//{
//	const size_t oldSize = wcslen(oldValue);
//	const size_t newSize = wcslen(newValue);
//
//	// diff < 0 = OLD IS LARGER
//	// diff > 0 = NEW IS LARGER
//	const int diff = newSize - oldSize;
//
//	if (oldSize == 0) return mStr.data();
//
//	Array<size_t> idx = IndicesOf(oldValue);
//	if (idx.GetLength() == 0) return mStr.data();
//
//	size_t newcpSize = GetLength() + diff * (idx.GetLength());
//	wchar_t* ch = new wchar_t[newcpSize];
//
//	for (size_t i = 0, j = 0, l = 0; i < newcpSize;) 
//	{
//		if (j < idx.GetLength() && idx[j] == i - (diff * (int)j))
//		{
//			for (size_t k = 0; k < newSize; ++i, ++k) {
//				ch[i] = newValue[k];
//			}
//			l += oldSize;
//			++j;
//		}
//		else {
//			ch[i] = mStr[l];
//			++i;
//			++l;
//		}
//	}
//
//	ch[newcpSize] = '\0';
//	String ret = ch;
//	delete[] ch;
//	return ret;
//}
//
//Array<String> String::Split(const wchar_t* delimiter, int count) {
//	if (count < 0) throw std::invalid_argument("count");
//
//	if ((GetLength() == 0)) {
//		return Array<String>{mStr.data()};
//	}
//
//	auto array = IndicesOf(delimiter);
//	return InternalSplit(delimiter, count, array);
//}
//
//Array<String> String::Split(wchar_t delimiter, StringSplitOptions options) const noexcept {
//	if (GetLength() == 0) {
//		if (options == StringSplitOptions::RemoveEmptyEntries) return Array<String>{};
//		else return Array<String>{mStr.data()};
//	}
//
//	auto array = IndicesOf(delimiter);
//	wchar_t temp[2] = { delimiter, '\0' };
//	return InternalSplit(temp, array.GetLength(), array, options);
//}
//
//Array<String> String::Split(const wchar_t* delimiter, StringSplitOptions options) const noexcept {
//	if (GetLength() == 0) {
//		if (options == StringSplitOptions::RemoveEmptyEntries) return Array<String>{};
//		else return Array<String>{mStr.data()};
//	}
//
//	auto array = IndicesOf(delimiter);
//	return InternalSplit(delimiter, array.GetLength(), array, options);
//}
//
//Array<String> String::Split(wchar_t delimiter, int count, StringSplitOptions options) const {
//	if (count < 0) throw std::invalid_argument("count");
//
//	if (GetLength() == 0) {
//		if (options == StringSplitOptions::RemoveEmptyEntries) return Array<String>{};
//		else return Array<String>{mStr.data()};
//	}
//
//	auto array = IndicesOf(delimiter);
//	wchar_t temp[2] = { delimiter, '\0' };
//	return InternalSplit(temp, count, array, options);
//}
//
//Array<String> String::Split(const wchar_t* delimiter, int count, StringSplitOptions options) const {
//	if (count < 0) throw std::invalid_argument("count");
//
//	if (GetLength() == 0) {
//		if (options == StringSplitOptions::RemoveEmptyEntries) return Array<String>{};
//		else return Array<String>{mStr.data()};
//	}
//
//	auto array = IndicesOf(delimiter);
//	return InternalSplit(delimiter, count, array, options);
//}
//
//Boolean String::StartsWith(const wchar_t* c, StringComparison options) const noexcept {
//	const size_t s = wcslen(c);
//	switch (options) 
//	{
//	case StringComparison::CaseSensitive:
//		if (wcsncmp(mStr.data(), c, s) == 0) return true;
//		break;
//	case StringComparison::CaseInsensitive:
//		if (wcsnicmp(mStr.data(), c, s) == 0) return true;
//		break;
//	}
//	return false;
//}
//
//String String::Substring(int startIndex) const {
//	return Substring(startIndex, GetLength() - startIndex);
//}
//
//String String::Substring(int startIndex, int length) const {
//	if (startIndex < 0) throw std::out_of_range("startIndex");
//	if (startIndex > GetLength()) throw std::out_of_range("startIndex");
//	if (length < 0) throw std::out_of_range("length");
//	if (startIndex > GetLength() - length) throw std::out_of_range("length");
//
//	if (length == 0) return String{};
//	if (startIndex == 0 && length == GetLength()) return String{ mStr.data() };
//
//	size_t size = length - startIndex;
//	wchar_t* c = new wchar_t[size];
//	wcsncpy_s(c, size, mStr.data() + startIndex, length);
//	String ret = c;
//	delete[] c;
//	return ret;
//}
//
//Array<Char> String::ToCharArray() const noexcept {
//	if (GetLength() == 0) return Array<Char>{};
//
//	Array<Char> array(GetLength());
//	for (size_t i = 0; i < array.GetLength(); ++i) {
//		array[i] = mStr[i];
//	}
//
//	return array;
//}
//
//String String::ToLower() const noexcept {
//	wchar_t* ch = new wchar_t[GetLength()];
//
//	for (size_t i = 0; i < GetLength(); ++i) {
//		ch[i] = tolower((wchar_t)mStr[i]);
//	}
//
//	String ret = ch;
//	delete[] ch;
//	return ret;
//}
//
//String String::ToUpper() const noexcept {
//	wchar_t* ch = new wchar_t[GetLength()];
//
//	for (size_t i = 0; i < GetLength(); ++i) {
//		ch[i] = toupper((wchar_t)mStr[i]);
//	}
//
//	String ret = ch;
//	delete[] ch;
//	return ret;
//}
//
//String String::Trim() const noexcept {
//	return mStr.trim().data();
//}
//
//String String::Trim(wchar_t c) const noexcept {
//	wchar_t temp[2] = { c, '\0' };
//	return Trim(temp);
//}
//
//String String::Trim(const wchar_t* c) const noexcept
//{
//	if (GetLength() == 0) return "";
//	if (wcscmp(c, L"") == 0) return mStr.data();
//
//	auto p = mStr.data();
//	size_t start = 0;
//	size_t length = wcslen(c);
//	size_t start2 = 0;
//	while (*p == *(c + start2)) {
//		++start;
//		++p;
//		++start2;
//		if (start2 == length) start2 = 0;
//	}
//
//	size_t end = GetLength() - 1;;
//	p = mStr + end;
//	size_t end2 = length - 1;
//	while (*p == *(c + end2)) {
//		--end;
//		--p;
//		--end2;
//		if (end2 == -1) end2 = length - 1;
//	}
//
//	end = (size_t)(mStr + end) - (size_t)mStr.data();
//	wchar_t* temp = new wchar_t[end - start + 1];
//	std::copy(mStr + start, mStr + end + 1, temp);
//	temp[end - start + 1] = '\0';
//	String ret = temp;
//	delete[] temp;
//	return ret;
//}
//
//String String::TrimEnd() const noexcept {
//	return mStr.rtrim().data();
//}
//
//String String::TrimEnd(wchar_t c) const noexcept {
//	wchar_t temp[2] = { c, '\0' };
//	return Trim(temp);
//}
//
//String String::TrimEnd(const wchar_t* c) const noexcept {
//	if (GetLength() == 0) return "";
//	if (wcscmp(c, L"") == 0) return mStr.data();
//
//	size_t end = GetLength() - 1;;
//	auto p = mStr + end;
//	size_t length = wcslen(c);
//	size_t start2 = length - 1;
//	while (*p == *(c + start2)) {
//		--end;
//		--p;
//		--start2;
//		if (start2 == -1) start2 = length - 1;
//	}
//
//	end = (size_t)(mStr + end) - (size_t)mStr.data();
//	wchar_t* temp = new wchar_t[end + 1];
//	std::copy(mStr.data(), mStr + end + 1, temp);
//	temp[end + 1] = '\0';
//	String ret = temp;
//	delete[] temp;
//	return ret;
//}
//
//String String::TrimStart() const noexcept {
//	return mStr.ltrim().data();
//}
//
//String String::TrimStart(wchar_t c) const noexcept {
//	wchar_t temp[2] = { c, '\0' };
//	return TrimStart(temp);
//}
//
//String String::TrimStart(const wchar_t* c) const noexcept {
//	if (GetLength() == 0) return "";
//	if (wcscmp(c, L"") == 0) return mStr.data();
//
//	auto p = mStr.data();
//	size_t start = 0;
//	size_t length = wcslen(c);
//	size_t start2 = 0;
//	while (*p == *(c + start2))
//	{
//		++start;
//		++p;
//		++start2;
//		if (start2 == length) start2 = 0;
//	}
//
//	return mStr.data() + start;
//}
