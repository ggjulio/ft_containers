#include "tests.hpp"

#include <vector>
#include <string>
#include "vector.hpp"

TEMPLATE_TEST_CASE( "vector - construct", "[vector][constructors][leak]", int, IsLeaky )
{
	SECTION( "empty construtor" ) {
		cn::vector<TestType> first;
		REQUIRE( first.size() == 0);
		REQUIRE( first.empty());
		REQUIRE( first.capacity() == 0);
	}
	cn::vector<TestType> second (4,100);
	SECTION( "fill constructor" )
	{
		CHECK( second[0] == 100);
		CHECK( second[1] == 100);
		CHECK( second[2] == 100);
		CHECK( second[3] == 100);
		REQUIRE( second.size() == 4);
		REQUIRE( !second.empty());
		REQUIRE( second.capacity() == 4);
	}
	cn::vector<TestType> third (second.begin(),second.end());
	SECTION( "range constructor" )
	{
		CHECK( third[0] == 100);
		CHECK( third[1] == 100);
		CHECK( third[2] == 100);
		CHECK( third[3] == 100);
		REQUIRE( third.size() == 4);
		REQUIRE( !third.empty());
		REQUIRE( second.capacity() == 4);
	}
	cn::vector<TestType> fourth (third);
	SECTION( "copy constructor" )
	{
		CHECK( fourth[0] == 100);
		CHECK( fourth[1] == 100);
		CHECK( fourth[2] == 100);
		CHECK( fourth[3] == 100);
		REQUIRE( fourth.size() == 4);
		REQUIRE( !fourth.empty());
		REQUIRE( second.capacity() == 4);
		
		SECTION( "A deep_copy/clone must be made" ) {
			REQUIRE( &fourth[0] != &third[0]);
		}
	}
	SECTION( "the iterator constructor can also be used to construct from arrays" )
	{
		TestType myT[] = {16,2,77,29, 42};
		cn::vector<TestType> fifth(myT, myT + sizeof(myT) / sizeof(TestType));

		CHECK( fifth[0] == 16);
		CHECK( fifth[1] == 2);
		CHECK( fifth[2] == 77);
		CHECK( fifth[3] == 29);
		CHECK( fifth[4] == 42);
		REQUIRE( !fifth.empty());
		REQUIRE( fifth.size() == 5);
		REQUIRE( second.capacity() == 4);
	}
}

TEMPLATE_TEST_CASE( "vector - operator - assignment ", "[vector][operator][assignment][leak]", int, IsLeaky )
{
	cn::vector<TestType> first(3, 42);
	cn::vector<TestType> second(5, 43);

	REQUIRE(first.size() == 3);
	REQUIRE(second.size() == 5);

	second = first;
	REQUIRE(first.size() == 3);
	REQUIRE(second.size() == 3);
	REQUIRE(second[0] == 42);

	first = cn::vector<TestType>();
	REQUIRE(first.size() == 0);
	REQUIRE(first.empty());
}

TEMPLATE_TEST_CASE( "vector - iterator ", "[vector][iterator][leak]", int, IsLeaky )
{
	cn::vector<TestType> myvector;
	SECTION( "empty container should have begin() == end()" )
	{
		REQUIRE( myvector.begin() == myvector.end() );
	}
	myvector.push_back(10);
	SECTION( "container with one element should have consistant boundary" )
	{
		REQUIRE( ++myvector.begin() == myvector.end() );
		REQUIRE( myvector.begin() == --myvector.end() );
		REQUIRE( myvector.begin().operator*() == 10 );
		REQUIRE( myvector.begin().operator->() == &*myvector.begin() );
	}
	myvector.push_back(20);
	myvector.push_back(30);
	SECTION( "container with three elements should loop properly" )
	{
		auto it = myvector.begin();
		int i = 0;
		while (it != myvector.end())
		{
			i += 10;
			REQUIRE(*it == i);
			++it;
		}
		REQUIRE(i == 30);
	}
	SECTION( "container with three elements should loop properly in reverse" )
	{
		auto it = myvector.end();
		int i = 40;
		while (--it != myvector.begin())
		{
			i -= 10;
			REQUIRE(*it == i);
		}
		REQUIRE(*it == 10);
	}

	SECTION( "const iterator should be comparable with iterator" )
	{
		typename cn::vector<TestType>::const_iterator const_it = myvector.begin();
		typename cn::vector<TestType>::iterator it = myvector.begin();
		typename cn::vector<TestType>::iterator it2 = myvector.begin() + 1;

		REQUIRE( const_it == it );
		REQUIRE( const_it <= it );
		REQUIRE( const_it >= it );
		REQUIRE( !(const_it > it) );
		REQUIRE( !(const_it < it) );
	
		REQUIRE( const_it != it2 );
		REQUIRE( const_it <= it2 );
		REQUIRE( const_it < it2 );
		REQUIRE( !(const_it > it2) );
		REQUIRE( !(const_it >= it2) );
	}

}

