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
//#define DEBUG

// TODO comment everything
// TODO clean up output

#include "RBTree.hpp"
#include <stdlib.h>
#include <stdint.h>
#include <string>

#include <iostream>
#include <fstream>
using std::ifstream;

using std::cout;
using std::endl;
using std::cin;

int main(){

	int continueFlag = 1;
	char choice;

	RBTree* tree = new RBTree();
	ifstream infile;
	string inFileName = "RBinput.txt";
	int maxNodes = 100;
	Color colors[maxNodes];
	int data[maxNodes];
	int key;
	int numNodes = 0;
	string token;

	for(int i=0;i<maxNodes;++i){ colors[i]=RED;data[i]=-1; }

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
		case 'C': // create a new RBTree
			tree = new RBTree();
			if(tree){cout << endl <<"A new tree has been created" << endl;}
			else{cout << endl << "A problem occurred when creating your tree..." << endl;}
			break;

		case 'R': // read in a RBTree from RBinput.txt
			// use a char instead
			infile.open((char*)inFileName.c_str()); //2nd arg: ifstream::in

			if(infile.fail()){
				cout << endl <<"An error occurred while reading from the file \""
						<< inFileName << "\"." << endl;}
			else{
				// create a new tree if one does not exist
				if(!tree){
					tree = new RBTree();
				}

				// pull RBTree data from file
				while (infile.good() && !infile.eof() ){
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
					cout << "Some nodes were lost during read..." << endl;
					exit(1);
				}
			}

			break;

		case 'W': // write out a RBTree to the screen in pre-order
			if(tree == NULL){
				cout << endl <<"No tree exists yet, you should make one first..." << endl;
			}else {
				tree->RBTree::RBWrite();
				cout << endl <<"A tree has been written to the screen, isn't it pretty??" << endl;
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
			// delete the node with data value matching 'n'
			cin >> key;

			if(!tree->RBTree::IsValid()){
				cout << endl <<"No tree exists yet, you should make one first..." << endl;
			}else {
				if(key < 0){
					cout << "Only delete positive integers please...(" << key << ")" << endl;
				}else {
					int delKey = tree->RBTree::Delete(key);
					if(delKey == -1){
						cout << "No node containing the key \"" << key << "\" was found in the tree." << endl;
					}else if ( delKey != key){
						// this should never happen
						cout << "A node containing data value \"" << delKey << "\" was found in the tree." << endl;
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
// C-style file open
static FILE *_file_open(char *filename, char *mode, char *msg) {
    FILE *fstream = fopen(filename, mode);
    if (fstream) return fstream;
    fprintf(stdout, "Cannot open '%s' for %s. Terminating.\n", filename, msg);
    exit(-1); /* Declared in <stdlib.h> */
}
#endif

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
