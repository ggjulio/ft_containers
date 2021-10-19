#include "tests.hpp"

#include "function.hpp"

#include <utility>

#include <typeinfo>
#include <string>
#include <vector>


TEST_CASE( "cn::_Identity",
	"[function][identity]" )
{
	typedef std::pair<short, int>	some_pair;
	// typedef std::vector<int>	vector_of_ints;


	typedef  ft::_Identity<int> 		ident_int;
	typedef  ft::_Identity<some_pair> 		ident_pair;
	// typedef  ft::_Identity<vector_of_ints> 		ident_vector;

	CHECK(		typeid(ident_int::argument_type).hash_code() == typeid(int).hash_code()  );
	CHECK(		typeid(ident_int::result_type).hash_code() == typeid(int).hash_code()  );
	REQUIRE(	typeid(ident_int::result_type).name() == typeid(int).name()  );

	CHECK(		typeid(ident_pair::argument_type).hash_code() == typeid(some_pair::first_type).hash_code()  );
	REQUIRE(	typeid(ident_pair::argument_type).name() == typeid(some_pair).name()  );
	CHECK( 		typeid(ident_pair::result_type).hash_code() == typeid(some_pair).hash_code()  );
	REQUIRE(	typeid(ident_pair::result_type).name() == typeid(some_pair).name()  );

	// CHECK( 		typeid(ident_vector).hash_code() == typeid(ident_vector).hash_code()  );
	// REQUIRE(	typeid(ident_vector::result_type).name() == typeid(ident_vector).name()  );
}