#ifndef RB_TREE
#define RB_TREE

/**
 *  Rb tree rules
 * 
 *  1. a node is either red or black
 *  2. the root and leaves (NIL) are black
 *  3. if a node is red, then its children are black
 *  4. all paths from a node to its NIL descendants
 * 		contain the same number of black nodes
 * 
 *           8                            B                  
 *        /     \                      /     \               
 *       5       15                   B       R               
 * 	    / \     /   \                / \     /   \                 
 *    nil nil  12     19           nil nil  B      B               
 *            /   \   /  \                 / \     / \          
 *          9    13 nil   23             R     R  nil  R    
 *        /  \   / \     /  \          /  \   / \     /  \  
 *     nil  nil nil nil nil nil     nil  nil nil nil nil nil
 *  
 * Notes:
 *    The longest path (root to farthest NIL) is no more
 *  than twice the length of shortest path (root to nearest NIL)
 *   - SHortest path: all black nodes
 *   - Longest path: alernating red and black
 *
 */



template<class T>
struct node {
	enum Color
	{
		kRed,
		kBlack,
	};
	struct node*	parent;
	struct node*	left;
	struct node*	right;
	enum Color		color;
	T				data;
	
};

template<class T>
class RbTree
{
	node<T> *root;
public:

	// 
	// search
	// insert
	// remove

};

#endif /* RB_TREE */