// Rijad Kasumi (rijad.kasumi11@myhunter.cuny.edu)
// Date 09-10-2022
// CSCI 335 - Assignment 2
// Professor Anita Raja
// Avl_tree_p2c.h file for part 2c. In this this file the doublewithleft and doublewithright rotation is implemented instead of doign 2 single rotation.

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include "sequence_map.h"
#include <algorithm>
#include <iostream>
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order

//***************************************************************

// Implemented function by Rijad Kasumi:

// void find ()           --> Prints the value of the node if its found
// int CountNodes()		  --> Counts the nodes in the tree
// iint tree_Path() 	  --> Checks the path of the length of the tree

// Modified Function       ************************************
// insert()               --> Merge added(if duplicates)
// remove()               --> To remove calls while pre incrementin the remove calls
// find1()                --> To preincrement the number of recursive calls
// void doubleWithLeftChild --> to perform a double rotations
// void doubleWithRightChild --> to perform a double rotations
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
public:
	AvlTree( ) : root{ nullptr }
	{ }

	AvlTree( const AvlTree & rhs ) : root{ nullptr }
	{
		root = clone( rhs.root );
	}

	AvlTree( AvlTree && rhs ) : root{ rhs.root }
	{
		rhs.root = nullptr;
	}

	~AvlTree( )
	{
		makeEmpty( );
	}

	/**
	 * Deep copy.
	 */
	AvlTree & operator=( const AvlTree & rhs )
	{
		AvlTree copy = rhs;
		std::swap( *this, copy );
		return *this;
	}

	/**
	 * Move.
	 */
	AvlTree & operator=( AvlTree && rhs )
	{
		std::swap( root, rhs.root );

		return *this;
	}

	/**
	 * Find the smallest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	const Comparable & findMin( ) const
	{
		if( isEmpty( ) )
			throw UnderflowException{ };
		return findMin( root )->element;
	}

	/**
	 * Find the largest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	const Comparable & findMax( ) const
	{
		if( isEmpty( ) )
			throw UnderflowException{ };
		return findMax( root )->element;
	}

	/**
	 * Returns true if x is found in the tree.
	 */
	bool contains( const Comparable & x ) const
	{
		return contains( x, root );
	}
	/**
	 * Prints the value of the node if its found. Else "Not Found"
	 */
    void find(const Comparable &x) const {
        return findF(x, root);
    }
	/**
	 * Prints the value of the node
	 */
	 bool find1( const Comparable & x, Comparable & y ){
        return findF2(x, y, root);
    }
	/**
	 * Print the total number of Recursive calls
	 */
	float total_Recursion_Calls(){
        return total_Number_Rec;
		}
	/**
	 * Prints the remove number of Recursive calls
	 */
	
	float remove_Call(){
		return remove_Calls;
	}

     /**
	 * Counts the nodes in the tree
	 */
    int CountNodes() const {
        return Count_Nodes(root);
    }
     /**
	 * Check the length of depth of the tree
	 */
    int tree_Path() const {
        int depth = 0; //initial depth 0
        return Depth_Of_Tree(root, depth);
	}
	/**
	 * Test if the tree is logically empty.
	 * Return true if empty, false otherwise.
	 */
	bool isEmpty( ) const
	{
		return root == nullptr;
	}

	/**
	 * Print the tree contents in sorted order.
	 */
	void printTree( ) const
	{
		if( isEmpty( ) )
			cout << "Empty tree" << endl;
		else
			printTree( root );
	}

	/**
	 * Make the tree logically empty.
	 */
	void makeEmpty( )
	{
		makeEmpty( root );
	}

	/**
	 * Insert x into the tree; duplicates are ignored.
	 */
	void insert( const Comparable & x )
	{
		insert( x, root );

	}

	/**
	 * Insert x into the tree; duplicates are ignored.
	 */
	void insert( Comparable && x )
	{
		insert( std::move( x ), root );
	}

	/**
	 * Remove x from the tree. Nothing is done if x is not found.
	 */
	void remove( const Comparable & x )
	{
		remove( x, root );
	}

