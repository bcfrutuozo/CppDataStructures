//
// Created by bcfrutuozo on 18/03/2022.
//

#ifndef CPPDATASTRUCTURES_TEST_QUEUE_HPP
#define CPPDATASTRUCTURES_TEST_QUEUE_HPP

#include <catch2/catch.hpp>
#include <cstring>
#include "../Queue.h"

TEST_CASE("Queue<T>")
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
                REQUIRE(c == Queue<uint8_t>{1u, 2u, 3u, 4u, 5u});
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
                REQUIRE(c == Queue<uint16_t>{1u, 2u, 3u, 4u, 5u});
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
                REQUIRE(c == Queue<uint32_t>{1u, 2u, 3u, 4u, 5u});
            }

            SECTION("Queue<uint64_t>")
            {
                Queue<uint64_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue(1ul);
                c.Enqueue(2ul);
                c.Enqueue(3ul);
                c.Enqueue(4ul);
                c.Enqueue(5ul);
                REQUIRE(c.GetLength() == 5);
                REQUIRE(c == Queue<uint64_t>{1ul, 2ul, 3ul, 4ul, 5ul});
            }

            SECTION("Queue<int8_t>")
            {
                Queue<int8_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue(1);
                c.Enqueue(2);
                c.Enqueue(3);
                c.Enqueue(4);
                c.Enqueue(5);
                REQUIRE(c.GetLength() == 5);
                REQUIRE(c == Queue<int8_t>{1, 2, 3, 4, 5});
            }

            SECTION("Queue<int16_t>")
            {
                Queue<int16_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue(1);
                c.Enqueue(2);
                c.Enqueue(3);
                c.Enqueue(4);
                c.Enqueue(5);
                REQUIRE(c.GetLength() == 5);
                REQUIRE(c == Queue<int16_t>{1, 2, 3, 4, 5});
            }

            SECTION("Queue<int32_t>")
            {
                Queue<int32_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue(1);
                c.Enqueue(2);
                c.Enqueue(3);
                c.Enqueue(4);
                c.Enqueue(5);
                REQUIRE(c.GetLength() == 5);
                REQUIRE(c == Queue<int32_t>{1, 2, 3, 4, 5});
            }

            SECTION("Queue<int64_t>")
            {
                Queue<int64_t> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue(1l);
                c.Enqueue(2l);
                c.Enqueue(3l);
                c.Enqueue(4l);
                c.Enqueue(5l);
                REQUIRE(c.GetLength() == 5);
                REQUIRE(c == Queue<int64_t>{1l, 2l, 3l, 4l, 5l});
            }

            SECTION("Queue<char>")
            {
                Queue<char> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue('1');
                c.Enqueue('2');
                c.Enqueue('3');
                c.Enqueue('4');
                c.Enqueue('5');
                REQUIRE(c.GetLength() == 5);
                REQUIRE(c == Queue<char>{'1', '2', '3', '4', '5'});
            }

            SECTION("Queue<unsigned char>")
            {
                Queue<unsigned char> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue('1');
                c.Enqueue('2');
                c.Enqueue('3');
                c.Enqueue('4');
                c.Enqueue('5');
                REQUIRE(c.GetLength() == 5);
                REQUIRE(c == Queue<unsigned char>{'1', '2', '3', '4', '5'});
            }

            SECTION("Queue<float>")
            {
                Queue<float> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue(1.0f);
                c.Enqueue(2.0f);
                c.Enqueue(3.0f);
                c.Enqueue(4.0f);
                c.Enqueue(5.0);
                REQUIRE(c.GetLength() == 5);
                REQUIRE(c == Queue<float>{1.0f, 2.0f, 3.0f, 4.0f, 5.0f});
            }

            SECTION("Queue<double>")
            {
                Queue<double> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue(1.0f);
                c.Enqueue(2.0f);
                c.Enqueue(3.0f);
                c.Enqueue(4.0f);
                c.Enqueue(5.0);
                REQUIRE(c.GetLength() == 5);
                REQUIRE(c == Queue<double>{1.0f, 2.0f, 3.0f, 4.0f, 5.0f});
            }
        }

        SECTION("Non-primitive types")
        {
            SECTION("Queue<const char*> Array")
            {
                Queue<const char *> c;
                REQUIRE(c.GetLength() == 0);
                c.Enqueue("ABC");
                c.Enqueue("BRUNO");
                c.Enqueue("FRUTUOZO");
                REQUIRE(c.GetLength() == 3);
                REQUIRE(c == Queue<const char*>{"ABC", "BRUNO", "FRUTUOZO"});
            }
        }

        SECTION("Copy constructor")
        {
            Queue<int> a{1, 2, 3, 4, 5, 6};
            Queue<int> b(a);

            REQUIRE(a == b);
            a.Enqueue(7);
            REQUIRE(a != b);
            REQUIRE(a.Dequeue() == 1);
            REQUIRE(a == Queue<int>{2, 3, 4, 5, 6, 7});
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
            Queue<int> c{2, 3, 4, 5, 6, 7};
            REQUIRE(a.Dequeue() == 1);
            REQUIRE(a == c);
            a.Dequeue();
            a.Enqueue(10);
            REQUIRE(a != b);
        }

        SECTION("Move constructor")
        {
            Queue<int> a{1, 2, 3, 4};
            Queue<int> b = std::move(a);
            REQUIRE(a.IsEmpty());
            REQUIRE(b == Queue<int>({1, 2, 3, 4}));
        }

        SECTION("Move assignment")
        {
            Queue<int> a{1, 2, 3, 4};
            Queue<int> b{5, 6};
            b = std::move(a);
            REQUIRE(a.IsEmpty());
            REQUIRE(b == Queue<int>({1, 2, 3, 4}));
        }
    }

    SECTION("Comparison")
    {
        SECTION("Queue<T> == Queue<T>")
        {
            REQUIRE(Queue<int>{1, 2, 3, 4, 5, 6} == Queue<int>{1, 2, 3, 4, 5, 6});
        }

        SECTION("Queue<T> != Queue<T>")
        {
            REQUIRE(Queue<int>{1, 2, 3, 4, 5, 6} != Queue<int>{1, 2, 3, 0, 5, 6});
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
                REQUIRE(c == Queue<const char *> {"TEST", "LOREM", "ABC", "DEF", "ZZZ"});
            }

            SECTION("Array of elements")
            {
                Queue<const char *> c = {"A", "TEST", "LOREM", "TEST", "TEST2", "TEST3"};
                REQUIRE(c.GetLength() == 6);
                Array<const char *> a = c.Dequeue(3);
                REQUIRE(a.GetLength() == 3);
                REQUIRE(c.GetLength() == 3);
                REQUIRE(strcmp(a[0], "A") == 0);
                REQUIRE(strcmp(a[1], "TEST") == 0);
                REQUIRE(strcmp(a[2], "LOREM") == 0);
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

    SECTION("Clear container")
    {
        Queue<const char *> a{"ABC", "DEF", "GHIJKLM"};
        a.Clear();
        REQUIRE(a == Queue<const char*>{});
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

    SECTION("Conversion to Array<T>") {
        Queue<int> a{1, 2, 3, 4, 5};
        Array<int> b = a.ToArray();
        REQUIRE(a == Queue<int>{1, 2, 3, 4, 5});
        REQUIRE(b == Array<int>{1, 2, 3, 4, 5});
    }

    SECTION("CopyTo(Array<T>)") {
        Queue<int> a{1, 2, 3, 4, 5, 6};
        Array<int> b{0, 0, 0, 0, 0, 0, 0, 0};
        a.CopyTo(b, 2);
        REQUIRE(b == Array<int>{0, 0, 1, 2, 3, 4, 5, 6});

        Array<int> c;
        CHECK_THROWS(a.CopyTo(c, 0));

        Array<int> d{1, 2, 3};
        a.CopyTo(d, 2);
        REQUIRE(d == Array<int>{1, 2, 1, 2, 3, 4, 5, 6});

        Array<int> e{1};
        CHECK_THROWS(a.CopyTo(e, 1));

        Array<int> f{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        a.CopyTo(f, 2);
        REQUIRE(f == Array<int>{0, 0, 1, 2, 3, 4, 5, 6, 0, 0});
    }
}

#endif //CPPDATASTRUCTURES_TEST_QUEUE_HPP