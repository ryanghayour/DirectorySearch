/*
Name: Ryan Ghayour
Assignment: Proj 2 (Gerp)
Due Date: December 6, 2019
File: hashTable.cpp: This file contains functions pertaining to hashTable.cpp.
					 These functions create a hashtable, sort, resort, and
					 expand it, and traverse the tree and print words within it
*/

#include "hashTable.h"

// hashtable constructor
// Parameters: dirnode
// Returns: none
// Does: constructs a hashtable
hashTable::hashTable(DirNode *root){
	numElements = 0;
	addresses.resize(0);
	dictionary.resize(1000);
	traverseDirectories(root);
}

// desens
// Parameters: string
// Returns: string
// Does: makes a string lowercase
string hashTable::desens(string toProcess){
	for (int i = 0; i < (int)toProcess.size(); i++){
		toProcess[i] = tolower(toProcess[i]);
	}
	return toProcess;
}

// traverseDirectories
// Parameters: Dirnode
// Returns: none
// Does: recursively reads in files from a directory, constructs hashtable.
void hashTable::traverseDirectories(DirNode *root){
	for (int i = 0; i < root->numFiles(); i++){
		readFile(root->getFile(i), root);
	}
	for (int i = 0; i < root->numSubDirs(); i++){
		traverseDirectories(root->getSubDir(i));
	}
}

// printWordd
// Parameters: word to search, ofstream, whether case insensitive or not
// Returns: bool
// Does: Prints out all locations of given word in hashtable.
bool hashTable::printWord(string word, ofstream &clout, bool insensitive){
	bool found = false;
	if (insensitive){
		for (size_t i = 0; i < dictionary[wordHash(desens(word))%dictionary
		.size()].list.size(); i++){
			if (desens(dictionary[wordHash(desens(word))%dictionary.size()]
			.list[i].word) == desens(word)){
				found = true;
				for (size_t j = 0; j < dictionary[wordHash(desens(word))%
				dictionary.size()].list[i].directory.size(); j++){
					clout << addresses[dictionary[wordHash(desens(word))%
					dictionary.size()].list[i].directory[j]] << endl;
				} 
			}
		}
	}
	else{
		for (size_t i = 0; i < dictionary[wordHash(desens(word))%dictionary
		.size()].list.size(); i++){
			if (dictionary[wordHash(desens(word))%dictionary.size()]
			.list[i].word == word){
				found = true;
				for (size_t j = 0; j < dictionary[wordHash(desens(word))%
				dictionary.size()].list[i].directory.size(); j++){
					clout << addresses[dictionary[wordHash(desens(word))%
					dictionary.size()].list[i].directory[j]] << endl;
				}
			}
		}
	}
	return found;
}

// expand
// Parameters: none 
// Returns: none
// Does: doubles size of hashtable and redistributes values within it
void hashTable::expand(){
	int oldSize = dictionary.size();
	dictionary.resize(2*dictionary.size());
	for (int i = 0; i < oldSize; i++){
		for (size_t j = 0; j < dictionary[i].list.size(); j++){
			wordNode temp = dictionary[i].list[0];
			dictionary[i].list.erase(dictionary[i].list.begin() + 0);
			dictionary[wordHash(desens(temp.word))%dictionary.size()].
			list.push_back(temp);
		}
	}
}

// addWord
// Parameters: word, line to print for word
// Returns: none
// Does: adds word to hashtable based on hash value
void hashTable::addWord(string word, string line){
	if (5*numElements/4 > (int)dictionary.size()){
		expand();
	}
	int location = addresses.size();
	addresses.push_back(line);
	bool found = false;
	for (size_t i = 0; i < dictionary[wordHash(desens(word))%dictionary.size()]
		.list.size(); i++){
		if (dictionary[wordHash(desens(word))%dictionary.size()].list[i].word 
			== word){
			dictionary[wordHash(desens(word))%dictionary.size()].list[i]
			.directory.push_back(location);
			found = true;
		}
	}
	if (!found){
		wordNode current;
		current.word = word;
		current.directory.push_back(location);
		dictionary[wordHash(desens(word))%dictionary.size()].list
		.push_back(current);
	}
	numElements++;
}

// strip NonAlphaNum
// Parameters: string
// Returns: string
// Does: strips nonalphanum off of ends of string
string hashTable::stripNonAlphaNum(string toProcess){
	while ((!isalnum(toProcess[0])) and (toProcess.length() > 0)){
		toProcess.erase(0, 1);
	}
	while((!isalnum(toProcess[toProcess.length() - 1])) 
	 and (toProcess.length() > 0)){
		toProcess.erase(toProcess.length() - 1, 1);
	}
	return toProcess;
}

// readFile
// Parameters: filename, dirnode
// Returns: none
// Does: takes a file and adds every word within it to the hash table
void hashTable::readFile(string filename, DirNode *current){
	while (current != NULL){
	filename = current->getName() + "/" + filename;
	current = current->getParent();
	}
	ifstream in(filename);
	if (!in){
		cerr << "File cannot be opened\n";
		exit(1);
	}
	int lineNumber = 1;
	while (!in.eof()){
		string currLine;
		getline(in, currLine);
		stringstream ss(currLine);
		string word;
		while (ss >> word){
			word = stripNonAlphaNum(word);
			addWord(word, writeLine(currLine, lineNumber, filename));
		}
		lineNumber++;
	}
	in.close();
}

// writeLine
// Parameters: sentence, line number, filename
// Returns: string
// Does: creates a printable address
string hashTable::writeLine(string sentence, int lineNum, string filename){
	string line = filename + ":" + to_string(lineNum) 
	+ ": " + sentence;
	return line;
}
