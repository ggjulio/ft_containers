
#include "tests.hpp"

#include <utility>
#include <string>
#include <vector>

#include <iostream>

#include "utility.hpp"

namespace NS_NAME
{
	template<class T1, class T2>
	std::ostream&	operator<<(std::ostream& os, const pair<T1, T2>& pair)
	{
		os << "pair<" << pair.first << "," << pair.second << ">";
		return os;
	}
}


TEST_CASE( "cn::swap", "[utility][swap]")
{
	std::string a = "one";
	std::string b = "two";

	CHECK( a == "one");
	CHECK( b == "two");
	cn::swap(a,b);
	CHECK( b == "one");
	CHECK( a == "two");
}

TEST_CASE( "cn::make_pair", "[utility][pair][make_pair]" ) {
	cn::pair<int, std::string> p = cn::make_pair(42, std::string("foo"));

	CHECK( p.first == 42);
	CHECK( p.second == "foo");
}

TEST_CASE( "cn::pair lexicographical comparison", "[utility][pair][comparison]" ) {

	SECTION("Equality and inequality")
	{
		cn::pair<int, std::string> p1 = cn::make_pair(42, std::string("foo"));
		cn::pair<int, std::string> p2 = p1;
		cn::pair<int, std::string> p3 = p1;
		
		CHECK( p1 == p2);
		p2.second = "bar";
		CHECK( p1 != p2);

		CHECK( p1 == p3);
		p3.first = 13;
		CHECK( p1 != p3);
	}


	SECTION("Sort test")
	{
		std::vector<cn::pair<int, std::string>> v = { {2, "baz"},
                                                   {2, "bar"},
                                                   {1, "foo"} };
		std::sort(v.begin(), v.end());
		REQUIRE(v[0] == cn::pair<int, std::string>(1, "foo"));
		REQUIRE(v[1] == cn::pair<int, std::string>(2, "bar"));
		REQUIRE(v[2] == cn::pair<int, std::string>(2, "baz"));
	}

}