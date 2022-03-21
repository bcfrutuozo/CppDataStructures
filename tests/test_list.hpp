//
// Created by bcfrutuozo on 19/03/2022.
//

#ifndef CPPDATASTRUCTURES_TEST_LIST_HPP
#define CPPDATASTRUCTURES_TEST_LIST_HPP

#include <catch2/catch.hpp>
#include <cstring>
#include <ostream>
#include "../List.h"

TEST_CASE("List")
{
    SECTION("Instantiation")
    {
        SECTION("Primitive types")
        {
            SECTION("List<uint8_t>")
            {
                List<uint8_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1u);
                c.Add(2u);
                c.Add(3u);
                c.Add(4u);
                c.Add(5u);
                REQUIRE(c.GetLength() == 5);
                List<uint8_t> c2 = {1u, 2u, 3u, 4u, 5u};
                REQUIRE(c == c2);
            }

            SECTION("List<uint16_t>")
            {
                List<uint16_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1u);
                c.Add(2u);
                c.Add(3u);
                c.Add(4u);
                c.Add(5u);
                REQUIRE(c.GetLength() == 5);
                List<uint16_t> c2 = {1u, 2u, 3u, 4u, 5u};
                REQUIRE(c == c2);
            }

            SECTION("List<uint32_t>")
            {
                List<uint32_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1u);
                c.Add(2u);
                c.Add(3u);
                c.Add(4u);
                c.Add(5u);
                REQUIRE(c.GetLength() == 5);
                List<uint32_t> c2 = {1u, 2u, 3u, 4u, 5u};
                REQUIRE(c == c2);
            }

            SECTION("List<uint64_t>")
            {
                List<uint64_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1ul);
                c.Add(2ul);
                c.Add(3ul);
                c.Add(4ul);
                c.Add(5ul);
                REQUIRE(c.GetLength() == 5);
                List<uint64_t> c2 = {1ul, 2ul, 3ul, 4ul, 5ul};
                REQUIRE(c == c2);
            }

            SECTION("List<int8_t>")
            {
                List<int8_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1);
                c.Add(2);
                c.Add(3);
                c.Add(4);
                c.Add(5);
                REQUIRE(c.GetLength() == 5);
                List<int8_t> c2 = {1, 2, 3, 4, 5};
                REQUIRE(c == c2);
            }

            SECTION("List<int16_t>")
            {
                List<int16_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1);
                c.Add(2);
                c.Add(3);
                c.Add(4);
                c.Add(5);
                REQUIRE(c.GetLength() == 5);
                List<int16_t> c2 = {1, 2, 3, 4, 5};
                REQUIRE(c == c2);
            }

            SECTION("List<int32_t>")
            {
                List<int32_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1);
                c.Add(2);
                c.Add(3);
                c.Add(4);
                c.Add(5);
                REQUIRE(c.GetLength() == 5);
                List<int32_t> c2 = {1, 2, 3, 4, 5};
                REQUIRE(c == c2);
            }

            SECTION("List<int64_t>")
            {
                List<int64_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1l);
                c.Add(2l);
                c.Add(3l);
                c.Add(4l);
                c.Add(5l);
                REQUIRE(c.GetLength() == 5);
                List<int64_t> c2 = {1l, 2l, 3l, 4l, 5l};
                REQUIRE(c == c2);
            }

            SECTION("List<char>")
            {
                List<char> c;
                REQUIRE(c.GetLength() == 0);
                c.Add('1');
                c.Add('2');
                c.Add('3');
                c.Add('4');
                c.Add('5');
                REQUIRE(c.GetLength() == 5);
                List<char> c2 = {'1', '2', '3', '4', '5'};
                REQUIRE(c == c2);
            }

            SECTION("List<unsigned char>")
            {
                List<unsigned char> c;
                REQUIRE(c.GetLength() == 0);
                c.Add('1');
                c.Add('2');
                c.Add('3');
                c.Add('4');
                c.Add('5');
                REQUIRE(c.GetLength() == 5);
                List<unsigned char> c2 = {'1', '2', '3', '4', '5'};
                REQUIRE(c == c2);
            }

            SECTION("List<float>")
            {
                List<float> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1.0f);
                c.Add(2.0f);
                c.Add(3.0f);
                c.Add(4.0f);
                c.Add(5.0);
                REQUIRE(c.GetLength() == 5);
                List<float> c2 = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                REQUIRE(c == c2);
            }

            SECTION("List<double>")
            {
                List<double> c;
                REQUIRE(c.GetLength() == 0);
                c.Add(1.0f);
                c.Add(2.0f);
                c.Add(3.0f);
                c.Add(4.0f);
                c.Add(5.0);
                REQUIRE(c.GetLength() == 5);
                List<double> c2 = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                REQUIRE(c == c2);
            }
        }

        SECTION("Non-primitive types")
        {
            SECTION("List<const char*> Array")
            {
                List<const char *> c;
                REQUIRE(c.GetLength() == 0);
                c.Add("ABC");
                c.Add("BRUNO");
                c.Add("FRUTUOZO");
                REQUIRE(c.GetLength() == 3);
            }
        }

        SECTION("Copy constructor")
        {
            List<int> a{1, 2, 3, 4, 5, 6};
            List<int> b(a);

            REQUIRE(a == b);
            a.Add(7);
            REQUIRE(a != b);
            List<int> c{2, 3, 4, 5, 6, 7};
            a.Remove(1);
            REQUIRE(a == c);
            a.Remove(2);
            a.Add(10);
            REQUIRE(a != b);
        }

        SECTION("Copy assignment constructor")
        {
            List<int> a{1, 2, 3, 4, 5, 6};
            List<int> b = a;

            REQUIRE(a == b);
            a.Add(7);
            REQUIRE(a != b);
            List<int> c{2, 3, 4, 5, 6, 7};
            a.Remove(1);
            REQUIRE(a == c);
            a.Remove(2);
            a.Add(10);
            REQUIRE(a != b);
        }
    }

    SECTION("Comparison")
    {
        SECTION("List<T> == List<T>")
        {
            List<int> a{1, 2, 3, 4, 5, 6};
            List<int> b{1, 2, 3, 4, 5, 6};

            REQUIRE(a == b);
        }

        SECTION("List<T> != List<T>")
        {
            List<int> a{1, 2, 3, 4, 5, 6};
            List<int> b{1, 2, 3, 0, 5, 6};

            REQUIRE(a != b);
        }
    }

    SECTION("Elements insertion")
    {
        SECTION("Adding element at the end of List<T>")
        {
            List<const char *> cpList = {"BRUNO", "FRUTUOZO", "ENGINEERING", "LOREM", "IPSUM"};
            REQUIRE(cpList.GetLength() == 5);
            REQUIRE(cpList.LastIndex() == 4);

            cpList.Add("NEW");
            cpList.Add("NEW 2");
            cpList.Add("NEW 3");
            REQUIRE(cpList.GetLength() == 8);
            REQUIRE(cpList.LastIndex() == 7);

            List<const char *> other = {"BRUNO", "FRUTUOZO", "ENGINEERING", "LOREM", "IPSUM", "NEW", "NEW 2", "NEW 3"};
            REQUIRE(cpList == other);
        }

        SECTION("Adding a collection of elements to the List<T>")
        {
            List<const char *> cpList = {"BRUNO", "FRUTUOZO", "ENGINEERING", "LOREM", "IPSUM"};
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

            List<const char *> other = {"BRUNO", "FRUTUOZO", "ENGINEERING", "LOREM", "IPSUM",
                                        "Single New",
                                        "ELEMENT 1", "ELEMENT 2", "ELEMENT 3", "ELEMENT 4", "ELEMENT 5",
                                        "C",
                                        "ELEMENT 6", "ELEMENT 7", "ELEMENT 8", "ELEMENT 9", "ELEMENT 10"};

            REQUIRE(cpList == other);
        }

        SECTION("Adding element to an specific index")
        {
            List<char> a = {'1', '3', '4', '2', '8'};
            a.AddAt('1', 2);
            List<char> b = {'1', '3', '1', '4', '2', '8'};
            REQUIRE(a == b);
            a.AddAt('9', 5);
            List<char> c = {'1', '3', '1', '4', '2', '9', '8'};
            REQUIRE(a == c);

            List<int> d;
            d.AddAt(1, 0);
            List<int> e = {1};
            REQUIRE(d == e);

            List<int> f;
            CHECK_THROWS(f.AddAt(1, 1));
        }

        SECTION("Adding collection at the middle of the container")
        {
            List<char> a = {1, 3, -4, 2, 8};
            List<char> b = {1, 3, 100, -4, 2, 8};
            a.AddRangeAt(b, 1);
            List<char> final = {1, 1, 3, 100, -4, 2, 8, 3, -4, 2, 8};
            REQUIRE(a == final);

            List<char> c = {1, 3, -4, 2, 8};
            List<char> d = {1, 3, 100, -4, 2, 8};
            c.AddRangeAt(d, 0);
            List<char> final2 = {1, 3, 100, -4, 2, 8, 1, 3, -4, 2, 8};
            REQUIRE(c == final2);

            List<char> e = {1, 3, -4, 2, 8};
            List<char> f = {1, 3, 100, -4, 2, 8};
            e.AddRangeAt(f, e.LastIndex());
            List<char> final3 = {1, 3, -4, 2, 1, 3, 100, -4, 2, 8, 8};
            REQUIRE(e == final3);
        }
    }

    SECTION("Clear container")
    {
        List<const char*> a { "ABC", "DEF", "GHIJKLM" };
        a.Clear();
        List<const char*> b;
        REQUIRE(a == b);
    }
}

#endif //CPPDATASTRUCTURES_TEST_LIST_HPP
