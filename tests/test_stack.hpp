//
// Created by bcfrutuozo on 18/03/2022.
//

#ifndef CPPDATASTRUCTURES_TEST_STACK_CPP
#define CPPDATASTRUCTURES_TEST_STACK_CPP

#include <catch2/catch.hpp>
#include <cstring>
#include "../Stack.h"

TEST_CASE("Stack")
{
    SECTION("Instantiation")
    {
        SECTION("Primitive types")
        {
            SECTION("Stack<uint8_t>")
            {
                Stack<uint8_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Push(1u);
                c.Push(2u);
                c.Push(3u);
                c.Push(4u);
                c.Push(5u);
                REQUIRE(c.GetLength() == 5);
                Stack<uint8_t> c2 = {1u, 2u, 3u, 4u, 5u};
                REQUIRE(c == c2);
            }

            SECTION("Stack<uint16_t>")
            {
                Stack<uint16_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Push(1u);
                c.Push(2u);
                c.Push(3u);
                c.Push(4u);
                c.Push(5u);
                REQUIRE(c.GetLength() == 5);
                Stack<uint16_t> c2 = {1u, 2u, 3u, 4u, 5u};
                REQUIRE(c == c2);
            }

            SECTION("Stack<uint32_t>")
            {
                Stack<uint32_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Push(1u);
                c.Push(2u);
                c.Push(3u);
                c.Push(4u);
                c.Push(5u);
                REQUIRE(c.GetLength() == 5);
                Stack<uint32_t> c2 = {1u, 2u, 3u, 4u, 5u};
                REQUIRE(c == c2);
            }

            SECTION("Stack<uint64_t>")
            {
                Stack<uint64_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Push(1ul);
                c.Push(2ul);
                c.Push(3ul);
                c.Push(4ul);
                c.Push(5ul);
                REQUIRE(c.GetLength() == 5);
                Stack<uint64_t> c2 = {1ul, 2ul, 3ul, 4ul, 5ul};
                REQUIRE(c == c2);
            }

            SECTION("Stack<int8_t>")
            {
                Stack<int8_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Push(1);
                c.Push(2);
                c.Push(3);
                c.Push(4);
                c.Push(5);
                REQUIRE(c.GetLength() == 5);
                Stack<int8_t> c2 = {1, 2, 3, 4, 5};
                REQUIRE(c == c2);
            }

            SECTION("Stack<int16_t>")
            {
                Stack<int16_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Push(1);
                c.Push(2);
                c.Push(3);
                c.Push(4);
                c.Push(5);
                REQUIRE(c.GetLength() == 5);
                Stack<int16_t> c2 = {1, 2, 3, 4, 5};
                REQUIRE(c == c2);
            }

            SECTION("Stack<int32_t>")
            {
                Stack<int32_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Push(1);
                c.Push(2);
                c.Push(3);
                c.Push(4);
                c.Push(5);
                REQUIRE(c.GetLength() == 5);
                Stack<int32_t> c2 = {1, 2, 3, 4, 5};
                REQUIRE(c == c2);
            }

            SECTION("Stack<int64_t>")
            {
                Stack<int64_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Push(1l);
                c.Push(2l);
                c.Push(3l);
                c.Push(4l);
                c.Push(5l);
                REQUIRE(c.GetLength() == 5);
                Stack<int64_t> c2 = {1l, 2l, 3l, 4l, 5l};
                REQUIRE(c == c2);
            }

            SECTION("Stack<char>")
            {
                Stack<char> c;
                REQUIRE(c.GetLength() == 0);
                c.Push('1');
                c.Push('2');
                c.Push('3');
                c.Push('4');
                c.Push('5');
                REQUIRE(c.GetLength() == 5);
                Stack<char> c2 = {'1', '2', '3', '4', '5'};
                REQUIRE(c == c2);
            }

            SECTION("Stack<unsigned char>")
            {
                Stack<unsigned char> c;
                REQUIRE(c.GetLength() == 0);
                c.Push('1');
                c.Push('2');
                c.Push('3');
                c.Push('4');
                c.Push('5');
                REQUIRE(c.GetLength() == 5);
                Stack<unsigned char> c2 = {'1', '2', '3', '4', '5'};
                REQUIRE(c == c2);
            }

            SECTION("Stack<float>")
            {
                Stack<float> c;
                REQUIRE(c.GetLength() == 0);
                c.Push(1.0f);
                c.Push(2.0f);
                c.Push(3.0f);
                c.Push(4.0f);
                c.Push(5.0);
                REQUIRE(c.GetLength() == 5);
                Stack<float> c2 = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                REQUIRE(c == c2);
            }

            SECTION("Stack<double>")
            {
                Stack<double> c;
                REQUIRE(c.GetLength() == 0);
                c.Push(1.0f);
                c.Push(2.0f);
                c.Push(3.0f);
                c.Push(4.0f);
                c.Push(5.0);
                REQUIRE(c.GetLength() == 5);
                Stack<double> c2 = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                REQUIRE(c == c2);
            }
        }

        SECTION("Non-primitive types")
        {
            SECTION("Stack<const char*> Array")
            {
                Stack<const char *> c;
                REQUIRE(c.GetLength() == 0);
                c.Push("ABC");
                c.Push("BRUNO");
                c.Push("FRUTUOZO");
                REQUIRE(c.GetLength() == 3);
            }
        }

        SECTION("Copy constructor")
        {
            Stack<int> a{1, 2, 3, 4, 5, 6};
            Stack<int> b(a);

            REQUIRE(a == b);
            a.Push(7);
            REQUIRE(a != b);
            REQUIRE(a.Pop() == 7);
            REQUIRE(a == b);
            a.Pop();
            a.Push(10);
            REQUIRE(a != b);
        }

        SECTION("Copy assignment constructor")
        {
            Stack<int> a{1, 2, 3, 4, 5, 6};
            Stack<int> b = a;

            REQUIRE(a == b);
            a.Push(7);
            REQUIRE(a != b);
            REQUIRE(a.Pop() == 7);
            REQUIRE(a == b);
            a.Pop();
            a.Push(10);
            REQUIRE(a != b);
        }
    }

    SECTION("Push elements")
    {
        SECTION("Single element")
        {
            Stack<const char *> c = {"A", "TEST", "LOREM"};
            c.Push("ZZZZZ");
            REQUIRE(c.GetLength() == 4);
            REQUIRE(strcmp(c.Pop(), "ZZZZZ") == 0);
        }

        SECTION("Array of elements")
        {
            Stack<const char *> c = {"A", "TEST", "LOREM"};
            Array<const char *> a = {"ABC", "DEF", "ZZZ"};
            c.Push(a);
            REQUIRE(c.GetLength() == 6);
            REQUIRE(strcmp(c.Pop(), "ZZZ") == 0);
            REQUIRE(c.GetLength() == 5);
            Stack<const char *> final = {"A", "TEST", "LOREM", "ABC", "DEF"};
            REQUIRE(c == final);
        }
    }

    SECTION("Pop elements")
    {
        SECTION("Single element")
        {
            Stack<int> c = {4, 99, -37, 0, 2};
            REQUIRE(c.Pop() == 2);
            REQUIRE(c.Pop() == 0);
            REQUIRE(c.Pop() == -37);
            REQUIRE(c.Pop() == 99);
            REQUIRE(c.Pop() == 4);
            CHECK_THROWS(c.Pop());
        }

        SECTION("Array of elements")
        {
            Stack<const char *> c = {"A", "TEST", "LOREM", "TEST", "TEST2", "TEST3"};
            REQUIRE(c.GetLength() == 6);
            Array<const char *> a = c.Pop(3);
            REQUIRE(a.GetLength() == 3);
            REQUIRE(c.GetLength() == 3);
            a[0] == "TEST3";
            a[1] == "TEST2";
            a[2] == "TEST";
        }
    }

    SECTION("Check peek")
    {
        Stack<int> c = {4, 99, -37, 0, 2};
        REQUIRE(c.Peek() == 2);
        REQUIRE(c.GetLength() == 5);
        while (!c.IsEmpty())
            c.Pop();
        CHECK_THROWS(c.Peek());
    }

    SECTION("Unload one Stack into another")
    {
        Stack<int> a = {1, 2, 3, 4, 5};
        Stack<int> c = {4, 99, -37};

        Stack<int>::UnloadInto(a, c
        );
        REQUIRE(a.GetLength() == 0);
        REQUIRE(c.GetLength() == 8);
        Stack<int> final = {4, 99, -37, 5, 4, 3, 2, 1};
        REQUIRE(c == final);
    }

    SECTION("Swap container")
    {
        Stack<int> a{0, 1, 2, 3};
        Stack<int> b{9, 8, 7, 6};

        a.Swap(b);
        REQUIRE(a.Pop() == 6);
        REQUIRE(a.Pop() == 7);
        REQUIRE(a.Pop() == 8);
        REQUIRE(a.Pop() == 9);
        CHECK_THROWS(a.Pop());
        REQUIRE(b.Pop() == 3);
        REQUIRE(b.Pop() == 2);
        REQUIRE(b.Pop() == 1);
        REQUIRE(b.Pop() == 0);
        CHECK_THROWS(b.Pop());
    }

    SECTION("Conversion to Array<T>"){
        Stack<int> a { 1, 2, 3, 4, 5 };
        Array<int> b = a.ToArray();
        Stack<int> copy = a;
        Array<int> comp { 1, 2, 3, 4, 5};
        REQUIRE(a == copy);
        REQUIRE(b == comp);
    }
}

#endif //CPPDATASTRUCTURES_TEST_STACK_CPP