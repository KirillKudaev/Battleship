/*##############################################################################################
File: PaperDriver.cpp

Authors: Kirill Kudaev and Amanda Breneman
Course: CSCI 182 - Introduction to Data Structures
Company: Principia College
Date:   05/6/2015

Description: This program holds a paper database and keeps track of the company ID number,
			 name, current amount paid, and the amount due. The user has the options of adding
			 a company, issuing a payment, accepting a delivers, and printing the report as
			 well as saving the report to a file. The user can quit the program any time they
			 like.

##############################################################################################*/
#include <iostream>
#include <fstream>
#include <string>
#include "Client_BST.h"

using namespace std;

// Global constants
const string sFILE_NAME = "Clients.csv";
const string sFILE_OUTPUT_NAME = "PaperDB.csv";

// Function prototypes
int Menu();
void GetData(Client_BST &clients);
void AddRecord(Client_BST &clients);
void IssuePayment(Client_BST &clients);
void AcceptDelivery(Client_BST &clients);
void PrintReport(Client_BST clients);
void SaveReport(Client_BST clients);
void Clear();

int main()
{
	// Variable list
	Client_BST clients;
	client_type oneClient;

	GetData(clients);

	while (true) // Program loop...loop until exit condition breaks loop
	{
		switch (Menu()) // Display the menu and switch on the resulting selection
		{
		case 0: goto quit; // Quit program...break out of while loop
		case 1: AddRecord(clients); break;
		case 2: IssuePayment(clients); break;
		case 3: AcceptDelivery(clients); break;
		case 4: PrintReport(clients); break;
		default:
			cout << "Invalid selection...try again\n\n";
			break;
		}

		// Wait for user input and clear the screen for the next program itteration
		system("pause");
		system("cls");
	}

	// Quit program label
	quit:

	// Save report to output file
	SaveReport(clients);
	system("PaperDB.csv"); // Open file

	// Exit program and return control to caller
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FUNCTION:   Menu
PRE:        Menu is called from the switch statement
POST:       Returns the users specified action
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Menu()
{
	// Variable pool
	int iSelection;

	do
	{
		cout << "Please select an option from the menu:\n\n"

			<< "1. Add a record\n"
			<< "2. Issue a payment\n"
			<< "3. Accept a delivery\n"
			<< "4. Print Summary Report\n"
			<< "\n0. Exit\n\n"
			<< "Selection: ";

		// Get user selected menu item
		cin >> iSelection;
		Clear();

		if (iSelection < 0 || iSelection > 4){
			system("cls");
			cout << "Invalid input. Try again!\n\n";
		}

	} while (iSelection < 0 || iSelection > 4); // Repeat while input is invalid

	return iSelection;

} // Menu

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FUNCTION:   GetData
PRE:        clients has been created and sent to function
POST:       Data from Clients.csv has been read into tree
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void GetData(Client_BST &clients)
{
	ifstream fin;
	client_type client;
	string sTemp, sDummyVar;

	// Input file preparation
	fin.open(sFILE_NAME);

	if (!fin.fail()) // If the file exists
	{
		cout << sFILE_NAME << " was opened.\n";
		cout << "\t...Getting Data\n";

		getline(fin, sDummyVar); // Read in and ignore first line of file (the headers)

		while (!fin.eof())
		{
			// Read and store all the data in client
			getline(fin, sTemp, ',');
			client.iID = stoi(sTemp);

			getline(fin, client.sName, ',');

			getline(fin, sTemp, ',');
			client.fCAP = stof(sTemp);

			getline(fin, sTemp);
			client.fDue = stof(sTemp);

			// Add client to tree
			clients.Insert(client);
		}

		clients.Balance(); // Balance tree

		// Input file cleanup
		fin.close();
		cout << sFILE_NAME << " was closed.\n\n";
	}
	else // Otherwise, file was not found
	{
		cout << "File not found.\n";
		exit(0); // Quit progarm
	}

	// pause and wait for user input before clearing the screen
	system("pause");
	system("cls");
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FUNCTION:   AddRecord
PRE:        AddRecord is called from the switch statement
POST:       Adds a record to the list, and sets the iID and sName
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void AddRecord(Client_BST &clients)
{
	system("cls"); // Clear screen

	// Variable pool
	client_type newClient;
	int iTemp = -9999;

	cout << "Add a record\n\n";
	cout << "Enter ID number for new provider: ";
	cin >> iTemp;
	Clear();

	// If ID is already delclared, give user option to reenter a number
	while (clients.GetNode(newClient) != nullptr || iTemp <= 0)
	{
		system("cls");
		cout << "Invalid ID.\n\n";
		cout << "Enter a different ID number for new provider: ";
		cin >> iTemp;
		Clear();
	}

	if (iTemp > 0) // If valid ID number, add client to list
	{
		newClient.iID = iTemp; // Set ID to temp variable

		cout << "Enter provider name for ID-" << newClient.iID << ": ";
		cin >> newClient.sName;

		// Set amount due and paid to 0
		newClient.fCAP = 0.0f;
		newClient.fDue = 0.0f;

		clients.Insert(newClient); // Add new client to list

		clients.Balance(); // Balance tree

		cout << "\nClient has been added!\n";
	}
	else // Otherwise, output error message
		cout << "Invalid ID";
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FUNCTION:   IssuePayment
PRE:        IssuePayment is called from the switch statement
POST:       Amount due has been outputted and the client has payed less than or equal to
			the amount that they owe
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void IssuePayment(Client_BST &clients)
{
	// Variable pool
	client_type client;
	float fPaymentAmount;

	system("cls");

	// User input
	cout << "Please enter the ID number: ";
	cin >> client.iID;
	Clear();

	cout << endl;

	if (clients.GetNode(client) == nullptr) // If ID is not found, return to menu
	{
		cout << "ID not found\n\n";
	}
	else // ID has been found
	{
		// Print header
		cout.setf(ios::left);
		cout << fixed << showpoint
			<< setw(10) << "ID"
			<< setw(30) << "Provider Name"
			<< setw(13) << setprecision(2) << "YID Paid"
			<< setw(10) << setprecision(2) << "Amount Due\n";
		cout << "---------------------------------------------------------------\n";

		// Print data
		cout << fixed << showpoint
			<< setw(10) << clients.GetNode(client)->iID
			<< setw(30) << clients.GetNode(client)->sName
			<< setw(13) << setprecision(2) << clients.GetNode(client)->fCAP
			<< setw(10) << setprecision(2) << clients.GetNode(client)->fDue;

		cout << endl << endl;

		// User input
		cout << "Please enter the payment amount ($" << clients.GetNode(client)->fDue << " max): ";
		cin >> fPaymentAmount;
		Clear();

		while ((fPaymentAmount <= 0) || (fPaymentAmount > (clients.GetNode(client)->fDue))) // While input is invalid
		{
			system("cls");

			// Ask for correct user input
			cout << "Invalid - input must be greater than 0 and less than amount due\n\n";
			cout << "Please enter the payment amount: ";
			cin >> fPaymentAmount;

			Clear();
		}

		// Update fCap and fDue based off user input
		clients.GetNode(client)->fCAP = clients.GetNode(client)->fCAP + fPaymentAmount;
		clients.GetNode(client)->fDue = clients.GetNode(client)->fDue - fPaymentAmount;

		cout << endl;
		cout << "Up-to-date amount due: " << clients.GetNode(client)->fDue << endl << endl;
	}

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FUNCTION:   AcceptDelivery
PRE:        AcceptDelivery is called from the switch statement
POST:       The value of the paper delivered is added to the clients fDue
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void AcceptDelivery(Client_BST &clients)
{
	// Variable pool
	client_type client;
	float fTemp = 0.0f;
	int iTemp = 0;

	system("cls");

	cout << "Please enter the ID number: ";
	cin >> client.iID;
	Clear();

	if (clients.GetNode(client) == nullptr)
	{
		cout << "Record not found\n\n"; // If ID is not found, return to menu
	}
	else
	{
		// Print header
		cout.setf(ios::left);
		cout << fixed << showpoint
			<< setw(10) << "ID"
			<< setw(30) << "Provider Name"
			<< setw(13) << setprecision(2) << "YID Paid"
			<< setw(10) << setprecision(2) << "Amount Due\n";
		cout << "---------------------------------------------------------------\n";

		// Print data
		cout << fixed << showpoint
			<< setw(10) << clients.GetNode(client)->iID
			<< setw(30) << clients.GetNode(client)->sName
			<< setw(13) << setprecision(2) << clients.GetNode(client)->fCAP
			<< setw(10) << setprecision(2) << clients.GetNode(client)->fDue;
		cout << endl << endl;

		// User input
		cout << "Please enter the amount of paper delivered: ";
		cin >> fTemp;
		Clear();

		while ((fTemp > (clients.GetNode(client)->fDue))) // While input is invalid
		{
			system("cls");

			// Ask for correct user input
			cout << "Invalid - input must be greater than 0 and less than amount due\n\n";
			cout << "Please enter the payment amount: ";
			cin >> fTemp;

			Clear();
		}

		// Update fDue
		clients.GetNode(client)->fDue = clients.GetNode(client)->fDue + fTemp;

		cout << endl;
		cout << "Up-to-date amount due: " << clients.GetNode(client)->fDue << endl << endl;
	}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FUNCTION:   PrintReport
PRE:        PrintReport is called from the switch statement
POST:       The report has been printed to the screen
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void PrintReport(Client_BST clients)
{
	system("cls"); // Clear screen

	// Print header
	cout.setf(ios::left);
	cout << fixed << showpoint
		<< setw(10) << "ID"
		<< setw(30) << "Provider Name"
		<< setw(13) << setprecision(2) << "YID Paid"
		<< setw(10) << setprecision(2) << "Amount Due\n";
	cout << "---------------------------------------------------------------\n";

	// Print report to screen based on ID numbers
	clients.InOrder(cout);
	cout << "\n";
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FUNCTION:   SaveReport
PRE:        SaveReport is called once the user requests to quit the program
POST:       The report generated in PrintReport is saved to PaperDB.csv
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void SaveReport(Client_BST clients)
{
	// create output stream
	ofstream fout;

	system("cls"); // Clear screen

	// open output file
	fout.open(sFILE_OUTPUT_NAME);
	cout << sFILE_OUTPUT_NAME << " has been opened to write.\n";

	cout << "Reporting...\n";

	// Print header
	fout.setf(ios::left);
	fout << fixed << showpoint
		<< setw(10) << "ID"
		<< setw(30) << "Provider Name"
		<< setw(13) << setprecision(2) << "YID Paid"
		<< setw(10) << setprecision(2) << "Amount Due\n";

	// Print report to screen based on ID numbers
	clients.InOrder(fout);

	//close output file
	fout.close();
	cout << sFILE_OUTPUT_NAME << " has been closed.\n\n";

	system("pause");
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Function:   Clear
Pre:        None
Post:       Takes out 100 characters from the buffer but stops if it encounters a newline
*/
void Clear()
{
	cin.clear();
	cin.ignore(100, '\n');
}