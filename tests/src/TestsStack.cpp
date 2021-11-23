#include "tests.hpp"

#include "stack.hpp"

#include <stack>
#include <string>
#include <deque>
#include <type_traits>

TEMPLATE_TEST_CASE( "stack - construct",
	"[stack][constructors][leak]", int, IsLeaky )
{
	std::deque<TestType> stdDeque (3,100);
	cn::vector<TestType> cnvector (2,200);
	std::vector<TestType> stdVector (2,200);

	SECTION( "empty construtor" ) {
		cn::stack<TestType> first;
		cn::stack<TestType, ft::vector<TestType>> second;
		cn::stack<TestType, std::vector<TestType>> third;
		REQUIRE( first.size() == 0);
		REQUIRE( first.empty());
		REQUIRE( second.size() == 0);
		REQUIRE( second.empty());
		REQUIRE( third.size() == 0);
		REQUIRE( third.empty());
	}
	SECTION( "Copy of base container deque" ) {
		cn::stack<TestType, std::deque<TestType> > first (stdDeque);
		
		REQUIRE( first.size() == 3);
		REQUIRE( first.top() == 100);
		REQUIRE( !first.empty());
	}
	SECTION( "Copy of base container vector" ) {
		std::stack<TestType, std::vector<TestType> > first(stdVector);
		std::stack<TestType, cn::vector<TestType> > second(cnvector);

		REQUIRE( first.size() == 2);
		REQUIRE( first.top() == 200);
		REQUIRE( !first.empty());
		REQUIRE( second.size() == 2);
		REQUIRE( second.top() == 200);
		REQUIRE( !second.empty());
	}
}

TEMPLATE_TEST_CASE( "stack - pop",
	"[stack][pop][leak]", int, IsLeaky )
{
	std::deque<TestType> stdDeque (3,100);
	std::stack<TestType, std::deque<TestType> > s(stdDeque);

	REQUIRE( s.size() == 3);
	s.pop();
	REQUIRE( s.size() == 2);
	s.pop();
	REQUIRE( s.size() == 1);
	REQUIRE( !s.empty());
	s.pop();
	REQUIRE( s.size() == 0);
	REQUIRE( s.empty());


}

TEMPLATE_TEST_CASE( "stack - push",
	"[stack][push][top][leak]", int, IsLeaky )
{
	std::deque<TestType> stdDeque (3,100);
	std::stack<TestType, std::deque<TestType> > s(stdDeque);

	REQUIRE( s.size() == 3 );
	REQUIRE( s.top() == 100);
	s.push(42);
	REQUIRE( s.top() == 42);
	REQUIRE( s.size() == 4 );
	s.push(-42);
	REQUIRE( s.top() == -42);
	REQUIRE( s.size() == 5 );
}







// Old stuff below  -> dont have time for this shit...just doing the basic test above

typedef int				T;
typedef std::deque<T>   Container;

TEST_CASE( "Stack - member types", "[stack][member_type][to_do]" ) {

	SECTION( "value_type -  Should be the same type as the first template parameter (T)" ) {
		REQUIRE( std::is_same<cn::stack<T, Container>::value_type, T>::value );
	}
	// SECTION( "container_type - Should be the same type as the second template parameter (Container)" ) {
	//     REQUIRE( std::is_same<std::stack<T, Container>::container_type::value_type, Container >::value );
	// }
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
	// std::deque<T> deq = std::deque<T>();          // deque with 3 elements
	cn::stack<T, Container> s = cn::stack<T, Container>();
	

	SECTION( "Is empty" ) {
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