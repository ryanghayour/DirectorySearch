/*
Name: Ryan Ghayour
Assignment: Proj 2 (Gerp)
Due Date: December 6, 2019
File: hashTable.h: This file contains the hashtable class, which creates, 
				   manipulates, and searches a tree. The private section
				   contains a track of the number of elements in the hashtable,
				   a list of line addresses, a hashtable, and a stl hash
				   function.
*/

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "DirNode.h"
#include "FSTree.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


struct wordNode{
	string word;
	vector<int> directory;
};

struct wordList{
	vector<wordNode> list;
};

class hashTable{
public:
	hashTable(DirNode *root);
	void addWord(string word, string line);
	void readFile(string filename, DirNode *current);
	string writeLine(string sentence, int lineNum, string filename);
	void traverseDirectories(DirNode *root);
	bool printWord(string word, ofstream &clout, bool insensitive);
	void expand();
	string stripNonAlphaNum(string toProcess);
	string desens(string toProcess);
private:
	hash<string> wordHash;
	vector<wordList> dictionary;
	int numElements;
	vector<string> addresses;
};

#endif
