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

// Simulate an int, but allocated
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

	friend bool operator==(const IsLeaky& x, const IsLeaky& y) { return *x.leakPtr == *y.leakPtr; }
	friend bool operator!=(const IsLeaky& x, const IsLeaky& y) { return *x.leakPtr != *y.leakPtr; }

	friend std::ostream&	operator<<(std::ostream& os, const IsLeaky& leak)
	{
		os << *leak.leakPtr;
		return os;
	}
};


#endif /* TESTS_HPP */