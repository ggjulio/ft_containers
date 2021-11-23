#include "tests.hpp"

#include "map.hpp"
#include <map>

bool fncomp_map (int lhs, int rhs) {return lhs>rhs;}

struct classcomp_map {
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs>rhs;}
};

TEMPLATE_TEST_CASE( "map - construct",
	"[map][constructors][leak]", int, IsLeaky )
{
    cn::map<char,TestType> first;
	SECTION( "empty construtor" ) {
		REQUIRE(first.empty());
		REQUIRE(first.size() == 0);
	}
    first['a']=10;
    first['b']=20;
    first['c']=30;
    first['d']=40;
    first['e']=50;
    REQUIRE(first.size() == 5);

	cn::map<char,TestType> second (first.begin(), first.end());
	SECTION( "range construtor" ) {
		REQUIRE(!second.empty());
		REQUIRE(second.size() == 5);
	}
	SECTION( "copy construtor" ) {
		cn::map<char,TestType> third (second);
		REQUIRE(!third.empty());
		REQUIRE(third.size() == 5);

		SECTION( "A deep_copy/clone must be made" ) {
			third.erase(--third.end());
			REQUIRE(third.size() == 4);
			REQUIRE(third.find('e') == third.end());
			REQUIRE(second.size() == 5);
			REQUIRE(second.find('e')->second == 50);
		}
	}
	SECTION( "iterator construtor" ) {
		cn::map<char,TestType> fourth (second.begin(), second.end());
		REQUIRE(!fourth.empty());
		REQUIRE(fourth.size() == 5);
	}
	SECTION( "class as Compare" ) {
		cn::map<char,TestType,classcomp_map> fifth;
		fifth.insert(cn::pair('a', 10));
		fifth.insert(cn::pair('b', 20));
		REQUIRE(fifth.begin()->second == 20);
		REQUIRE((--fifth.end())->second == 10);
		REQUIRE(fifth.find('b')->second == 20);
	}
	SECTION( "function ptr as Compare" ) {
		bool(*fn_pt)(int,int) = fncomp_map;
		cn::map<char,TestType,bool(*)(int,int)> sixth (fn_pt);

		sixth.insert(cn::pair('a', 10));
		sixth.insert(cn::pair('b', 20));
		REQUIRE(sixth.begin()->second == 20);
		REQUIRE((--sixth.end())->second == 10);
		REQUIRE(sixth.find('b')->second == 20);
	}
}

TEMPLATE_TEST_CASE( "map - operator - assignment ",
	"[map][operator][assignment][leak]", int, IsLeaky )
{
	cn::map<char,TestType> first;
  	cn::map<char,TestType> second;
	
	first['x']=10;
	first['y']=20;
	first['z']=30;

	REQUIRE(!first.empty());
	REQUIRE(first.size() == 3);
	REQUIRE(second.empty());
	REQUIRE(second.size() == 0);

	second = first;
	REQUIRE(!second.empty());
	REQUIRE(second.size() == 3);
	
	SECTION( "A deep_copy/clone must be made" ) {
		second.erase(second.begin());
		REQUIRE(second.size() == 2);
		REQUIRE(second.find('x') == second.end());
		REQUIRE(first.size() == 3);
		REQUIRE(first.find('x')->second == 10);
	}
	SECTION( "Must have no leaks when running w ur fav leak detect prog" ) {
		first = cn::map<char,TestType>();
	}
}

TEMPLATE_TEST_CASE( "map - iterator ",
	"[map][iterator][leak]", int, IsLeaky )
{
	cn::map<char, TestType> first;
	SECTION( "empty container should have begin() == end()" )
	{
		REQUIRE( first.begin() == first.end() );
	}
	first.insert(cn::pair('a', 10));
	SECTION( "container with one element should have consistant boundary" )
	{
		REQUIRE( ++first.begin() == first.end() );
		REQUIRE( first.begin() == --first.end() );
		REQUIRE( first.begin().operator*().second == 10 );
		REQUIRE( first.begin().operator->() == &*first.begin() );
	}
	first.insert(cn::pair('b', 20));
	first.insert(cn::pair('c', 30));
	SECTION( "container with three elements should loop properly" )
	{
		auto it = first.begin();
		int i = 0;
		while (it != first.end())
		{
			i += 10;
			REQUIRE(it->second == i);
			++it;
		}
		REQUIRE(i == 30);
	}
	SECTION( "container with three elements should loop properly in reverse" )
	{
		auto it = first.end();
		int i = 40;
		while (--it != first.begin())
		{
			i -= 10;
			REQUIRE(it->second == i);
		}
		REQUIRE(it->second == 10);
	}
}