TEMPLATE_TEST_CASE( "vector - reverse iterator ", "[vector][reverse_iterator][leak]", int, IsLeaky )
{
	cn::vector<TestType> myvector;
	SECTION( "empty container should have begin() == end()" )
	{
		REQUIRE( myvector.rbegin() == myvector.rend() );
	}
	myvector.push_back(10);
	SECTION( "container with one element should have consistant boundary" )
	{
		REQUIRE( ++myvector.rbegin() == myvector.rend() );
		REQUIRE( myvector.rbegin() == --myvector.rend() );
		REQUIRE( myvector.rbegin().operator*() == 10 );
		REQUIRE( myvector.rbegin().operator->() == &*myvector.rbegin() );
	}
	myvector.push_back(20);
	myvector.push_back(30);
	SECTION( "container with three elements should loop properly" )
	{
		auto it = myvector.rbegin();
		int i = 40;
		while (it != myvector.rend())
		{
			i -= 10;
			REQUIRE(*it == i);
			++it;
		}
		REQUIRE(i == 10);
	}
	SECTION( "container with three elements should loop properly in reverse" )
	{
		auto it = myvector.rend();
		int i = 0;
		while (--it != myvector.rbegin())
		{
			i += 10;
			REQUIRE(*it == i);
		}
		REQUIRE(*it == 30);
	}
}

TEMPLATE_TEST_CASE( "vector - capacity ", "[vector][capacity][leak]", int, IsLeaky )
{
	cn::vector<TestType> myvector;
	std::vector<TestType> std_vector;

	SECTION( "empty container should be empty (insightful)" )
	{
		REQUIRE(myvector.empty());
		REQUIRE(myvector.size() == 0);
	}
	myvector.push_back(10);
	SECTION( "container with one element should be of size one (and not empty, of course)" )
	{
		REQUIRE(!myvector.empty());
		REQUIRE(myvector.size() == 1);
	}
	myvector.erase(myvector.begin());
	SECTION( "delete the single element, should become an empty container again." )
	{
		REQUIRE(myvector.size() == 0);
		REQUIRE(myvector.empty());
	}
	SECTION( "max_size(), For now I don't know which value is suposed to be equal to (probably depend on the underlying implementation)" )
	{
		REQUIRE(std_vector.max_size() == myvector.max_size());
	}
}

TEMPLATE_TEST_CASE( "vector - capacity - resize" ,
	"[vector][capacity][resize][leak]", int, IsLeaky )
{
	cn::vector<TestType> myvector;

	for (int i= 1 ;i<10;i++)
	{
		REQUIRE( myvector.size() <= myvector.capacity());
		size_t capacity = myvector.capacity() ? myvector.capacity() : 1;
		bool shouldGrow = capacity == myvector.size();
		myvector.push_back(i); // 1 2 3 4 5 6 7 8 9
		if (shouldGrow)
			REQUIRE(capacity * 2 == myvector.capacity());
	}
	// push back should work
	{
		int i = -1;
		while (++i < 9)
			REQUIRE( myvector[i] == i + 1);
		REQUIRE( &*myvector.end() == &myvector[i]);
		REQUIRE( myvector.size() == 9);
		REQUIRE( myvector.capacity() == 16);
	}

	// resize lower
	myvector.resize(5);
	{
		int i = -1;
		while (++i < 5)
			REQUIRE( myvector[i] == i + 1);
		REQUIRE( &*myvector.end() == &myvector[i]);
		REQUIRE( myvector.size() == 5);
		REQUIRE( myvector.capacity() == 16);
	}

	// resize bigger with 100 as default value
	myvector.resize(8,100);
	{
		int i = 0;
		for (; i < 5; i++)
		 	REQUIRE( myvector[i] == i + 1);
		for (; i < 8; i++)
			REQUIRE( myvector[i] == 100);
		REQUIRE( &*myvector.end() == &myvector[i]);
		REQUIRE( myvector.size() == 8);
		REQUIRE( myvector.capacity() == 16);
	}

	// resize bigger with no value
	myvector.resize(12);
	{
		int i = 0;
		for (; i < 5; i++)
			REQUIRE( myvector[i] == i + 1);
		for (; i < 8; i++)
			REQUIRE( myvector[i] == 100);
		for (; i < 12; i++)
			REQUIRE( myvector[i] == 0);
		REQUIRE( &*myvector.end() == &myvector[i]);
		REQUIRE( myvector.size() == 12);
		REQUIRE( myvector.capacity() == 16);
	}
}

