// Ryan Ghayour
// November 20th
// Project 2 part 1
// FSTreeTraversal.cpp

#include "DirNode.h"
#include "FSTree.h"
#include <iostream>
using namespace std;

void printTree(DirNode *root);

int main(int argc, char *argv[]){
	if (argc != 2){
		cerr << "Incorrect input, use ./treeTraversal Directory\n";
		exit(1);
	}
	string directory = argv[1];
	FSTree tree(directory);
	printTree(tree.getRoot());
	return 0;
}

// printTree
// parameters: dirnode
// returns: none
// Does: prints tree
void printTree(DirNode *root){
	for (int i = 0; i < root->numFiles(); i++){
		string output = root->getName() + "/" + root->getFile(i);
		DirNode *curr = root->getParent();
		while (curr != NULL){
			output = curr->getName() + "/" + output;
			curr = curr->getParent();
		}
		cout << output << endl;
	}
	for (int i = 0; i < root->numSubDirs(); i++){
		printTree(root->getSubDir(i));
	}
}