TEMPLATE_TEST_CASE( "map - reverse iterator ",
	"[map][reverse_iterator][leak]", int, IsLeaky )
{
	cn::map<char,TestType> mymap;
	SECTION( "empty container should have begin() == end()" )
	{
		REQUIRE( mymap.rbegin() == mymap.rend() );
	}
	mymap.insert(cn::pair('a', 10));
	SECTION( "container with one element should have consistant boundary" )
	{
		REQUIRE( ++mymap.rbegin() == mymap.rend() );
		REQUIRE( mymap.rbegin() == --mymap.rend() );
		REQUIRE( mymap.rbegin().operator*().second == 10 );
		REQUIRE( mymap.rbegin().operator->() == &*mymap.rbegin() );
	}
	mymap.insert(cn::pair('b', 20));
	mymap.insert(cn::pair('c', 30));
	SECTION( "container with three elements should loop properly" )
	{
		auto it = mymap.rbegin();
		int i = 40;
		while (it != mymap.rend())
		{
			i -= 10;
			REQUIRE(it->second == i);
			++it;
		}
		REQUIRE(i == 10);
	}
	SECTION( "container with three elements should loop properly in reverse" )
	{
		auto it = mymap.rend();
		int i = 0;
		while (--it != mymap.rbegin())
		{
			i += 10;
			REQUIRE(it->second == i);
		}
		REQUIRE(it->second == 30);
	}
}

TEMPLATE_TEST_CASE( "map - capacity ",
	"[map][capacity][leak]", int, IsLeaky )
{
	cn::map<char, TestType> mine;
	std::map<char, TestType> std_map;

	SECTION( "empty container should be empty (insightful)" )
	{
		REQUIRE(mine.empty());
		REQUIRE(mine.size() == 0);
	}
	mine.insert(cn::pair('a', 10));
	SECTION( "container with one element should be of size one (and not empty, of course)" )
	{
		REQUIRE(!mine.empty());
		REQUIRE(mine.size() == 1);
	}
	mine.erase(mine.begin());
	SECTION( "delete the single element, should become an empty container again." )
	{
		REQUIRE(mine.size() == 0);
		REQUIRE(mine.empty());
	}
	SECTION( "max_size(), May not be equal to the std because depend on the underlying implementation of the node. (also OS dependant linux_side != macos_size)" )
	{
		CHECK_NOFAIL(std_map.max_size() == mine.max_size());
	}
}

TEST_CASE( "map - Element access - operator[] (subscript) ", "[map][element_access][operator][subscript]" )
{
	cn::map<char,std::string> mymap;

	mymap['a'] = "an element";
	REQUIRE( mymap.size() == 1);
	REQUIRE( mymap.find('a')->second == "an element");

	SECTION( "Should be able to override a value" )
	{
		mymap['a'] = "I changed my mind";
		REQUIRE( mymap.size() == 1);
		REQUIRE( mymap.find('a')->second == "I changed my mind");

	}
	mymap['b'] = "another element";
	REQUIRE( mymap.size() == 2);
	REQUIRE( mymap.find('b')->second == "another element");


	mymap['c'] = mymap['b'];
	REQUIRE( mymap.size() == 3);
	REQUIRE( mymap.find('c')->second == "another element");
	REQUIRE( mymap.find('b')->second == "another element");
}

