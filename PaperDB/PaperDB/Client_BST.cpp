/*##############################################################################################
File: Client_BST.cpp

Authors: Kirill Kudaev and Amanda Breneman
Course:	CSCI 182 - Introduction to Data Structures
Company: Principia College
Date:	05/06/2015

Description: Implementation file for a Client BST

##############################################################################################*/
#include "Client_BST.h"

/********************************************************************************************
operator<<  **  operator<<  **  operator<<  **  operator<<  **  operator<<  **  operator<<
********************************************************************************************/
std::ostream& operator<< (std::ostream& os, client_type s)
{
	// Print out all the different variable in a client_type
	os.setf(std::ios::left);
	os << std::fixed << std::showpoint
		<< std::setw(10) << s.iID
		<< std::setw(30) << s.sName
		<< std::setw(13) << std::setprecision(2) << s.fCAP
		<< std::setw(10) << std::setprecision(2) << s.fDue;

	return os;

} // operator<<

/********************************************************************************************
INSERT  **  INSERT  **  INSERT  **  INSERT  **  INSERT  **  INSERT  **  INSERT  **  INSERT
********************************************************************************************/
void Client_BST::Insert(client_type &s)
{
	Insert(root, s); // Call protected Insert() function

} // Insert

/********************************************************************************************
GetNode  **  GetNode  **  GetNode  **  GetNode  **  GetNode  **  GetNode  **  GetNode
********************************************************************************************/
client_type* Client_BST::GetNode(client_type &s)
{
	node<client_type> *tmp = root, *prev = nullptr;

	// While it is not pointing to null and not equal to our item 
	while (tmp != nullptr && !(tmp->item == s)) 
	{
		prev = tmp;
		if (tmp->item < s)        // If pointing to item that is less than the one we are searching for                           
			tmp = tmp->right;     // Point to the one on the right
		else
			tmp = tmp->left;      // Otherwise point to the one on the left
	}

	if (tmp != nullptr && tmp->item == s)  // If pointer is not pointing to null add points to our item
		return &(tmp->item);               // Returns a pointer to the item
	else
		return nullptr;                    // Returns pointer to null

} // GetNode

/********************************************************************************************
DELETE  **  DELETE  **  DELETE  **  DELETE  **  DELETE  **  DELETE  **  DELETE  **  DELETE
********************************************************************************************/
void Client_BST::Delete(client_type &s)
{
	node<client_type> *tmp = root, *prev = nullptr;

	// While it is not pointing to null and not equal to our item 
	while (tmp != nullptr && !(tmp->item == s))
	{
		prev = tmp;				// Hold the most recent item
		if (tmp->item < s)		// If new item is less than other item, look to the right
			tmp = tmp->right;
		else                    // Otherwise, look to the left
			tmp = tmp->left;
	}

	if (tmp != nullptr && tmp->item == s)	// If item isn't null and isn't the one we are looking for
		if (tmp == root)
			Delete(root);					// Delete root
		else if (prev->left == tmp)
			Delete(prev->left);				// Recursive call to delete left node
		else
			Delete(prev->right);			// Recursive call to delete right node
	else
		std::cout << "not in tree.\n";		// Item is not in tree

} // Delete

/********************************************************************************************
MAKE_BST  **   MAKE_BST  **  MAKE_BST  **  MAKE_BST  **  MAKE_BST  **  MAKE_BST  **  MAKE_BST
********************************************************************************************/
void Client_BST::MakeBST(client_type data[], int F, int L)
{
	if (root)						// If there is already a tree, destroy it
		DestroyTree(root);

	root = MakeBSTP(data, F, L);	// Make a new BST and return the root

} // Make_BST

/********************************************************************************************
BALANCE  **   BALANCE  ** BALANCE  **  BALANCE  **  BALANCE  **  BALANCE  **  BALANCE
********************************************************************************************/
void Client_BST::Balance()
{
	client_type *data;
	int N = CountNode(root);

	data = new client_type[N];			// Create an array the size of the tree

	DumpTree(root, data, 0, N - 1);		// Copy data from tree into array
	DestroyTree(root);					// Destroy the tree

	// Balance the tree by starting over with the root and the info in the array (data)
	root = MakeBSTP(data, 0, N - 1);	
	delete[] data;

} // Balance

/********************************************************************************************
INSERT  **  INSERT  **  INSERT  **  INSERT  **  INSERT  **  INSERT  **  INSERT  **  INSERT
********************************************************************************************/
void Client_BST::Insert(node<client_type>* &rt, client_type &s)
{
	if (rt == nullptr)					// If tree is empty, create new root
		rt = new node<client_type>(s);
	else if (s < rt->item)				// If new item is less than the item, insert on left
		Insert(rt->left, s);
	else                                // If new item is greater than the item, insert on right
		Insert(rt->right, s);

} // Insert

/********************************************************************************************
DELETE  **  DELETE  **  DELETE  **  DELETE  **  DELETE  **  DELETE  **  DELETE  **  DELETE
********************************************************************************************/
void Client_BST::Delete(node<client_type>* &nd)
{
	node<client_type> *prev, *tmp = nd;

	if (nd->right == nullptr)		// If right ptr of node is null, set to right
		nd = nd->left;
	else if (nd->left == nullptr)	// If left ptr of node is null, set to left
		nd = nd->right;
	else
	{
		prev = nd;					// Hold value of previous pointer
		tmp = nd->left;				// Temp = current left ptr
		while (tmp->right != nullptr)	// If temp pointer is null
		{
			prev = tmp;				// Set temp ptr to previous
			tmp = tmp->right;		// Set temp ptr to temp's right ptr
		}

		nd->item = tmp->item;

		// If it is the item you are looking for, set left prev ptr to left pointer tmp
		if (prev == nd)
			prev->left = tmp->left;
		else // Else, set right prev to temp left
			prev->right = tmp->left;
	}

	delete tmp; // Delete temp node

} // Delete

/********************************************************************************************
Make_BSTP  **   Make_BSTP  **  Make_BSTP  **  Make_BSTP  **  Make_BSTP  **  Make_BSTP
********************************************************************************************/
node<client_type>* Client_BST::MakeBSTP(client_type data[], int F, int L)
{
	node<client_type> *rt = nullptr; // Temp root variable

	if (F <= L) // If first element is <= the last element
	{
		int M = (F + L) / 2; // Find the middle element (midpoint)
		rt = new node<client_type>(data[M], MakeBSTP(data, F, M - 1), MakeBSTP(data, M + 1, L));
	}

	return rt; // Return the new root pointer

} // Make_BSTP

/********************************************************************************************
DUMPTREE  **   DUMPTREE  ** DUMPTREE  **  DUMPTREE  **  DUMPTREE  **  DUMPTREE  **  DUMPTREE
********************************************************************************************/
void Client_BST::DumpTree(node<client_type> *rt, client_type *data, int F, int L)
{
	if (rt != nullptr) // If root pointer is not null
	{
		int leftCount = CountNode(rt->left); // Create variable to count nodes left in tree
		data[leftCount + F] = rt->item;		 // Replace spot in data with the item from rt

		// Recursive calls to copy left and right nodes into the array (data)
		DumpTree(rt->right, data, leftCount + F + 1, L);
		DumpTree(rt->left, data, F, F + leftCount - 1);
	}

} // DumpTree