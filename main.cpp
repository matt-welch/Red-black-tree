/********************************************************************************************
 * Red-Black Tree Driver:
 * AUTHOR: 	James Matthew Welch [JMW]
 * CLASS:	CSE310
 * SECTION:	71409
 *
 * All Red-Black Tree methods, when possible, are adapted from pseudocode provided in
 * _Introduction_to_Algorithms_ (Cormen, Leiserson, Rivest & Stein)
 *
 * Some code-conventions taken from CSE220: Programming from Computer Engineering
 * and from C++ Programming Practicum (Fall 11)
 *
 ********************************************************************************************/

/*
 * main.cpp
 *
 *  Created on: Oct 11, 2011
 *      Author: mwelch

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

// uncomment following #define to enable debug printing during tree-read
//#define DEBUG

#include "RBTree.hpp"
#include <stdlib.h>
#include <stdint.h>
#include <string>

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <fstream>
using std::ifstream;

// beginning of Red-Black Tree driver
int main(){

	int continueFlag = 1;
	char choice;

	RBTree* tree = new RBTree();
	ifstream infile;
	string inFileName = "RBinput.txt";
	const int maxNodes = 1000;  // read in up to 1000 nodes stored in the text input file
	Color colors[maxNodes];
	int data[maxNodes];
	int key;
	int numNodes;
	string token;

	cout << endl << ":::Red-Black Tree:::" << endl;
	cout << "Welcome to the Red-Black Tree program!!" << endl;

	do{
		cout << endl << "Choose which option you would like to perform with Red-Black Trees." << endl;
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
		case 'C': // create a new RBTree
			// create a new tree if one does not exist
			if(tree){
				//if a tree already exists, delete it
				delete tree;
			}

			tree = new RBTree();
			if(tree){cout << endl <<"A new tree has been created" << endl;}
			else{cout << endl << "A problem occurred when creating your tree..." << endl;}
			break;

		case 'R': // read in a RBTree from RBinput.txt
			// set numNodes (already read in) to 0
			numNodes = 0;

			// use a char instead
			infile.open((char*)inFileName.c_str()); //2nd arg: ifstream::in

			if(infile.fail()){
				cout << endl <<"An error occurred while reading from the file \""
						<< inFileName << "\"." << endl;}
			else{
				//if a tree already exists, delete it
				if(tree){
					delete tree;
				}

				// create a new tree
				tree = new RBTree();

				//initialize color and data arrays
				for(int i=0;i<maxNodes;++i){
					colors[i]=RED;
					data[i]=-1;
				}

				// pull RBTree data from file
				while (infile.good() && !infile.eof() ){
					// parse color and key tokens from theinput file
					infile >> token;
					if(!token.empty()) {
						colors[numNodes] = ( (token[0] == 'r') ? RED : BLACK );
#ifdef DEBUG
						cout << "colorStr: " << token[0];
						cout << "||char: " << colors[numNodes];
#endif
					}
					infile >> token;
					if(!token.empty()) {
						data[numNodes] = atoi(token.c_str());
#ifdef DEBUG
						cout <<"||dataStr: " << token << "||data: "<< data[numNodes] << endl;
#endif
						++numNodes;
					}
					token = "";
				}
				infile.close();

				cout << endl <<"A tree has been read in from the file \"" << inFileName << "\"." << endl;
				// now put the data into the tree in pre-order format
				int index = tree->RBTree::RBInsertFromList(data, colors, numNodes);

				if(index < numNodes){
					cout << "Some nodes were lost during read...not good" << endl;
					exit(1);
				}
			}

			break;

		case 'W': // write out a RBTree to the screen in pre-order formats
			if(tree == NULL){
				cout << endl <<"No tree exists yet, you should make one first..." << endl;
			}else {
				tree->RBTree::RBWrite();
				cout << endl <<"A Red-Black tree has been written to the screen in pre-order format." << endl;
			}
			break;

		case 'I':
			/* On reading I n, the program
			inserts a new node with data n into the current red-black tree and perform the corresponding
			fixes, and waits for the next command. Insertion is only performed when there is no node in
			the tree with data field equal to n. When there is already such a node, your program should
			print out a line ”node already in the tree” and wait for the next command. */
			cin >> key;

			if(!tree->RBTree::IsValid()){
				cout << endl <<"No tree exists yet, you should make one first..." << endl;
			}else {
				if(key < 0){
					cout << "Only insert positive integers please...(" << key << ")" << endl;
				}else {
					if(tree->RBTree::RBInsert(key)){
						cout << endl <<"A new node with the value " << key << " has been inserted into the tree" << endl;
					}else {
						cout << endl <<"A node containing value \"" << key << "\" is already in the tree" << endl;
					}
				}
			}
			break;

		case 'D':// input: D n
			// delete the node with data value matching the integer key 'n'
			cin >> key;

			// make sure tree is not NULL
			if(tree == NULL){
				cout << endl <<"No tree exists yet, you should make one first..." << endl;
				break;
			}

			// check that tree is valid (instantiated)
			if(!tree->RBTree::IsValid()){
				cout << endl <<"No tree exists yet, you should make one first..." << endl;
			}else {
				if(key < 0){
					cout << endl <<"Only delete positive integers please...(" << key << ")" << endl;
				}else {
					int delKey = tree->RBTree::Delete(key);
					if(delKey == -1){
						cout << endl <<"No node containing the key \"" << key << "\" was found in the tree." << endl;
					}else if ( delKey != key){
						// this should never happen
						cout << endl << "A node containing data value \"" << delKey << "\" was found in the tree." << endl;
						cout << "This node should not have been deleted from the tree" << endl;
					}else{
						cout << endl <<"A node with the value \"" << key << "\" has been deleted from the tree" << endl;
					}
				}
			}
			break;

		case 'S':
			cout << endl <<"Stopping the Red-Black Tree program..." << endl;
			continueFlag = 0;

			break;

		default:
			cout << endl <<"The requested option, \"" << choice << "\" is not a valid selection, try again..." << endl;
			break;
		}
	}while(continueFlag);

	// goodbye message
	cout << endl << endl << "Thanks for using Red-Black Trees! Goodbye!" << endl << endl;

	// clean everything up here
	delete(tree);

	return 0;
}
