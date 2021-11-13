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

	}
	cn::vector<int> fourth (third);
	SECTION( "copy constructor" )
	{
		CHECK( fourth[0] == 100);
		CHECK( fourth[1] == 100);
		CHECK( fourth[2] == 100);
		CHECK( fourth[3] == 100);
		REQUIRE( fourth.size() == 4);
		REQUIRE( !fourth.empty());
	}
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
	}
}

TEST_CASE( "vector - operator - assignment ", "[vector][operator][assignment]" )
{
	cn::vector<int> first(3, 42);
	cn::vector<int> second(5, 43);

	REQUIRE(first.size() == 3);
	REQUIRE(second.size() == 5);

	second = first;
	REQUIRE(first.size() == 3);
	REQUIRE(second.size() == 3);
	REQUIRE(second[0] == 42);

	first = std::vector<int>();
	REQUIRE(first.size() == 0);
	REQUIRE(first.empty());
}

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
		REQUIRE(myvector.max_size() == 2305843009213693951);
	}
}







// TEST_CASE( "vectors can be sized and resized", "[vector][template][size()][capacity]" ) {

	// cn::vector<int> v( 5 );
	// REQUIRE( v.size() == 5 );
	// REQUIRE( v.capacity() >= 5 );

	// SECTION("resizing bigger changes size and capacity") {
	//     v.resize( 10 );

	//     REQUIRE( v.size() == 10 );
	//     REQUIRE( v.capacity() >= 10 );
	// }
	// SECTION("resizing smaller changes size but not capacity") {
	//     v.resize( 0 );

	//     REQUIRE( v.size() == 0 );
	//     REQUIRE( v.capacity() >= 5 );
	// }
	// SECTION("We can use the 'swap trick' to reset the capacity") {
	//     cn::vector<int> empty;
	//     empty.swap( v );

	//     REQUIRE( v.capacity() == 0 );
	// }
	// SECTION("reserving smaller does not change size or capacity") {
	//     v.reserve( 0 );
		
	//     REQUIRE( v.size() == 5 );
	//     REQUIRE( v.capacity() >= 5 );
	// }
// }