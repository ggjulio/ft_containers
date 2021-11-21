#include "tests.hpp"

#include "rb_tree.hpp"
#include "function.hpp"

#include <iostream>
#include <set>

void insert_v(ft::rbTree<int,int, ft::_Identity<int> >& tree, int value, size_t actualTreeSize)
{
	CHECK( tree.size() == actualTreeSize);
	tree.insert_unique(value);
	CHECK( tree.size() == actualTreeSize + 1);
	CHECK( tree.__rb_verify());
}

TEST_CASE( "rbTree::insert_unique - random insert value + decrease insert", "[rb_tree][insert_unique][basic]" )
{
	ft::rbTree<int, int, ft::_Identity<int> > tree;
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

	ft::rbTree<int, int, ft::_Identity<int>>::iterator it = tree.begin();
	ft::rbTree<int, int, ft::_Identity<int>>::iterator end = tree.end();

	int prev = static_cast<ft::node<int>>(*it).data;
	++it;
	while (it != end)
		REQUIRE( prev < static_cast<ft::node<int>>(*it++).data );
}

TEST_CASE( "rbTree::insert_unique - test insert increase value", "[rb_tree][insert_unique]" )
{
	ft::rbTree<int, int, ft::_Identity<int>> tree;
	
	for (size_t i = 0; i < 60; i++)
	{
		tree.insert_unique(i);
		CHECK( tree.size() == i + 1);

		REQUIRE( tree.__rb_verify());
	}
}

TEST_CASE( "rbTree - lower_bound and upper_bound ", "[rb_tree][lower_bound][upper_bound]" )
{
	ft::rbTree<int, int, ft::_Identity<int> > tree;
	
	auto itLow = tree.lower_bound(30);
	auto itUp = tree.upper_bound(60);

	CHECK(itLow == tree.end());
	CHECK(itUp == tree.end());

	for (int i=1; i<10; i++)
		insert_v(tree, i*10, i - 1); // 10 20 30 40 50 60 70 80 90

	itLow = tree.lower_bound(30);
	itUp = tree.upper_bound(60);

	CHECK(*itLow == 30);
	CHECK(*itUp == 70);
}


TEST_CASE( "rbTree::find ", "[rb_tree][find]" )
{
	ft::rbTree<int, int, ft::_Identity<int> > tree;

	CHECK( tree.find(30) == tree.end() );

	insert_v(tree, -42, 0);
	CHECK( *tree.find(-42) == -42 );
	CHECK( tree.find(30) == tree.end() );

	for (int i=1; i<10; i++)
		insert_v(tree, i*10, i); // 10 20 30 40 50 60 70 80 90

	CHECK( *tree.find(30) == 30 );
	CHECK( tree.find(42) == tree.end() );
}

TEST_CASE( "rbTree::equal_range ", "[rb_tree][equal_range]" )
{
	ft::rbTree<int, int, ft::_Identity<int> > tree;

	// empty tree
	auto res = tree.equal_range(42);
	CHECK( res.first == tree.begin());
	CHECK( res.second == tree.begin());
	CHECK( res.first == tree.end());
	CHECK( res.second == tree.end());
	REQUIRE( res.first == res.second);

	for (int i=1; i<10; i++)
		insert_v(tree, i*10, i - 1); // 10 20 30 40 50 60 70 80 90

	// min limit
	res = tree.equal_range(9);  
	CHECK( res.first == tree.begin());
	CHECK( res.second == tree.begin());
	REQUIRE( res.first == res.second);


	res = tree.equal_range(10);  
	CHECK( res.first == tree.begin());
	REQUIRE( *res.second == 20);
	
	// middle
	res = tree.equal_range(35);  
	CHECK( *res.first == 40);
	CHECK( *res.second == 40);
	REQUIRE( res.first == res.second);

	res = tree.equal_range(50);  
	CHECK( *res.first == 50);
	REQUIRE( *res.second == 60);


	// max limits
	res = tree.equal_range(90);  
	CHECK( *res.first == 90);
	REQUIRE( res.second == tree.end());

	res = tree.equal_range(91);  
	CHECK( res.first == tree.end());
	CHECK( res.second == tree.end());
	REQUIRE( res.first == res.second);



}

// will abort (as expected), and we can't check for abort with the catch2 framework
// TEST_CASE( "rbTree::erase empty tree", "[rb_tree][erase][iterator][position][empty]" )
// {
// 	ft::rbTree<int, int, int> tree;
	
// 	tree.erase(tree.find(30));
// 	CHECK( tree.size() == 0);
// 	REQUIRE( tree.__rb_verify());
// }

TEST_CASE( "rbTree::erase node with no childs", "[rb_tree][erase][iterator][position][no][child]" )
{
	ft::rbTree<int, int, ft::_Identity<int> > tree;
	
	for (int i=1; i<10; i++)
		insert_v(tree, i*10, i - 1); // 10 20 30 40 50 60 70 80 90
	
	tree.erase(tree.find(30));
	CHECK( tree.size() == 8);
	REQUIRE( tree.find(30) == tree.end());
	REQUIRE( tree.__rb_verify());
}

TEST_CASE( "rbTree::erase leftmost node", "[rb_tree][erase][iterator][position][leftmost]" )
{
	ft::rbTree<int, int, ft::_Identity<int> > tree;
	
	for (int i=1; i<10; i++)
		insert_v(tree, i*10, i - 1); // 10 20 30 40 50 60 70 80 90
	
	tree.erase(tree.find(10));
	CHECK( tree.size() == 8);
	REQUIRE( tree.find(10) == tree.end());
	REQUIRE( tree.__rb_verify());
}

