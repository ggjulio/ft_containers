#include "tests.hpp"

#include "iterator.hpp"

#include <iterator>
#include <vector>
#include <typeinfo>

/////////////////////
// iterator traits //
/////////////////////

TEST_CASE( "cn::iterator_traits", "[iterator][iterator_traits]" )
{
	typedef cn::iterator_traits<int*> traitsIntPtr;
	CHECK( typeid(traitsIntPtr::iterator_category).name() ==typeid(std::random_access_iterator_tag).name());

	typedef cn::iterator_traits<const int*> traitsConstIntPtr;
	CHECK( typeid(traitsConstIntPtr::iterator_category).name() ==typeid(std::random_access_iterator_tag).name());

	// typedef cn::iterator_traits<std::())> traits;
//   CHECK( typeid(traitsInt::iterator_category).name() ==typeid(cn::  ).name());

}

//////////////////////
// reverse iterator //
//////////////////////

typedef cn::reverse_iterator<std::vector<int>::iterator> reverse_it;

TEST_CASE( "cn::reverse_iterator - basic loop pre increment",
	"[iterator][reverse_iterator][basic_loop][pre][increment][pre_increment]" )
{
	std::vector<int> vec = {1,2,3,4,5};

	reverse_it it(vec.end());
	reverse_it end(vec.begin());

	int n = 5;
	while (it != end && n > -10)
	{
		CHECK(*it == n--);
		++it;
	}
	REQUIRE( n == 0);
	REQUIRE( *--it == 1);
}

TEST_CASE( "cn::reverse_iterator - basic loop post increment",
	"[iterator][reverse_iterator][basic_loop][post][increment][post_increment]" )
{
	std::vector<int> vec = {1,2,3,4,5};

	reverse_it it(vec.end());
	reverse_it end(vec.begin());

	int n = 5;
	while (it != end && n > -10)
	{
		CHECK(*it++ == n--);
	}
	REQUIRE( n == 0);
	it--;
	REQUIRE( *it == 1);
}

TEST_CASE( "cn::reverse_iterator - basic loop pre decrement",
	"[iterator][reverse_iterator][basic_loop][pre][decrement][pre_decrement]" )
{
	std::vector<int> vec = {1,2,3,4,5};

	reverse_it it(vec.begin());
	reverse_it end(vec.end());

	int n = 0;
	while (it != end && ++n < 10)
	{
		CHECK(*--it == n);
	}
	CHECK(n == 5);
	CHECK( *++it == 4);
}

TEST_CASE( "cn::reverse_iterator - basic loop post decrement",
	"[iterator][reverse_iterator][basic_loop][post][decrement][post_decrement]" )
{
	std::vector<int> vec = {1,2,3,4,5};

	reverse_it it(vec.begin());
	reverse_it end(vec.end());

	int n = 0;
	while (it != end && ++n < 10)
	{
		it--;
		CHECK(*it == n);
	}
	CHECK(n == 5);
	it++;
	CHECK( *it == 4);
}

TEST_CASE( "cn::reverse_iterator - should return the base iterator",
	"[iterator][reverse_iterator][base]" )
{
	std::vector<int> vec = {1,2,3,4,5};
	
	reverse_it it(vec.begin());

	REQUIRE( it.base() == vec.begin() );
}

TEST_CASE( "cn::reverse_iterator - other operator",
	"[iterator][reverse_iterator][other][operator]" )
{
	std::vector<int> vec = {1,2,3,4,5};

	reverse_it it(vec.begin());
	reverse_it it3(vec.begin() + 3);
	reverse_it it5(vec.begin() + 5);

	// member operator-
	CHECK( *(it - 3) == 3);
	REQUIRE( &*(it - 3) == &vec[2]);

	// member operator+
	CHECK( *(it3 + 2) == 1);
	REQUIRE( &*(it3 + 2) == &vec[0]);

	// non member operator-
	CHECK( (it5 - it) == -5);
	REQUIRE( (it - it5) == 5);

	// non member operator+
	CHECK( *(0 + it3) == vec[2]);
	CHECK( &*(0 + it3) == &vec[2]);
	CHECK( *(1 + it3) == vec[1]);
	REQUIRE( &*(1 + it3) == &vec[1]);

	// member operator[]
	CHECK(it3[0] == vec[2]);
	REQUIRE(&it3[0] == &vec[2]);

	// member operator->
	CHECK( it3.operator->() == &vec[2] );
	REQUIRE( it3.operator->() == &it3.operator*() );

	// members operators -= and +=
	{
		reverse_it it_test(it3);
		REQUIRE(it_test == it3);

		// member operator-=
		it_test -= 2;
		CHECK(*it_test == *it5);
		REQUIRE(&*it_test == &*it5);

		// member operator+=
		it_test += 2;
		CHECK(*it_test == *it3);
		REQUIRE(&*it_test == &*it3);
	}
}

TEST_CASE( "cn::reverse_iterator - comparison",
	"[iterator][reverse_iterator][operator][comparison]" )
{
	std::vector<int> vec = {1,2,3,4,5};

	reverse_it it(vec.begin());
	reverse_it it3(vec.begin() + 3);
	reverse_it it3_bis(vec.begin() + 3);
	reverse_it it5(vec.begin() + 5);

	CHECK( it > it3 );
	CHECK( it3 <= it3_bis );
	CHECK( it3 == it3_bis );
	CHECK( it3 >= it3_bis );
	CHECK( it3 > it5 );

}

TEST_CASE( "cn::reverse_iterator - const iter are comparable with iter",
	"[iterator][reverse_iterator][operator][comparison]" )
{
	std::vector<int> vec = {1,2,3,4,5};

	cn::reverse_iterator<std::vector<int>::const_iterator>	const_it(vec.begin());
	cn::reverse_iterator<std::vector<int>::iterator> 				it(vec.begin());
	cn::reverse_iterator<std::vector<int>::iterator> 				it2(vec.begin()+1);

	REQUIRE( const_it == it );
	REQUIRE( const_it <= it );
	REQUIRE( const_it >= it );
	REQUIRE( !(const_it > it) );
	REQUIRE( !(const_it < it) );

	REQUIRE( const_it != it2 );
	REQUIRE( const_it > it2 );
	REQUIRE( const_it >= it2 );
	REQUIRE( !(const_it <= it2) );
	REQUIRE( !(const_it < it2) );
}