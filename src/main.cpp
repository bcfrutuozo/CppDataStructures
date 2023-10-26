#include <iostream>
#include "types/String.hpp"
#include "collections/Array.hpp"

int main(int argc, char* argv[])
{
	String s("ABCDE");

    Array<int> aa = {123, 4};

    const int x = aa[1];

    const char c1 = s[2];
    std::cout << c1 << std::endl;

	String s2 = "DEFG";
    String s3 = "ZZZ";

	if(s2 == "CDEABC") std::cout << "YEAH" << std::endl;

    String s4 = String::Concat(s, s2, s3);
    Array<String> as {s, s2, s3, s4};
    auto s5 = s4.Concat(as);

    std::cout << s5.Count('Z') << std::endl;

    String s10 = "A";
    String s11 = "B";

	//Array<String> f;
	//f.Add(s);
	//f.Add(z);
	//
	//String final1 = s.Concat(f);
	//
	//std::cout << (s == z) << std::endl;
	//std::cout << (s == "ABC") << std::endl;
	return 0;
}