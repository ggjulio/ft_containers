#include "tests.hpp"

#include "function.hpp"

#include <utility>

#include <typeinfo>
#include <string>
#include <vector>

TEMPLATE_TEST_CASE( "cn::_Identity",
	"[function][identity]", std::string, int, const int)
{
	typedef typename TestType type_test;
	typedef	typename const TestType  const_type_test;

	typedef typename ft::_Identity<type_test> 			ident;
	typedef typename ft::_Identity<const type_test> 	ident_const;

	CHECK(		typeid(ident::argument_type).hash_code() == typeid(type_test).hash_code()  );
	CHECK(		typeid(ident::result_type).hash_code() == typeid(type_test).hash_code()  );
	REQUIRE(	typeid(ident::result_type).name() == typeid(type_test).name()  );

	CHECK(		typeid(ident_const::argument_type).hash_code() == typeid(const_type_test).hash_code()  );
	CHECK(		typeid(ident_const::result_type).hash_code() == typeid(const_type_test).hash_code()  );
	REQUIRE(	typeid(ident_const::result_type).name() == typeid(const_type_test).name()  );


}

TEST_CASE( "cn::_Select1st",
	"[function][select1st]")
{
	typedef std::pair<short, long>		some_pair;
	typedef ft::_Select1st<some_pair> 	ident;

	ident t;
	(void)t;

}
