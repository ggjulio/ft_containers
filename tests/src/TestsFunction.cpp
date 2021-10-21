#include "tests.hpp"

#include "function.hpp"

#include <utility>

#include <typeinfo>
#include <string>
#include <vector>

TEMPLATE_TEST_CASE( "cn::_Identity",
	"[function][identity]", int, const int, std::string)
{
	typedef typename ft::_Identity<TestType> 			ident;

	CHECK(	typeid(typename ident::argument_type).hash_code() == typeid(TestType).hash_code()  );
	CHECK(	typeid(typename ident::result_type).hash_code() == typeid(TestType).hash_code()  );
	CHECK(	typeid(typename ident::result_type).name() == typeid(TestType).name()  );
}

TEST_CASE( "cn::_Select1st",
	"[function][select1st]")
{
	typedef std::pair<short, long>		some_pair;
	typedef ft::_Select1st<some_pair> 	ident_pair;

	CHECK(	typeid(typename ident_pair::argument_type).hash_code() == typeid(some_pair).hash_code()  );

	CHECK(	typeid(typename ident_pair::result_type).hash_code() == typeid(short).hash_code()  );
	CHECK(	typeid(typename ident_pair::result_type).name() == typeid(short).name()  );

}
