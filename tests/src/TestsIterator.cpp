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
// namespace NS_NAME
// {
// 	template<class T1, class T2>
// 	std::ostream&	operator<<(std::ostream& os, const reverse_iter& rev)
// 	{
// 		os << rev.base();
// 		return os;
// 	}
// }

TEST_CASE( "cn::reverse_iterator", "[reverse_iterator]" ) {
	std::vector<int> vec = {1,2,4,5,6};

typedef std::reverse_iterator<std::vector<int>::iterator> reverse_iter;

	reverse_iter it(vec.end());
	reverse_iter end(vec.begin());

	CHECK( *it == 6 );
	CHECK( *++it == 5 );
	CHECK( *++it == 4 );
	CHECK( *++it == 2 );
	CHECK( *++it == 1 );
	CHECK( *--it == 2 );
	CHECK( *++it == 1 );
	// CHECK( it.base() == end.base() );

	it = reverse_iter(vec.end());
	REQUIRE( *it == 6 );
	
	// while

	// CHECK(  );
}
