#include "tests.hpp"

#include "rb_tree.hpp"
#include "function.hpp"

#include <iostream>
#include <set>

void insert_v(ft::rbTree<int,int, int>& tree, int value, size_t actualTreeSize)
{
	CHECK( tree.size() == actualTreeSize);
	tree.insert_unique(value);
	CHECK( tree.size() == actualTreeSize + 1);
	CHECK( tree.__rb_verify());
}

TEST_CASE( "rb tree", "[rb_tree]" )
{
	ft::rbTree<int, int, int> tree;
	CHECK( tree.size() == 0);	
	REQUIRE( tree.__rb_verify());

	insert_v(tree, 5, 0);
	insert_v(tree, 2, 1);
	insert_v(tree, 8, 2);
	insert_v(tree, 6, 3);
	insert_v(tree, 9, 4);
	insert_v(tree, 1, 5);
	insert_v(tree, 10, 6);
	insert_v(tree, -1, 7);
	insert_v(tree, -3, 7);


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