TEMPLATE_TEST_CASE( "map - Modifiers ",
	"[map][modifier][insert][leak]", int, IsLeaky )
{
	cn::map<char,TestType> mymap;
	typename cn::map<char,TestType>::iterator it_res;
	cn::pair< typename cn::map<char,TestType>::iterator,bool> ret;
	
	ret = mymap.insert(cn::pair('c', 42));
	SECTION( "Insert single value" )
	{
		REQUIRE(ret.second == true);
		REQUIRE((*ret.first).first == 'c');
		REQUIRE((*ret.first).second == 42);
		REQUIRE(mymap.size() == 1);
	}
	ret = mymap.insert(cn::pair('c', -42000));
	SECTION( "Already inserted value should not be inserted" )
	{
		REQUIRE(ret.second == false);
		REQUIRE(ret.first->first == 'c');
		REQUIRE(ret.first->second == 42);
		REQUIRE(mymap.size() == 1);
	}
	it_res = mymap.insert(ret.first, cn::pair('d', 43));
	SECTION( "Insert with hint" )
	{
		REQUIRE(it_res->first == 'd');
		REQUIRE(it_res->second == 43);
		REQUIRE(mymap.size() == 2);
	}
	it_res = mymap.insert(ret.first, cn::pair('d', -43000));
	SECTION( "Already inserted value even with hint should not be inserted" )
	{
		REQUIRE(it_res->first == 'd');
		REQUIRE(it_res->second == 43);
		REQUIRE(mymap.size() == 2);
	}

	cn::pair<char,TestType> myints[]= {
		cn::pair('a',40),
		cn::pair('b',41),
		cn::pair('c',42),
		cn::pair('d',43)};
	mymap.insert(myints, myints+4);
	SECTION( "Insert range, with some values already inserted should not be inserted twice")
	{
		REQUIRE(mymap.size() == 4);
		int i = 39;
		char c = 'a' - 1;
		auto it = mymap.begin();
		while (it != mymap.end())
		{
			REQUIRE(it->first == ++c);
			REQUIRE((it++)->second == ++i);
		}
		REQUIRE(c == 'd');
		REQUIRE(i == 43);
	}
}


TEMPLATE_TEST_CASE( "map - Modifiers - erase ",
	"[map][modifier][erase][leak]", int, IsLeaky )
{
	cn::map<char,TestType> mymap;

	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	mymap['d']=40;
	mymap['e']=50;
	mymap['f']=60;
	mymap['g']=70;
	mymap['h']=80;
	mymap['i']=90;
	REQUIRE(mymap.size() == 9);
	
	mymap.erase (++mymap.begin());
	SECTION( "erase 'b' by iterator" )
	{
		REQUIRE((++mymap.begin())->first == 'c');
		REQUIRE((++mymap.begin())->second == 30);
		REQUIRE(mymap.size() == 8);
	}
	mymap.erase('c');
	SECTION( "erase 'c' by value" )
	{
		REQUIRE((++mymap.begin())->first == 'd');
		REQUIRE(mymap.size() == 7);
	}
	
	typename cn::map<char,TestType>::iterator it = ++mymap.begin();
	typename cn::map<char,TestType>::iterator endRange =  --mymap.end();
	--endRange; --endRange; --endRange;
	REQUIRE(it->first == 'd');
	REQUIRE(endRange->first == 'f');
	mymap.erase(it, endRange);
	SECTION( "erase range 'd' to 'f' ('f' excluded)" )
	{
		REQUIRE((++mymap.begin())->first == 'f');
		REQUIRE((++mymap.begin())->second == 60);
		REQUIRE(mymap.size() == 5);
	}

	mymap.erase (mymap.begin(), mymap.end());
	SECTION( "erase range from begin to end, must be empty" )
	{
		REQUIRE(mymap.begin() == mymap.end());
		REQUIRE(mymap.size() == 0);
		REQUIRE(mymap.empty());
	}
}

TEMPLATE_TEST_CASE( "map - Modifiers - swap ",
	"[map][modifier][swap][leak]", int, IsLeaky )
{
	cn::map<char,TestType> first,second;

	first['x']=100;
	first['y']=200;

	second['a']=11;
	second['b']=22;
	second['c']=33;

	void* first_begin = (void*)&*first.begin();
	void* second_begin = (void*)&*second.begin();

	typename cn::map<char, TestType>::size_type first_size = first.size();
	typename cn::map<char, TestType>::size_type second_size = second.size();
	REQUIRE(first_size == 2 );
	REQUIRE(second_size == 3 );


	auto it = first.begin();
	REQUIRE( it->first == 'x');
	REQUIRE( it++->second == 100);
	REQUIRE( it->first == 'y');
	REQUIRE( it++->second == 200);
	REQUIRE( it == first.end());

	it = second.begin();
	REQUIRE( it->first == 'a');
	REQUIRE( it++->second == 11);
	REQUIRE( it->first == 'b');
	REQUIRE( it++->second == 22);
	REQUIRE( it->first == 'c');
	REQUIRE( it++->second == 33);
	REQUIRE(it == second.end());

	first.swap(second);

	REQUIRE(first_size == second.size() );
	REQUIRE(second_size == first.size() );


	it = first.begin();
	REQUIRE( it->first == 'a');
	REQUIRE( it++->second == 11);
	REQUIRE( it->first == 'b');
	REQUIRE( it++->second == 22);
	REQUIRE( it->first == 'c');
	REQUIRE( it++->second == 33);
	REQUIRE( it == first.end());

	it = second.begin();
	REQUIRE( it->first == 'x');
	REQUIRE( it++->second == 100);
	REQUIRE( it->first == 'y');
	REQUIRE( it++->second == 200);
	REQUIRE( it == second.end());

	SECTION( "Must only swap pointers. No allocation should be done" )
	{
		REQUIRE( first_begin == (void*)&*second.begin());
		REQUIRE( second_begin == (void*)&*first.begin());
	}
}

