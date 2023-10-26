//
// Created by bcfru on 10/26/2023.
//

#include "../src/types/String.hpp"

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

TEST_CASE("String")
{
     SECTION("Empty String as Static Variable")
     {
            String s1 = String::Empty();
            String s2 = String::Empty();
            const char *s1ca = s1;
            const char *s2ca = s2;
            REQUIRE(s1 == s2);
     }

    SECTION("Instantiation")
    {
        SECTION("Empty Constructor")
        {
            String s;
            REQUIRE(s == "");
            REQUIRE(s.IsEmpty());
        }
        SECTION("Char*")
        {
            String s("ABCDEF");
            REQUIRE(s == "ABCDEF");
            REQUIRE(s.GetLength() == 6);
            REQUIRE(!s.IsEmpty());
        }
        SECTION("const char, length")
        {
            String s('A', 5);
            REQUIRE(s == "AAAAA");
            REQUIRE(s.GetLength() == 5);
        }
        SECTION("const char*, startIndex, length")
        {
            String s("ABCDEFGHIJ", 2, 6);
            REQUIRE(s == "CDEFGH");
            REQUIRE(s.GetLength() == 6);
            String s2("ABCDEFGHIJ", 0, 12);
            REQUIRE(s2 == "ABCDEFGHIJ");
            REQUIRE(s2.GetLength() == 10);
            String s3("ABCDEFGHIJ", 0, 8);
            REQUIRE(s3 == "ABCDEFGH");
            REQUIRE(s3.GetLength() == 8);
            String s4("ABCDEFGHIJ", 9, 32);
            REQUIRE(s4 == "J");
            REQUIRE(s4.GetLength() == 1);
        }
        SECTION("Copy Constructor")
        {
            String s1 = "ABCDE";
            String s2(s1);
            REQUIRE(s2 == "ABCDE");
            REQUIRE(s1 == "ABCDE");
        }
        SECTION("Move Constructor")
        {
            String s1 = "ABCDE";
            String s2(std::move(s1));
            REQUIRE(s1 == String::Empty());
            REQUIRE(s1.GetLength() == 0);
            REQUIRE(s2 == "ABCDE");
            REQUIRE(s2.GetLength() == 5);
        }
        SECTION("Copy Assignment")
        {
            String s1 = "ABCDE";
            String s2 = s1;
            REQUIRE(s2 == "ABCDE");
            REQUIRE(s1 == "ABCDE");
        }
        SECTION("Move Assignment")
        {
            String s1 = "ABCDE";
            String s2 = std::move(s1);
            REQUIRE(s1 == String::Empty());
            REQUIRE(s1.GetLength() == 0);
            REQUIRE(s2 == "ABCDE");
            REQUIRE(s2.GetLength() == 5);
        }
    }
    SECTION("Operators")
    {
         SECTION("operator+") {
             SECTION("const char*") {
                 String s1 = "ABCDE";
                 const char *s2 = "123";
                 String s3 = s1 + s2;
                 REQUIRE(s3 == "ABCDE123");
                 REQUIRE(s3.GetLength() == 8);
                 REQUIRE(s1 == "ABCDE");
                 REQUIRE(s1.GetLength() == 5);
             }
             SECTION("String") {
                 String s1 = "ABCDE";
                 String s2 = "123";
                 String s3 = s1 + s2;
                 REQUIRE(s3 == "ABCDE123");
                 REQUIRE(s3.GetLength() == 8);
                 REQUIRE(s1 == "ABCDE");
                 REQUIRE(s1.GetLength() == 5);
                 REQUIRE(s2 == "123");
                 REQUIRE(s2.GetLength() == 3);
             }
         }
        SECTION("operator+=")
        {
            SECTION("const char*") {
                String s1 = "ABCDE";
                s1 += "123";
                REQUIRE(s1 == "ABCDE123");
                REQUIRE(s1.GetLength() == 8);
            }
            SECTION("String") {
                String s1 = "ABCDE";
                String s2 = "123";
                s1 += s2;
                REQUIRE(s1 == "ABCDE123");
                REQUIRE(s1.GetLength() == 8);
                REQUIRE(s2 == "123");
                REQUIRE(s2.GetLength() == 3);
            }
        }
        /*
         * Only way to proper edit the char address is using const_cast<char&>:
         * char& c2 = const_cast<char&>(s1[1]);     OR
         * char* c2 = const_cast<char*>(&s1[1]);
         * Which is an absurd, since we are using this String class simply
         * because it is supposed to be Immutable (unchangeable) :D
         */
        SECTION("operator[]")
        {
             String s1 = "ABC";
             // Forces a copy of the string, not the reference
             char c2 = s1[1];
             REQUIRE(c2 == 'B');
             c2 = 'a';
             REQUIRE(s1 == "ABC");
        }
        SECTION("operator const char*")
        {
            String s1 = "ABC";
            const char* s2 = s1;
            REQUIRE(s2[0] == 'A');
            REQUIRE(s2[1] == 'B');
            REQUIRE(s2[2] == 'C');
            REQUIRE(s2[3] == '\0');
        }
        SECTION("operator==")
        {
            String s1 = "ABC";
            String s2 = "ABC";
            REQUIRE(s1 == s2);
            const char* s3 = "ABC";
            REQUIRE(s1 == s3);
        }
        SECTION("operator!=")
        {
            String s1 = "ABC";
            String s2 = "AC";
            REQUIRE(s1 != s2);
            const char* s3 = "AD";
            REQUIRE(s1 != s3);
        }
    }
}