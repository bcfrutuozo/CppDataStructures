//
// Created by bcfrutuozo on 17/03/2022.
//

#ifndef LNXCPPLEARNING_TEST_ARRAY_CPP
#define LNXCPPLEARNING_TEST_ARRAY_CPP

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../Array.h"

TEST_CASE("Array Instantiation", "[Array]")
{
    SECTION("Primitive Type Testing")
    {
        SECTION("uint8_t Array")
        {
            Array<uint8_t> c;
            REQUIRE(c.GetSize() == 0);
            Array<uint8_t> cSize(2);
            REQUIRE(cSize.GetSize() == 2);
            Array<uint8_t> cDefault(1, 2);
            REQUIRE(cDefault[0] == 1);
            REQUIRE(cDefault[1] == 1);
            REQUIRE(cDefault.GetSize() == 2);
            Array<uint8_t> arrayu8 = {1, 2, 3, 4, 5};
            REQUIRE(arrayu8.GetSize() == 5);
        }

        SECTION("uint16_t Array")
        {
            Array<uint16_t> c;
            REQUIRE(c.GetSize() == 0);
            Array<uint16_t> cSize(2);
            REQUIRE(cSize.GetSize() == 2);
            Array<uint16_t> cDefault(1, 2);
            REQUIRE(cDefault[0] == 1);
            REQUIRE(cDefault[1] == 1);
            REQUIRE(cDefault.GetSize() == 2);
            Array<uint16_t> arrayu16 = {1, 2, 3, 4, 5};
            REQUIRE(arrayu16.GetSize() == 5);
        }

        SECTION("uint32_t Array")
        {
            Array<uint32_t> c;
            REQUIRE(c.GetSize() == 0);
            Array<uint32_t> cSize(2);
            REQUIRE(cSize.GetSize() == 2);
            Array<uint32_t> cDefault(1, 2);
            REQUIRE(cDefault[0] == 1);
            REQUIRE(cDefault[1] == 1);
            REQUIRE(cDefault.GetSize() == 2);
            Array<uint32_t> arrayu32 = {1, 2, 3, 4, 5};
            REQUIRE(arrayu32.GetSize() == 5);
        }

        SECTION("uint64_t Array")
        {
            Array<uint32_t> c;
            REQUIRE(c.GetSize() == 0);
            Array<uint64_t> cSize(2);
            REQUIRE(cSize.GetSize() == 2);
            Array<uint64_t> cDefault(1, 2);
            REQUIRE(cDefault[0] == 1);
            REQUIRE(cDefault[1] == 1);
            REQUIRE(cDefault.GetSize() == 2);
            Array<uint64_t> arrayu64 = {1, 2, 3, 4, 5};
            REQUIRE(arrayu64.GetSize() == 5);
        }

        SECTION("int8_t Array")
        {
            Array<int8_t> c;
            REQUIRE(c.GetSize() == 0);
            Array<int8_t> cSize(2);
            REQUIRE(cSize.GetSize() == 2);
            Array<int8_t> cDefault(1, 2);
            REQUIRE(cDefault[0] == 1);
            REQUIRE(cDefault[1] == 1);
            REQUIRE(cDefault.GetSize() == 2);
            Array<int8_t> array8 = {1, 2, 3, 4, 5};
            REQUIRE(array8.GetSize() == 5);
        }

        SECTION("int16_t Array")
        {
            Array<int16_t> c;
            REQUIRE(c.GetSize() == 0);
            Array<int16_t> cSize(2);
            REQUIRE(cSize.GetSize() == 2);
            Array<int16_t> cDefault(1, 2);
            REQUIRE(cDefault[0] == 1);
            REQUIRE(cDefault[1] == 1);
            REQUIRE(cDefault.GetSize() == 2);
            Array<int16_t> array16 = {1, 2, 3, 4, 5};
            REQUIRE(array16.GetSize() == 5);
        }

        SECTION("int32_t Array")
        {
            Array<int32_t> c;
            REQUIRE(c.GetSize() == 0);
            Array<int32_t> cSize(2);
            REQUIRE(cSize.GetSize() == 2);
            Array<int32_t> cDefault(1, 2);
            REQUIRE(cDefault[0] == 1);
            REQUIRE(cDefault[1] == 1);
            REQUIRE(cDefault.GetSize() == 2);
            Array<int32_t> array32 = {1, 2, 3, 4, 5};
            REQUIRE(array32.GetSize() == 5);
        }

        SECTION("int64_t Array")
        {
            Array<int64_t> c;
            REQUIRE(c.GetSize() == 0);
            Array<int64_t> cSize(2);
            REQUIRE(cSize.GetSize() == 2);
            Array<int64_t> cDefault(1, 2);
            REQUIRE(cDefault[0] == 1);
            REQUIRE(cDefault[1] == 1);
            REQUIRE(cDefault.GetSize() == 2);
            Array<int64_t> array64 = {1, 2, 3, 4, 5};
            REQUIRE(array64.GetSize() == 5);
        }

        SECTION("char Array")
        {
            Array<char> c;
            REQUIRE(c.GetSize() == 0);
            Array<char> cSize(2);
            REQUIRE(cSize.GetSize() == 2);
            Array<char> cDefault('1', 2);
            REQUIRE(cDefault[0] == '1');
            REQUIRE(cDefault[1] == '1');
            REQUIRE(cDefault.GetSize() == 2);
            Array<char> arrayc = {'1', '2', '3', '4', '5',};
            REQUIRE(arrayc.GetSize() == 5);
        }

        SECTION("unsigned char Array")
        {
            Array<unsigned char> c;
            REQUIRE(c.GetSize() == 0);
            Array<unsigned char> cSize(2);
            REQUIRE(cSize.GetSize() == 2);
            Array<unsigned char> cDefault('1', 2);
            REQUIRE(cDefault[0] == '1');
            REQUIRE(cDefault[1] == '1');
            REQUIRE(cDefault.GetSize() == 2);
            Array<unsigned char> arrayuc = {'1', '2', '3', '4', '5',};
            REQUIRE(arrayuc.GetSize() == 5);
        }

        SECTION("float Array")
        {
            Array<float> c;
            REQUIRE(c.GetSize() == 0);
            Array<float> cSize(2);
            REQUIRE(cSize.GetSize() == 2);
            Array<float> cDefault(1.0, 2);
            REQUIRE(cDefault[0] == 1.0);
            REQUIRE(cDefault[1] == 1.0);
            REQUIRE(cDefault.GetSize() == 2);
            Array<float> arrayf = {1.0, 2.0, 3.0, 4.0, 5.0,};
            REQUIRE(arrayf.GetSize() == 5);
        }

        SECTION("double Array")
        {
            Array<double> c;
            REQUIRE(c.GetSize() == 0);
            Array<double> cSize(2);
            REQUIRE(cSize.GetSize() == 2);
            Array<double> cDefault(1.0, 2);
            REQUIRE(cDefault[0] == 1.0);
            REQUIRE(cDefault[1] == 1.0);
            REQUIRE(cDefault.GetSize() == 2);
            Array<double> arrayd = {1.0, 2.0, 3.0, 4.0, 5.0,};
            REQUIRE(arrayd.GetSize() == 5);
        }
    }

    SECTION("Non-Primitive Type Testing")
    {
        SECTION("const char* Array")
        {
            Array<const char*> c;
            REQUIRE(c.GetSize() == 0);
            Array<const char*> cSize(2);
            REQUIRE(cSize.GetSize() == 2);
            Array<const char*> cDefault("ABCDEF", 2);
            REQUIRE(cDefault[0] == "ABCDEF");
            REQUIRE(cDefault[1] == "ABCDEF");
            REQUIRE(cDefault.GetSize() == 2);
            Array<const char*> arraycc = { "A", "BRUNO", "LOREM", "TEST" };
            REQUIRE(arraycc.GetSize() == 4);
            REQUIRE(arraycc[0] == "A");
            REQUIRE(arraycc[1] == "BRUNO");
            REQUIRE(arraycc[2] == "LOREM");
            REQUIRE(arraycc[3] == "TEST");
            REQUIRE_THROWS(arraycc[4] == "ERROR!");
        }
    }
}

