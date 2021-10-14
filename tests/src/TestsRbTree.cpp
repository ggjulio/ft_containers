#include "tests.hpp"
#include "rb_tree.hpp"
#include "function.hpp"

#include <iostream>
#include <set>

TEST_CASE( "rb tree", "[rb_tree]" )
{
	ft::rbTree<int, int, int> tree;


	tree.insert(5);
	CHECK( tree.size() == 1);
	
	CHECK( tree.__rb_verify());

	// tree.insert(7);
	// tree.insert(3);
	// tree.insert(6);
	// tree.insert(10);
	// tree.insert(9);
	// tree.insert(11);

	// ft::rbTree<int>::iterator it = tree.begin();
	// ft::rbTree<int>::iterator end = tree.end();

	// while (it != end)
	// {
	// 	std::cout << "> "<< static_cast<ft::node<int>>(*it).data << std::endl;
	// 	++it;
	// }
}
