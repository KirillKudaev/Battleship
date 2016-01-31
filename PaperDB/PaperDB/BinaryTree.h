/*#############################################################################################
File: BinaryTree.h

Authors: Kirill Kudaev and Amanda Breneman
Course: CSCI 182 - Introduction to Data Structures
Company: Principia College
Date:   05/06/2015

Description: Program creates a binary tree and has many functions that can modify the tree.
For example, we can search, display, and delete the tree.

##############################################################################################*/
#ifndef BINARY_TREE_H

#include <iostream>
#include <Query.h>

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
S P E C I F I C A T I O N       S P E C I F I C A T I O N       S P E C I F I C A T I O N
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

// user defined structure for nodes of the tree
template<class ItemType>
struct node
{
	ItemType item;
	node<ItemType> *left; // Left pointer
	node<ItemType> *right; // Right pointer

	node() { left = right = nullptr; } // Default constuctor --> set pointers to null

	node(ItemType i, node<ItemType> *l = nullptr, node<ItemType> *r = nullptr) // Overloaded constructor
	{
		// Set pointers and item to the specified values
		item = i;
		left = l;
		right = r;
	}
};

template<class ItemType>
class BinaryTree
{
public:
	//////////////////////////////////  CONSTRUCTORS  /////////////////////////////////////////
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   BinaryTree Constructor
	Pre:        None
	Post:       Root of the tree is set to null
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BinaryTree() { root = nullptr; } // BinaryTree

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   BinaryTree Copy Constructor
	Pre:        bt has been initialized
	Post:       A deep copy of the binary tree has been returned
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BinaryTree(const BinaryTree<ItemType> &bt); // BinaryTree

	///////////////////////////////////  DESTRUCTORS  /////////////////////////////////////////
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   ~BinaryTree Destructor
	Pre:        None
	Post:       All the nodes of the tree have been destroyed
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	~BinaryTree(); // ~BinaryTree

	//////////////////////////////////  OPERATOR OVERLOADING  /////////////////////////////////
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   operator=
	Pre:        None
	Post:       Copies the tree with the new root being sent in, and returns the item being
	worked with (*this)
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BinaryTree<ItemType>& operator= (const BinaryTree<ItemType> &bt); // operator=

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   operator==
	Pre:        None
	Post:       Return whether the tree is equal
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	bool operator== (BinaryTree<ItemType>); // operator==

	//////////////////////////////////  OBSERVER FUNCTIONS  ///////////////////////////////////
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   IsEmpty
	Pre:        None
	Post:       Returns true if tree is empty, false otherwise
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	bool IsEmpty() { return root == nullptr; } // IsEmpty

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   Height
	Pre:        None
	Post:       The height of the tree has been returned
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int Height() { return Height(root); } // Height

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   CountNode
	Pre:        None
	Post:       Returns the number of nodes in the tree
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int CountNode() { return CountNode(root); } // CountNode

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   PreOrder
	Pre:        os has been declared and initialized
	Post:       Outputs the tree preorder, using recursion
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	void PreOrder(std::ostream &os) const { PreOrder(root, os); } // PreOrder

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   InOrder
	Pre:        os has been declared and initialized
	Post:       Outputs the tree inorder, using recursion
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	void InOrder(std::ostream &os) const { InOrder(root, os); } // InOrder

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   PostOrder
	Pre:        os has been declared and initialized
	Post:       Outputs the tree in postorder, using recursion
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	void PostOrder(std::ostream &os) const { PostOrder(root, os); } // PostOrder

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   Largest
	Pre:        The 2 items sent in have been declared and initialized
	Post:       Returns the largest item of the two sent to the function
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemType* Largest(bool(*lessthan) (ItemType, ItemType)); // Largest

protected:
	node<ItemType> *root; // Pointer to the root