TEST_CASE( "rbTree::erase rightmost node", "[rb_tree][erase][iterator][position][rightmost]" )
{
	ft::rbTree<int, int, ft::_Identity<int> > tree;
	
	for (int i=1; i<10; i++)
		insert_v(tree, i*10, i - 1); // 10 20 30 40 50 60 70 80 90

	tree.erase(tree.find(90));
	CHECK( tree.size() == 8);
	REQUIRE( tree.find(90) == tree.end());
	REQUIRE( tree.__rb_verify());
}


TEST_CASE( "rbTree::erase node with no left childs", "[rb_tree][erase][iterator][position][l][no]" )
{
	ft::rbTree<int, int, ft::_Identity<int> > tree;
	
	for (int i=1; i<10; i++)
		insert_v(tree, i*10, i - 1); // 10 20 30 40 50 60 70 80 90
	insert_v(tree, 35, 9);
	
	/*
	            .———90
	        .———80
	       |    `———70
	    .———60
	   |    `———50
	———40       .———35
	   |    .———30
	    `———20
	        `———10
	*/
	tree.erase(tree.find(30));
	REQUIRE(tree.size() == 9);
	REQUIRE(tree.find(30) == tree.end());
	REQUIRE(*tree.find(35) == 35);
	REQUIRE(tree.__rb_verify());
}

TEST_CASE( "rbTree::erase node with no right childs", "[rb_tree][erase][iterator][position][r][no]" )
{
	ft::rbTree<int, int, ft::_Identity<int> > tree;
	
	for (int i=1; i<10; i++)
		insert_v(tree, i*10, i - 1); // 10 20 30 40 50 60 70 80 90
	insert_v(tree, 25, 9);
	/*
	            .———90
	        .———80
	       |    `———70
	    .———60
	   |    `———50
	———40
	   |    .———30
	    `———20  `———25
	        `———10
	*/
	tree.erase(tree.find(30));
	REQUIRE(tree.size() == 9);
	REQUIRE(tree.find(30) == tree.end());
	REQUIRE(*tree.find(25) == 25);
	REQUIRE(tree.__rb_verify());
}


TEST_CASE( "rbTree::erase node with no left sibbling", "[rb_tree][erase][iterator][position][l][sibling]" )
{
	ft::rbTree<int, int, ft::_Identity<int> > tree;
	
	for (int i=1; i<10; i++)
		insert_v(tree, i*10, i - 1); // 10 20 30 40 50 60 70 80 90
	insert_v(tree, 35, 9);
	
	/*
	            .———90
	        .———80
	       |    `———70
	    .———60
	   |    `———50
	———40       .———35
	   |    .———30
	    `———20
	        `———10
	*/
	tree.erase(tree.find(35));
	REQUIRE(tree.size() == 9);
	REQUIRE(tree.find(35) == tree.end());
	REQUIRE(*tree.find(30) == 30);
	REQUIRE(tree.__rb_verify());
}


TEST_CASE( "rbTree::erase node with left sibbling and a nephew", "[rb_tree][erase][iterator][position][l][sibling][nephew]" )
{
	ft::rbTree<int, int, ft::_Identity<int> > tree;
	
	for (int i=1; i<10; i++)
		insert_v(tree, i*10, i - 1); // 10 20 30 40 50 60 70 80 90
	insert_v(tree, 35, 9);
	insert_v(tree, 11, 10);
	
	/*
	            .———90
	        .———80
	       |    `———70
	    .———60
	   |    `———50
	———40       .———35
	   |    .———30
	    `———20  .———11
	        `———10
	*/
	tree.erase(tree.find(30));
	REQUIRE(tree.size() == 10);
	REQUIRE(tree.find(30) == tree.end());
	REQUIRE(tree.__rb_verify());
}

TEST_CASE( "rbTree::erase node with no right sibling", "[rb_tree][erase][iterator][position][r][sibling]" )
{
	ft::rbTree<int, int, ft::_Identity<int> > tree;
	
	for (int i=1; i<10; i++)
		insert_v(tree, i*10, i - 1); // 10 20 30 40 50 60 70 80 90
	insert_v(tree, 25, 9);
	/*
	            .———90
	        .———80
	       |    `———70
	    .———60
	   |    `———50
	———40
	   |    .———30
	    `———20  `———25
	        `———10
	*/
	tree.erase(tree.find(25));
	REQUIRE(tree.size() == 9);
	REQUIRE(tree.find(25) == tree.end());
	REQUIRE(*tree.find(30) == 30);
	REQUIRE(tree.__rb_verify());
}



TEST_CASE( "rbTree::erase node with two childs", "[rb_tree][erase][iterator][position][two]" )
{
	ft::rbTree<int, int, ft::_Identity<int> > tree;
	
	for (int i=1; i<10; i++)
		insert_v(tree, i*10, i - 1); // 10 20 30 40 50 60 70 80 90
	
	/*
	            .———90
	        .———80
	       |    `———70
	    .———60
	   |    `———50
	———40
	   |    .———30
	    `———20
	        `———10
	*/

	tree.erase(tree.find(60));
	REQUIRE(tree.size() == 8);
	REQUIRE(tree.find(60) == tree.end());
	REQUIRE(tree.__rb_verify());


}
