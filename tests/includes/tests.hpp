#ifndef TESTS_HPP
#define TESTS_HPP

#include "catch.hpp"

namespace ft {}

#if !defined(NS_NAME)
 	#define NS_NAME ft
#endif

namespace cn = ::NS_NAME;

#include "utility.hpp" //the file containing pair definition

namespace NS_NAME
{
	template<class T1, class T2>
	std::ostream&	operator<<(std::ostream& os, const pair<T1, T2>& pair)
	{
		os << "pair<" << pair.first << ", " << pair.second << ">";
		return os;
	}
}


#endif /* TESTS_HPP */