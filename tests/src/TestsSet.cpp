#include "tests.hpp"

#include "set.hpp"

bool fncomp_set (int lhs, int rhs) {return lhs>rhs;}

struct classcomp_set {
	bool operator() (const int& lhs, const int& rhs) const
	{ return lhs>rhs; }
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

TEST_CASE( "set - iterator ", "[set][iterator]" )
{
	cn::set<int> first;
	SECTION( "empty container should have begin() == end()" )
	{
		REQUIRE( first.begin() == first.end() );
	}
	first.insert(10);
	SECTION( "container with one element should have consistant boundary" )
	{
		REQUIRE( ++first.begin() == first.end() );
		REQUIRE( first.begin() == --first.end() );
		REQUIRE( first.begin().operator*() == 10 );
		REQUIRE( first.begin().operator->() == &*first.begin() );
	}
	first.insert(20);
	first.insert(30);
	SECTION( "container with three elements should loop properly" )
	{
		auto it = first.begin();
		int i = 0;
		while (it != first.end())
		{
			i += 10;
			REQUIRE(*it == i);
			++it;
		}
		REQUIRE(i == 30);
	}
	SECTION( "container with three elements should loop properly in reverse" )
	{
		auto it = first.end();
		int i = 40;
		while (--it != first.begin())
		{
			i -= 10;
			REQUIRE(*it == i);
		}
		REQUIRE(*it == 10);
	}
}

TEST_CASE( "set - reverse iterator ", "[set][reverse_iterator]" )
{
	cn::set<int> first;
	SECTION( "empty container should have begin() == end()" )
	{
		REQUIRE( first.rbegin() == first.rend() );
	}
	first.insert(10);
	SECTION( "container with one element should have consistant boundary" )
	{
		REQUIRE( ++first.rbegin() == first.rend() );
		REQUIRE( first.rbegin() == --first.rend() );
		REQUIRE( first.rbegin().operator*() == 10 );
		REQUIRE( first.rbegin().operator->() == &*first.rbegin() );
	}
	first.insert(20);
	first.insert(30);
	SECTION( "container with three elements should loop properly" )
	{
		auto it = first.rbegin();
		int i = 40;
		while (it != first.rend())
		{
			i -= 10;
			REQUIRE(*it == i);
			++it;
		}
		REQUIRE(i == 10);
	}
	SECTION( "container with three elements should loop properly in reverse" )
	{
		auto it = first.rend();
		int i = 0;
		while (--it != first.rbegin())
		{
			i += 10;
			REQUIRE(*it == i);
		}
		REQUIRE(*it == 30);
	}
}

TEST_CASE( "set - capacity ", "[set][capacity]" )
{
	cn::set<int> first;

	SECTION( "empty container should be empty (insightful)" )
	{
		REQUIRE(first.empty());
		REQUIRE(first.size() == 0);
	}
	first.insert(10);
	SECTION( "container with one element should be of size one (and not empty, of course)" )
	{
		REQUIRE(!first.empty());
		REQUIRE(first.size() == 1);
	}
	first.erase(first.begin());
	SECTION( "delete the single element, should become an empty container again." )
	{
		REQUIRE(first.size() == 0);
		REQUIRE(first.empty());
	}
	SECTION( "max_size(), For now I don't know which value is suposed to be equal to (probably depend on the underlying implementation)" )
	{
		REQUIRE(first.max_size() == 230584300921369395);
	}
}

TEST_CASE( "set - Modifiers - insert ", "[set][modifier][insert]" )
{
	cn::set<int> myset;
	cn::set<int>::iterator it_res;
	cn::pair<cn::set<int>::iterator,bool> ret;
	
	ret = myset.insert(42);
	SECTION( "Insert single value" )
	{
		REQUIRE(ret.second == true);
		REQUIRE(*ret.first == 42);
		REQUIRE(myset.size() == 1);
	}
	ret = myset.insert(42);
	SECTION( "Already inserted value should not be inserted" )
	{
		REQUIRE(ret.second == false);
		REQUIRE(*ret.first == 42);
		REQUIRE(myset.size() == 1);
	}
	it_res = myset.insert(ret.first, 43);
	SECTION( "Insert with hint" )
	{
		REQUIRE(*it_res == 43);
		REQUIRE(myset.size() == 2);
	}
	it_res = myset.insert(ret.first, 43);
	SECTION( "Already inserted value even with hint should not be inserted" )
	{
		REQUIRE(*it_res == 43);
		REQUIRE(myset.size() == 2);
	}

	int myints[]= {40,41,42,43};
	myset.insert(myints, myints+4);
	SECTION( "Insert range, with some values already inserted should not be inserted twice")
	{
		REQUIRE(myset.size() == 4);
		int i = 39;
		auto it = myset.begin();
		while (it != myset.end())
			REQUIRE(*it++ == ++i);
		REQUIRE(i == 43);
	}
}
