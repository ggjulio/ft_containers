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

TEST_CASE( "rbTree::insert_unique - random insert value + decrease insert", "[rb_tree][insert_unique]" )
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

	int i = -1;
	int len = 7;
	while (i > -40)
	{
		insert_v(tree, i, len);
		--i;
		++len;
	}

	ft::rbTree<int, int, int>::iterator it = tree.begin();
	ft::rbTree<int, int, int>::iterator end = tree.end();

	int prev = static_cast<ft::node<int>>(*it).data;
	++it;
	while (it != end)
		REQUIRE( prev < static_cast<ft::node<int>>(*it++).data );
}

TEST_CASE( "rbTree::insert_unique - test insert increase value", "[rb_tree][insert_unique]" )
{
	ft::rbTree<int, int, int> tree;
	
	for (size_t i = 0; i < 60; i++)
	{
		tree.insert_unique(i);
		CHECK( tree.size() == i + 1);

		REQUIRE( tree.__rb_verify());
	}
}
