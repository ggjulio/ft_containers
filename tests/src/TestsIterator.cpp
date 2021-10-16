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


TEST_CASE( "cn::iterator_traits", "[iterator_traits]" ) {
	typedef cn::iterator_traits<int*> traitsIntPtr;
	CHECK( typeid(traitsIntPtr::iterator_category).name() ==typeid(std::random_access_iterator_tag).name());

	typedef cn::iterator_traits<const int*> traitsConstIntPtr;
	CHECK( typeid(traitsConstIntPtr::iterator_category).name() ==typeid(std::random_access_iterator_tag).name());

	// typedef cn::iterator_traits<std::())> traits;
//   CHECK( typeid(traitsInt::iterator_category).name() ==typeid(cn::  ).name());

}

TEST_CASE( "cn::reverse_iterator - basic loop pre increment", "[reverse_iterator][basic_loop][pre_increment]" )
{
	std::vector<int> vec = {1,2,3,4,5};
	typedef std::reverse_iterator<std::vector<int>::iterator> reverse_iter;

	reverse_iter it(vec.end());
	reverse_iter end(vec.begin());

	int n = 5;
	while (it != end)
	{
		CHECK(*it == n);
		++it;
		REQUIRE( n > 0);
		--n;
	}
	REQUIRE( *--it == 1);
}

TEST_CASE( "cn::reverse_iterator - basic loop post increment", "[reverse_iterator][basic_loop][post_increment]" )
{
	std::vector<int> vec = {1,2,3,4,5};
	typedef std::reverse_iterator<std::vector<int>::iterator> reverse_iter;

	reverse_iter it(vec.end());
	reverse_iter end(vec.begin());

	int n = 5;
	while (it != end)
	{
		CHECK(*it++ == n);
		REQUIRE( n > 0);
		--n;
	}
	it--;
	REQUIRE( *it == 1);
}


TEST_CASE( "cn::reverse_iterator", "[reverse_iterator]" ) {
	std::vector<int> vec = {1,2,3,4,5};

typedef std::reverse_iterator<std::vector<int>::iterator> reverse_iter;

	reverse_iter it(vec.end());
	reverse_iter end(vec.begin());

	CHECK( *it == 5 );
	CHECK( *++it == 4 );
	CHECK( *++it == 3 );
	CHECK( *++it == 2 );
	CHECK( *++it == 1 );
	CHECK( *--it == 2 );
	CHECK( *++it == 1 );
	CHECK( ++it == end );

	it = reverse_iter(vec.end());
	REQUIRE( *it == 5 );
	
	// while

	// CHECK(  );
}