TEST_CASE("Elements Insertion")
{
    SECTION("Adding element at the end of a populated array")
    {
        Array<const char*> cpArray = { "BRUNO", "FRUTUOZO", "ENGINEERING", "LOREM", "IPSUM" };
        REQUIRE(cpArray.GetSize() == 5);
        REQUIRE(cpArray.LastIndex() == 4);

        cpArray.Add("NEW");
        cpArray.Add("NEW 2");
        cpArray.Add("NEW 3");
        REQUIRE(cpArray.GetSize() == 8);
        REQUIRE(cpArray.LastIndex() == 7);
    }

    SECTION("Adding a collection of elements to the array")
    {
        Array<const char*> cpArray = { "BRUNO", "FRUTUOZO", "ENGINEERING", "LOREM", "IPSUM" };
        REQUIRE(cpArray.GetSize() == 5);
        REQUIRE(cpArray.LastIndex() == 4);

        cpArray.Add("Single New");
        cpArray.Add({"ELEMENT 1", "ELEMENT 2", "ELEMENT 3", "ELEMENT 4", "ELEMENT 5",
                     "C",
                     "ELEMENT 6", "ELEMENT 7", "ELEMENT 8", "ELEMENT 9", "ELEMENT 10"});

        // Checking index and size
        REQUIRE(cpArray.GetSize() == 17);
        REQUIRE(cpArray.LastIndex() == 16);

        // Checking element contents
        REQUIRE(cpArray[2] == "ENGINEERING");
        REQUIRE(cpArray[5] == "Single New");
        REQUIRE(cpArray[16] == "ELEMENT 10");
    }

    SECTION("Adding element at an empty instantiated array")
    {
        Array<int> emptyArrayForSingleInsertion;

        // Checking index and size
        REQUIRE(emptyArrayForSingleInsertion.GetSize() == 0);
        REQUIRE(emptyArrayForSingleInsertion.LastIndex() == -1);

        emptyArrayForSingleInsertion.Add(10);

        // Checking index and size
        REQUIRE(emptyArrayForSingleInsertion.GetSize() == 1);
        REQUIRE(emptyArrayForSingleInsertion.LastIndex() == 0);

        // Checking element contents
        REQUIRE(emptyArrayForSingleInsertion[0] == 10);
    }

    SECTION("Adding a collection of element at an empty instantiated array")
    {
        Array<int> emptyArrayForRangeInsertion;

        // Checking index and size
        REQUIRE(emptyArrayForRangeInsertion.GetSize() == 0);
        REQUIRE(emptyArrayForRangeInsertion.LastIndex() == -1);

        emptyArrayForRangeInsertion.Add({4, 6, 3, 1, 6, 6 , 6 , 19, 2, 164, 52231, 2, 1, 0 , -132, -4, -7, 32, -999});

        // Checking index and size
        REQUIRE(emptyArrayForRangeInsertion.GetSize() == 19);
        REQUIRE(emptyArrayForRangeInsertion.LastIndex() == 18);

        // Checking element contents
        REQUIRE(emptyArrayForRangeInsertion[0] == 4);
        REQUIRE(emptyArrayForRangeInsertion[7] == 19);
        REQUIRE(emptyArrayForRangeInsertion[16] == -7);
        REQUIRE(emptyArrayForRangeInsertion[18] == -999);
    }
}

TEST_CASE("First element manipulation from array")
{
    SECTION("Trying to remove an element from an empty array")
    {
        Array<float> fArray {};
        REQUIRE_THROWS(fArray.GetFront());
    }

    SECTION("Removing an element from array with single element")
    {
        Array<int> iArray { -44 };
        REQUIRE(iArray.GetFront() == -44);
        REQUIRE(iArray.GetSize() == 1);
        REQUIRE(iArray.RemoveFront() == -44);
        REQUIRE(iArray.GetSize() == 0);
        REQUIRE_THROWS(iArray.GetFront());
        //REQUIRE_THROWS(iArray.RemoveFront() == -44);
        //REQUIRE_THROWS(iArray.RemoveAt(0));
    }
}

#endif //LNXCPPLEARNING_TEST_ARRAY_CPP