#include "tests.hpp"

#include <vector>
#include <string>
#include "vector.hpp"

TEST_CASE( "vector - construct", "[vector][constructors]" )
{
	SECTION( "empty construtor" ) {
		cn::vector<int> first;
		REQUIRE( first.empty());
		REQUIRE( first.size() == 0);
	}
	cn::vector<int> second (4,100);
	SECTION( "fill constructor" )
	{
		REQUIRE( !second.empty());
		REQUIRE( second.size() == 4);
		REQUIRE( second[0] == 100);
		REQUIRE( second[1] == 100);
		REQUIRE( second[2] == 100);
		REQUIRE( second[3] == 100);
	}
	cn::vector<int> third (second.begin(),second.end());
	SECTION( "range constructor" )
	{
		REQUIRE( !third.empty());
		REQUIRE( third.size() == 4);
		REQUIRE( third[0] == 100);
		REQUIRE( third[1] == 100);
		REQUIRE( third[2] == 100);
		REQUIRE( third[3] == 100);


	}
	cn::vector<int> fourth (third);
	SECTION( "copy constructor" )
	{
		REQUIRE( !fourth.empty());
		REQUIRE( fourth.size() == 4);
		REQUIRE( fourth[0] == 100);
		REQUIRE( fourth[1] == 100);
		REQUIRE( fourth[2] == 100);
		REQUIRE( fourth[3] == 100);
	}
	SECTION( "the iterator constructor can also be used to construct from arrays" )
	{
		int myints[] = {16,2,77,29, 42};
		cn::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

		REQUIRE( !fifth.empty());
		REQUIRE( fifth.size() == 5);
		REQUIRE( fifth[0] == 16);
		REQUIRE( fifth[1] == 2);
		REQUIRE( fifth[2] == 77);
		REQUIRE( fifth[3] == 29);
		REQUIRE( fifth[4] == 42);
	}
/*

	// constructors used in the same order as described above:
	std::vector<int> first;                                // empty vector of ints
	std::vector<int> second (4,100);                       // four ints with value 100
	std::vector<int> third (second.begin(),second.end());  // iterating through second
	std::vector<int> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of fifth are:";
	for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
*/
}

// TEST_CASE( "vectors can be sized and resized", "[vector][template][size()][capacity]" ) {

	// cn::vector<int> v( 5 );
	// REQUIRE( v.size() == 5 );
	// REQUIRE( v.capacity() >= 5 );

	// SECTION("resizing bigger changes size and capacity") {
	//     v.resize( 10 );

	//     REQUIRE( v.size() == 10 );
	//     REQUIRE( v.capacity() >= 10 );
	// }
	// SECTION("resizing smaller changes size but not capacity") {
	//     v.resize( 0 );

	//     REQUIRE( v.size() == 0 );
	//     REQUIRE( v.capacity() >= 5 );
	// }
	// SECTION("We can use the 'swap trick' to reset the capacity") {
	//     cn::vector<int> empty;
	//     empty.swap( v );

	//     REQUIRE( v.capacity() == 0 );
	// }
	// SECTION("reserving smaller does not change size or capacity") {
	//     v.reserve( 0 );
		
	//     REQUIRE( v.size() == 5 );
	//     REQUIRE( v.capacity() >= 5 );
	// }
// }