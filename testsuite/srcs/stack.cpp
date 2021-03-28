#include "catch_amalgamated.hpp"

#include <stack>
#include <string>
#include <deque>

#define NS_NAME std

#ifdef NS_NAME
    namespace cn = ::NS_NAME;
#else
    namespace cn = ft;
#endif

TEMPLATE_TEST_CASE( "stack", "[stack][template][size][capacity]", std::string ) {

    typedef int T;
    cn::stack<T> s = cn::stack<T>();

    SECTION( "Member types") {
        REQUIRE( std::is_same<std::stack<T>::value_type, T>::value );

    }
}