TEMPLATE_TEST_CASE( "vector - capacity - vectors can be sized and resized",
	"[vector][capacity][reserve][leak]", int, IsLeaky )
{
	cn::vector<TestType> v( 5 );
	REQUIRE( v.size() == 5 );
	REQUIRE( v.capacity() >= 5 );

	SECTION("resizing bigger changes size and capacity") {
		v.resize( 10 );

		REQUIRE( v.size() == 10 );
		REQUIRE( v.capacity() >= 10 );
	}
	SECTION("resizing smaller changes size but not capacity") {
		v.resize( 0 );

		REQUIRE( v.size() == 0 );
		REQUIRE( v.capacity() >= 5 );
	}
	SECTION("We can use the 'swap trick' to reset the capacity") {
		cn::vector<TestType> empty;
		empty.swap( v );

		REQUIRE( v.capacity() == 0 );
	}
	SECTION("reserving smaller does not change size or capacity") {
		v.reserve( 0 );
		
		REQUIRE( v.size() == 5 );
		REQUIRE( v.capacity() >= 5 );
	}
	SECTION("reserving should work") {
		cn::vector<TestType> vec;

		REQUIRE( vec.size() == 0 );
		REQUIRE( vec.capacity() == 0 );
		
		vec.reserve(1);
		REQUIRE( vec.size() == 0 );
		REQUIRE( vec.capacity() == 1 );
		
		vec.reserve(3);
		REQUIRE( vec.size() == 0 );
		REQUIRE( vec.capacity() == 3 );

		vec.push_back(42);
		vec.push_back(42);
		vec.push_back(42);
		REQUIRE( vec.size() == 3 );
		REQUIRE( vec.capacity() == 3 );

		vec.push_back(42);
		REQUIRE( vec.size() == 4 );
		REQUIRE( vec.capacity() == 6 );
	}
}

TEST_CASE( "vector - Element access - operator[] (subscript) ", "[vector][element_access][operator][subscript]" )
{
	cn::vector<int> v(5, 42);

	REQUIRE( v[0] == 42);
	v[0] = -42;
	REQUIRE( v[0] == -42);
	v[1] = v[0];
	REQUIRE( v[1] == -42);
}

TEST_CASE( "vector - Element access - at() ", "[vector][element_access][at]" )
{
	cn::vector<int> v(5, 42);

	REQUIRE( v.at(0) == 42);
	v.at(0) = -42;
	REQUIRE( v.at(0) == -42);
	v.at(1) = v.at(0);
	REQUIRE( v.at(1) == -42);

	REQUIRE_NOTHROW(v.at(4));
	REQUIRE_THROWS_AS(v.at(5), std::out_of_range);
}

TEST_CASE( "vector - Element access - front() ", "[vector][element_access][front]" )
{
	cn::vector<int> v(5, 42);

	REQUIRE( v.front() == 42);
	v.at(0) = -42;
	REQUIRE( v.front() == -42);
}

TEST_CASE( "vector - Element access - back() ", "[vector][element_access][back]" )
{
	cn::vector<int> v(5, 42);

	REQUIRE( v.back() == 42);
	v.at(4) = -42;
	REQUIRE( v.back() == -42);
}