	//////////////////////////////////  MEMBER FUNCTIONS  ////////////////////////////////////
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   TreeEqual
	Pre:        None
	Post:       Returns true if trees are equal(roots, leaves have same data), false otherwise
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	bool TreeEqual(node<ItemType>*, node<ItemType>*); // TreeEqual

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   CopyTree
	Pre:        None
	Post:       Creates a deep copy of a binary tree
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	node<ItemType>* CopyTree(node<ItemType> *rt) const; // CopyTree

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   DestroyTree
	Pre:        None
	Post:       Deletes all the nodes of the tree, root is pointing to 0
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	void DestroyTree(node<ItemType> *rt); // DestroyTree

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   Height
	Pre:        None
	Post:       Returns the maximum height of the tree
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int Height(node<ItemType> *rt); // Height

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   CountNode
	Pre:        None
	Post:       Returns the number of nodes in the tree
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int CountNode(node<ItemType> *rt); // CountNode

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   PreOrder
	Pre:        Has at least 1 node
	Post:       Prints the nodes of the tree in preorder
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	void PreOrder(node<ItemType>* rt, std::ostream &) const; // PreOrder

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   InOrder
	Pre:        Has at least 1 node
	Post:       Prints the nodes of the tree in inorder
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	void InOrder(node<ItemType>* rt, std::ostream &) const; // InOrder

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   PostOrder
	Pre:        Has at least 1 node
	Post:       Prints the nodes of the tree in postorder
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	void PostOrder(node<ItemType>* rt, std::ostream &) const; // PostOrder

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   Largest
	Pre:        None
	Post:       Returns the largest element of the tree
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	node<ItemType>* Largest(node<ItemType>* rt, bool(*lessthan) (ItemType, ItemType)); // Largest

}; // BinaryTree class

/*********************************************************************************************
COPY CONSTRUCTOR  **  COPY CONSTRUCTOR  **  COPY CONSTRUCTOR  **  COPY CONSTRUCTOR
*********************************************************************************************/
template<class ItemType>
BinaryTree<ItemType>::BinaryTree(const BinaryTree<ItemType> &bt)
{
	root = CopyTree(bt.root); // Copy tree from the root being sent in

} // BinaryTree

/*********************************************************************************************
DESTRUCTOR  **  DESTRUCTOR  **  DESTRUCTOR  **  DESTRUCTOR  **  DESTRUCTOR  **  DESTRUCTOR
*********************************************************************************************/
template<class ItemType>
BinaryTree<ItemType>::~BinaryTree()
{
	DestroyTree(root);  // Destroy all the nodes in the tree
	root = nullptr;     // Root points to 0

} // ~BinaryTree

/*********************************************************************************************
OPERATOR OVERLOADING  **  OPERATOR OVERLOADING  **  OPERATOR OVERLOADING
*********************************************************************************************/
template<class ItemType>
BinaryTree<ItemType>& BinaryTree<ItemType>::operator= (const BinaryTree<ItemType> &bt)
{
	DestroyTree(root);  // Destroy the tree
	root = CopyTree(bt.root);   // Create a new tree with the root of the tree sent in (bt)
	return *this;       // A deferenced pointer

} // operator=

/********************************************************************************************/
template<class ItemType>
bool BinaryTree<ItemType>::operator==(BinaryTree<ItemType> bt)
{
	return TreeEqual(root, bt.root); // Call TreeEqual to see if trees are the same

} // operator==

/********************************************************************************************/
template<class ItemType>
ItemType* BinaryTree<ItemType>::Largest(bool(*lessthan) (ItemType, ItemType))
{
	node<ItemType> *lg = Largest(root, (*lessthan)); // Holds largest item
	if (lg) // If there is an item
		return &(lg->item); // Return largest item
	else // Otherwise, return null
		return nullptr;

}// Largest

/*********************************************************************************************
MEMBER FUNCTIONS **  MEMBER FUNCTIONS **  MEMBER FUNCTIONS **  MEMBER FUNCTIONS
*********************************************************************************************/
template<class ItemType>
bool BinaryTree<ItemType>::TreeEqual(node<ItemType> *rt1, node<ItemType> *rt2)
{
	if (rt1 == nullptr && rt2 == nullptr) // both are empty
		return true; // If they are both empty, they are equal
	else if (rt1 == nullptr || rt2 == nullptr) // one is empty
		return false; // If one is empty, they aren't equal
	else if (rt1->item == rt2->item) // roots have same data
		return TreeEqual(rt1->left, rt2->left) &&
		TreeEqual(rt1->right, rt2->right); // check leaves to see if they are equal
	else // roots have different data
		return false; // They are not equal

} // TreeEqual

