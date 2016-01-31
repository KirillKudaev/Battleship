/*##############################################################################################
File: Client_BST.h

Authors: Kirill Kudaev and Amanda Breneman
Course: CSCI 182 - Introduction to Data Structures
Company: Principia College
Date:   05/06/2015

Description: Specification file for a Client BST

###############################################################################################*/
#ifndef CLIENT_BST_H

#include <string>
#include <iomanip>
#include "BinaryTree.h"

/********************************************************************************************
CLIENT_TYPE  **  CLIENT_TYPE  **  CLIENT_TYPE  **  CLIENT_TYPE  **  CLIENT_TYPE
********************************************************************************************/
struct client_type
{
	int iID;
	std::string sName;
	float fCAP;
	float fDue;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   client_type constructor
	Pre:        None
	Post:       Sets ID to 9999, name to None, Current Amount Paid and Amount Due to 0
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	client_type()
	{
		iID = -9999;
		sName = "None";
		fCAP = 0.0f;
		fDue = 0.0f;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   overload operator==
	Pre:        None
	Post:       Overloads the "==" operator. Returns true if IDs are equal, false otherwise
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	bool operator== (client_type &s)
	{
		return iID == s.iID;

	} // operator==

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   overload operator<
	Post:       Overloads the ">" operator. Returns true if the first ID is smaller than the
	second one, false otherwise
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	bool operator< (client_type &s)
	{
		return iID < s.iID;

	} // operator<


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   overload operator>
	Pre:        None
	Post:       Overloads the ">" operator. Returns true if the first ID is bigger than the
	second one, false otherwise
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	bool operator>(client_type &s)
	{
		// using == and < operators
		return !((*this)<s) && !((*this) == s);

	} // operator>

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   overload operator<<
	Pre:        None
	Post:       Overloads the "<<" operator. Provides well organized output of the ID, Name,
	Current Amount Paid and Amount Due of the provider.
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	friend std::ostream& operator<< (std::ostream &out, client_type s);

};

/********************************************************************************************
CLIENT_BST  **  CLIENT_BST  **  CLIENT_BST  **  CLIENT_BST  **  CLIENT_BST  **  CLIENT_BST
********************************************************************************************/
class Client_BST : public BinaryTree<client_type>
{
public:
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   Insert
	Pre:        bt has been initialized
	Post:       Adds a node from the bt
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	void Insert(client_type &s);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   GetNode
	Pre:        bt has been initialized
	Post:       Returns a pointer to the node we are searching for, and null if it not found
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	client_type* GetNode(client_type &s);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   Delete
	Pre:        bt has been initialized
	Post:       Deletes thes node sent in from the bt
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	void Delete(client_type &s);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   Make_BST
	Pre:        Items has been stored in the array
	Post:       Creates a binary search tree
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	void MakeBST(client_type data[], int F, int L);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   Balance
	Pre:        bt has been initialized
	Post:       Balances the binary tree to reduce the height
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	void Balance();

private:
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   Insert
	Pre:        bt has been initialized
	Post:       Adds a node to bt
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	void Insert(node<client_type>* &rt, client_type &s);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   Delete
	Pre:        bt has been initialized
	Post:       Deletes a node from the bt if it exists
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	void Delete(node<client_type>* &nd);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   Make_BSTP
	Pre:        Items has been stored in the array
	Post:       Creates a binary search tree
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	node<client_type>* MakeBSTP(client_type data[], int F, int L);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Function:   DumpTree
	Pre:        bt has been initialized
	Post:       Stores nodes of the binary tree in the array
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	void DumpTree(node<client_type> *rt, client_type *data, int F, int L);

};

#define CLIENT_BST_H
#endif