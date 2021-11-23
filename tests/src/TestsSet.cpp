#include "tests.hpp"

#include "set.hpp"
#include <set>

#include <typeinfo>

bool fncomp_set (int lhs, int rhs) {return lhs>rhs;}

struct classcomp_set {
	bool operator() (const int& lhs, const int& rhs) const
	{ return lhs>rhs; }
};

TEMPLATE_TEST_CASE( "set - constructor ", "[set][constructor][leak]", int, IsLeaky )
{
	SECTION( "empty construtor" ) {
		cn::set<TestType> first;
		REQUIRE(first.empty());
		REQUIRE(first.size() == 0);
	}
	TestType myints[]= {10,20,30,40,50};
	cn::set<TestType> second (myints, myints+5);
	SECTION( "range construtor" ) {
		REQUIRE(!second.empty());
		REQUIRE(second.size() == 5);
	}
	SECTION( "copy construtor" ) {
		cn::set<TestType> third (second);
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
		cn::set<TestType> fourth (second.begin(), second.end());
		REQUIRE(!fourth.empty());
		REQUIRE(fourth.size() == 5);
	}
	SECTION( "class as Compare" ) {
		cn::set<TestType,classcomp_set> fifth;
		fifth.insert(1);
		fifth.insert(2);
		REQUIRE(*fifth.begin() == 2);
		REQUIRE(*--fifth.end() == 1);
		REQUIRE(*fifth.find(2) == 2);
	}
	SECTION( "function ptr as Compare" ) {
		bool(*fn_pt)(int,int) = fncomp_set;
		cn::set<TestType,bool(*)(int,int)> sixth (fn_pt);

		sixth.insert(1);
		sixth.insert(2);
		REQUIRE(*sixth.begin() == 2);
		REQUIRE(*--sixth.end() == 1);
		REQUIRE(*sixth.find(2) == 2);
	}

}

TEMPLATE_TEST_CASE( "set - operator - assignment ",
	"[set][operator][assignment][leak]", int, IsLeaky )
{
	TestType myints[] = { 10,20,30,40,50 };
	cn::set<TestType> first (myints,myints+5);
	cn::set<TestType> second;
	
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
		first = cn::set<TestType>();
	}
}

TEMPLATE_TEST_CASE( "set - iterator ",
	"[set][iterator][leak]", int, IsLeaky )
{
	cn::set<TestType> myset;
	SECTION( "empty container should have begin() == end()" )
	{
		REQUIRE( myset.begin() == myset.end() );
	}
	myset.insert(10);
	SECTION( "container with one element should have consistant boundary" )
	{
		REQUIRE( ++myset.begin() == myset.end() );
		REQUIRE( myset.begin() == --myset.end() );
		REQUIRE( myset.begin().operator*() == 10 );
		REQUIRE( myset.begin().operator->() == &*myset.begin() );
	}
	myset.insert(20);
	myset.insert(30);
	SECTION( "container with three elements should loop properly" )
	{
		auto it = myset.begin();
		int i = 0;
		while (it != myset.end())
		{
			i += 10;
			REQUIRE(*it == i);
			++it;
		}
		REQUIRE(i == 30);
	}
	SECTION( "container with three elements should loop properly in reverse" )
	{
		auto it = myset.end();
		int i = 40;
		while (--it != myset.begin())
		{
			i -= 10;
			REQUIRE(*it == i);
		}
		REQUIRE(*it == 10);
	}
}