/********************************************************************************************/
template<class ItemType>
node<ItemType>* BinaryTree<ItemType>::CopyTree(node<ItemType> *rt) const
{
	node<ItemType> *newRoot = nullptr;

	if (rt != nullptr) // recursively copy all data until we reach the end of the tree
		newRoot = new node<ItemType>(rt->item, CopyTree(rt->left), CopyTree(rt->right));

	return newRoot;

} // CopyTree

/********************************************************************************************/
template<class ItemType>
void BinaryTree<ItemType>::DestroyTree(node<ItemType> *rt)
{
	if (rt != nullptr) // If right is not null
	{
		DestroyTree(rt->left); // Recursively call DestroyTree on left pointers
		DestroyTree(rt->right); // Recursively call DestroyTree on right pointers
		delete rt; // Delete leaf
	}

} // DestroyTree

/********************************************************************************************/
template<class ItemType>
int BinaryTree<ItemType>::Height(node<ItemType> *rt)
{
	int l, r;

	if (rt == nullptr) // base case...tree is empty
		return 0; // Height is 0
	else
		// If left statement is bigger, return l; if right statement is bigger, return r
		return ((l = Height(rt->left) + 1) > (r = Height(rt->right) + 1)) ? l : r;

} // Height

/********************************************************************************************/
template<class ItemType>
int BinaryTree<ItemType>::CountNode(node<ItemType> *rt)
{
	if (rt == nullptr) // Base case --> tree is empty so count is 0
		return 0;
	else
		// Go through all the nodes recursively and add to the height (add 1 for the root)
		return CountNode(rt->left) + CountNode(rt->right) + 1;

} // CountNode

/********************************************************************************************/
template<class ItemType>
void BinaryTree<ItemType>::PreOrder(node<ItemType>* rt, std::ostream &os) const
{
	if (rt != nullptr) // If right ptr is not null
	{
		// output current node to the screen
		os << rt->item << endl;

		// recursively check left nodes
		if (rt->left != nullptr)
			PreOrder(rt->left, os); // Recursively call with left nodes

		// recursively check right nodes
		if (rt->right != nullptr)
			PreOrder(rt->right, os); // Recursively call with right nodes
	}

} // PreOrder

/********************************************************************************************/
template<class ItemType>
void BinaryTree<ItemType>::InOrder(node<ItemType>* rt, std::ostream &os) const
{
	if (rt != nullptr) // If tree is not empty
	{
		InOrder(rt->left, os); // Recursively call with left nodes
		os << rt->item << endl; // Print item to screen
		InOrder(rt->right, os); // Recursively call with right nodes
	}

} // InOrder

/********************************************************************************************/
template<class ItemType>
void BinaryTree<ItemType>::PostOrder(node<ItemType>* rt, std::ostream &os) const
{
	if (rt != nullptr) // If tree is not empty
	{
		PostOrder(rt->left, os); // Recursively call with left nodes
		PostOrder(rt->right, os); // Recursively call with right nodes
		os << rt->item << endl; // Then print to screen
	}

}  // PostOrder

/********************************************************************************************/
template<class ItemType>
node<ItemType>* BinaryTree<ItemType>::Largest(node<ItemType>* rt, bool(*lessthan) (ItemType, ItemType))
{
	node<ItemType> *lg = rt, *llg, *rlg;
	if (rt == nullptr) // If tree is empty
		return nullptr; // Return null ptr

	// check left ptr
	if ((llg = Largest(rt->left, lessthan)) != nullptr && lessthan(lg->item, llg->item))
		lg = llg; // Set left ptr to largest left ptr
	// check right ptr
	if ((rlg = Largest(rt->right, lessthan)) != nullptr && lessthan(lg->item, rlg->item))
		lg = rlg; // Set right ptr to largest right ptr

	return lg;    // Return largest node from the whole tree

}// Largest

#define BINARY_TREE_H
#endif