TEMPLATE_TEST_CASE( "vector - Modifiers - assign() ",
	"[vector][modifier][assign][leak]", int, IsLeaky )
{
	cn::vector<TestType> first;

	REQUIRE( first.empty());
	first.assign(7,100);
	SECTION( "assign fill should work" )
	{
		REQUIRE( first.size() == 7);
	}

	cn::vector<TestType> second;
	SECTION( "assign range should work" )
	{
		second.assign (first.begin()+1, first.end()-1); // the 5 central values of first
		REQUIRE( second.size() == 5);
	}
	SECTION( "assign range from simple array" )
	{
		TestType myT[] = {1776,7,4};
		cn::vector<TestType> third;
		third.assign (myT, myT+3);
		REQUIRE( third.size() == 3);
	}
}

TEMPLATE_TEST_CASE( "vector - Modifiers - push_back() and pop_back() ",
	"[vector][modifier][push_back][pop_back][leak]", int, IsLeaky )
{
	cn::vector<TestType> myvector;

	myvector.push_back(42);
	REQUIRE( myvector.size() == 1);
	REQUIRE( myvector.capacity() == 1);
	REQUIRE( myvector[0] == 42);

	myvector.push_back(43);
	REQUIRE( myvector.size() == 2);
	REQUIRE( myvector.capacity() == 2);
	REQUIRE( myvector[1] == 43);

	myvector.push_back(44);
	REQUIRE( myvector.size() == 3);
	REQUIRE( myvector.capacity() == 4);
	REQUIRE( myvector[2] == 44);

	myvector.pop_back();
	REQUIRE( myvector.size() == 2);
	REQUIRE( myvector.capacity() == 4);

	myvector.pop_back();
	REQUIRE( myvector.size() == 1);
	REQUIRE( myvector.capacity() == 4);

	myvector.pop_back();
	REQUIRE( myvector.size() == 0);
	REQUIRE( myvector.capacity() == 4);
	REQUIRE( myvector.empty());

}

TEMPLATE_TEST_CASE( "vector - Modifiers - insert() ",
	"[vector][modifier][insert][leak]", int, IsLeaky )
{
	cn::vector<TestType> myvector (3,100);
	REQUIRE( myvector[0] == 100);
	REQUIRE( myvector[1] == 100);
	REQUIRE( myvector[2] == 100);
	REQUIRE( &myvector[3] == &*myvector.end());
	REQUIRE( !myvector.empty());
	REQUIRE( myvector.size() == 3);
	REQUIRE( myvector.capacity() == 3);

	// Insert single element overload
	myvector.insert(myvector.begin(), 200);
	{
		REQUIRE( myvector[0] == 200);
		REQUIRE( myvector[1] == 100);
		REQUIRE( myvector[2] == 100);
		REQUIRE( myvector[3] == 100);
		REQUIRE( &myvector[4] == &*myvector.end());
		REQUIRE( myvector.size() == 4);
		REQUIRE( myvector.capacity() == 6);
	}

  // Insert fill overload
	myvector.insert(myvector.begin(), 3, 50);
	{
		REQUIRE( myvector[0] == 50);
		REQUIRE( myvector[1] == 50);
		REQUIRE( myvector[2] == 50);
		REQUIRE( myvector[3] == 200);
		REQUIRE( myvector[4] == 100);
		REQUIRE( myvector[5] == 100);
		REQUIRE( myvector[6] == 100);
		REQUIRE( &myvector[7] == &*myvector.end());
		REQUIRE( myvector.size() == 7);
		REQUIRE( myvector.capacity() >= 7);
	}

	// Insert range from array
	TestType myarray[] = { 501,502,503 };
	myvector.insert(myvector.begin(), myarray, myarray+3);
	{
		REQUIRE( myvector[0] == 501);
		REQUIRE( myvector[1] == 502);
		REQUIRE( myvector[2] == 503);
		REQUIRE( myvector.size() == 10);
		REQUIRE( myvector.capacity() >= 10);
	}


	// Insert range from basic iterator
	std::vector<TestType> anothervector (2,400);
	myvector.insert(--myvector.end(),anothervector.begin(),anothervector.end());
	{
		REQUIRE( myvector[9] == 400);
		REQUIRE( myvector[10] == 400);
		REQUIRE( myvector.size() == 12);
		REQUIRE( myvector.capacity() >= 12);
	}
}