TEMPLATE_TEST_CASE( "set - reverse iterator ",
	"[set][reverse_iterator][leak]", int, IsLeaky )
{
	cn::set<TestType> myset;
	SECTION( "empty container should have begin() == end()" )
	{
		REQUIRE( myset.rbegin() == myset.rend() );
	}
	myset.insert(10);
	SECTION( "container with one element should have consistant boundary" )
	{
		REQUIRE( ++myset.rbegin() == myset.rend() );
		REQUIRE( myset.rbegin() == --myset.rend() );
		REQUIRE( myset.rbegin().operator*() == 10 );
		REQUIRE( myset.rbegin().operator->() == &*myset.rbegin() );
	}
	myset.insert(20);
	myset.insert(30);
	SECTION( "container with three elements should loop properly" )
	{
		auto it = myset.rbegin();
		int i = 40;
		while (it != myset.rend())
		{
			i -= 10;
			REQUIRE(*it == i);
			++it;
		}
		REQUIRE(i == 10);
	}
	SECTION( "container with three elements should loop properly in reverse" )
	{
		auto it = myset.rend();
		int i = 0;
		while (--it != myset.rbegin())
		{
			i += 10;
			REQUIRE(*it == i);
		}
		REQUIRE(*it == 30);
	}
}

TEST_CASE( "set - capacity ", "[set][capacity]" )
{
	cn::set<int> mine;
	std::set<int> std_set;

	SECTION( "empty container should be empty (insightful)" )
	{
		REQUIRE(mine.empty());
		REQUIRE(mine.size() == 0);
	}
	mine.insert(10);
	SECTION( "container with one element should be of size one (and not empty, of course)" )
	{
		REQUIRE(!mine.empty());
		REQUIRE(mine.size() == 1);
	}
	mine.erase(mine.begin());
	SECTION( "delete the single element, should become an empty container again." )
	{
		REQUIRE(mine.size() == 0);
		REQUIRE(mine.empty());
	}
	SECTION( "max_size(), May not be equal to the std because depend on the underlying implementation of the node. (also OS dependant linux_side != macos_size)" )
	{
		CHECK_NOFAIL(std_set.max_size() == mine.max_size());
	}
}

