#include "tests.hpp"

#include "iterator.hpp"

#include <iterator>
#include <vector>
#include <typeinfo>

namespace NS_NAME
{
	// std::ostream&	operator<<(std::ostream& os, const cn::& tag)
	// {
	// 	os << ;
	// 	return os;
	// }
}

/////////////////////
// iterator traits //
/////////////////////

TEST_CASE( "cn::iterator_traits", "[iterator_traits]" ) {
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
	"[reverse_iterator][basic_loop][pre][increment][pre_increment]" )
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
	"[reverse_iterator][basic_loop][post][increment][post_increment]" )
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
	"[reverse_iterator][basic_loop][pre][decrement][pre_decrement]" )
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
	"[reverse_iterator][basic_loop][post][decrement][post_decrement]" )
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