#include "tests.hpp"

#include "iterator.hpp"

#include <iterator>
#include <typeinfo>

namespace NS_NAME
{
	template<class T1, class T2>
	std::ostream&	operator<<(std::ostream& os, const pair<T1, T2>& pair)
	{
		os << "pair<" << pair.first << ", " << pair.second << ">";
		return os;
	}
}


TEST_CASE( "cn::it", "[iterator]" ) {
  typedef std::iterator_traits<int*> traits;
  CHECK( typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag));

}