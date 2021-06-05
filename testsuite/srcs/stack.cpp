#include "catch_amalgamated.hpp"

#include <stack>
#include <string>
#include <deque>
#include <type_traits>

#define NS_NAME std

#ifdef NS_NAME
    namespace cn = ::NS_NAME;
#else
    namespace cn = ft;
#endif

typedef int             T;
typedef std::deque<T>   Container;

TEST_CASE( "Stack - member types", "[stack][member_type][to_do]" ) {

    SECTION( "value_type -  Should be the same type as the first template parameter (T)" ) {
        REQUIRE( std::is_same<cn::stack<T, Container>::value_type, T>::value );
    }
    SECTION( "container_type - Should be the same type as the second template parameter (Container)" ) {
        REQUIRE( std::is_same<std::stack<T, Container>::container_type::value_type, Container >::value );
    }
    SECTION( "size_type - Should be defined using member type 'size_type' of the underlying container" ) {
        REQUIRE( sizeof(cn::stack<T, Container>::size_type) == sizeof(cn::stack<T, Container>::container_type::size_type) );
        // this works ? probably not...
        REQUIRE( std::is_same<cn::stack<T, Container>::size_type, cn::stack<T, Container>::container_type::size_type >::value);
    }
    SECTION( "has all member types ??" ) {
        // must test if others member types are properly declared
        // (value_type, container_type, size_type)
        REQUIRE( std::is_object<std::stack<T>::container_type::value_type >::value );
        // REQUIRE( std::is_member_object_pointer<std::stack<T>::container_type >::value );
    }
    SECTION( "Has every member functions" ) {
        REQUIRE( std::is_member_function_pointer< decltype( &std::stack<T>::empty ) >::value);
    }
}
TEST_CASE( "Stack - Constructors", "[stack][member_function][constructor][to_do]" ) {

}

TEST_CASE( "Stack - empty()", "[stack][member_function][empty]" ) {
	std::deque<T> deq = std::deque<T>();          // deque with 3 elements
    

    SECTION( "Is empty" ) {
        cn::stack<T, Container> s = cn::stack<T, Container>();
        REQUIRE( s.empty() );
    }
    SECTION( "Is not empty" ) {
        s.push(42);
        REQUIRE( !s.empty() );
    }
    SECTION( "Is empty after a loop." ) {
        int actual = 0;
        int expected = 10;

        for (int i=1;i<=expected;i++) s.push(42);

        while (!s.empty())
        {
            s.pop();
            actual++;
        }
        REQUIRE( actual == expected );
    }
}

// TEST_CASE( "Stack - size()", "[stack][member_function][size]" ) {

//     cn::stack<T, Container> s = cn::stack<T, Container>();

//     SECTION( "size = 0" ) {
//         REQUIRE( s.empty() );
//     }
//     SECTION( "size" ) {
//         s.push(42);
//         REQUIRE( !s.empty() );
//     }
//     SECTION( "Is not" ) {
//         int actual = 0;
//         int expected = 10;

//         for (int i=1;i<=expected;i++) s.push(42);

//         while (!s.empty())
//         {
//             s.pop();
//             actual++;
//         }
//         REQUIRE( actual == expected );
//     }
// }

// TEST_CASE( "Stack - top()", "[stack][member_function][top]" ) {
//     cn::stack<T, Container> s = cn::stack<T, Container>();


// }