TEMPLATE_TEST_CASE( "vector - Modifiers - erase() ",
	"[vector][modifier][erase][leak]", int, IsLeaky)
{
	 cn::vector<TestType> myvector;

	for (int i=1; i<=10; i++)
		myvector.push_back(i); // 1 2 3 4 5 6 7 8 9 10

	REQUIRE( myvector.size() == 10);

	REQUIRE( myvector[0] == 1);
	REQUIRE( myvector[1] == 2);
	REQUIRE( myvector[2] == 3);
	REQUIRE( myvector[3] == 4);
	REQUIRE( myvector[4] == 5);
	REQUIRE( myvector[5] == 6);
	REQUIRE( myvector[6] == 7);
	REQUIRE( myvector[7] == 8);
	REQUIRE( myvector[8] == 9);
	REQUIRE( myvector[9] == 10);

	myvector.erase (myvector.begin()+5);
	SECTION( "erase position middle")
	{
		REQUIRE( myvector.size() == 9);

		REQUIRE( myvector[0] == 1);
		REQUIRE( myvector[1] == 2);
		REQUIRE( myvector[2] == 3);
		REQUIRE( myvector[3] == 4);
		REQUIRE( myvector[4] == 5);
		REQUIRE( myvector[5] == 7);
		REQUIRE( myvector[6] == 8);
		REQUIRE( myvector[7] == 9);
		REQUIRE( myvector[8] == 10);

	}

	myvector.erase (--myvector.end());
	SECTION( "erase position last")
	{
		REQUIRE( myvector.size() == 8);

		REQUIRE( myvector[0] == 1);
		REQUIRE( myvector[1] == 2);
		REQUIRE( myvector[2] == 3);
		REQUIRE( myvector[3] == 4);
		REQUIRE( myvector[4] == 5);
		REQUIRE( myvector[5] == 7);
		REQUIRE( myvector[6] == 8);
		REQUIRE( myvector[7] == 9);

	}
	myvector.erase (myvector.begin());
	SECTION( "erase position begin")
	{
		REQUIRE( myvector.size() == 7);

		REQUIRE( myvector[0] == 2);
		REQUIRE( myvector[1] == 3);
		REQUIRE( myvector[2] == 4);
		REQUIRE( myvector[3] == 5);
		REQUIRE( myvector[4] == 7);
		REQUIRE( myvector[5] == 8);
		REQUIRE( myvector[6] == 9);
	}

	myvector.erase (myvector.begin(),myvector.begin()+3);
	SECTION( "erase range 3 elem from begin")
	{
		REQUIRE( myvector.size() == 4);

		REQUIRE( myvector[0] == 5);
		REQUIRE( myvector[1] == 7);
		REQUIRE( myvector[2] == 8);
		REQUIRE( myvector[3] == 9);
	}

	myvector.erase (myvector.begin(),myvector.end());
	SECTION( "erase range begin to end")
	{
		REQUIRE( myvector.size() == 0);
	}
}

TEMPLATE_TEST_CASE( "vector - Modifiers - swap ",
	"[vector][modifier][swap][leak]", int, IsLeaky )
{
	TestType myT[]={12,75,10,32,20,25};
	cn::vector<TestType> first (myT,myT+2);     // 12,75
	cn::vector<TestType> second (myT+2,myT+6);  // 10,20,25,32

	typename cn::vector<TestType>::pointer first_start = &*first.begin();
	typename cn::vector<TestType>::pointer first_finish = &*first.end();
	typename cn::vector<TestType>::pointer first_end_of_storage = &*first.begin() + first.capacity();
	REQUIRE( first_start + 2 == first_finish);
	REQUIRE( first_finish == first_end_of_storage);

	typename cn::vector<TestType>::pointer second_start = &*second.begin();
	typename cn::vector<TestType>::pointer second_finish = &*second.end();
	typename cn::vector<TestType>::pointer second_end_of_storage = &*second.begin() + second.capacity();
	REQUIRE( second_start + 4 == second_finish);
	REQUIRE( second_finish == second_end_of_storage);


	REQUIRE( first.size() == 2 );
	REQUIRE( first.capacity() == 2 );
	REQUIRE( second.size() == 4 );
	REQUIRE( second.capacity() == 4 );

	auto it = first.begin();
	REQUIRE(*it++ == 12);
	REQUIRE(*it++ == 75);
	REQUIRE(it == first.end());

	it = second.begin();
	REQUIRE(*it++ == 10);
	REQUIRE(*it++ == 32);
	REQUIRE(*it++ == 20);
	REQUIRE(*it++ == 25);
	REQUIRE(it == second.end());

	first.swap(second);

	REQUIRE( first.size() == 4 );
	REQUIRE( first.capacity() == 4 );
	REQUIRE( second.size() == 2 );
	REQUIRE( second.capacity() == 2 );

	it = first.begin();
	REQUIRE(*it++ == 10);
	REQUIRE(*it++ == 32);
	REQUIRE(*it++ == 20);
	REQUIRE(*it++ == 25);
	REQUIRE(it == first.end());

	it = second.begin();
	REQUIRE(*it++ == 12);
	REQUIRE(*it++ == 75);
	REQUIRE(it == second.end());


	SECTION( "Must only swap pointers. No allocation should be done" )
	{
		REQUIRE( first_start == &*second.begin());
		REQUIRE( first_finish == &*second.end());
		REQUIRE( first_end_of_storage == &*second.begin() + second.capacity());

		REQUIRE( second_start == &*first.begin());
		REQUIRE( second_finish == &*first.end());
		REQUIRE( second_end_of_storage == &*first.begin() + first.capacity());
	}
}

