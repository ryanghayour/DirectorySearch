// Ryan Ghayour
// November 20th
// Project 2 part 1
// stringProcessing.cpp

#include "stringProcessing.h"

// stripNonAlphaNum
// Parameters: string
// returns: string
// Does: strips nonalphanumeric chars
string stripNonAlphaNum(string toProcess){
	while ((!isalnum(toProcess[0])) and (toProcess.length() > 0)){
		toProcess.erase(0, 1);
	}
	while((!isalnum(toProcess[toProcess.length() - 1])) 
	 and (toProcess.length() > 0)){
		toProcess.erase(toProcess.length() - 1, 1);
	}
	return toProcess;
}

int main(){
	string toProcess;
	while (cin >> toProcess){
		string word = stripNonAlphaNum(toProcess);
		cout << word << endl;
	}
}