TEMPLATE_TEST_CASE( "map - Modifiers - clear ",
	"[map][modifier][clear][leak]", int, IsLeaky )
{
	cn::map<char,TestType> emptyMap;
	SECTION( "Empty set being clear should be okay" )
	{
		emptyMap.clear();
		REQUIRE( emptyMap.empty() );
		REQUIRE( emptyMap.size() == 0);
	}

	cn::map<char, TestType> mymap;
	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	mymap['d']=40;

	REQUIRE( !mymap.empty() );
	REQUIRE( mymap.size() == 4);
	mymap.clear();
	SECTION( "Clear set who contain element should be ok" )
	{
		REQUIRE( mymap.empty() );
		REQUIRE( mymap.size() == 0);
	}
	mymap.clear();
	SECTION( "Clear two times should be ok" )
	{
		REQUIRE( mymap.empty() );
		REQUIRE( mymap.size() == 0);
	}
}

TEST_CASE( "map - Observers - key_comp and value_comp", "[map][observer][key_comp][value_comp]" )
{
	cn::map<char,int> mymap;

	cn::map<char,int>::key_compare mycomp = mymap.key_comp();
	SECTION( "Default constructor should use std::less as default key_comp" )
	{
		cn::map<char,int>::key_compare stdless;
		REQUIRE(typeid(mycomp).name() == typeid(stdless).name());
		REQUIRE(typeid(mycomp).hash_code() == typeid(stdless).hash_code());

		REQUIRE( mycomp(4, 5) == true );
		REQUIRE( mycomp(5, 5) == false );
		REQUIRE( mycomp(6, 5) == false );
	}
	SECTION( "Default constructor should use std::less as default key_comp" )
	{
		cn::map<char,int, classcomp_map>::key_compare mycustomComp;

		REQUIRE(typeid(mycomp).name() != typeid(mycustomComp).name());
		REQUIRE(typeid(mycomp).hash_code() != typeid(mycustomComp).hash_code());
	
		REQUIRE( mycustomComp(4, 5) == false );
		REQUIRE( mycustomComp(5, 5) == false );
		REQUIRE( mycustomComp(6, 5) == true );
	}
	SECTION( "Map should have different key_comp and value_comp (because of pair)" )
	{
		REQUIRE(typeid(mymap.key_comp()).name() != typeid(mymap.value_comp()).name());
		REQUIRE(typeid(mymap.key_comp()).hash_code() != typeid(mymap.value_comp()).hash_code());
	}
}

TEST_CASE( "map - Operations - find ", "[map][operation][find]" )
{
	cn::map<char,int> mymap;
	cn::map<char,int>::iterator it;

	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	mymap['d']=30;

	REQUIRE( mymap.find('a')->first == 'a');
	REQUIRE( mymap.find('b')->first == 'b');
	REQUIRE( mymap.find('c')->first == 'c');
	REQUIRE( mymap.find('e') == mymap.end());
	
}

TEST_CASE( "map - Operations - count ", "[map][operation][count]" )
{
	cn::map<char,int> mymap;

	mymap['a']=101;
	mymap['c']=202;
	mymap['f']=303;


	REQUIRE( mymap.count('z') == 0);
	REQUIRE( mymap.count('o') == 0);
	REQUIRE( mymap.count('a') == 1);
	REQUIRE( mymap.count('c') == 1);
}

