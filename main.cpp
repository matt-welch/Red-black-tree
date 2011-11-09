/*
 * main.cpp
 *
 *  Created on: Oct 11, 2011
 *      Author: mwelch
 *
 * 6. You should implement a main function which takes the following commands from the key-board:
 *
 * C	create an empty tree (RBTree())
 * R	read in the tree stored in RBinput.txt, then wait for input
 * W	write the current tree to the screen in pre-order format (root, left, right)
 * I n	inserts a new node with data n into the current red-black tree and perform the corresponding
 * 		fixes, and waits for the next command. Insertion is only performed when there is no node in
 * 		the tree with data field equal to n.  When there is already such a node, your program should
 * 		print out a line ”node already in the tree” and wait for the next command.
 * D n	delete the node with data n, perform the necessary fix-up, and waits for the next command.
 * 		If there is no node with data field equal to n, the program prints ”no such node in the tree”
 * 		and waits for the next command.
 * S	stop program

 */
#include "RBTree.hpp"
//#include <stdio.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::cin;
using std::ifstream;


int main()
{
	// print a welcome message
	// ask the user what they want to do (while loop)
	// 		switch statement inside the while loop to choose actions

	int continueFlag = 1;
	char choice;
	string inFileName = "RBInput.txt";
	RBTree *tree;
	ifstream infile;
	stringstream inFileStream;

	do{
		cout << endl << "Hello User, What would you like to do with Red-Black Trees?" << endl;
		cout << "Here are your choices: " << endl <<
				"(C)reate a new list (C)" << endl <<
				"(R)ead in a Red-Black Tree from RBInput.txt (R)" << endl <<
				"(W)rite an existing Red-Black Tree to the screen (W)" << endl <<
				"(I)nsert a new integer node into the tree (I n)" << endl <<
				"(D)elete the node with data field equal to n (D n)" << endl <<
				"(S)top program (S)" << endl;
		cout << "Enter a choice from above: ";
		cin >> choice;

		switch(choice){
		case 'C':
			// create a new RBTree
			tree = new RBTree();
			if(!tree){cout << endl <<"A new tree has been created" << endl;}
			else{cout << endl << "A problem occurred when creating your tree..." << endl;}
			break;
		case 'R':
			// read in a RBTree from RBinput.txt
			infile.open(inFileName.c_str());//2nd arg: ifstream::in

			if(infile.fail()){
				cout << endl <<"An error occurred while reading from the file \""
						<< inFileName << "\"." << endl;}
			else{
				// pull RBTree data from file, send to RBTree-Build function??
				while (infile.good() && !infile.eof() ){
					inFileStream << infile.get();
				}
				// infile >> char >> int; // another way to read in
				infile.close();
				cout << endl <<"A tree has been read in from the file \"" <<
						inFileName << "\"." << endl;}
			break;
		case 'W':
			// write out a RBTree to the screen in pre-order
			if(tree == NULL){
				cout << endl <<"No tree exists yet, you should make one first..." << endl;
			}else {
				cout << endl <<"A tree has been written to the screen, isn't it pretty??" << endl;
				cout << tree->RBWrite(tree->GetRoot()) << endl;
			}
			break;
		case 'I':
			if(tree == NULL){
				cout << endl <<"No tree exists yet, you should make one first..." << endl;
			}else {
				cout << endl <<"A new node with the value ?? has been inserted into the tree" << endl;
			}
			break;
		case 'D':

			if(tree == NULL){
				cout << endl <<"No tree exists yet, you should make one first..." << endl;
			}else {
				cout << endl <<"The node containing the value ?? has been deleted" << endl;
			}
			break;
		case 'S':
			cout << endl <<"Stopping the Red-Black Tree program..." << endl;
			continueFlag = 0;
			// clean everything up here
			break;
		default:
			cout << endl <<"The requested option, \"" << choice << "\" is not a valid selection, try again..." << endl;
			break;
		}
	}while(continueFlag);

	// goodbye message
	cout << endl << endl << "Thanks for using Red-Black Trees! Goodbye!" << endl << endl;
	return 0;
}

#if 0
// "Magic Formula" for formatting cout & outFile streams
cout.setf(ios::fixed)	         outFile.setf(ios::fixed)
cout.setf(ios::showpoint)	     outFile.setf(ios::showpoint)
cout.precision(2)		         outFile.precision(2)
cout.setf(ios::right);
cout.width(6);

//Short cut to call a formatting function.
outFile.setf(ios::right);
outFile << setw(4) << hours << setw(6) << rate;
//need  #include <iomanip>

//To get one character including white space use get.
cin.get(char);
//To get entire line up to the newline use getline.
cin.getline(char, intSize);
//To put out one character use put.
cout.put(char);
// check a-z
isalpha(char);
// check 0-9
isdigit(char);
//check whitespace
isspace(char);
// (checks for uppercase)
isupper(char);
// (checks for lowercase)
islower(char);
tolower(char);
toupper (char);
	#endif
