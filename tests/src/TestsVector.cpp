#include "tests.hpp"

#include <vector>
#include <string>
#include "vector.hpp"

TEST_CASE( "vector - construct", "[vector][constructors]" )
{
//   // constructors used in the same order as described above:
//   std::vector<int> first;                                // empty vector of ints
//   std::vector<int> second (4,100);                       // four ints with value 100
//   std::vector<int> third (second.begin(),second.end());  // iterating through second
//   std::vector<int> fourth (third);                       // a copy of third

//   // the iterator constructor can also be used to construct from arrays:
//   int myints[] = {16,2,77,29};
//   std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

//   std::cout << "The contents of fifth are:";
//   for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
//     std::cout << ' ' << *it;
//   std::cout << '\n';

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