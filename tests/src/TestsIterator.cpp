#include "tests.hpp"

#include "iterator.hpp"

#include <iterator>
#include <typeinfo>

namespace NS_NAME
{
	// std::ostream&	operator<<(std::ostream& os, const cn::& tag)
	// {
	// 	os << ;
	// 	return os;
	// }
}


TEST_CASE( "cn::it", "[iterator]" ) {
	typedef cn::iterator_traits<int*> traitsIntPtr;
	CHECK( typeid(traitsIntPtr::iterator_category).name() ==typeid(cn::random_access_iterator_tag).name());

	typedef cn::iterator_traits<const int*> traitsConstIntPtr;
	CHECK( typeid(traitsConstIntPtr::iterator_category).name() ==typeid(cn::random_access_iterator_tag).name());

	// typedef cn::iterator_traits<std::())> traits;
//   CHECK( typeid(traitsInt::iterator_category).name() ==typeid(cn::  ).name());

}