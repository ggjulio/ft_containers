#include "tests.hpp"

#include <vector>
#include <string>
#include "vector.hpp"

TEST_CASE( "vector - construct", "[vector][constructors]" )
{
	SECTION( "empty construtor" ) {
		cn::vector<int> first;
		REQUIRE( first.size() == 0);
		REQUIRE( first.empty());
		REQUIRE( first.capacity() == 0);
	}
	cn::vector<int> second (4,100);
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
	cn::vector<int> third (second.begin(),second.end());
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
	// cn::vector<int> fourth (third);
	// SECTION( "copy constructor" )
	// {
	// 	CHECK( fourth[0] == 100);
	// 	CHECK( fourth[1] == 100);
	// 	CHECK( fourth[2] == 100);
	// 	CHECK( fourth[3] == 100);
	// 	REQUIRE( fourth.size() == 4);
	// 	REQUIRE( !fourth.empty());
	// 	REQUIRE( second.capacity() == 4);
	// }
	SECTION( "the iterator constructor can also be used to construct from arrays" )
	{
		int myints[] = {16,2,77,29, 42};
		cn::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

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

// TEST_CASE( "vector - operator - assignment ", "[vector][operator][assignment]" )
// {
// 	cn::vector<int> first(3, 42);
// 	cn::vector<int> second(5, 43);

// 	REQUIRE(first.size() == 3);
// 	REQUIRE(second.size() == 5);

// 	second = first;
// 	REQUIRE(first.size() == 3);
// 	REQUIRE(second.size() == 3);
// 	REQUIRE(second[0] == 42);

// 	first = cn::vector<int>();
// 	REQUIRE(first.size() == 0);
// 	REQUIRE(first.empty());
// }

TEST_CASE( "vector - iterator ", "[vector][iterator]" )
{
	cn::vector<int> myvector;
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
}

TEST_CASE( "vector - reverse iterator ", "[vector][reverse_iterator]" )
{
	cn::vector<int> myvector;
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

TEST_CASE( "vector - capacity ", "[vector][capacity]" )
{
	cn::vector<int> myvector;
	std::vector<int> std_vector;

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

TEST_CASE( "vector - capacity - resize" ,
	"[vector][capacity][resize]" )
{
	cn::vector<int> myvector;

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

// TEST_CASE( "vector - capacity - vectors can be sized and resized",
// 	"[vector][capacity]" )
// {
// 	cn::vector<int> v( 5 );
// 	REQUIRE( v.size() == 5 );
// 	REQUIRE( v.capacity() >= 5 );

// 	SECTION("resizing bigger changes size and capacity") {
// 		v.resize( 10 );

// 		REQUIRE( v.size() == 10 );
// 		REQUIRE( v.capacity() >= 10 );
// 	}
// 	SECTION("resizing smaller changes size but not capacity") {
// 		v.resize( 0 );

// 		REQUIRE( v.size() == 0 );
// 		REQUIRE( v.capacity() >= 5 );
// 	}
// 	SECTION("We can use the 'swap trick' to reset the capacity") {
// 		cn::vector<int> empty;
// 		empty.swap( v );

// 		REQUIRE( v.capacity() == 0 );
// 	}
// 	SECTION("reserving smaller does not change size or capacity") {
// 		v.reserve( 0 );
		
// 		REQUIRE( v.size() == 5 );
// 		REQUIRE( v.capacity() >= 5 );
// 	}
// }

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

// TEST_CASE( "vector - Modifiers - assign() ", "[vector][modifier][assign]" )
// {
// 	cn::vector<int>::iterator it;
// 	cn::vector<int> first;

// 	REQUIRE( first.empty());
// 	first.assign(7,100);
// 	SECTION( "assign fill should work" )
// 	{
// 		REQUIRE( first.size() == 7);
// 	}

// 	it = first.begin()+1;
// 	cn::vector<int> second;
// 	SECTION( "assign range should work" )
// 	{
// 		second.assign (it, first.end()-1); // the 5 central values of first
// 		REQUIRE( second.size() == 5);
// 	}
// 	SECTION( "assign range from simple array" )
// 	{
// 		int myints[] = {1776,7,4};
// 		cn::vector<int> third;
// 		third.assign (myints, myints+3);
// 		REQUIRE( third.size() == 3);
// 	}
// }

TEST_CASE( "vector - Modifiers - push_back() and pop_back() ", "[vector][modifier][push_back][pop_back]" )
{
	cn::vector<int> myvector;

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


	myvector.pop_back();
	SECTION( "pop_back an empty vector" )
	{
		REQUIRE( myvector.size() == (size_t)-1);
		REQUIRE( !myvector.empty());
	}

	// also add tests for resize when size > capacity

}

TEST_CASE( "vector - Modifiers - insert() ", "[vector][modifier][insert]" )
{
	cn::vector<int> myvector (3,100);
	REQUIRE( myvector[0] == 100);
	REQUIRE( myvector[1] == 100);
	REQUIRE( myvector[2] == 100);
	REQUIRE( &myvector[3] == &*myvector.end());
	REQUIRE( !myvector.empty());
	REQUIRE( myvector.size() == 3);
	REQUIRE( myvector.capacity() == 3);

	myvector.insert(myvector.begin(), 200);
	SECTION( "Insert single element overload" )
	{
		REQUIRE( myvector[0] == 200);
		REQUIRE( myvector[1] == 100);
		REQUIRE( myvector[2] == 100);
		REQUIRE( myvector[3] == 100);
		REQUIRE( &myvector[4] == &*myvector.end());
		REQUIRE( myvector.size() == 4);
		REQUIRE( myvector.capacity() == 6);
	}

	// myvector.insert(myvector.begin(), 3, 50);
	// SECTION( "Insert fill overload" )
	// {
	// 	REQUIRE( myvector[0] == 50);
	// 	REQUIRE( myvector[1] == 50);
	// 	REQUIRE( myvector[2] == 50);
	// 	REQUIRE( myvector[3] == 200);
	// 	REQUIRE( myvector[4] == 100);
	// 	REQUIRE( myvector[5] == 100);
	// 	REQUIRE( myvector[6] == 100);
	// 	REQUIRE( &myvector[7] == &*myvector.end());
	// 	REQUIRE( myvector.size() == 7);
	// 	REQUIRE( myvector.capacity() == 8);
	// }

	// int myarray [] = { 501,502,503 };
	// myvector.insert(myvector.begin(), myarray, myarray+3);
	// SECTION( "Insert range from array" )
	// {
	// 	REQUIRE( myvector[0] == 501);
	// 	REQUIRE( myvector[1] == 502);
	// 	REQUIRE( myvector[2] == 503);
	// 	REQUIRE( myvector.size() == 10);
	// 	REQUIRE( myvector.capacity() == 14);
	// }
	// std::vector<int> anothervector (2,400);
	// myvector.insert(--myvector.end(),anothervector.begin(),anothervector.end());

	// SECTION( "Insert range from basic iterator" )
	// {
	// 	REQUIRE( myvector[9] == 400);
	// 	REQUIRE( myvector[10] == 400);
	// 	REQUIRE( myvector.size() == 12);
	// 	REQUIRE( myvector.capacity() == 14);
	// }
}

TEST_CASE( "vector - Modifiers - erase() ", "[vector][modifier][erase]" )
{
	 cn::vector<int> myvector;

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

TEST_CASE( "vector - Modifiers - swap ", "[vector][modifier][swap]" )
{
	int myints[]={12,75,10,32,20,25};
	cn::vector<int> first (myints,myints+2);     // 12,75
	cn::vector<int> second (myints+2,myints+6);  // 10,20,25,32

	cn::vector<int>::pointer first_start = &*first.begin();
	cn::vector<int>::pointer first_finish = &*first.end();
	cn::vector<int>::pointer first_end_of_storage = &*first.begin() + first.capacity();
	REQUIRE( first_start + 2 == first_finish);
	REQUIRE( first_finish == first_end_of_storage);

	cn::vector<int>::pointer second_start = &*second.begin();
	cn::vector<int>::pointer second_finish = &*second.end();
	cn::vector<int>::pointer second_end_of_storage = &*second.begin() + second.capacity();
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

TEST_CASE( "vector - non-member - swap", "[vector][non-member][swap]" )
{
	int myints[]={12,75,10,32,20,25};
	cn::vector<int> first (myints,myints+2);     // 12,75
	cn::vector<int> second (myints+2,myints+6);  // 10,20,25,32

	cn::vector<int>::pointer first_start = &*first.begin();
	cn::vector<int>::pointer first_finish = &*first.end();
	cn::vector<int>::pointer first_end_of_storage = &*first.begin() + first.capacity();
	REQUIRE( first_start + 2 == first_finish);
	REQUIRE( first_finish == first_end_of_storage);

	cn::vector<int>::pointer second_start = &*second.begin();
	cn::vector<int>::pointer second_finish = &*second.end();
	cn::vector<int>::pointer second_end_of_storage = &*second.begin() + second.capacity();
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
}