TEST_CASE( "vector - Modifiers - clear ", "[vector][modifier][clear]" )
{
	cn::vector<int> emptyVector;
	SECTION( "Empty vector being clear should be okay" )
	{
		emptyVector.clear();
		REQUIRE( emptyVector.empty() );
		REQUIRE( emptyVector.size() == 0);
		REQUIRE( emptyVector.capacity() == 0);
	}

	int myints[]={12,75,10,32,20,25};
	cn::vector<int> myvector (myints,myints+6);
	REQUIRE( !myvector.empty() );
	REQUIRE( myvector.size() == 6);
	REQUIRE( myvector.capacity() == 6);
	myvector.clear();
	SECTION( "Clear set who contain element should be ok" )
	{
		REQUIRE( myvector.empty() );
		REQUIRE( myvector.size() == 0);
		REQUIRE( myvector.capacity() == 6);
	}
	myvector.clear();
	SECTION( "Clear two times should be ok" )
	{
		REQUIRE( myvector.empty() );
		REQUIRE( myvector.size() == 0);
		REQUIRE( myvector.capacity() == 6);
	}
}

TEST_CASE( "vector - Allocator - get_allocator ", "[vector][allocator][get_allocator]" )
{
	cn::vector<int> myvector;
	int * p;
	unsigned int i;

	p = myvector.get_allocator().allocate(5);

	for (i=0; i<5; i++)
		p[i]=(i+1)*10; // 10 20 30

	myvector.get_allocator().deallocate(p,5);
}

TEST_CASE( "vector - non-member - relational operators", "[vector][non-member][relational][operator]" )
{
	std::vector<int> foo (3,100);
	std::vector<int> bar (2,200);
	std::vector<int> bare (2,200);


	REQUIRE( foo != bar );
	REQUIRE( foo < bar );
	REQUIRE( foo <= bar );

	REQUIRE( bar > foo );
	REQUIRE( bar >= foo );

	REQUIRE( bar == bare );
	REQUIRE( bar <= bare );

	REQUIRE( bare  >= bar );

}

