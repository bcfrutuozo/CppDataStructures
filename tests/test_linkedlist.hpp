//
// Created by bcfrutuozo on 22/03/2022.
//

#ifndef CPPDATASTRUCTURES_TEST_LINKEDLIST_HPP
#define CPPDATASTRUCTURES_TEST_LINKEDLIST_HPP

#include <catch2/catch.hpp>
#include <cstring>
#include <ostream>
#include "../LinkedList.h"

TEST_CASE("LinkedList<T>")
{
    SECTION("Instantiation")
    {
        SECTION("Primitive types")
        {
            SECTION("LinkedList<uint8_t>")
            {
                LinkedList<uint8_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1u);
                c.Add(2u);
                c.Add(3u);
                c.Add(4u);
                c.Add(5u);
                REQUIRE(c.GetLength() == 5);
                LinkedList<uint8_t> c2 = {1u, 2u, 3u, 4u, 5u};
                REQUIRE(c == c2);
            }

            SECTION("LinkedList<uint16_t>")
            {
                LinkedList<uint16_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1u);
                c.Add(2u);
                c.Add(3u);
                c.Add(4u);
                c.Add(5u);
                REQUIRE(c.GetLength() == 5);
                LinkedList<uint16_t> c2 = {1u, 2u, 3u, 4u, 5u};
                REQUIRE(c == c2);
            }

            SECTION("LinkedList<uint32_t>")
            {
                LinkedList<uint32_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1u);
                c.Add(2u);
                c.Add(3u);
                c.Add(4u);
                c.Add(5u);
                REQUIRE(c.GetLength() == 5);
                LinkedList<uint32_t> c2 = {1u, 2u, 3u, 4u, 5u};
                REQUIRE(c == c2);
            }

            SECTION("LinkedList<uint64_t>")
            {
                LinkedList<uint64_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1ul);
                c.Add(2ul);
                c.Add(3ul);
                c.Add(4ul);
                c.Add(5ul);
                REQUIRE(c.GetLength() == 5);
                LinkedList<uint64_t> c2 = {1ul, 2ul, 3ul, 4ul, 5ul};
                REQUIRE(c == c2);
            }

            SECTION("LinkedList<int8_t>")
            {
                LinkedList<int8_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1);
                c.Add(2);
                c.Add(3);
                c.Add(4);
                c.Add(5);
                REQUIRE(c.GetLength() == 5);
                LinkedList<int8_t> c2 = {1, 2, 3, 4, 5};
                REQUIRE(c == c2);
            }

            SECTION("LinkedList<int16_t>")
            {
                LinkedList<int16_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1);
                c.Add(2);
                c.Add(3);
                c.Add(4);
                c.Add(5);
                REQUIRE(c.GetLength() == 5);
                LinkedList<int16_t> c2 = {1, 2, 3, 4, 5};
                REQUIRE(c == c2);
            }

            SECTION("LinkedList<int32_t>")
            {
                LinkedList<int32_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1);
                c.Add(2);
                c.Add(3);
                c.Add(4);
                c.Add(5);
                REQUIRE(c.GetLength() == 5);
                LinkedList<int32_t> c2 = {1, 2, 3, 4, 5};
                REQUIRE(c == c2);
            }

            SECTION("LinkedList<int64_t>")
            {
                LinkedList<int64_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1l);
                c.Add(2l);
                c.Add(3l);
                c.Add(4l);
                c.Add(5l);
                REQUIRE(c.GetLength() == 5);
                LinkedList<int64_t> c2 = {1l, 2l, 3l, 4l, 5l};
                REQUIRE(c == c2);
            }

            SECTION("LinkedList<char>")
            {
                LinkedList<char> c;
                REQUIRE(c.GetLength() == 0);
                c.Add('1');
                c.Add('2');
                c.Add('3');
                c.Add('4');
                c.Add('5');
                REQUIRE(c.GetLength() == 5);
                LinkedList<char> c2 = {'1', '2', '3', '4', '5'};
                REQUIRE(c == c2);
            }

            SECTION("LinkedList<unsigned char>")
            {
                LinkedList<unsigned char> c;
                REQUIRE(c.GetLength() == 0);
                c.Add('1');
                c.Add('2');
                c.Add('3');
                c.Add('4');
                c.Add('5');
                REQUIRE(c.GetLength() == 5);
                LinkedList<unsigned char> c2 = {'1', '2', '3', '4', '5'};
                REQUIRE(c == c2);
            }

            SECTION("LinkedList<float>")
            {
                LinkedList<float> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1.0f);
                c.Add(2.0f);
                c.Add(3.0f);
                c.Add(4.0f);
                c.Add(5.0);
                REQUIRE(c.GetLength() == 5);
                LinkedList<float> c2 = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                REQUIRE(c == c2);
            }

            SECTION("LinkedList<double>")
            {
                LinkedList<double> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1.0f);
                c.Add(2.0f);
                c.Add(3.0f);
                c.Add(4.0f);
                c.Add(5.0);
                REQUIRE(c.GetLength() == 5);
                LinkedList<double> c2 = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                REQUIRE(c == c2);
            }
        }

        SECTION("Non-primitive types")
        {
            SECTION("LinkedList<const char*> Array")
            {
                LinkedList<const char *> c;
                REQUIRE(c.GetLength() == 0);
                c.Add("ABC");
                c.Add("BRUNO");
                c.Add("FRUTUOZO");
                REQUIRE(c.GetLength() == 3);
            }
        }

        SECTION("Copy constructor")
        {
            LinkedList<int> a{1, 2, 3, 4, 5, 6};
            LinkedList<int> b(a);

            REQUIRE(a == b);
            a.Add(7);
            REQUIRE(a != b);
            LinkedList<int> c{2, 3, 4, 5, 6, 7};
            a.Remove(1);
            REQUIRE(a == c);
            a.Remove(2);
            a.Add(10);
            REQUIRE(a != b);
        }

        SECTION("Copy assignment constructor")
        {
            LinkedList<int> a{1, 2, 3, 4, 5, 6};
            LinkedList<int> b = a;

            REQUIRE(a == b);
            a.Add(7);
            REQUIRE(a != b);
            LinkedList<int> c{2, 3, 4, 5, 6, 7};
            a.Remove(1);
            REQUIRE(a == c);
            a.Remove(2);
            a.Add(10);
            REQUIRE(a != b);
        }

        SECTION("Move constructor")
        {
            LinkedList<int> a{1, 2, 3, 4};
            LinkedList<int> b = std::move(a);
            REQUIRE(a.IsEmpty());
            REQUIRE(b == LinkedList<int>({1, 2, 3, 4}));
        }

        SECTION("Move assignment")
        {
            LinkedList<int> a{1, 2, 3, 4};
            LinkedList<int> b{5, 6};
            b = std::move(a);
            REQUIRE(a.IsEmpty());
            REQUIRE(b == LinkedList<int>({1, 2, 3, 4}));
        }
    }

    SECTION("Comparison")
    {
        SECTION("LinkedList<T> == LinkedList<T>")
        {
            LinkedList<int> a{1, 2, 3, 4, 5, 6};
            LinkedList<int> b{1, 2, 3, 4, 5, 6};

            REQUIRE(a == b);
        }

        SECTION("LinkedList<T> != LinkedList<T>")
        {
            LinkedList<int> a{1, 2, 3, 4, 5, 6};
            LinkedList<int> b{1, 2, 3, 0, 5, 6};

            REQUIRE(a != b);
        }
    }

    SECTION("Elements insertion")
    {
        SECTION("Adding element at the end of LinkedList<T>")
        {
            LinkedList<const char *> cpList = {"BRUNO", "FRUTUOZO", "ENGINEERING", "LOREM", "IPSUM"};
            REQUIRE(cpList.GetLength() == 5);
            REQUIRE(cpList.LastIndex() == 4);

            cpList.Add("NEW");
            cpList.Add("NEW 2");
            cpList.Add("NEW 3");
            REQUIRE(cpList.GetLength() == 8);
            REQUIRE(cpList.LastIndex() == 7);

            LinkedList<const char *> other = {"BRUNO", "FRUTUOZO", "ENGINEERING", "LOREM", "IPSUM", "NEW", "NEW 2",
                                              "NEW 3"};
            REQUIRE(cpList == other);
        }

        SECTION("Adding a collection of elements to the List<T>")
        {
            LinkedList<const char *> cpList = {"BRUNO", "FRUTUOZO", "ENGINEERING", "LOREM", "IPSUM"};
            REQUIRE(cpList.GetLength() == 5);
            REQUIRE(cpList.LastIndex() == 4);

            cpList.Add("Single New");
            cpList.AddRange({"ELEMENT 1", "ELEMENT 2", "ELEMENT 3", "ELEMENT 4", "ELEMENT 5",
                             "C",
                             "ELEMENT 6", "ELEMENT 7", "ELEMENT 8", "ELEMENT 9", "ELEMENT 10"});

            // Checking index and Size
            REQUIRE(cpList.GetLength() == 17);
            REQUIRE(cpList.LastIndex() == 16);

            // Checking element contents
            REQUIRE(cpList.IndexOf("ENGINEERING") == 2);
            REQUIRE(cpList.IndexOf("Single New") == 5);
            REQUIRE(cpList.IndexOf("ELEMENT 10") == 16);

            LinkedList<const char *> other = {"BRUNO", "FRUTUOZO", "ENGINEERING", "LOREM", "IPSUM",
                                              "Single New",
                                              "ELEMENT 1", "ELEMENT 2", "ELEMENT 3", "ELEMENT 4", "ELEMENT 5",
                                              "C",
                                              "ELEMENT 6", "ELEMENT 7", "ELEMENT 8", "ELEMENT 9", "ELEMENT 10"};

            REQUIRE(cpList == other);
        }

        SECTION("Adding element to an specific index")
        {
            LinkedList<char> a = {'1', '3', '4', '2', '8'};
            a.AddAt('1', 2);
            LinkedList<char> b = {'1', '3', '1', '4', '2', '8'};
            REQUIRE(a == b);
            a.AddAt('9', 5);
            LinkedList<char> c = {'1', '3', '1', '4', '2', '9', '8'};
            REQUIRE(a == c);

            LinkedList<int> d;
            d.AddAt(1, 0);
            LinkedList<int> e = {1};
            REQUIRE(d == e);

            List<int> f;
            CHECK_THROWS(f.AddAt(1, 1));
        }

        SECTION("Adding collection at the middle of the container")
        {
            LinkedList<char> a = {1, 3, -4, 2, 8};
            LinkedList<char> b = {1, 3, 100, -4, 2, 8};
            a.AddRangeAt(b, 1);
            LinkedList<char> final = {1, 1, 3, 100, -4, 2, 8, 3, -4, 2, 8};
            REQUIRE(a == final);

            LinkedList<char> c = {1, 3, -4, 2, 8};
            LinkedList<char> d = {1, 3, 100, -4, 2, 8};
            c.AddRangeAt(d, 0);
            LinkedList<char> final2 = {1, 3, 100, -4, 2, 8, 1, 3, -4, 2, 8};
            REQUIRE(c == final2);

            LinkedList<char> e = {1, 3, -4, 2, 8};
            LinkedList<char> f = {1, 3, 100, -4, 2, 8};
            e.AddRangeAt(f, e.LastIndex());
            LinkedList<char> final3 = {1, 3, -4, 2, 1, 3, 100, -4, 2, 8, 8};
            REQUIRE(e == final3);
        }
    }

    SECTION("Elements removal")
    {
        SECTION("Remove at the beginning of LinkedList<T>")
        {
            LinkedList<int> il{0, 2, 8, 45, -332, 1};
            REQUIRE(il.GetLength() == 6);
            REQUIRE(il.RemoveAt(0) == 0);
            REQUIRE(il.GetLength() == 5);
            REQUIRE(il.RemoveAt(0) == 2);
            REQUIRE(il.GetLength() == 4);
            REQUIRE(il == LinkedList<int>{8, 45, -332, 1});
        }

        SECTION("Remove in the middle of LinkedList<T>")
        {
            LinkedList<int> il{0, 2, 8, 45, -332, 1};
            REQUIRE(il.GetLength() == 6);
            REQUIRE(il.RemoveAt(3) == 45);
            REQUIRE(il.GetLength() == 5);
            REQUIRE(il.RemoveAt(2) == 8);
            REQUIRE(il.GetLength() == 4);
            REQUIRE(il == LinkedList<int>{0, 2, -332, 1});
        }

        SECTION("Remove at the end of LinkedList<T>")
        {
            LinkedList<int> il{0, 2, 8, 45, -332, 1};
            REQUIRE(il.GetLength() == 6);
            REQUIRE(il.RemoveAt(5) == 1);
            REQUIRE(il.GetLength() == 5);
            REQUIRE(il.RemoveAt(4) == -332);
            REQUIRE(il.GetLength() == 4);

            LinkedList<int> end{0, 2, 8, 45};
            REQUIRE(il == end);
        }

        SECTION("Remove an specific element")
        {
            LinkedList<int> il{0, 1, 2, 3, 4, 5};
            il.Remove(3);
            REQUIRE(il == LinkedList<int>{0, 1, 2, 4, 5});
            il.Remove(0);
            REQUIRE(il == LinkedList<int>{1, 2, 4, 5});
            il.Remove(5);
            REQUIRE(il == LinkedList<int>{1, 2, 4});
            REQUIRE(il.Remove(100) == false);
        }

        SECTION("Remove an range of elements")
        {
            LinkedList<int> il{1, 2, 3, 4, 5, 6, 7, 8, 9};
            REQUIRE(il.RemoveRange(1, 3) == Array<int>({2, 3, 4}));
            REQUIRE(il == LinkedList<int>{1, 5, 6, 7, 8, 9});
            REQUIRE(il.RemoveRange(0, 2) == Array<int>({1, 5}));
            REQUIRE(il == LinkedList<int>{6, 7, 8, 9});
            REQUIRE(il.RemoveRange(2, 2) == Array<int>({8, 9}));
            REQUIRE(il == LinkedList<int>{6, 7});
            CHECK_THROWS(il.RemoveRange(0, 0));
            CHECK_THROWS(il.RemoveRange(0, 3));
            CHECK_THROWS(il.RemoveRange(2, 0));
        }

        SECTION("Remove last specified element")
        {
            LinkedList<int> il{1, 2, 3, 4, 1, 6, 7, 8, 1};
            il.RemoveLast(1);
            REQUIRE(il == LinkedList<int>{1, 2, 3, 4, 1, 6, 7, 8});
            il.RemoveLast(1);
            REQUIRE(il == LinkedList<int>{1, 2, 3, 4, 6, 7, 8});
            il.RemoveLast(1);
            REQUIRE(il == LinkedList<int>{2, 3, 4, 6, 7, 8});
            il.RemoveLast(8);
            REQUIRE(il == LinkedList<int>{2, 3, 4, 6, 7});
            // Block to check for Head or Tail corruption
            il.AddAt(0, 0);
            il.Add(10);
            REQUIRE(il == LinkedList<int>{0, 2, 3, 4, 6, 7, 10});
            REQUIRE(il.GetLength() == 7);

            std::ostringstream oss;
            for(auto it = il.cbegin(); it != il.cend(); ++it)
                oss << *it;
            REQUIRE(strcmp(oss.str().c_str(), "02346710") == 0);
            oss.str("");
            oss.clear();
            for(auto it = il.crbegin(); it != il.crend(); ++it)
                oss << *it;
            REQUIRE(strcmp(oss.str().c_str(), "10764320") == 0);
        }
    }

    SECTION("Clear container")
    {
        LinkedList<const char *> a{"ABC", "DEF", "GHIJKLM"};
        a.Clear();
        LinkedList<const char *> b;
        REQUIRE(a == b);
    }

    SECTION("Obtain index information according to argument")
    {
        SECTION("Find the index of the first occurrence")
        {
            LinkedList<long> a{0l, -3321475l, 3218875l, -1l, 0l, 4005822, 0l, 0l, 3323411l, -3321, 97057l, 0l};
            REQUIRE(a.IndexOf(0l) == 0);
            REQUIRE(a.IndexOf(-1l) == 3);
            REQUIRE(a.IndexOf(97057l) == 10);
            REQUIRE(a.IndexOf(444444) == -1);
        }

        SECTION("Find the index of the last occurrence")
        {
            LinkedList<long> a{0l, -3321, 3218875l, -1l, 0l, 4005822, 0l, 0l, 3323411l, -3321, 97057l, 0l};
            REQUIRE(a.LastIndexOf(0l) == 11);
            REQUIRE(a.LastIndexOf(-3321) == 9);
            REQUIRE(a.LastIndexOf(3218875l) == 2);
            REQUIRE(a.LastIndexOf(-4444) == -1);
        }

        SECTION("Find all indices ")
        {
            LinkedList<long> a{0l, -3321, 3218875l, -1l, 0l, 4005822, 0l, 0l, 3323411l, -3321, 97057l, 0l};
            Array<size_t> indicesCheck1 = {0ul, 4ul, 6ul, 7ul, 11ul};
            Array<size_t> indicesCheck2 = {1ul, 9ul};
            Array<size_t> indicesCheck3 = {};
            REQUIRE(indicesCheck1 == a.IndicesOf(0l));
            REQUIRE(indicesCheck2 == a.IndicesOf(-3321));
            REQUIRE(indicesCheck3 == a.IndicesOf(-4444));
        }
    }

    SECTION("Check if element exists in LinkedList<T>")
    {
        LinkedList<const char *> a{"BRUNO", "FRUTUOZO", "LOREM", "IMPSUM"};
        REQUIRE(a.Contains("LOREM") == 1);
        REQUIRE(a.Contains("TEST") == 0);
    }

    SECTION("Count an specified element within the LinkedList<T>")
    {
        LinkedList<int> a{0, 4, 3, 1, 1, 1, 1, 1, 3, 3, 2, 1, 0, 6, 0, -4, -2, 1};
        REQUIRE(a.Count(0) == 3);
        REQUIRE(a.Count(1) == 7);
        REQUIRE(a.Count(-4) == 1);
        REQUIRE(a.Count(-999) == 0);
        REQUIRE(a.Count(3) == 3);
    }

    SECTION("Swap LinkedList<T> container")
    {
        LinkedList<int> a{0, 1, 2, 3};
        LinkedList<int> b{9, 8, 7, 6};
        LinkedList<int> empty;

        a.Swap(b);
        a.Remove(6);
        a.Remove(7);
        a.Remove(8);
        a.Remove(9);
        REQUIRE(a == empty);
        b.Remove(3);
        b.Remove(2);
        b.Remove(1);
        b.Remove(0);
        REQUIRE(b == empty);
    }

    SECTION("Head analysis")
    {
        LinkedList<int> a{0, 1, 2, 3};
        a.AddAt(-1, 0);
        REQUIRE(a.IndexOf(-1) == 0);
        a.AddRangeAt({-3, -2}, 0);
        REQUIRE(a.IndexOf(-3) == 0);
        a.Remove(-3);
        REQUIRE(a.IndexOf(-2) == 0);
        REQUIRE(a.RemoveAt(0) == -2);
        a.RemoveAll(-1);
        REQUIRE(a.IndexOf(0) == 0);
    }

    SECTION("Tail analysis")
    {
        LinkedList<int> a{0, 1, 2, 3};
        a.AddAt(4, 4);
        REQUIRE(a.IndexOf(3) == 3);
        REQUIRE(a.IndexOf(4) == 4);
        a.AddAt(5, 4);
        REQUIRE(a.IndexOf(5) == 4);
        REQUIRE(a.IndexOf(4) == 5);
        REQUIRE(a == LinkedList<int>{0, 1, 2, 3, 5, 4});

        a.AddRangeAt({-3, -2}, 5);
        REQUIRE(a == LinkedList<int>{0, 1, 2, 3, 5, -3, -2, 4});
        a.AddRangeAt({1, 2}, 8);
        REQUIRE(a == LinkedList<int>{0, 1, 2, 3, 5, -3, -2, 4, 1, 2});
        a.RemoveAt(9);
        REQUIRE(a == LinkedList<int>{0, 1, 2, 3, 5, -3, -2, 4, 1});
        a.RemoveRange(7, 2);
        REQUIRE(a == LinkedList<int>{0, 1, 2, 3, 5, -3, -2});
        CHECK_THROWS(a.RemoveRange(6, 2));
    }

    SECTION("Reverse container")
    {
        LinkedList<const char *> a{"ABC", "DEF", "G", "XY", "Z"};
        a.Reverse();
        REQUIRE(a == LinkedList<const char *>{"Z", "XY", "G", "DEF", "ABC"});
    }

    SECTION("Iterators")
    {
        SECTION("List<T>::Iterator")
        {
            std::ostringstream oss;
            LinkedList<const char *> c = {"ABC", "DEF", "G", "HI", "J", "KLMNOPQ"};

            for (auto it = c.begin(); it != c.end(); ++it) {
                *it = "A";
                oss << *it;
            }

            REQUIRE(strcmp("AAAAAA", oss.str().c_str()) == 0);
        }

        SECTION("List<T>::ConstIterator")
        {
            std::ostringstream oss;
            LinkedList<const char *> c = {"ABC", "DEF", "G", "HI", "J", "KLMNOPQ"};

            for (auto it = c.cbegin(); it != c.cend(); ++it) {
                oss << *it;
            }

            REQUIRE(strcmp("ABCDEFGHIJKLMNOPQ", oss.str().c_str()) == 0);
        }

        SECTION("List<T>::ReverseIterator")
        {
            std::ostringstream oss;
            LinkedList<const char *> c = {"ABC", "DEF", "G", "HI", "J", "KLMNOPQ"};

            for (auto it = c.rbegin(); it != c.rend(); ++it) {
                *it = "A";
                oss << *it;
            }

            REQUIRE(strcmp("AAAAAA", oss.str().c_str()) == 0);
        }

        SECTION("List<T>::ConstReverseIterator")
        {
            std::ostringstream oss;
            LinkedList<const char *> c = {"ABC", "DEF", "G", "HI", "J", "KLMNOPQ"};

            for (auto it = c.crbegin(); it != c.crend(); ++it) {
                oss << *it;
            }

            REQUIRE(strcmp("KLMNOPQJHIGDEFABC", oss.str().c_str()) == 0);
        }
    }
}

#endif //CPPDATASTRUCTURES_TEST_LINKEDLIST_HPP
