//
// Created by bcfrutuozo on 17/03/2022.
//

#ifndef CPPDATASTRUCTURES_TEST_ARRAY_CPP
#define CPPDATASTRUCTURES_TEST_ARRAY_CPP

#include <catch2/catch.hpp>
#include <cstring>
#include <ostream>
#include "../Array.h"

TEST_CASE("Array")
{
    SECTION("Instantiation")
    {
        SECTION("Primitive types")
        {
            SECTION("Array<uint8_t>")
            {
                Array<uint8_t> c;
                REQUIRE(c.GetLength() == 0);
                Array<uint8_t> cSize(2);
                REQUIRE(cSize.GetLength() == 2);
                Array<uint8_t> cDefault(1, 2);
                REQUIRE(cDefault[0] == 1);
                REQUIRE(cDefault[1] == 1);
                REQUIRE(cDefault.GetLength() == 2);
                Array<uint8_t> arrayu8 = {1, 2, 3, 4, 5};
                REQUIRE(arrayu8.GetLength() == 5);
            }

            SECTION("Array<uint16_t>")
            {
                Array<uint16_t> c;
                REQUIRE(c.GetLength() == 0);
                Array<uint16_t> cSize(2);
                REQUIRE(cSize.GetLength() == 2);
                Array<uint16_t> cDefault(1, 2);
                REQUIRE(cDefault[0] == 1);
                REQUIRE(cDefault[1] == 1);
                REQUIRE(cDefault.GetLength() == 2);
                Array<uint16_t> arrayu16 = {1, 2, 3, 4, 5};
                REQUIRE(arrayu16.GetLength() == 5);
            }

            SECTION("Array<uint32_t>")
            {
                Array<uint32_t> c;
                REQUIRE(c.GetLength() == 0);
                Array<uint32_t> cSize(2);
                REQUIRE(cSize.GetLength() == 2);
                Array<uint32_t> cDefault(1, 2);
                REQUIRE(cDefault[0] == 1);
                REQUIRE(cDefault[1] == 1);
                REQUIRE(cDefault.GetLength() == 2);
                Array<uint32_t> arrayu32 = {1, 2, 3, 4, 5};
                REQUIRE(arrayu32.GetLength() == 5);
            }

            SECTION("Array<uint64_t>")
            {
                Array<uint32_t> c;
                REQUIRE(c.GetLength() == 0);
                Array<uint64_t> cSize(2);
                REQUIRE(cSize.GetLength() == 2);
                Array<uint64_t> cDefault(1, 2);
                REQUIRE(cDefault[0] == 1);
                REQUIRE(cDefault[1] == 1);
                REQUIRE(cDefault.GetLength() == 2);
                Array<uint64_t> arrayu64 = {1, 2, 3, 4, 5};
                REQUIRE(arrayu64.GetLength() == 5);
            }

            SECTION("Array<int8_t>")
            {
                Array<int8_t> c;
                REQUIRE(c.GetLength() == 0);
                Array<int8_t> cSize(2);
                REQUIRE(cSize.GetLength() == 2);
                Array<int8_t> cDefault(1, 2);
                REQUIRE(cDefault[0] == 1);
                REQUIRE(cDefault[1] == 1);
                REQUIRE(cDefault.GetLength() == 2);
                Array<int8_t> array8 = {1, 2, 3, 4, 5};
                REQUIRE(array8.GetLength() == 5);
            }

            SECTION("Array<int16_t>")
            {
                Array<int16_t> c;
                REQUIRE(c.GetLength() == 0);
                Array<int16_t> cSize(2);
                REQUIRE(cSize.GetLength() == 2);
                Array<int16_t> cDefault(1, 2);
                REQUIRE(cDefault[0] == 1);
                REQUIRE(cDefault[1] == 1);
                REQUIRE(cDefault.GetLength() == 2);
                Array<int16_t> array16 = {1, 2, 3, 4, 5};
                REQUIRE(array16.GetLength() == 5);
            }

            SECTION("Array<int32_t>")
            {
                Array<int32_t> c;
                REQUIRE(c.GetLength() == 0);
                Array<int32_t> cSize(2);
                REQUIRE(cSize.GetLength() == 2);
                Array<int32_t> cDefault(1, 2);
                REQUIRE(cDefault[0] == 1);
                REQUIRE(cDefault[1] == 1);
                REQUIRE(cDefault.GetLength() == 2);
                Array<int32_t> array32 = {1, 2, 3, 4, 5};
                REQUIRE(array32.GetLength() == 5);
            }

            SECTION("Array<int64_t>")
            {
                Array<int64_t> c;
                REQUIRE(c.GetLength() == 0);
                Array<int64_t> cSize(2);
                REQUIRE(cSize.GetLength() == 2);
                Array<int64_t> cDefault(1, 2);
                REQUIRE(cDefault[0] == 1);
                REQUIRE(cDefault[1] == 1);
                REQUIRE(cDefault.GetLength() == 2);
                Array<int64_t> array64 = {1, 2, 3, 4, 5};
                REQUIRE(array64.GetLength() == 5);
            }

            SECTION("Array<char>")
            {
                Array<char> c;
                REQUIRE(c.GetLength() == 0);
                Array<char> cSize(2);
                REQUIRE(cSize.GetLength() == 2);
                Array<char> cDefault('1', 2);
                REQUIRE(cDefault[0] == '1');
                REQUIRE(cDefault[1] == '1');
                REQUIRE(cDefault.GetLength() == 2);
                Array<char> arrayc = {'1', '2', '3', '4', '5',};
                REQUIRE(arrayc.GetLength() == 5);
            }

            SECTION("Array<unsigned char>")
            {
                Array<unsigned char> c;
                REQUIRE(c.GetLength() == 0);
                Array<unsigned char> cSize(2);
                REQUIRE(cSize.GetLength() == 2);
                Array<unsigned char> cDefault('1', 2);
                REQUIRE(cDefault[0] == '1');
                REQUIRE(cDefault[1] == '1');
                REQUIRE(cDefault.GetLength() == 2);
                Array<unsigned char> arrayuc = {'1', '2', '3', '4', '5',};
                REQUIRE(arrayuc.GetLength() == 5);
            }

            SECTION("Array<float>")
            {
                Array<float> c;
                REQUIRE(c.GetLength() == 0);
                Array<float> cSize(2);
                REQUIRE(cSize.GetLength() == 2);
                Array<float> cDefault(1.0, 2);
                REQUIRE(cDefault[0] == 1.0);
                REQUIRE(cDefault[1] == 1.0);
                REQUIRE(cDefault.GetLength() == 2);
                Array<float> arrayf = {1.0, 2.0, 3.0, 4.0, 5.0,};
                REQUIRE(arrayf.GetLength() == 5);
            }

            SECTION("Array<double>")
            {
                Array<double> c;
                REQUIRE(c.GetLength() == 0);
                Array<double> cSize(2);
                REQUIRE(cSize.GetLength() == 2);
                Array<double> cDefault(1.0, 2);
                REQUIRE(cDefault[0] == 1.0);
                REQUIRE(cDefault[1] == 1.0);
                REQUIRE(cDefault.GetLength() == 2);
                Array<double> arrayd = {1.0, 2.0, 3.0, 4.0, 5.0,};
                REQUIRE(arrayd.GetLength() == 5);
            }
        }

        SECTION("Non-primitive types")
        {
            SECTION("Array<const char*> Array")
            {
                Array<const char *> c;
                REQUIRE(c.GetLength() == 0);
                Array<const char *> cSize(2);
                REQUIRE(cSize.GetLength() == 2);
                Array<const char *> cDefault("ABCDEF", 2);
                REQUIRE(strcmp(cDefault[0], "ABCDEF") == 0);
                REQUIRE(strcmp(cDefault[1], "ABCDEF") == 0);
                REQUIRE(cDefault.GetLength() == 2);
                Array<const char *> arraycc = {"A", "BRUNO", "LOREM", "TEST"};
                REQUIRE(arraycc.GetLength() == 4);
                REQUIRE(arraycc[0] == "A");
                REQUIRE(arraycc[1] == "BRUNO");
                REQUIRE(arraycc[2] == "LOREM");
                REQUIRE(arraycc[3] == "TEST");
                REQUIRE_THROWS(strcmp(arraycc[4], "ERROR!") == 0);
            }
        }

        SECTION("Copy constructor")
        {
            Array<int> a{1, 2, 3, 4, 5, 6};
            Array<int> b(a);

            REQUIRE(a == b);
            a.Add(7);
            REQUIRE(a != b);
            REQUIRE(a.RemoveBack() == 7);
            REQUIRE(a == b);
            a.RemoveBack();
            a.Add(10);
            REQUIRE(a != b);
        }

        SECTION("Copy assignment constructor")
        {
            Array<int> a{1, 2, 3, 4, 5, 6};
            Array<int> b(a);

            REQUIRE(a == b);
            a.Add(7);
            REQUIRE(a != b);
            REQUIRE(a.RemoveBack() == 7);
            REQUIRE(a == b);
            a.RemoveBack();
            a.Add(10);
            REQUIRE(a != b);
        }

        SECTION("Move constructor")
        {
            Array<int> a{1, 2, 3, 4};
            Array<int> b = std::move(a);
            REQUIRE(a.IsEmpty());
            REQUIRE(b == Array<int>({1, 2, 3, 4}));
        }

        SECTION("Move assignment")
        {
            Array<int> a{1, 2, 3, 4};
            Array<int> b{5, 6};
            b = std::move(a);
            REQUIRE(a.IsEmpty());
            REQUIRE(b == Array<int>({1, 2, 3, 4}));
        }
    }

    SECTION("Comparison")
    {
        SECTION("Array<T> == Array<T>")
        {
            Array<int> a{1, 2, 3, 4, 5, 6};
            Array<int> b{1, 2, 3, 4, 5, 6};

            REQUIRE(a == b);
        }

        SECTION("Array<T> != Array<T>")
        {
            Array<int> a{1, 2, 3, 4, 5, 6};
            Array<int> b{1, 2, 3, 0, 5, 6};

            REQUIRE(a != b);
        }
    }

    SECTION("Elements insertion")
    {
        SECTION("Adding element at the end of a populated Array<T>")
        {
            Array<const char *> cpArray = {"BRUNO", "FRUTUOZO", "ENGINEERING", "LOREM", "IPSUM"};
            REQUIRE(cpArray.GetLength() == 5);
            REQUIRE(cpArray.LastIndex() == 4);

            cpArray.Add("NEW");
            cpArray.Add("NEW 2");
            cpArray.Add("NEW 3");
            REQUIRE(cpArray.GetLength() == 8);
            REQUIRE(cpArray.LastIndex() == 7);

            Array<const char *> other = {"BRUNO", "FRUTUOZO", "ENGINEERING", "LOREM", "IPSUM", "NEW", "NEW 2", "NEW 3"};
            REQUIRE(cpArray == other);
        }

        SECTION("Adding a collection of elements to the Array<T>")
        {
            Array<const char *> cpArray = {"BRUNO", "FRUTUOZO", "ENGINEERING", "LOREM", "IPSUM"};
            REQUIRE(cpArray.GetLength() == 5);
            REQUIRE(cpArray.LastIndex() == 4);

            cpArray.Add("Single New");
            cpArray.Add({"ELEMENT 1", "ELEMENT 2", "ELEMENT 3", "ELEMENT 4", "ELEMENT 5",
                         "C",
                         "ELEMENT 6", "ELEMENT 7", "ELEMENT 8", "ELEMENT 9", "ELEMENT 10"});

            // Checking index and Size
            REQUIRE(cpArray.GetLength() == 17);
            REQUIRE(cpArray.LastIndex() == 16);

            // Checking element contents
            REQUIRE(strcmp(cpArray[2], "ENGINEERING") == 0);
            REQUIRE(strcmp(cpArray[5], "Single New") == 0);
            REQUIRE(strcmp(cpArray[16], "ELEMENT 10") == 0);

            Array<const char *> other = {"BRUNO", "FRUTUOZO", "ENGINEERING", "LOREM", "IPSUM",
                                         "Single New",
                                         "ELEMENT 1", "ELEMENT 2", "ELEMENT 3", "ELEMENT 4", "ELEMENT 5",
                                         "C",
                                         "ELEMENT 6", "ELEMENT 7", "ELEMENT 8", "ELEMENT 9", "ELEMENT 10"};

            REQUIRE(cpArray == other);
        }

        SECTION("Adding element at an empty instantiated Array<T>")
        {
            Array<int> emptyArrayForSingleInsertion;

            // Checking index and Size
            REQUIRE(emptyArrayForSingleInsertion.GetLength() == 0);
            REQUIRE(emptyArrayForSingleInsertion.LastIndex() == -1);

            emptyArrayForSingleInsertion.Add(10);

            // Checking index and Size
            REQUIRE(emptyArrayForSingleInsertion.GetLength() == 1);
            REQUIRE(emptyArrayForSingleInsertion.LastIndex() == 0);

            // Checking element contents
            REQUIRE(emptyArrayForSingleInsertion[0] == 10);
            Array<int> other = {10};
            REQUIRE(emptyArrayForSingleInsertion == other);
        }

        SECTION("Adding a collection of element at an empty instantiated Array<T>")
        {
            Array<int> emptyArrayForRangeInsertion;

            // Checking index and Size
            REQUIRE(emptyArrayForRangeInsertion.GetLength() == 0);
            REQUIRE(emptyArrayForRangeInsertion.LastIndex() == -1);

            emptyArrayForRangeInsertion.Add({4, 6, 3, 1, 6, 6, 6, 19, 2, 164, 52231, 2, 1, 0, -132, -4, -7, 32, -999});

            // Checking index and Size
            REQUIRE(emptyArrayForRangeInsertion.GetLength() == 19);
            REQUIRE(emptyArrayForRangeInsertion.LastIndex() == 18);

            // Checking element contents
            REQUIRE(emptyArrayForRangeInsertion[0] == 4);
            REQUIRE(emptyArrayForRangeInsertion[7] == 19);
            REQUIRE(emptyArrayForRangeInsertion[16] == -7);
            REQUIRE(emptyArrayForRangeInsertion[18] == -999);

            Array<int> other = {4, 6, 3, 1, 6, 6, 6, 19, 2, 164, 52231, 2, 1, 0, -132, -4, -7, 32, -999};
            REQUIRE(emptyArrayForRangeInsertion == other);
        }

        SECTION("Adding element at to an specific index")
        {
            Array<char> a = {'1', '3', '4', '2', '8'};
            a.AddAtIndex('1', 2);
            Array<char> b = {'1', '3', '1', '4', '2', '8'};
            REQUIRE(a == b);
            a.AddAtIndex('9', 5);
            Array<char> c = {'1', '3', '1', '4', '2', '9', '8'};
            REQUIRE(a == c);

            Array<int> d;
            d.AddAtIndex(1, 0);
            Array<int> e = {1};
            REQUIRE(d == e);

            Array<int> f(0);
            CHECK_THROWS(f.AddAtIndex(1, 1));
        }

        SECTION("Adding collection at the middle of the container")
        {
            Array<char> a = {1, 3, -4, 2, 8};
            Array<char> b = {1, 3, 100, -4, 2, 8};
            a.AddAtIndex(b, 1);
            Array<char> final = {1, 1, 3, 100, -4, 2, 8, 3, -4, 2, 8};
            REQUIRE(a == final);

            Array<char> c = {1, 3, -4, 2, 8};
            Array<char> d = {1, 3, 100, -4, 2, 8};
            c.AddAtIndex(d, 0);
            Array<char> final2 = {1, 3, 100, -4, 2, 8, 1, 3, -4, 2, 8};
            REQUIRE(c == final2);

            Array<char> e = {1, 3, -4, 2, 8};
            Array<char> f = {1, 3, 100, -4, 2, 8};
            e.AddAtIndex(f, e.LastIndex());
            Array<char> final3 = {1, 3, -4, 2, 1, 3, 100, -4, 2, 8, 8};
            REQUIRE(e == final3);
        }
    }

    SECTION("First element manipulation from Array<T>")
    {
        SECTION("Trying to remove an element from an empty Array<T>")
        {
            Array<float> fArray{};
            CHECK_THROWS(fArray.GetFront());
        }

        SECTION("Removing an element from Array<T> with single element")
        {
            Array<int> iArray{-44};
            REQUIRE(iArray.GetFront() == -44);
            REQUIRE(iArray.GetLength() == 1);
            REQUIRE(iArray.RemoveFront() == -44);
            REQUIRE(iArray.GetLength() == 0);
            CHECK_THROWS(iArray.GetFront());
            CHECK_THROWS(iArray.RemoveFront());
            CHECK_THROWS(iArray.RemoveAt(0));
        }

        SECTION("Removing an element from Array<T> with multiple elements")
        {
            Array<int> iArray{0, 2, 8, 45, -332, 1};
            REQUIRE(iArray.GetFront() == 0);
            REQUIRE(iArray.GetLength() == 6);
            REQUIRE(iArray.RemoveFront() == 0);
            REQUIRE(iArray.GetLength() == 5);
            REQUIRE(iArray.GetFront() == 2);
            REQUIRE(iArray.RemoveFront() == 2);
            REQUIRE(iArray.RemoveAt(0) == 8);
            REQUIRE(iArray.GetLength() == 3);

            Array<int> other{45, -332, 1};
            REQUIRE(iArray == other);
        }
    }

    SECTION("Elements removal")
    {
        SECTION("Remove at the beginning of Array<T>")
        {
            Array<int> iArray{0, 2, 8, 45, -332, 1};
            REQUIRE(iArray.GetLength() == 6);
            REQUIRE(iArray.RemoveAt(0) == 0);
            REQUIRE(iArray.GetLength() == 5);
            REQUIRE(iArray.RemoveAt(0) == 2);
            REQUIRE(iArray.GetLength() == 4);

            Array<int> end{8, 45, -332, 1};
            REQUIRE(iArray == end);
        }

        SECTION("Remove in the middle of Array<T>")
        {
            Array<int> iArray{0, 2, 8, 45, -332, 1};
            REQUIRE(iArray.GetLength() == 6);
            REQUIRE(iArray.RemoveAt(3) == 45);
            REQUIRE(iArray.GetLength() == 5);
            REQUIRE(iArray.RemoveAt(2) == 8);
            REQUIRE(iArray.GetLength() == 4);
            Array<int> end{0, 2, -332, 1};
            REQUIRE(iArray == end);
        }

        SECTION("Remove at the end of Array<T>")
        {
            Array<int> iArray{0, 2, 8, 45, -332, 1};
            REQUIRE(iArray.GetLength() == 6);
            REQUIRE(iArray.RemoveAt(5) == 1);
            REQUIRE(iArray.GetLength() == 5);
            REQUIRE(iArray.RemoveAt(4) == -332);
            REQUIRE(iArray.GetLength() == 4);

            Array<int> end{0, 2, 8, 45};
            REQUIRE(iArray == end);
        }
    }

    SECTION("Last element manipulation from Array<T>")
    {
        SECTION("Trying to remove an element from an empty Array<T>")
        {
            Array<float> fArray{};
            CHECK_THROWS(fArray.GetBack());
        }

        SECTION("Removing an element from Array<T> with single element")
        {
            Array<int> iArray{-44};
            REQUIRE(iArray.GetBack() == -44);
            REQUIRE(iArray.GetLength() == 1);
            REQUIRE(iArray.RemoveBack() == -44);
            REQUIRE(iArray.GetLength() == 0);
            CHECK_THROWS(iArray.GetFront());
            CHECK_THROWS(iArray.RemoveBack() == -44);
            CHECK_THROWS(iArray.RemoveAt(0));
        }

        SECTION("Removing an element from Array<T> with multiple elements")
        {
            Array<int> iArray{0, 2, 8, 45, -332, 1};
            REQUIRE(iArray.GetBack() == 1);
            REQUIRE(iArray.GetLength() == 6);
            REQUIRE(iArray.RemoveBack() == 1);
            REQUIRE(iArray.GetLength() == 5);
            REQUIRE(iArray.GetBack() == -332);
            REQUIRE(iArray.RemoveBack() == -332);
            REQUIRE(iArray.RemoveAt(iArray.LastIndex()) == 45);
            REQUIRE(iArray.GetLength() == 3);

            Array<int> other{0, 2, 8};
            REQUIRE(iArray == other);
        }
    }

    SECTION("Validating Array<T>::ArrayValue proxy class to handle operator[]")
    {
        SECTION("Getter")
        {
            Array<const char *> a{"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio.",
                                  "Praesent libero.",
                                  "Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum",
                                  "imperdiet. Duis sagittis ipsum. Praesent mauris.",
                                  "Mauris massa. Vestibulum lacinia arcu eget nulla.",
                                  "Class aptent taciti sociosqu ad litora torquent per conubia nostra,",
                                  "per inceptos himenaeos. Curabitur sodales ligula in libero. ",
                                  "Sed dignissim lacinia nunc. Curabitur tortor. Pellentesque nibh."};

            REQUIRE(strcmp(a[0], "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio.") == 0);
            REQUIRE(strcmp(a[1], "Praesent libero.") == 0);
            REQUIRE(strcmp(a[2], "Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum") == 0);
            REQUIRE(strcmp(a[3], "imperdiet. Duis sagittis ipsum. Praesent mauris.") == 0);
            REQUIRE(strcmp(a[4], "Mauris massa. Vestibulum lacinia arcu eget nulla.") == 0);
            REQUIRE(strcmp(a[5], "Class aptent taciti sociosqu ad litora torquent per conubia nostra,") == 0);
            REQUIRE(strcmp(a[6], "per inceptos himenaeos. Curabitur sodales ligula in libero. ") == 0);
            REQUIRE(strcmp(a[7], "Sed dignissim lacinia nunc. Curabitur tortor. Pellentesque nibh.") == 0);
            CHECK_THROWS(strcmp(a[8], "FINAL TEST") == 0);
        }

        SECTION("Setter")
        {
            Array<const char *> a(10);

            a[0] = "A";
            a[1] = "AB";
            a[2] = "ABC";
            a[3] = "ABCD";
            a[4] = "ABCDE";
            a[5] = "ABCEDF";
            a[6] = "ABCDEFG";
            a[7] = "ABCDEFGH";
            a[8] = "ABCDEFGHI";
            a[9] = "ABCDEFGHIJ";
            CHECK_THROWS(a[10] = "ABCDEFGHIJK");

            REQUIRE(strcmp(a[0], "A") == 0);
            REQUIRE(strcmp(a[1], "AB") == 0);
            REQUIRE(strcmp(a[2], "ABC") == 0);
            REQUIRE(strcmp(a[3], "ABCD") == 0);
            REQUIRE(strcmp(a[4], "ABCDE") == 0);
            REQUIRE(strcmp(a[5], "ABCEDF") == 0);
            REQUIRE(strcmp(a[6], "ABCDEFG") == 0);
            REQUIRE(strcmp(a[7], "ABCDEFGH") == 0);
            REQUIRE(strcmp(a[8], "ABCDEFGHI") == 0);
            REQUIRE(strcmp(a[9], "ABCDEFGHIJ") == 0);
        }
    }

    SECTION("Obtain index information according to argument")
    {
        SECTION("Find the index of the first occurrence")
        {
            Array<long> a{0l, -3321475l, 3218875l, -1l, 0l, 4005822, 0l, 0l, 3323411l, -3321, 97057l, 0l};
            REQUIRE(a.IndexOf(0l) == 0);
            REQUIRE(a.IndexOf(-1l) == 3);
            REQUIRE(a.IndexOf(97057l) == 10);
            REQUIRE(a.IndexOf(444444) == -1);
        }

        SECTION("Find the index of the last occurrence")
        {
            Array<long> a{0l, -3321, 3218875l, -1l, 0l, 4005822, 0l, 0l, 3323411l, -3321, 97057l, 0l};
            REQUIRE(a.LastIndexOf(0l) == 11);
            REQUIRE(a.LastIndexOf(-3321) == 9);
            REQUIRE(a.LastIndexOf(3218875l) == 2);
            REQUIRE(a.LastIndexOf(-4444) == -1);
        }

        SECTION("Find all indices ")
        {
            Array<long> a{0l, -3321, 3218875l, -1l, 0l, 4005822, 0l, 0l, 3323411l, -3321, 97057l, 0l};
            Array<size_t> indicesCheck1 = {0ul, 4ul, 6ul, 7ul, 11ul};
            Array<size_t> indicesCheck2 = {1ul, 9ul};
            Array<size_t> indicesCheck3 = {};
            REQUIRE(indicesCheck1 == a.IndicesOf(0l));
            REQUIRE(indicesCheck2 == a.IndicesOf(-3321));
            REQUIRE(indicesCheck3 == a.IndicesOf(-4444));
        }
    }

    SECTION("Check if element exists in Array<T>")
    {
        Array<const char *> a{"BRUNO", "FRUTUOZO", "LOREM", "IMPSUM"};
        REQUIRE(a.Contains("LOREM") == 1);
        REQUIRE(a.Contains("TEST") == 0);
    }

    SECTION("Count an specified element within the Array<T>")
    {
        Array<int> a{0, 4, 3, 1, 1, 1, 1, 1, 3, 3, 2, 1, 0, 6, 0, -4, -2, 1};
        REQUIRE(a.Count(0) == 3);
        REQUIRE(a.Count(1) == 7);
        REQUIRE(a.Count(-4) == 1);
        REQUIRE(a.Count(-999) == 0);
        REQUIRE(a.Count(3) == 3);
    }

    SECTION("Fill Array<T> with the same element")
    {
        Array<long> a{1, 1, 1, 1, 1, 1, 1, 1};
        Array<long> b{0, 0, 0, 0, 0, 0, 0, 0};
        a.Fill(0);
        REQUIRE(a == b);
    }

    SECTION("Copy")
    {
        SECTION("Full Array<T> to full Array<T>")
        {
            Array<const char *> a{"ABC", "DEF", "GHI"};
            Array<const char *> b{"XYZ", "UYT", "PON"};
            Array<const char *> out{"ABC", "DEF", "GHI"};
            Array<const char *>::Copy(a, b);

            REQUIRE(b == out);
        }

        SECTION("Both source and destination providing indices")
        {
            // Block Source 0
            Array<const char *> a{"ABC", "DEF", "GHI"};
            Array<const char *> b{"XYZ", "UYT", "PON"};
            Array<const char *> out{"ABC", "DEF", "GHI"};
            Array<const char *>::Copy(a, 0, b, 0);
            REQUIRE(b == out);

            a = {"ABC", "DEF", "GHI"};
            b = {"XYZ", "UYT", "PON"};
            out = {"XYZ", "ABC", "DEF", "GHI"};
            Array<const char *>::Copy(a, 0, b, 1);
            REQUIRE(b == out);

            a = {"ABC", "DEF", "GHI"};
            b = {"XYZ", "UYT", "PON"};
            out = {"XYZ", "UYT", "ABC", "DEF", "GHI"};
            Array<const char *>::Copy(a, 0, b, 2);
            REQUIRE(b == out);

            // Force exception
            a = {"ABC", "DEF", "GHI"};
            b = {"XYZ", "UYT", "PON"};
            CHECK_THROWS(Array<const char *>::Copy(a, 0, b, 3));

            // Block Source 1
            out = {"DEF", "GHI", "PON"};
            Array<const char *>::Copy(a, 1, b, 0);
            REQUIRE(b == out);

            a = {"ABC", "DEF", "GHI"};
            b = {"XYZ", "UYT", "PON"};
            out = {"XYZ", "DEF", "GHI"};
            Array<const char *>::Copy(a, 1, b, 1);
            REQUIRE(b == out);

            a = {"ABC", "DEF", "GHI"};
            b = {"XYZ", "UYT", "PON"};
            out = {"XYZ", "UYT", "DEF", "GHI"};
            Array<const char *>::Copy(a, 1, b, 2);
            REQUIRE(b == out);

            // Force exception
            a = {"ABC", "DEF", "GHI"};
            b = {"XYZ", "UYT", "PON"};
            CHECK_THROWS(Array<const char *>::Copy(a, 1, b, 3));

            // Block Source 2
            out = {"GHI", "UYT", "PON"};
            Array<const char *>::Copy(a, 2, b, 0);
            REQUIRE(b == out);

            a = {"ABC", "DEF", "GHI"};
            b = {"XYZ", "UYT", "PON"};
            out = {"XYZ", "GHI", "PON"};
            Array<const char *>::Copy(a, 2, b, 1);
            REQUIRE(b == out);

            a = {"ABC", "DEF", "GHI"};
            b = {"XYZ", "UYT", "PON"};
            out = {"XYZ", "UYT", "GHI"};
            Array<const char *>::Copy(a, 2, b, 2);
            REQUIRE(b == out);

            // Force exception
            a = {"ABC", "DEF", "GHI"};
            b = {"XYZ", "UYT", "PON"};
            CHECK_THROWS(Array<const char *>::Copy(a, 2, b, 3));

            // Force exception
            a = {"ABC", "DEF", "GHI"};
            b = {"XYZ", "UYT", "PON"};
            CHECK_THROWS(Array<const char *>::Copy(a, 3, b, 3));
        }
    }

    SECTION("Reverse container")
    {
        Array<const char *> a{"ABC", "DEF", "G", "XY", "Z"};
        Array<const char *> out{"Z", "XY", "G", "DEF", "ABC"};

        a.Reverse();
        REQUIRE(a == out);
    }

    SECTION("Swap Array<T> with another one")
    {
        Array<int> a{0, 1, 2, 3};
        Array<int> b{9, 8, 7, 6};

        a.Swap(b);
        REQUIRE(a.RemoveBack() == 6);
        REQUIRE(a.RemoveBack() == 7);
        REQUIRE(a.RemoveBack() == 8);
        REQUIRE(a.RemoveBack() == 9);
        CHECK_THROWS(a.RemoveBack());
        REQUIRE(b.RemoveBack() == 3);
        REQUIRE(b.RemoveBack() == 2);
        REQUIRE(b.RemoveBack() == 1);
        REQUIRE(b.RemoveBack() == 0);
        CHECK_THROWS(b.RemoveBack());
    }

    SECTION("Resizing")
    {
        Array<int> a;
        Array<int>::Resize(a, 30);

        // Check if the correct amount is set
        REQUIRE(a.GetLength() == 30);

        // Check if default pValue was set
        REQUIRE(a.Count(0) == 30);

        Array<int> b = {1, 2, 3, 4, 5, 6};
        Array<int> c = {1, 2, 3, 4};
        Array<int>::Resize(b, 4);

        // Check if array is properly reduced keeping its elements
        REQUIRE(b == c);

        Array<int> d{1, 2, 3, 4};
        Array<int> e = {1};
        Array<int>::Resize(d, 1);
        REQUIRE(d == e);

        Array<int> f{1, 2, 3};
        Array<int> g{};
        Array<int>::Resize(f, 0);
        REQUIRE(f == g);
    }

    SECTION("Iterators")
    {
        SECTION("Array<T>::Iterator")
        {
            std::ostringstream oss;
            Array<const char *> c = {"ABC", "DEF", "G", "HI", "J", "KLMNOPQ"};

            for (auto it = c.begin(); it != c.end(); ++it) {
                *it = "A";
                oss << *it;
            }

            REQUIRE(strcmp("AAAAAA", oss.str().c_str()) == 0);
        }

        SECTION("Array<T>::ConstIterator")
        {
            std::ostringstream oss;
            Array<const char *> c = {"ABC", "DEF", "G", "HI", "J", "KLMNOPQ"};

            for (auto it = c.cbegin(); it != c.cend(); ++it) {
                oss << *it;
            }

            REQUIRE(strcmp("ABCDEFGHIJKLMNOPQ", oss.str().c_str()) == 0);
        }

        SECTION("Array<T>::ReverseIterator")
        {
            std::ostringstream oss;
            Array<const char *> c = {"ABC", "DEF", "G", "HI", "J", "KLMNOPQ"};

            for (auto it = c.rbegin(); it != c.rend(); ++it) {
                *it = "A";
                oss << *it;
            }

            REQUIRE(strcmp("AAAAAA", oss.str().c_str()) == 0);
        }

        SECTION("Array<T>::ConstReverseIterator")
        {
            std::ostringstream oss;
            Array<const char *> c = {"ABC", "DEF", "G", "HI", "J", "KLMNOPQ"};

            for (auto it = c.crbegin(); it != c.crend(); ++it) {
                oss << *it;
            }

            REQUIRE(strcmp("KLMNOPQJHIGDEFABC", oss.str().c_str()) == 0);
        }
    }
}

#endif //LNXCPPLEARNING_TEST_ARRAY_CPP