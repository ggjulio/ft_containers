#include "tests.hpp"

#include "rb_tree.hpp"
#include "function.hpp"

#include <iostream>
#include <set>

TEST_CASE( "rb tree", "[rb_tree]" )
{
	ft::rbTree<int, int, int> tree;
	CHECK( tree.size() == 0);	
	REQUIRE( tree.__rb_verify());

	tree.insert_unique(5);
	tree.insert_unique(7);
	tree.insert_unique(8);
	tree.insert_unique(6);
	tree.insert_unique(9);
	tree.insert_unique(0);
	tree.insert_unique(1);


	// CHECK( tree.size() == 5);	
	// REQUIRE( tree.__rb_verify());

	// tree.insert(7);
	// tree.insert(3);
	// tree.insert(6);
	// tree.insert(10);
	// tree.insert(9);
	// tree.insert(11);

	ft::rbTree<int, int, int>::iterator it = tree.begin();
	ft::rbTree<int, int, int>::iterator end = tree.end();

	std::cout << "iter: " << std::endl;
	while (it != end)
	{
		std::cout << "	> "<< static_cast<ft::node<int>>(*it).data << std::endl;
		++it;
	}
	std::cout << "iter end " << std::endl;
}
