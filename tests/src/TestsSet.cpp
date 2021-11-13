#include "tests.hpp"

#include "set.hpp"

#include <typeinfo>

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

TEST_CASE( "set - Modifiers - erase ", "[set][modifier][erase]" )
{
	cn::set<int> myset;

	for (int i=1; i<10; i++)
		myset.insert(i*10);  // 10 20 30 40 50 60 70 80 90
	REQUIRE(myset.size() == 9);
	
	myset.erase (++myset.begin());
	SECTION( "erase 20 by iterator" )
	{
		REQUIRE(*++myset.begin() == 30);
		REQUIRE(myset.size() == 8);
	}
	myset.erase (30);
	SECTION( "erase 30 by value" )
	{
		REQUIRE(*++myset.begin() == 40);
		REQUIRE(myset.size() == 7);
	}
	
	cn::set<int>::iterator it = ++myset.begin();
	cn::set<int>::iterator endRange =  ++myset.end();
	--endRange; --endRange; --endRange;
	REQUIRE(*it == 40);
	REQUIRE(*endRange == 60);
	myset.erase(it, endRange);
	SECTION( "erase range 40 to 60 (60 excluded)" )
	{
		REQUIRE(*++myset.begin() == 60);
		REQUIRE(myset.size() == 5);
	}

	myset.erase (myset.begin(), myset.end());
	SECTION( "erase range from begin to end, must be empty" )
	{
		REQUIRE(myset.begin() == myset.end());
		REQUIRE(myset.size() == 0);
		REQUIRE(myset.empty());
	}

}

TEST_CASE( "set - Modifiers - swap ", "[set][modifier][swap]" )
{
	int myints[]={12,75,10,32,20,25};
	cn::set<int> first (myints,myints+2);     // 12,75
	cn::set<int> second (myints+2,myints+6);  // 10,20,25,32,75

	auto it = first.begin();
	REQUIRE(*it++ == 12);
	REQUIRE(*it++ == 75);
	REQUIRE(it == first.end());

	it = second.begin();
	REQUIRE(*it++ == 10);
	REQUIRE(*it++ == 20);
	REQUIRE(*it++ == 25);
	REQUIRE(*it++ == 32);
	REQUIRE(it == second.end());

	first.swap(second);

	it = first.begin();
	REQUIRE(*it++ == 10);
	REQUIRE(*it++ == 20);
	REQUIRE(*it++ == 25);
	REQUIRE(*it++ == 32);
	REQUIRE(it == first.end());

	it = second.begin();
	REQUIRE(*it++ == 12);
	REQUIRE(*it++ == 75);
	REQUIRE(it == second.end());
}

TEST_CASE( "set - Modifiers - clear ", "[set][modifier][clear]" )
{
	cn::set<int> emptySet;
	SECTION( "Empty set being clear should be okay" )
	{
		emptySet.clear();
		REQUIRE( emptySet.empty() );
		REQUIRE( emptySet.size() == 0);
	}

	int myints[]={12,75,10,32,20,25};
	cn::set<int> myset (myints,myints+6);
	REQUIRE( !myset.empty() );
	REQUIRE( myset.size() == 6);
	myset.clear();
	SECTION( "Clear set who contain element should be ok" )
	{
		REQUIRE( myset.empty() );
		REQUIRE( myset.size() == 0);
	}
	myset.clear();
	SECTION( "Clear two times should be ok" )
	{
		REQUIRE( myset.empty() );
		REQUIRE( myset.size() == 0);
	}
}

TEST_CASE( "set - Observers - key_comp and value_comp ", "[set][observer][key_comp][value_comp]" )
{
	cn::set<int> myset;

	cn::set<int>::key_compare mycomp = myset.key_comp();
	SECTION( "Default constructor should use std::less as default key_comp" )
	{
		cn::set<int>::key_compare stdless;
		REQUIRE(typeid(mycomp).name() == typeid(stdless).name());
		REQUIRE(typeid(mycomp).hash_code() == typeid(stdless).hash_code());

		REQUIRE( mycomp(4, 5) == true );
		REQUIRE( mycomp(5, 5) == false );
		REQUIRE( mycomp(6, 5) == false );
	}
	SECTION( "Default constructor should use std::less as default key_comp" )
	{
		cn::set<int, classcomp_set>::key_compare mycustomComp;

		REQUIRE(typeid(mycomp).name() != typeid(mycustomComp).name());
		REQUIRE(typeid(mycomp).hash_code() != typeid(mycustomComp).hash_code());

		REQUIRE( mycustomComp(4, 5) == false );
		REQUIRE( mycustomComp(5, 5) == false );
		REQUIRE( mycustomComp(6, 5) == true );
	}
	SECTION( "Set should have equal key_comp and value_comp" )
	{
		REQUIRE(typeid(myset.key_comp()).name() == typeid(myset.value_comp()).name());
		REQUIRE(typeid(myset.key_comp()).hash_code() == typeid(myset.value_comp()).hash_code());
	}
}

TEST_CASE( "set - Operations - find ", "[set][operation][find]" )
{
	std::set<int> myset;
	std::set<int>::iterator it;

	for (int i=1; i<=5; i++)
		myset.insert(i*10);    // set: 10 20 30 40 50

	REQUIRE( *myset.find(10) == 10);
	REQUIRE( *myset.find(20) == 20);
	REQUIRE( *myset.find(50) == 50);
	REQUIRE( myset.find(42) == myset.end());
}
