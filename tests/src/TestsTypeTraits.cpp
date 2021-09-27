#include "catch_amalgamated.hpp"

#include <type_traits>

#include <cstdint>
#include "type_traits.hpp"

#ifdef NS_NAME
    namespace cn = ::NS_NAME;
#else
    namespace cn = ft;
#endif

TEST_CASE( "cn::is_integral", "[type_traits][is_integral]" ) {
	REQUIRE( cn::is_integral<bool>::value );
	REQUIRE( cn::is_integral<char>::value );
		// char16_t and char32_t only since c++11...
		// REQUIRE( cn::is_integral<char16_t>::value );
		// REQUIRE( cn::is_integral<char32_t>::value );
	REQUIRE( cn::is_integral<wchar_t>::value );

	REQUIRE( cn::is_integral<signed char>::value );
	REQUIRE( cn::is_integral<short int>::value );
	REQUIRE( cn::is_integral<int>::value );
	REQUIRE( cn::is_integral<long int>::value );
	REQUIRE( cn::is_integral<long long int>::value );

	REQUIRE( cn::is_integral<unsigned char>::value );
	REQUIRE( cn::is_integral<unsigned short int>::value );
	REQUIRE( cn::is_integral<unsigned int>::value );
	REQUIRE( cn::is_integral<unsigned long int >::value );
	REQUIRE( cn::is_integral<unsigned long long int>::value );


	// stdint
	REQUIRE( cn::is_integral<intmax_t>::value );
	REQUIRE( cn::is_integral<int8_t>::value );
	REQUIRE( cn::is_integral<int16_t>::value );
	REQUIRE( cn::is_integral<int32_t>::value );
	REQUIRE( cn::is_integral<int64_t>::value );
	REQUIRE( cn::is_integral<int_least8_t>::value );
	REQUIRE( cn::is_integral<int_least16_t>::value );
	REQUIRE( cn::is_integral<int_least32_t>::value );
	REQUIRE( cn::is_integral<int_least64_t>::value );
	REQUIRE( cn::is_integral<int_fast8_t>::value );
	REQUIRE( cn::is_integral<int_fast16_t>::value );
	REQUIRE( cn::is_integral<int_fast32_t>::value );
	REQUIRE( cn::is_integral<int_fast64_t>::value );
	REQUIRE( cn::is_integral<intptr_t>::value );

	REQUIRE( cn::is_integral<uintmax_t>::value );
	REQUIRE( cn::is_integral<uint8_t>::value );
	REQUIRE( cn::is_integral<uint16_t>::value );
	REQUIRE( cn::is_integral<uint32_t>::value );
	REQUIRE( cn::is_integral<uint64_t>::value );
	REQUIRE( cn::is_integral<uint_least8_t>::value );
	REQUIRE( cn::is_integral<uint_least16_t>::value );
	REQUIRE( cn::is_integral<uint_least32_t>::value );
	REQUIRE( cn::is_integral<uint_least64_t>::value );
	REQUIRE( cn::is_integral<uint_fast8_t>::value );
	REQUIRE( cn::is_integral<uint_fast16_t>::value );
	REQUIRE( cn::is_integral<uint_fast32_t>::value );
	REQUIRE( cn::is_integral<uint_fast64_t>::value );
	REQUIRE( cn::is_integral<uintptr_t>::value );
	
	REQUIRE( cn::is_integral<const int>::value );

	REQUIRE( !cn::is_integral<float>::value );


}