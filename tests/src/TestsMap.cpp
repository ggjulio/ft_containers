#include "tests.hpp"

#include "map.hpp"

bool fncomp_map (int lhs, int rhs) {return lhs>rhs;}

struct classcomp_map {
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs>rhs;}
};

TEST_CASE( "map - construct", "[map][constructors]" )
{
    cn::map<char,int> first;
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

	cn::map<char,int> second (first.begin(), first.end());
	SECTION( "range construtor" ) {
		REQUIRE(!second.empty());
		REQUIRE(second.size() == 5);
	}
	SECTION( "copy construtor" ) {
		cn::map<char,int> third (second);
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
		cn::map<char,int> fourth (second.begin(), second.end());
		REQUIRE(!fourth.empty());
		REQUIRE(fourth.size() == 5);
	}
	SECTION( "class as Compare" ) {
		cn::map<char,int,classcomp_map> fifth;
		fifth.insert(cn::pair('a', 10));
		fifth.insert(cn::pair('b', 20));
		REQUIRE(fifth.begin()->second == 20);
		REQUIRE((--fifth.end())->second == 10);
		REQUIRE(fifth.find('b')->second == 20);
	}
	SECTION( "function ptr as Compare" ) {
		bool(*fn_pt)(int,int) = fncomp_map;
		cn::map<char,int,bool(*)(int,int)> sixth (fn_pt);

		sixth.insert(cn::pair('a', 10));
		sixth.insert(cn::pair('b', 20));
		REQUIRE(sixth.begin()->second == 20);
		REQUIRE((--sixth.end())->second == 10);
		REQUIRE(sixth.find('b')->second == 20);
	}
}


TEST_CASE( "map - operator - assignment ", "[map][operator][assignment]" )
{
	cn::map<char,int> first;
  	cn::map<char,int> second;
	
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
		first = cn::map<char,int>();
	}
}

TEST_CASE( "map - iterator ", "[map][iterator]" )
{
	cn::map<char, int> first;
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

TEST_CASE( "map - reverse iterator ", "[map][reverse_iterator]" )
{
	cn::map<char,int> first;
	SECTION( "empty container should have begin() == end()" )
	{
		REQUIRE( first.rbegin() == first.rend() );
	}
	first.insert(cn::pair('a', 10));
	SECTION( "container with one element should have consistant boundary" )
	{
		REQUIRE( ++first.rbegin() == first.rend() );
		REQUIRE( first.rbegin() == --first.rend() );
		REQUIRE( first.rbegin().operator*().second == 10 );
		REQUIRE( first.rbegin().operator->() == &*first.rbegin() );
	}
	first.insert(cn::pair('b', 20));
	first.insert(cn::pair('c', 30));
	SECTION( "container with three elements should loop properly" )
	{
		auto it = first.rbegin();
		int i = 40;
		while (it != first.rend())
		{
			i -= 10;
			REQUIRE(it->second == i);
			++it;
		}
		REQUIRE(i == 10);
	}
	SECTION( "container with three elements should loop properly in reverse" )
	{
		auto it = first.rend();
		int i = 0;
		while (--it != first.rbegin())
		{
			i += 10;
			REQUIRE(it->second == i);
		}
		REQUIRE(it->second == 30);
	}
}

TEST_CASE( "map - capacity ", "[map][capacity]" )
{
	cn::map<char, int> first;

	SECTION( "empty container should be empty (insightful)" )
	{
		REQUIRE(first.empty());
		REQUIRE(first.size() == 0);
	}
	first.insert(cn::pair('a', 10));
	SECTION( "container with one element should be of size one (and not empty, of course)" )
	{
		REQUIRE(!first.empty());
		REQUIRE(first.size() == 1);
	}
	first.erase(first.begin());
	SECTION( "delete the single element, should become an empty container again." )
	{
		REQUIRE(first.size() == 0);
		REQUIRE(first.empty());
	}
	SECTION( "max_size(), For now I don't know which value is suposed to be equal to (probably depend on the underlying implementation)" )
	{
		REQUIRE(first.max_size() == 230584300921369395);
	}
}

TEST_CASE( "map - Modifiers ", "[map][modifier][insert]" )
{
	cn::map<char,int> mymap;
	cn::map<char,int>::iterator it_res;
	cn::pair<cn::map<char,int>::iterator,bool> ret;
	
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

	cn::pair<char,int> myints[]= {
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
