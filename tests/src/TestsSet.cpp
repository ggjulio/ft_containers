#include "tests.hpp"

#include "set.hpp"

bool fncomp_set (int lhs, int rhs) {return lhs>rhs;}

struct classcomp_set {
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs>rhs;}
};

TEST_CASE( "set - constructor ", "[set][constructor]" )
{
	SECTION( "empty construtor" ) {
		cn::set<int> first;
		REQUIRE(first.empty());
		REQUIRE(first.size() == 0);
	}
	int myints[]= {10,20,30,40,50};
	cn::set<int> second (myints, myints+5);
	SECTION( "range construtor" ) {
		REQUIRE(!second.empty());
		REQUIRE(second.size() == 5);
	}
	SECTION( "copy construtor" ) {
		cn::set<int> third (second);
		REQUIRE(!third.empty());
		REQUIRE(third.size() == 5);
	
		SECTION( "A deep_copy/clone must be made" ) {
			third.erase(third.begin());
			REQUIRE(third.size() == 4);
			REQUIRE(third.find(10) == third.end());
			REQUIRE(second.size() == 5);
			REQUIRE(*second.find(10) == 10);
		}
	}
	SECTION( "iterator construtor" ) {
		cn::set<int> fourth (second.begin(), second.end());
		REQUIRE(!fourth.empty());
		REQUIRE(fourth.size() == 5);
	}
	SECTION( "class as Compare" ) {
		cn::set<int,classcomp_set> fifth;
		fifth.insert(1);
		fifth.insert(2);
		REQUIRE(*fifth.begin() == 2);
		REQUIRE(*--fifth.end() == 1);
		REQUIRE(*fifth.find(2) == 2);
	}
	SECTION( "function ptr as Compare" ) {
		bool(*fn_pt)(int,int) = fncomp_set;
		cn::set<int,bool(*)(int,int)> sixth (fn_pt);

		sixth.insert(1);
		sixth.insert(2);
		REQUIRE(*sixth.begin() == 2);
		REQUIRE(*--sixth.end() == 1);
		REQUIRE(*sixth.find(2) == 2);
	}

}

TEST_CASE( "set - operator - assignment ", "[set][operator][assignment]" )
{
	int myints[] = { 10,20,30,40,50 };
	cn::set<int> first (myints,myints+5);
	cn::set<int> second;
	
	REQUIRE(!first.empty());
	REQUIRE(first.size() == 5);
	REQUIRE(second.empty());
	REQUIRE(second.size() == 0);


	second = first;
	REQUIRE(!second.empty());
	REQUIRE(second.size() == 5);
	
	SECTION( "A deep_copy/clone must be made" ) {
		second.erase(second.begin());
		REQUIRE(second.size() == 4);
		REQUIRE(second.find(10) == second.end());
		REQUIRE(first.size() == 5);
		REQUIRE(*first.find(10) == 10);
	}
	SECTION( "Must have no leaks when running w ur fav leak detect prog" ) {
		first = cn::set<int>();
	}
}