TEST_CASE( "map - Operations - lower_bound and upper_bound ", "[map][operation][lower_bound][upper_bound]" )
{
	cn::map<int,char> mymap;
	cn::map<int,char>::iterator itlow,itup;

	auto itLow = mymap.lower_bound(30);
	auto itUp = mymap.upper_bound(60);

	CHECK(itLow == mymap.end());
	CHECK(itUp == mymap.end());

	mymap[10] = 'a';
	mymap[20] = 'b';
	mymap[30] = 'c';
	mymap[40] = 'd';
	mymap[50] = 'e';
	mymap[60] = 'f';
	mymap[70] = 'g';
	mymap[80] = 'h';
	mymap[90] = 'i';

	itLow = mymap.lower_bound(30);
	itUp = mymap.upper_bound(60);

	CHECK(itLow->first == 30);
	CHECK(itUp->first == 70);
}

TEST_CASE( "map - Operations - equal_range ", "[map][operation][equal_range]" )
{
	cn::map<int, char> mymap;

	// empty map
	auto res = mymap.equal_range(42);
	CHECK( res.first == mymap.begin());
	CHECK( res.second == mymap.begin());
	CHECK( res.first == mymap.end());
	CHECK( res.second == mymap.end());
	REQUIRE( res.first == res.second);

	mymap[10] = 'a';
	mymap[20] = 'b';
	mymap[30] = 'c';
	mymap[40] = 'd';
	mymap[50] = 'e';
	mymap[60] = 'f';
	mymap[70] = 'g';
	mymap[80] = 'h';
	mymap[90] = 'i';

	// min limit
	res = mymap.equal_range(9);
	CHECK( res.first == mymap.begin());
	CHECK( res.second == mymap.begin());
	REQUIRE( res.first == res.second);


	res = mymap.equal_range(10);
	CHECK( res.first == mymap.begin());
	REQUIRE( res.second->first == 20);

	// middle
	res = mymap.equal_range(35);
	CHECK( res.first->first == 40);
	CHECK( res.second->first == 40);
	REQUIRE( res.first == res.second);

	res = mymap.equal_range(50);
	CHECK( res.first->first == 50);
	REQUIRE( res.second->first == 60);

	// max limits
	res = mymap.equal_range(90);
	CHECK( res.first->first == 90);
	REQUIRE( res.second == mymap.end());

	res = mymap.equal_range(91);
	CHECK( res.first == mymap.end());
	CHECK( res.second == mymap.end());
	REQUIRE( res.first == res.second);
}

TEST_CASE( "map - Allocator - get_allocator ", "[map][allocator][get_allocator]" )
{
  cn::map<char,int> mymap;
  cn::pair<const char,int>* p;

  p = mymap.get_allocator().allocate(5);

  mymap.get_allocator().deallocate(p,5);
}

TEMPLATE_TEST_CASE( "map - non-member - swap", "[map][non-member][swap][leak]", int, IsLeaky )
{
	cn::map<char,TestType> first,second;

	first['x']=100;
	first['y']=200;

	second['a']=11;
	second['b']=22;
	second['c']=33;

	void* first_begin = (void*)&*first.begin();
	void* second_begin = (void*)&*second.begin();

	typename cn::map<char, TestType>::size_type first_size = first.size();
	typename cn::map<char, TestType>::size_type second_size = second.size();
	REQUIRE(first_size == 2 );
	REQUIRE(second_size == 3 );


	auto it = first.begin();
	REQUIRE( it->first == 'x');
	REQUIRE( it++->second == 100);
	REQUIRE( it->first == 'y');
	REQUIRE( it++->second == 200);
	REQUIRE( it == first.end());

	it = second.begin();
	REQUIRE( it->first == 'a');
	REQUIRE( it++->second == 11);
	REQUIRE( it->first == 'b');
	REQUIRE( it++->second == 22);
	REQUIRE( it->first == 'c');
	REQUIRE( it++->second == 33);
	REQUIRE(it == second.end());

	cn::swap(first, second);

	REQUIRE(first_size == second.size() );
	REQUIRE(second_size == first.size() );


	it = first.begin();
	REQUIRE( it->first == 'a');
	REQUIRE( it++->second == 11);
	REQUIRE( it->first == 'b');
	REQUIRE( it++->second == 22);
	REQUIRE( it->first == 'c');
	REQUIRE( it++->second == 33);
	REQUIRE( it == first.end());

	it = second.begin();
	REQUIRE( it->first == 'x');
	REQUIRE( it++->second == 100);
	REQUIRE( it->first == 'y');
	REQUIRE( it++->second == 200);
	REQUIRE( it == second.end());

	SECTION( "Must only swap pointers. No allocation should be done" )
	{
		REQUIRE( first_begin == (void*)&*second.begin());
		REQUIRE( second_begin == (void*)&*first.begin());
	}
}