/*
Name: Ryan Ghayour
Assignment: Proj 2 (Gerp)
Due Date: December 6, 2019
File: main.cpp: This main function creates an outfile, creates a tree and a 
			    hashtable based on the tree, then performs various actions 
			    based on user input.
*/

#include "hashTable.h"
#include <iostream>
void testsearch();

int main(int argc, char *argv[]){
	if (argc != 3){
		 cerr << "Usage:  gerp directory output_file\n";
		 return EXIT_FAILURE;
	}
	string DirectoryToIndex = argv[1];
	FSTree tree(DirectoryToIndex);
	hashTable hash(tree.getRoot());
	string OutputFile = argv[2];
	ofstream outfile;
	outfile.open(OutputFile);

	if (!outfile){
		cerr << "Output file could not be opened\n";
		exit(1);
	}
	string input;
	bool ins = false;
	bool file = false;
	cout << "Query? ";
	while (cin >> input){
		if ((input == "@i") or (input == "@insensitive")){
			ins = true;
		}
		else if (input == "@f"){
			file = true;
		}
		else if ((input == "@q") or (input == "@quit")){
			cout << endl << "Goodbye! Thank you and have a nice day.\n";
			outfile.close();
			return 0;
		}
		else if (file == true){
			outfile.close();
			outfile.open(input);
			file = false;
			cout << endl << "Query? ";
		}
		else if (ins == true){
			if (!hash.printWord(input, outfile, true)){
				outfile << input << " Not Found.\n";
			}
			ins = false;
			cout << endl << "Query? ";
		}
		else{
			if (!hash.printWord(input, outfile, false)){
				outfile << input << " Not Found. Try with @insensitive or @i."
				<< endl;
			}
			cout << endl << "Query? ";
		}
	}
}


/*void testsearch(){
	cout << "Input directory: ";
	string input;
	cin >> input;
	FSTree tree(input);
	hashTable hash(tree.getRoot());
	cout << "Search a word homie: ";
	string toSearch;
	cin >> toSearch;
}
*/