TEMPLATE_TEST_CASE( "vector - non-member - swap", "[vector][non-member][swap][leak]", int, IsLeaky )
{
	TestType myints[]={12,75,10,32,20,25};
	cn::vector<TestType> first (myints,myints+2);     // 12,75
	cn::vector<TestType> second (myints+2,myints+6);  // 10,20,25,32

	typename cn::vector<TestType>::pointer first_start = &*first.begin();
	typename cn::vector<TestType>::pointer first_finish = &*first.end();
	typename cn::vector<TestType>::pointer first_end_of_storage = &*first.begin() + first.capacity();
	REQUIRE( first_start + 2 == first_finish);
	REQUIRE( first_finish == first_end_of_storage);

	typename cn::vector<TestType>::pointer second_start = &*second.begin();
	typename cn::vector<TestType>::pointer second_finish = &*second.end();
	typename cn::vector<TestType>::pointer second_end_of_storage = &*second.begin() + second.capacity();
	REQUIRE( second_start + 4 == second_finish);
	REQUIRE( second_finish == second_end_of_storage);

	// save iterators to check their validity later after swap
	typename cn::vector<TestType>::iterator it_save = first.begin();
	typename cn::vector<TestType>::const_iterator const_it_save = first.begin();
	typename cn::vector<TestType>::iterator end_save = first.end();
	typename cn::vector<TestType>::const_iterator const_end_save = first.end();

	REQUIRE( first.size() == 2 );
	REQUIRE( first.capacity() == 2 );
	REQUIRE( second.size() == 4 );
	REQUIRE( second.capacity() == 4 );

	auto it = first.begin();
	REQUIRE(*it++ == 12);
	REQUIRE(*it++ == 75);
	REQUIRE(it == first.end());

	it = second.begin();
	REQUIRE(*it++ == 10);
	REQUIRE(*it++ == 32);
	REQUIRE(*it++ == 20);
	REQUIRE(*it++ == 25);
	REQUIRE(it == second.end());

	cn::swap(first, second);

	REQUIRE( first.size() == 4 );
	REQUIRE( first.capacity() == 4 );
	REQUIRE( second.size() == 2 );
	REQUIRE( second.capacity() == 2 );

	it = first.begin();
	REQUIRE(*it++ == 10);
	REQUIRE(*it++ == 32);
	REQUIRE(*it++ == 20);
	REQUIRE(*it++ == 25);
	REQUIRE(it == first.end());

	it = second.begin();
	REQUIRE(*it++ == 12);
	REQUIRE(*it++ == 75);
	REQUIRE(it == second.end());

	SECTION( "Must only swap pointers. No allocation should be done" )
	{
		REQUIRE( first_start == &*second.begin());
		REQUIRE( first_finish == &*second.end());
		REQUIRE( first_end_of_storage == &*second.begin() + second.capacity());

		REQUIRE( second_start == &*first.begin());
		REQUIRE( second_finish == &*first.end());
		REQUIRE( second_end_of_storage == &*first.begin() + first.capacity());
	}

	SECTION( "iterators. must remain valid" )
	{
		REQUIRE( it_save != first.begin());
		REQUIRE( it_save == second.begin());

		REQUIRE( const_it_save != first.begin());
		REQUIRE( const_it_save == second.begin());

		REQUIRE( end_save != first.end());
		REQUIRE( end_save == second.end());

		REQUIRE( const_end_save != first.end());
		REQUIRE( const_end_save == second.end());
	}
}


