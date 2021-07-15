

#include <memory>
#include <vector>
#include "vector.hpp"
#include <iostream>


// pointer allocate (size_type n, allocator<void>::const_pointer hint=0);
namespace ft{


template<class T, T v>
struct integral_constant
{
	static constexpr T value = v;
	typedef T value_type;
	typedef integral_constant type;
	constexpr operator value_type() const noexcept { return value; }
	constexpr value_type operator()() const noexcept { return value; }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template <class T>	struct is_integral							: public false_type{};
template <>			struct is_integral<bool>					: public true_type {};
template <>			struct is_integral<char>					: public true_type {};
template <>			struct is_integral<char16_t>				: public true_type {};
template <>			struct is_integral<char32_t>				: public true_type {};
template <>			struct is_integral<wchar_t>					: public true_type {};
template <>			struct is_integral<signed char>				: public true_type {};
template <>			struct is_integral<short int>				: public true_type {};
template <>			struct is_integral<int>						: public true_type {};
template <>			struct is_integral<long int>				: public true_type {};
template <>			struct is_integral<long long int>			: public true_type {};
template <>			struct is_integral<unsigned char>			: public true_type {};
template <>			struct is_integral<unsigned short int>		: public true_type {};
template <>			struct is_integral<unsigned int>			: public true_type {};
template <>			struct is_integral<unsigned long int>		: public true_type {};
template <>			struct is_integral<unsigned long long int>	: public true_type {};

}

int main()
{
	// std::allocator<int> test;

	// test.allocate(4);
	// std::vector<int> v(4,100);

	// std::is_integral<int>

	// std::cout << v.capacity();
	std::cout << std::boolalpha;
	std::cout << "is_integral:" << std::endl;
	std::cout << "char: " 	<< std::is_integral<char>::value << std::endl;
	std::cout << "int: " 	<< std::is_integral<int>::value << std::endl;
	std::cout << "float: " 	<< std::is_integral<float>::value << std::endl;
 
	return 0;
}
