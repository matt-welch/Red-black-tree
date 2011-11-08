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

using std::cout;
using std::endl;
using std::cin;


int main()
{
	// print a welcome message
	// ask the user what they want to do (while loop)
	// 		switch statement inside the while loop to choose actions

	int continueFlag = 1;
	char choice;
	string fileName = "RBInput.txt";
	RBTree *tree;

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
			cout << endl <<"A tree has been read in from the file \"" << fileName << "\"." << endl;
			break;
		case 'W':
			// write out a RBTree to the screen in pre-order
			cout << endl <<"A tree has been written to the screen, isn't it pretty??" << endl;
			cout << "b, 5; r, 1; r 10;" << endl;
			break;
		case 'I':
			cout << endl <<"A new node with the value ?? has been inserted into the tree" << endl;
			break;
		case 'D':
			cout << endl <<"The node containing the value ?? has been deleted" << endl;
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