// make check && valgrind --leak-check=full --show-leak-kinds=all --show-reachable=yes --track-origins=yes ./build/tests '-s [leak]'
// or just:
// cd tests && make valgrind
TEST_CASE( "vector - destruction - Having leaks here, mean objects are not destroyed properly",
	"[vector][destruction][leak]" )
{
	SECTION( "constructor empty - bro, impossible to have a leak here")
	{
		cn::vector<IsLeaky> vec;
	}
	SECTION( "constructor fill - basic may be some leak if destructor does not manage properly destruction")
	{
		cn::vector<IsLeaky> vec(5);
	}
	SECTION( "constructor fill - same shit as previous section")
	{
		cn::vector<IsLeaky> vec(5, 42);
	}
	SECTION( "constructor fill - same shit as previous section")
	{
		cn::vector<IsLeaky> vec(5, 42);
	}
	SECTION( "constructor range - same shit as previous section")
	{
		IsLeaky array[] = {1,2,3,4};
		cn::vector<IsLeaky> vec(array, array +  sizeof(array) / sizeof(IsLeaky));
	}
	SECTION( "assignment operator - basic")
	{
		cn::vector<IsLeaky> vec(5,42);
		cn::vector<IsLeaky> vec2;

		vec2 = vec;
	}
	SECTION( "assignment operator - destination capacity is greater than source")
	{
		cn::vector<IsLeaky> vec(5,42);
		cn::vector<IsLeaky> vec2(10,21);

		vec2 = vec;
	}
	SECTION( "assignment operator - destination capacity is lower than source (some leaks maybe ?)")
	{
		cn::vector<IsLeaky> vec(5,42);
		cn::vector<IsLeaky> vec2(2,21);

		vec2 = vec;
	}
	SECTION( "assignment operator - destination has same capacity than source")
	{
		cn::vector<IsLeaky> vec(5,42);
		cn::vector<IsLeaky> vec2(5,21);

		vec2 = vec;
	}
	SECTION( "assignment operator - destination capacity > source, bus dest size == 1")
	{
		cn::vector<IsLeaky> vec(5,42);
		cn::vector<IsLeaky> vec2(1,42);

		vec2.reserve(10);
		vec2 = vec;
	}
	SECTION( "Resize - no comment")
	{
		cn::vector<IsLeaky> vec;

		vec.resize(10);
		vec.resize(5);
		vec.resize(15);
		vec.resize(3);
	}
	SECTION( "Reserve - no comment")
	{
		cn::vector<IsLeaky> vec(2, 42);

		vec.reserve(5);
		vec.reserve(10);
		vec.reserve(15);
		vec.reserve(0); // lol useless 
	}
	SECTION( "Assign fill " )
	{
		cn::vector<IsLeaky> vec;

		vec.assign(4, 44);
		vec.assign(5, 45);
		vec.assign(5, 45);
		vec.assign(6, 46);
		vec.assign(9, 47);
		vec.assign(0, 47);
		vec.assign(5, 47);
		vec.assign(0, 47);
	}
	SECTION( "Assign fill " )
	{
		cn::vector<IsLeaky> vec(5, 42);

		vec.assign(4, 44);
		vec.assign(5, 45);
		vec.assign(5, 45);
		vec.assign(6, 46);
		vec.assign(9, 47);
		vec.assign(0, 47);
		vec.assign(5, 47);
	}
	SECTION( "Assign range " )
	{
		cn::vector<IsLeaky> vec;

		IsLeaky array1[] = {1,2,3};
		IsLeaky array2[] = {1,2,3,4};
		IsLeaky array3[] = {1,2,3,4,5};
		vec.assign(array2, array2 +  sizeof(array2) / sizeof(IsLeaky));
		vec.assign(array1, array1 +  sizeof(array1) / sizeof(IsLeaky));
		vec.assign(array3, array3 +  sizeof(array3) / sizeof(IsLeaky));
		vec.assign(array1, array1 +  sizeof(array1) / sizeof(IsLeaky));
		vec.assign(array1, array1 +  sizeof(array1) / sizeof(IsLeaky));

	}
	SECTION( "Some push_back, thus some grow/relocation (and hopefully destruct...)")
	{
		cn::vector<IsLeaky> vec;

		REQUIRE(vec.capacity() == 0);
		vec.push_back(33);
		REQUIRE(vec.capacity() == 1);
		vec.push_back(33);
		vec.push_back(33);
	}
	SECTION( "Some push_back, and pop back")
	{
		cn::vector<IsLeaky> vec;

		REQUIRE(vec.capacity() == 0);
		vec.push_back(33);
		REQUIRE(vec.capacity() == 1);
		vec.pop_back();
		vec.push_back(33);
		vec.push_back(33);
		REQUIRE(vec.capacity() == 2);
		vec.push_back(33);
		REQUIRE(vec.capacity() == 4);
		vec.pop_back();
	}
	SECTION( "insert pos")
	{
		cn::vector<IsLeaky> vec;

		REQUIRE(vec.capacity() == 0);
		vec.insert(vec.begin(), 42);
		REQUIRE(vec.capacity() == 1);
		vec.insert(vec.begin(), 43);
		REQUIRE(vec.capacity() == 2);
		vec.insert(vec.begin(), 44);
		vec.insert(vec.end(), 45);
		REQUIRE(vec.capacity() == 4);
		vec.insert(vec.end(), 46);
		vec.insert(vec.end(), 47);
		vec.insert(vec.begin()+1, 48); // sigsegv here: i was copying (copy call operator=() ) on the uninitialised block at end()
		REQUIRE( *--vec.end() == 47 );
		REQUIRE( *(vec.end()- 2) == 46 );
		REQUIRE( *++vec.begin() == 48 );
		vec.insert(vec.end() - 3, 50);
		vec.insert(vec.begin()+1, 51);
		vec.insert(--vec.end(), 52);
	}
	SECTION( "insert range")
	{
		cn::vector<IsLeaky> vec;

		IsLeaky array[] = {1};
		REQUIRE(vec.capacity() == 0);
		vec.insert(vec.begin(), array, array +  sizeof(array) / sizeof(IsLeaky));
		REQUIRE(vec.capacity() == 1);
		vec.insert(vec.begin(), array, array +  sizeof(array) / sizeof(IsLeaky));
		REQUIRE(vec.capacity() == 2);
		vec.insert(vec.begin(), array, array +  sizeof(array) / sizeof(IsLeaky));
	}

}