//
// Created by bcfrutuozo on 18/03/2022.
//

#ifndef CPPDATASTRUCTURES_TEST_QUEUE_HPP
#define CPPDATASTRUCTURES_TEST_QUEUE_HPP

#include <catch2/catch.hpp>
#include <cstring>
#include "../Queue.h"

TEST_CASE("Queue")
{
    SECTION("Instantiation")
    {
        SECTION("Primitive types")
        {
            SECTION("Queue<uint8_t>")
            {
                Queue<uint8_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue(1u);
                c.Enqueue(2u);
                c.Enqueue(3u);
                c.Enqueue(4u);
                c.Enqueue(5u);
                REQUIRE(c.GetLength() == 5);
                Queue<uint8_t> c2 = {1u, 2u, 3u, 4u, 5u};
                REQUIRE(c == c2);
            }

            SECTION("Queue<uint16_t>")
            {
                Queue<uint16_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue(1u);
                c.Enqueue(2u);
                c.Enqueue(3u);
                c.Enqueue(4u);
                c.Enqueue(5u);
                REQUIRE(c.GetLength() == 5);
                Queue<uint16_t> c2 = {1u, 2u, 3u, 4u, 5u};
                REQUIRE(c == c2);
            }

            SECTION("Queue<uint32_t>")
            {
                Queue<uint32_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue(1u);
                c.Enqueue(2u);
                c.Enqueue(3u);
                c.Enqueue(4u);
                c.Enqueue(5u);
                REQUIRE(c.GetLength() == 5);
                Queue<uint32_t> c2 = {1u, 2u, 3u, 4u, 5u};
                REQUIRE(c == c2);
            }

            SECTION("Stack<uint64_t>")
            {
                Queue<uint64_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue(1ul);
                c.Enqueue(2ul);
                c.Enqueue(3ul);
                c.Enqueue(4ul);
                c.Enqueue(5ul);
                REQUIRE(c.GetLength() == 5);
                Queue<uint64_t> c2 = {1ul, 2ul, 3ul, 4ul, 5ul};
                REQUIRE(c == c2);
            }

            SECTION("Stack<int8_t>")
            {
                Queue<int8_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue(1);
                c.Enqueue(2);
                c.Enqueue(3);
                c.Enqueue(4);
                c.Enqueue(5);
                REQUIRE(c.GetLength() == 5);
                Queue<int8_t> c2 = {1, 2, 3, 4, 5};
                REQUIRE(c == c2);
            }

            SECTION("Stack<int16_t>")
            {
                Queue<int16_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue(1);
                c.Enqueue(2);
                c.Enqueue(3);
                c.Enqueue(4);
                c.Enqueue(5);
                REQUIRE(c.GetLength() == 5);
                Queue<int16_t> c2 = {1, 2, 3, 4, 5};
                REQUIRE(c == c2);
            }

            SECTION("Stack<int32_t>")
            {
                Queue<int32_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue(1);
                c.Enqueue(2);
                c.Enqueue(3);
                c.Enqueue(4);
                c.Enqueue(5);
                REQUIRE(c.GetLength() == 5);
                Queue<int32_t> c2 = {1, 2, 3, 4, 5};
                REQUIRE(c == c2);
            }

            SECTION("Stack<int64_t>")
            {
                Queue<int64_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue(1l);
                c.Enqueue(2l);
                c.Enqueue(3l);
                c.Enqueue(4l);
                c.Enqueue(5l);
                REQUIRE(c.GetLength() == 5);
                Queue<int64_t> c2 = {1l, 2l, 3l, 4l, 5l};
                REQUIRE(c == c2);
            }

            SECTION("Stack<char>")
            {
                Queue<char> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue('1');
                c.Enqueue('2');
                c.Enqueue('3');
                c.Enqueue('4');
                c.Enqueue('5');
                REQUIRE(c.GetLength() == 5);
                Queue<char> c2 = {'1', '2', '3', '4', '5'};
                REQUIRE(c == c2);
            }

            SECTION("Stack<unsigned char>")
            {
                Queue<unsigned char> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue('1');
                c.Enqueue('2');
                c.Enqueue('3');
                c.Enqueue('4');
                c.Enqueue('5');
                REQUIRE(c.GetLength() == 5);
                Queue<unsigned char> c2 = {'1', '2', '3', '4', '5'};
                REQUIRE(c == c2);
            }

            SECTION("Stack<float>")
            {
                Queue<float> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue(1.0f);
                c.Enqueue(2.0f);
                c.Enqueue(3.0f);
                c.Enqueue(4.0f);
                c.Enqueue(5.0);
                REQUIRE(c.GetLength() == 5);
                Queue<float> c2 = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                REQUIRE(c == c2);
            }

            SECTION("Stack<double>")
            {
                Queue<double> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue(1.0f);
                c.Enqueue(2.0f);
                c.Enqueue(3.0f);
                c.Enqueue(4.0f);
                c.Enqueue(5.0);
                REQUIRE(c.GetLength() == 5);
                Queue<double> c2 = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                REQUIRE(c == c2);
            }
        }

        SECTION("Non-primitive types")
        {
            SECTION("Stack<const char*> Array")
            {
                Queue<const char *> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue("ABC");
                c.Enqueue("BRUNO");
                c.Enqueue("FRUTUOZO");
                REQUIRE(c.GetLength() == 3);
            }
        }

        SECTION("Copy constructor")
        {
            Queue<int> a{1, 2, 3, 4, 5, 6};
            Queue<int> b(a);

            REQUIRE(a == b);
            a.Enqueue(7);
            REQUIRE(a != b);
            Queue<int> c {2, 3, 4, 5, 6, 7};
            REQUIRE(a.Dequeue() == 1);
            REQUIRE(a == c);
            a.Dequeue();
            a.Enqueue(10);
            REQUIRE(a != b);
        }

        SECTION("Copy assignment constructor")
        {
            Queue<int> a{1, 2, 3, 4, 5, 6};
            Queue<int> b = a;

            REQUIRE(a == b);
            a.Enqueue(7);
            REQUIRE(a != b);
            Queue<int> c {2, 3, 4, 5, 6, 7};
            REQUIRE(a.Dequeue() == 1);
            REQUIRE(a == c);
            a.Dequeue();
            a.Enqueue(10);
            REQUIRE(a != b);
        }
    }

    SECTION("Push elements")
    {
        SECTION("Single element")
        {
            Queue<const char *> c = {"A", "TEST", "LOREM"};
            c.Enqueue("ZZZZZ");
            REQUIRE(c.GetLength() == 4);
            REQUIRE(strcmp(c.Dequeue(), "A") == 0);
        }

        SECTION("Array of elements")
        {
            SECTION("Single element")
            {
                Queue<const char *> c = {"A", "TEST", "LOREM"};
                Array<const char *> a = {"ABC", "DEF", "ZZZ"};
                c.Enqueue(a);
                REQUIRE(c.GetLength() == 6);
                REQUIRE(strcmp(c.Dequeue(), "A") == 0);
                REQUIRE(c.GetLength() == 5);
                Queue<const char *> final = {"TEST", "LOREM", "ABC", "DEF", "ZZZ"};
                REQUIRE(c == final);
            }

            SECTION("Array of elements")
            {
                Queue<const char *> c = {"A", "TEST", "LOREM", "TEST", "TEST2", "TEST3"};
                REQUIRE(c.GetLength() == 6);
                Array<const char *> a = c.Dequeue(3);
                REQUIRE(a.GetLength() == 3);
                REQUIRE(c.GetLength() == 3);
                a[0] == "A";
                a[1] == "TEST";
                a[2] == "LOREM";
            }
        }
    }

    SECTION("Pop elements")
    {
        Queue<int> c = {4, 99, -37, 0, 2};
        REQUIRE(c.Dequeue() == 4);
        REQUIRE(c.Dequeue() == 99);
        REQUIRE(c.Dequeue() == -37);
        REQUIRE(c.Dequeue() == 0);
        REQUIRE(c.Dequeue() == 2);
        CHECK_THROWS(c.Dequeue());
    }

    SECTION("Check peek")
    {
        Queue<int> c = {4, 99, -37, 0, 2};
        REQUIRE(c.Peek() == 4);
        REQUIRE(c.GetLength() == 5);
        while (!c.IsEmpty())
            c.Dequeue();
        CHECK_THROWS(c.Peek());
    }

    SECTION("Swap container")
    {
        Queue<int> a{0, 1, 2, 3};
        Queue<int> b{9, 8, 7, 6};

        a.Swap(b);
        REQUIRE(a.Dequeue() == 9);
        REQUIRE(a.Dequeue() == 8);
        REQUIRE(a.Dequeue() == 7);
        REQUIRE(a.Dequeue() == 6);
        CHECK_THROWS(a.Dequeue());
        REQUIRE(b.Dequeue() == 0);
        REQUIRE(b.Dequeue() == 1);
        REQUIRE(b.Dequeue() == 2);
        REQUIRE(b.Dequeue() == 3);
        CHECK_THROWS(b.Dequeue());
    }

    SECTION("Conversion to Array<T>"){
        Queue<int> a { 1, 2, 3, 4, 5 };
        Array<int> b = a.ToArray();
        Queue<int> copy = a;
        Array<int> comp { 1, 2, 3, 4, 5};
        REQUIRE(a == copy);
        REQUIRE(b == comp);
    }
}

#endif //CPPDATASTRUCTURES_TEST_QUEUE_HPP