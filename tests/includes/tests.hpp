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

// Just an int, but on the heap.
// This class allow to test whether objects are (constructed && destructed) or not.
// If not, then there will be nasty leaks everywhere, even segv if copy on uninitialised mem :)
class IsLeaky
{
	int* leakPtr;
public:
	IsLeaky() {
		leakPtr = new int(0);
	}
	IsLeaky(int n) {
		leakPtr = new int(n);
	}
	IsLeaky(const IsLeaky& other) {
		if (this == &other)
			return;
		leakPtr = new int(*other.leakPtr);
	}
	IsLeaky& operator=(const IsLeaky& other)
	{
		if (this != &other)
			*leakPtr = *other.leakPtr;
		return *this;
	}
	~IsLeaky() {
		delete leakPtr;
	}
	int& operator*() const { return *leakPtr; }
	int* operator->() const { return leakPtr; }

	operator int() const { return *leakPtr; }
	
	friend std::ostream&	operator<<(std::ostream& os, const IsLeaky& leak)
	{
		os << *leak.leakPtr;
		return os;
	}
};


#endif /* TESTS_HPP */