private:
	struct AvlNode
	{
		Comparable element;
		AvlNode   *left;
		AvlNode   *right;
		int       height;

		AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
			: element{ ele }, left{ lt }, right{ rt }, height{ h } { }

		AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
			: element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
	};

	AvlNode *root;

	int total_Number_Rec = 0;
	int remove_Calls = 0;


	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert( const Comparable & x, AvlNode * & t )
	{
		if( t == nullptr )
			t = new AvlNode{ x, nullptr, nullptr };
		else if( x < t->element )
			insert( x, t->left );
		else if( t->element < x )
			insert( x, t->right );
			else{ //else call the merge(X).
				t->element.Merge(x);
			}

		balance( t );
	}

	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert( Comparable && x, AvlNode * & t )
	{
		if( t == nullptr )
			t = new AvlNode{ std::move( x ), nullptr, nullptr };
		else if( x < t->element )
			insert( std::move( x ), t->left );
		else if( t->element < x )
			insert( std::move( x ), t->right );
			else{ //else call the merge(X).
				t->element.Merge(x);
			}

		balance( t );
	}

	/**
	 * Internal method to remove from a subtree.
	 * x is the item to remove.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void remove( const Comparable & x, AvlNode * & t )
	{
		if( t == nullptr )
			return;   // Item not found; do nothing

		if( x < t->element ){
			++remove_Calls; //pre increment remove_Calls
			remove( x, t->left );}
		else if( t->element < x ){
			++remove_Calls; // modified 
			remove( x, t->right );}
		else if( t->left != nullptr && t->right != nullptr )// Two children
		{
			++remove_Calls; //modified 
			t->element = findMin( t->right )->element;
			remove( t->element, t->right );
		}
		else
		{
			AvlNode *oldNode = t;
			t = ( t->left != nullptr ) ? t->left : t->right;
			delete oldNode;
		}

		balance( t );
	}

	static const int ALLOWED_IMBALANCE = 1;

	// Assume t is balanced or within one of being balanced
	void balance( AvlNode * & t )
	{
		if( t == nullptr )
			return;

		if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ) {
			if( height( t->left->left ) >= height( t->left->right ) )
				rotateWithLeftChild( t );
			else
				doubleWithLeftChild( t );
		} else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ) {
			if( height( t->right->right ) >= height( t->right->left ) )
				rotateWithRightChild( t );
			else
				doubleWithRightChild( t );
		}
		t->height = max( height( t->left ), height( t->right ) ) + 1;
	}

	/**
	 * Internal method to find the smallest item in a subtree t.
	 * Return node containing the smallest item.
	 */
	AvlNode * findMin( AvlNode *t ) const
	{
		if( t == nullptr )
			return nullptr;
		if( t->left == nullptr )
			return t;
		return findMin( t->left );
	}

	/**
	 * Internal method to find the largest item in a subtree t.
	 * Return node containing the largest item.
	 */
	AvlNode * findMax( AvlNode *t ) const
	{
		if( t != nullptr )
			while( t->right != nullptr )
				t = t->right;
		return t;
	}

	/**
	 * Internal method to test if an item is in a subtree.
	 * x is item to search for.
	 * t is the node that roots the tree.
	 */
	bool contains( const Comparable & x, AvlNode *t ) const
	{
		if( t == nullptr )
			return false;
		else if( x < t->element )
			return contains( x, t->left );
		else if( t->element < x )
			return contains( x, t->right );
		else
			return true;    // Match
	}
	/**
	 * find() function
	 * Prints the value of the node if a match node is found
	 * if there is no node cout "Not Found"
	 */
    void findF(const Comparable& x, AvlNode *t) const {
		
        if(t == nullptr) {
            cout << "Not Found" << endl;
        }
        else if(t->element < x) { 
            return findF(x, t->right); // traversing right until x is found
        }
        else if(x < t->element) {  // travering left until x is found
            return findF(x, t->left);
        }
        else {
            cout << t->element << endl; // else its found
        }
    }
	 bool findF2( const Comparable & x, Comparable & y, AvlNode *t){

        if( t == nullptr ){
			return false;
			}
        else if( x < t->element ){
            ++total_Number_Rec;;
            return findF2( x, y, t->left );
        }
        else if( t->element < x ){
            ++total_Number_Rec;
            return findF2( x, y, t->right );
        }
        else {
            y = t->element;
            return true;
        }  }  
	/**
	 * Function counts nodes in the tree recursively
	 */
	   int Count_Nodes(AvlNode * t) const {

        if (t == nullptr) {
            return 0;
        }
        else {
            return Count_Nodes(t->left)+1 + Count_Nodes(t->right);
        }
    }
   /**
	 * Function count the internal depth of the tree
	 */
    float Depth_Of_Tree(AvlNode * t, float depth) const {
        if (t == nullptr) {
            return 0;
        }
        else {
            return Depth_Of_Tree(t->left, depth + 1) + Depth_Of_Tree(t->right, depth + 1) + depth;
        }
    }

	// Counts the nodes
	/****** NONRECURSIVE VERSION*************************
	    bool contains( const Comparable & x, AvlNode *t ) const
	    {
	        while( t != nullptr )
	            if( x < t->element )
	                t = t->left;
	            else if( t->element < x )
	                t = t->right;
	            else
	                return true;    // Match

	        return false;   // No match
	    }
	*****************************************************/

	/**
	 * Internal method to make subtree empty.
	 */
	void makeEmpty( AvlNode * & t )
	{
		if( t != nullptr )
		{
			makeEmpty( t->left );
			makeEmpty( t->right );
			delete t;
		}
		t = nullptr;
	}

	/**
	 * Internal method to print a subtree rooted at t in sorted order.
	 */
	void printTree( AvlNode *t ) const
	{
		if( t != nullptr )
		{
			printTree( t->left );
			cout << t->element << endl;
			printTree( t->right );
		}
	}

	/**
	 * Internal method to clone subtree.
	 */
	AvlNode * clone( AvlNode *t ) const
	{
		if( t == nullptr )
			return nullptr;
		else
			return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
	}
	// Avl manipulations
	/**
	 * Return the height of node t or -1 if nullptr.
	 */
	int height( AvlNode *t ) const
	{
		return t == nullptr ? -1 : t->height;
	}

	int max( int lhs, int rhs ) const
	{
		return lhs > rhs ? lhs : rhs;
	}

	/**
	 * Rotate binary tree node with left child.
	 * For AVL trees, this is a single rotation for case 1.
	 * Update heights, then set new root.
	 */
	void rotateWithLeftChild( AvlNode * & k2 )
	{
		AvlNode *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
		k1->height = max( height( k1->left ), k2->height ) + 1;
		k2 = k1;
	}

	/**
	 * Rotate binary tree node with right child.
	 * For AVL trees, this is a single rotation for case 4.
	 * Update heights, then set new root.
	 */
	void rotateWithRightChild( AvlNode * & k1 )
	{
		AvlNode *k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
		k2->height = max( height( k2->right ), k1->height ) + 1;
		k1 = k2;
	}

	/**
	 * Double rotate binary tree node: first left child.
	 * with its right child; then node k3 with new left child.
	 * For AVL trees, this is a double rotation for case 2.
	 * Update heights, then set new root.
	 */
	void doubleWithLeftChild( AvlNode * & k3 )
	{
        AvlNode *k1 = k3->left->right; // first left child then right child
        k3->left->right = k1->left;
        k1->left = k3->left;
        k3->left->height = max(height(k3->left->left), height(k3->left->right)) + 1; //updating the heights
        k1->height = max(height(k1->right), k3->left->height) + 1;
        k3->left = k1;
        // Now rotate with left child
        AvlNode *k2 = k3->left;
        k3->left = k2->right;
        k2->right = k3;
        k3->height = max(height(k3->left), height(k3->right)) + 1;
        k2->height = max(height(k2->left), k3->height) + 1;
        k3 = k2; //setting new root
	}

	/**
	 * Double rotate binary tree node: first right child.
	 * with its left child; then node k1 with new right child.
	 * For AVL trees, this is a double rotation for case 3.
	 * Update heights, then set new root.
	 */
	void doubleWithRightChild( AvlNode * & k1 )
	{
        AvlNode *k3 = k1->right->left; // first right child then left child
        k1->right->left = k3->right;
        k3->right = k1->right;
        k1->right->height = max(height(k1->right->left), height(k1->right->right)) + 1;//updating the heights
        k3->height = max(height(k3->left), k1->right->height) + 1;
        k1->right = k3;

        // Now rotate with right child 
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;  // setting new root

	}
};

#endif
