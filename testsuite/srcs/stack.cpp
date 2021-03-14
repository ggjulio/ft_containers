#include "catch_amalgamated.hpp"

#include <stack>
#include <string>

TEMPLATE_TEST_CASE( "vectors can be sized and resized", "[vector][template][size][capacity]", int, std::string ) {

    std::stack<TestType> v( 5 );
    REQUIRE( v.() == 5 );
    REQUIRE( v.capacity() >= 5 );

    SECTION("resizing bigger changes size and capacity") {
        v.resize( 10 );

        REQUIRE( v.size() == 10 );
        REQUIRE( v.capacity() >= 10 );
    }
    SECTION("resizing smaller changes size but not capacity") {
        v.resize( 0 );

        REQUIRE( v.size() == 0 );
        REQUIRE( v.capacity() >= 5 );

        SECTION("We can use the 'swap trick' to reset the capacity") {
            std::vector<TestType> empty;
            empty.swap( v );

            REQUIRE( v.capacity() == 0 );
        }
    }
    SECTION("reserving smaller does not change size or capacity") {
        v.reserve( 0 );

        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 5 );
    }
}