TEMPLATE_TEST_CASE( "set - Modifiers - insert ",
	"[set][modifier][insert][leak]", int, IsLeaky )
{
	cn::set<TestType> myset;
	typename cn::set<TestType>::iterator it_res;
	cn::pair< typename cn::set<TestType>::iterator,bool> ret;
	
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

	TestType myType[]= {40,41,42,43};
	myset.insert(myType, myType+4);
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

TEMPLATE_TEST_CASE( "set - Modifiers - erase ", "[set][modifier][erase][leak]", int, IsLeaky )
{
	cn::set<TestType> myset;

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
	
	typename cn::set<TestType>::iterator it = ++myset.begin();
	typename cn::set<TestType>::iterator endRange =  --myset.end();
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

TEMPLATE_TEST_CASE( "set - Modifiers - swap ",
	"[set][modifier][swap][leak]", int, IsLeaky )
{
	TestType myints[]={12,75,10,32,20,25};
	cn::set<TestType> first (myints,myints+2);     // 12,75
	cn::set<TestType> second (myints+2,myints+6);  // 10,20,25,32

	void* first_begin = (void*)&*first.begin();
	void* second_begin = (void*)&*second.begin();

	typename cn::set<TestType>::size_type first_size = first.size();
	typename cn::set<TestType>::size_type second_size = second.size();
	REQUIRE(first_size == 2 );
	REQUIRE(second_size == 4 );

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

	REQUIRE(first_size == second.size() );
	REQUIRE(second_size == first.size() );

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

	SECTION( "Must only swap pointers. No allocation should be done" )
	{
		REQUIRE( first_begin == (void*)&*second.begin());
		REQUIRE( second_begin == (void*)&*first.begin());
	}

}

TEMPLATE_TEST_CASE( "set - Modifiers - clear ",
	"[set][modifier][clear][leak]", int, IsLeaky )
{
	cn::set<TestType> emptySet;
	SECTION( "Empty set being clear should be okay" )
	{
		emptySet.clear();
		REQUIRE( emptySet.empty() );
		REQUIRE( emptySet.size() == 0);
	}

	TestType myints[]={12,75,10,32,20,25};
	cn::set<TestType> myset (myints,myints+6);
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
	cn::set<int> myset;
	cn::set<int>::iterator it;

	for (int i=1; i<=5; i++)
		myset.insert(i*10);    // set: 10 20 30 40 50

	REQUIRE( *myset.find(10) == 10);
	REQUIRE( *myset.find(20) == 20);
	REQUIRE( *myset.find(50) == 50);
	REQUIRE( myset.find(42) == myset.end());
}

TEST_CASE( "set - Operations - count ", "[set][operation][count]" )
{
	cn::set<int> myset;

	for (int i=1; i<5; ++i)
		myset.insert(i*3); // 3 6 9 12

	REQUIRE( myset.count(0) == 0);
	REQUIRE( myset.count(1) == 0);
	REQUIRE( myset.count(3) == 1);
	REQUIRE( myset.count(12) == 1);
}

TEST_CASE( "set - Operations - lower_bound and upper_bound ", "[set][operation][lower_bound][upper_bound]" )
{
	cn::set<int> myset;
	cn::set<int>::iterator itlow,itup;

	auto itLow = myset.lower_bound(30);
	auto itUp = myset.upper_bound(60);

	CHECK(itLow == myset.end());
	CHECK(itUp == myset.end());

	for (int i=1; i<10; i++)
		myset.insert(i*10); // 10 20 30 40 50 60 70 80 90

	itLow = myset.lower_bound(30);
	itUp = myset.upper_bound(60);

	CHECK(*itLow == 30);
	CHECK(*itUp == 70);
}

TEST_CASE( "set - Operations - equal_range ", "[set][operation][equal_range]" )
{
	cn::set<int> myset;

	// empty set
	auto res = myset.equal_range(42);
	CHECK( res.first == myset.begin());
	CHECK( res.second == myset.begin());
	CHECK( res.first == myset.end());
	CHECK( res.second == myset.end());
	REQUIRE( res.first == res.second);

	for (int i=1; i<10; i++)
		myset.insert(i*10); // 10 20 30 40 50 60 70 80 90

	// min limit
	res = myset.equal_range(9);
	CHECK( res.first == myset.begin());
	CHECK( res.second == myset.begin());
	REQUIRE( res.first == res.second);


	res = myset.equal_range(10);
	CHECK( res.first == myset.begin());
	REQUIRE( *res.second == 20);

	// middle
	res = myset.equal_range(35);
	CHECK( *res.first == 40);
	CHECK( *res.second == 40);
	REQUIRE( res.first == res.second);

	res = myset.equal_range(50);
	CHECK( *res.first == 50);
	REQUIRE( *res.second == 60);

	// max limits
	res = myset.equal_range(90);
	CHECK( *res.first == 90);
	REQUIRE( res.second == myset.end());

	res = myset.equal_range(91);
	CHECK( res.first == myset.end());
	CHECK( res.second == myset.end());
	REQUIRE( res.first == res.second);
}

TEST_CASE( "set - Allocator - get_allocator ", "[set][allocator][get_allocator]" )
{
	cn::set<int> myset;
	int * p;
	unsigned int i;

	p = myset.get_allocator().allocate(5);

	for (i=0; i<5; i++)
		p[i]=(i+1)*10; // 10 20 30

	myset.get_allocator().deallocate(p,5);
}

TEMPLATE_TEST_CASE( "set - non-member - swap", "[set][non-member][swap][leak]", int, IsLeaky )
{
		TestType myints[]={12,75,10,32,20,25};
	cn::set<TestType> first (myints,myints+2);     // 12,75
	cn::set<TestType> second (myints+2,myints+6);  // 10,20,25,32

	void* first_begin = (void*)&*first.begin();
	void* second_begin = (void*)&*second.begin();

	typename cn::set<TestType>::size_type first_size = first.size();
	typename cn::set<TestType>::size_type second_size = second.size();
	REQUIRE(first_size == 2 );
	REQUIRE(second_size == 4 );

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

	cn::swap(first, second);

	REQUIRE(first_size == second.size() );
	REQUIRE(second_size == first.size() );

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

	SECTION( "Must only swap pointers. No allocation should be done" )
	{
		REQUIRE( first_begin == (void*)&*second.begin());
		REQUIRE( second_begin == (void*)&*first.begin());
	}

}