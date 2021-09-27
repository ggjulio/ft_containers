#include "catch_amalgamated.hpp"

#include <type_traits>

#include <cstdint>
#include <string>
#include "type_traits.hpp"

#ifdef NS_NAME
    namespace cn = ::NS_NAME;
#else
    namespace cn = ft;
#endif

TEST_CASE( "cn::is_integral", "[type_traits][is_integral]" ) {
	/// non const
	CHECK( cn::is_integral<bool>::value );
	CHECK( cn::is_integral<char>::value );
	CHECK( cn::is_integral<wchar_t>::value );
	CHECK( cn::is_integral<short int>::value );
	CHECK( cn::is_integral<signed char>::value );
	CHECK( cn::is_integral<long int>::value );
	CHECK( cn::is_integral<int>::value );
	CHECK( cn::is_integral<unsigned char>::value );
	CHECK( cn::is_integral<long long int>::value );
	CHECK( cn::is_integral<unsigned int>::value );
	CHECK( cn::is_integral<unsigned short int>::value );
	CHECK( cn::is_integral<unsigned long long int>::value );
	CHECK( cn::is_integral<unsigned long int >::value );

	// const
	CHECK( cn::is_integral<const char>::value );
	CHECK( cn::is_integral<const bool>::value );
	CHECK( cn::is_integral<const wchar_t>::value );
	CHECK( cn::is_integral<const signed char>::value );
	CHECK( cn::is_integral<const short int>::value );
	CHECK( cn::is_integral<const int>::value );
	CHECK( cn::is_integral<const long int>::value );
	CHECK( cn::is_integral<const long long int>::value );
	CHECK( cn::is_integral<const unsigned char>::value );
	CHECK( cn::is_integral<const unsigned short int>::value );
	CHECK( cn::is_integral<const unsigned int>::value );
	CHECK( cn::is_integral<const unsigned long int >::value );
	CHECK( cn::is_integral<const unsigned long long int>::value );


	// stdint
	CHECK( cn::is_integral<intmax_t>::value );
	CHECK( cn::is_integral<int8_t>::value );
	CHECK( cn::is_integral<int16_t>::value );
	CHECK( cn::is_integral<int32_t>::value );
	CHECK( cn::is_integral<int64_t>::value );
	CHECK( cn::is_integral<int_least8_t>::value );
	CHECK( cn::is_integral<int_least16_t>::value );
	CHECK( cn::is_integral<int_least32_t>::value );
	CHECK( cn::is_integral<int_least64_t>::value );
	CHECK( cn::is_integral<int_fast8_t>::value );
	CHECK( cn::is_integral<int_fast16_t>::value );
	CHECK( cn::is_integral<int_fast32_t>::value );
	CHECK( cn::is_integral<int_fast64_t>::value );
	CHECK( cn::is_integral<intptr_t>::value );

	CHECK( cn::is_integral<uintmax_t>::value );
	CHECK( cn::is_integral<uint8_t>::value );
	CHECK( cn::is_integral<uint16_t>::value );
	CHECK( cn::is_integral<uint32_t>::value );
	CHECK( cn::is_integral<uint64_t>::value );
	CHECK( cn::is_integral<uint_least8_t>::value );
	CHECK( cn::is_integral<uint_least16_t>::value );
	CHECK( cn::is_integral<uint_least32_t>::value );
	CHECK( cn::is_integral<uint_least64_t>::value );
	CHECK( cn::is_integral<uint_fast8_t>::value );
	CHECK( cn::is_integral<uint_fast16_t>::value );
	CHECK( cn::is_integral<uint_fast32_t>::value );
	CHECK( cn::is_integral<uint_fast64_t>::value );
	CHECK( cn::is_integral<uintptr_t>::value );
	
	CHECK( cn::is_integral<const int>::value );

	// everything false
	CHECK( !cn::is_integral<float>::value );
	CHECK( !cn::is_integral<const float>::value );
	CHECK( !cn::is_integral<std::string>::value );
	CHECK( !cn::is_integral<const std::string>::value );
}