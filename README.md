This program takes any given directory and reads in every file, storing the words in each file. This allows for a relatively rapid search of the hash table in order to find the location of any requested word. This program essentially allows the user to search for words within their directory using a hash table.

Important files to note:
  hashtable.h: Header file for hashtable class
  hashtable.cpp: hashtable class, creates and manipulates a hashtable
  main.cpp: main function, takes in user input and searches created hashtable
  
  The primary data structure I used for this assignment was a hashtable. In the private section of my class there is a vector of wordlists, or a hashtable, a vector of addresses, which are stored there for storage purposes, an stl hash function, and a count of the number of words stored. Each wordlist serves as a bucket for the hashtable, containing words that map to the same hashvalue. Words that are the same when made lowercase are stored in the same bucket. Each of these wordlists contains multiple wordnodes, which contain the word and indices of the address array. The address array contains the full lines that would be printed to the output file. My expand function expands the hashtable and redistributes values within the hashtable. traverseDirectories is a function that recursively builds the hashtable. printWord also serves as a search function.
