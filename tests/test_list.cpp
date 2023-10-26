//
// Created by bcfrutuozo on 19/03/2022.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/collections/List.hpp"

TEST_CASE("List<T>")
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
                REQUIRE(c == List<uint8_t>{1u, 2u, 3u, 4u, 5u});
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
                REQUIRE(c == List<uint16_t>{1u, 2u, 3u, 4u, 5u});
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
                REQUIRE(c == List<uint32_t>{1u, 2u, 3u, 4u, 5u});
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
                REQUIRE(c == List<uint64_t>{1ul, 2ul, 3ul, 4ul, 5ul});
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
                REQUIRE(c == List<int8_t>{1, 2, 3, 4, 5});
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
                REQUIRE(c == List<int16_t>{1, 2, 3, 4, 5});
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
                REQUIRE(c == List<int32_t>{1, 2, 3, 4, 5});
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
                REQUIRE(c == List<int64_t>{1l, 2l, 3l, 4l, 5l});
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
                REQUIRE(c == List<char>{'1', '2', '3', '4', '5'});
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
                REQUIRE(c == List<unsigned char>{'1', '2', '3', '4', '5'});
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
                REQUIRE(c == List<float>{1.0f, 2.0f, 3.0f, 4.0f, 5.0f});
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
                REQUIRE(c == List<double>{1.0f, 2.0f, 3.0f, 4.0f, 5.0f});
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
            a.Remove(1);
            REQUIRE(a == List<int>{2, 3, 4, 5, 6, 7});
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
            a.Remove(1);
            REQUIRE(a == List<int>{2, 3, 4, 5, 6, 7});
            a.Remove(2);
            a.Add(10);
            REQUIRE(a != b);
        }

        SECTION("Move constructor")
        {
            List<int> a{1, 2, 3, 4};
            List<int> b = std::move(a);
            REQUIRE(a.IsEmpty());
            REQUIRE(b == List<int>({1, 2, 3, 4}));
        }

        SECTION("Move assignment")
        {
            List<int> a{1, 2, 3, 4};
            List<int> b{5, 6};
            b = std::move(a);
            REQUIRE(a.IsEmpty());
            REQUIRE(b == List<int>({1, 2, 3, 4}));
        }
    }

    SECTION("Comparison")
    {
        SECTION("List<T> == List<T>")
        {
            REQUIRE(List<int>{1, 2, 3, 4, 5, 6} == List<int>{1, 2, 3, 4, 5, 6});
        }

        SECTION("List<T> != List<T>")
        {
            REQUIRE(List<int>{1, 2, 3, 4, 5, 6} != List<int>{1, 2, 3, 0, 5, 6});
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
            REQUIRE(cpList == List<const char *>{"BRUNO", "FRUTUOZO", "ENGINEERING", "LOREM", "IPSUM", "NEW", "NEW 2", "NEW 3"});
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
            REQUIRE(cpList == List<const char *>{"BRUNO", "FRUTUOZO", "ENGINEERING", "LOREM", "IPSUM",
                                                          "Single New",
                                                          "ELEMENT 1", "ELEMENT 2", "ELEMENT 3", "ELEMENT 4", "ELEMENT 5",
                                                          "C",
                                                          "ELEMENT 6", "ELEMENT 7", "ELEMENT 8", "ELEMENT 9", "ELEMENT 10"});
        }

        SECTION("Adding element to an specific index")
        {
            List<char> a = {'1', '3', '4', '2', '8'};
            a.AddAt('1', 2);
            REQUIRE(a ==  List<char>{'1', '3', '1', '4', '2', '8'});
            a.AddAt('9', 5);
            REQUIRE(a == List<char>{'1', '3', '1', '4', '2', '9', '8'});

            List<int> d;
            d.AddAt(1, 0);
            REQUIRE(d == List<int>{1});

            List<int> f;
            CHECK_THROWS(f.AddAt(1, 1));
        }

        SECTION("Adding collection at the middle of the container")
        {
            List<char> a = {1, 3, -4, 2, 8};
            List<char> b = {1, 3, 100, -4, 2, 8};
            a.AddRangeAt(b, 1);
            REQUIRE(a == List<char>{1, 1, 3, 100, -4, 2, 8, 3, -4, 2, 8});

            List<char> c = {1, 3, -4, 2, 8};
            List<char> d = {1, 3, 100, -4, 2, 8};
            c.AddRangeAt(d, 0);
            REQUIRE(c == List<char>{1, 3, 100, -4, 2, 8, 1, 3, -4, 2, 8});

            List<char> e = {1, 3, -4, 2, 8};
            List<char> f = {1, 3, 100, -4, 2, 8};
            e.AddRangeAt(f, e.LastIndex());
            REQUIRE(e == List<char>{1, 3, -4, 2, 1, 3, 100, -4, 2, 8, 8});
        }
    }

    SECTION("Elements removal")
    {
        SECTION("Remove at the beginning of List<T>")
        {
            List<int> il{0, 2, 8, 45, -332, 1};
            REQUIRE(il.GetLength() == 6);
            REQUIRE(il.RemoveAt(0) == 0);
            REQUIRE(il.GetLength() == 5);
            REQUIRE(il.RemoveAt(0) == 2);
            REQUIRE(il.GetLength() == 4);
            REQUIRE(il == List<int>{8, 45, -332, 1});
        }

        SECTION("Remove in the middle of List<T>")
        {
            List<int> il{0, 2, 8, 45, -332, 1};
            REQUIRE(il.GetLength() == 6);
            REQUIRE(il.RemoveAt(3) == 45);
            REQUIRE(il.GetLength() == 5);
            REQUIRE(il.RemoveAt(2) == 8);
            REQUIRE(il.GetLength() == 4);
            REQUIRE(il == List<int>{0, 2, -332, 1});
        }

        SECTION("Remove at the end of List<T>")
        {
            List<int> il{0, 2, 8, 45, -332, 1};
            REQUIRE(il.GetLength() == 6);
            REQUIRE(il.RemoveAt(5) == 1);
            REQUIRE(il.GetLength() == 5);
            REQUIRE(il.RemoveAt(4) == -332);
            REQUIRE(il.GetLength() == 4);
            REQUIRE(il == List<int>{0, 2, 8, 45});
        }

        SECTION("Remove an specific element")
        {
            List<int> il{0, 1, 2, 3, 4, 5};
            il.Remove(3);
            REQUIRE(il == List<int>{0, 1, 2, 4, 5});
            il.Remove(0);
            REQUIRE(il == List<int>{1, 2, 4, 5});
            il.Remove(5);
            REQUIRE(il == List<int>{1, 2, 4});
            REQUIRE(il.Remove(100) == false);
        }

        SECTION("Remove an range of elements")
        {
            List<int> il{1, 2, 3, 4, 5, 6, 7, 8, 9};
            REQUIRE(il.RemoveRange(1, 3) == Array<int>({2, 3, 4}));
            REQUIRE(il.RemoveRange(0, 2) == Array<int>({1, 5}));
            REQUIRE(il.RemoveRange(2, 2) == Array<int>({8, 9}));
            REQUIRE(il == List<int>{6, 7});
            CHECK_THROWS(il.RemoveRange(0, 0));
            CHECK_THROWS(il.RemoveRange(0, 3));
            CHECK_THROWS(il.RemoveRange(2, 0));
        }
    }

    SECTION("Clear container")
    {
        List<const char *> a{"ABC", "DEF", "GHIJKLM"};
        a.Clear();
        REQUIRE(a == List<const char*>{});
    }

    SECTION("Obtain index information according to argument")
    {
        SECTION("Find the index of the first occurrence")
        {
            List<long> a{0l, -3321475l, 3218875l, -1l, 0l, 4005822, 0l, 0l, 3323411l, -3321, 97057l, 0l};
            REQUIRE(a.IndexOf(0l) == 0);
            REQUIRE(a.IndexOf(-1l) == 3);
            REQUIRE(a.IndexOf(97057l) == 10);
            REQUIRE(a.IndexOf(444444) == -1);
        }

        SECTION("Find the index of the last occurrence")
        {
            List<long> a{0l, -3321, 3218875l, -1l, 0l, 4005822, 0l, 0l, 3323411l, -3321, 97057l, 0l};
            REQUIRE(a.LastIndexOf(0l) == 11);
            REQUIRE(a.LastIndexOf(-3321) == 9);
            REQUIRE(a.LastIndexOf(3218875l) == 2);
            REQUIRE(a.LastIndexOf(-4444) == -1);
        }

        SECTION("Find all indices ")
        {
            List<long> a{0l, -3321, 3218875l, -1l, 0l, 4005822, 0l, 0l, 3323411l, -3321, 97057l, 0l};
            REQUIRE(a.IndicesOf(0l) == Array<size_t>{0ul, 4ul, 6ul, 7ul, 11ul});
            REQUIRE(a.IndicesOf(-3321) == Array<size_t>{1ul, 9ul});
            REQUIRE(a.IndicesOf(-4444) == Array<size_t>{});
        }
    }

    SECTION("Check if element exists in List<T>")
    {
        List<const char *> a{"BRUNO", "FRUTUOZO", "LOREM", "IMPSUM"};
        REQUIRE(a.Contains("LOREM") == 1);
        REQUIRE(a.Contains("TEST") == 0);
    }

    SECTION("Count an specified element within the List<T>")
    {
        List<int> a{0, 4, 3, 1, 1, 1, 1, 1, 3, 3, 2, 1, 0, 6, 0, -4, -2, 1};
        REQUIRE(a.Count(0) == 3);
        REQUIRE(a.Count(1) == 7);
        REQUIRE(a.Count(-4) == 1);
        REQUIRE(a.Count(-999) == 0);
        REQUIRE(a.Count(3) == 3);
    }

    SECTION("Swap List<T> container")
    {
        List<int> a{0, 1, 2, 3};
        List<int> b{9, 8, 7, 6};
        a.Swap(b);
        a.Remove(6);
        a.Remove(7);
        a.Remove(8);
        a.Remove(9);
        REQUIRE(a == List<int>{});
        b.Remove(3);
        b.Remove(2);
        b.Remove(1);
        b.Remove(0);
        REQUIRE(b == List<int>{});
    }

    SECTION("Head analysis")
    {
        List<int> a{0, 1, 2, 3};
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
        List<int> a{0, 1, 2, 3};
        a.AddAt(4, 4);
        REQUIRE(a.IndexOf(3) == 3);
        REQUIRE(a.IndexOf(4) == 4);
        a.AddAt(5, 4);
        REQUIRE(a.IndexOf(5) == 4);
        REQUIRE(a.IndexOf(4) == 5);
        REQUIRE(a == List<int>{0, 1, 2, 3, 5, 4});

        a.AddRangeAt({-3, -2}, 5);
        REQUIRE(a == List<int>{0, 1, 2, 3, 5, -3, -2, 4});
        a.AddRangeAt({1, 2}, 8);
        REQUIRE(a == List<int>{0, 1, 2, 3, 5, -3, -2, 4, 1, 2});
        a.RemoveAt(9);
        REQUIRE(a == List<int>{0, 1, 2, 3, 5, -3, -2, 4, 1});
        a.RemoveRange(7, 2);
        REQUIRE(a == List<int>{0, 1, 2, 3, 5, -3, -2});
        CHECK_THROWS(a.RemoveRange(6, 2));
    }

    SECTION("Iterators")
    {
        SECTION("List<T>::Iterator")
        {
            std::ostringstream oss;
            List<const char *> c = {"ABC", "DEF", "G", "HI", "J", "KLMNOPQ"};

            for (auto it = c.begin(); it != c.end(); ++it) {
                *it = "A";
                oss << *it;
            }

            REQUIRE(strcmp("AAAAAA", oss.str().c_str()) == 0);
        }

        SECTION("List<T>::ConstIterator")
        {
            std::ostringstream oss;
            List<const char *> c = {"ABC", "DEF", "G", "HI", "J", "KLMNOPQ"};

            for (auto it = c.cbegin(); it != c.cend(); ++it) {
                oss << *it;
            }

            REQUIRE(strcmp("ABCDEFGHIJKLMNOPQ", oss.str().c_str()) == 0);
        }
    }
}