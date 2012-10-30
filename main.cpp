#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cctype>
#include "dictionary.h"
using namespace std;

void errorAndExit(string message) {
	cerr << message << endl
	<< "Now exiting" << endl;
	exit(0);
}


//If a word is longer than the dictionary's maximum
//string length, then exit program
void checkWordSize(string newWord, Dictionary *dPt) {
	if (newWord.length() > dPt->getArraySize()) {
		string error = "*Incorrect string length in program arguments*";
		error+=	"\n(Check again that the longest string in your dictionary is ";
		error+=	"accounted for)";
		errorAndExit(error);
	}
}


//Returns true if str is a valid word composed
//of lower case letters in the set {a,b,...,z}
bool isValidWord(string str) {
	if (str =="" ) {
		cerr << "The empty string is not a word" << endl;
		return false;
	}
	for (int i=0; i<str.length(); i++) {
		if(!isalpha(str[i]) || isupper(str[i])){
			string error="*Non-words are not permitted*";
			error+="\nA word is defined recursively as follows:";
			error+="\n-A sequence of one or more letters that is";
			error+="\n followed by another letter or the empty string.";
			error+="\n-If a letter is followed by the empty string, then";
			error+="\n this is the last letter of the word.";
			error+="\nA letter is always lower case, and is in the set {a,b,...,z}.";
			cerr << error << endl;
			return false;
		}
	}
	return true;
}

//Returns true if str is a valid integer
//and is greater than or equal to n 
bool isValidInteger(string str, int n) {
	for (int i=0; i<str.length(); i++) {
		if (!isdigit(str[i])) {
			cerr << "Invalid digit" << endl;
			return false;
		}
	}
	if(atoi(str.c_str()) < n) {
		return false;
	} else {
		return true;
	}
}

//Returns true if str is a valid integer
//and is in the range [lowerBound, upperBound] inclusive
bool isValidInteger(string str, int lowerBound, int upperBound) {
	for (int i=0; i<str.length(); i++) {
		if (!isdigit(str[i])) {
			cerr << "Invalid digit" << endl;
			return false;
		}
	}
	int num = atoi(str.c_str());
	if(num < lowerBound || num > upperBound) {
		cout << "*Invalid integer*" << endl;
		cout << "Cannot specify a negative distance" << endl;
		cout << "Cannot specify distance that is greater than the longest string in the dictionary" << endl;
		return false;
	} else {
		return true;
	}
}

int main(int argc, char **argv) {
	
	//Check args and open file
	string input(argv[1]);
	if (argc!=3 || !isValidInteger(input, 0)) {
		errorAndExit("*Command line error*");
	}
	Dictionary d(atoi(argv[1]));
	ifstream file(argv[2]);
	if(!file.good()){
		errorAndExit("*File input error*");
	}
	bool firstIteration=true;
	
	//Load each word into dictionary and
	//check each word for integrity
	while(file.good()) {
		getline(file,input);
		//Check for empty file on first iteration
		if (firstIteration && input=="" && file.eof()) {
			errorAndExit("*File is empty*");
		}
		if(file.eof()) {
			break;
		}
		checkWordSize(input, &d);
		if (!isValidWord(input)) {
			errorAndExit("");
		}
		d.add(input);
		firstIteration=false;
	}
	file.close();
	
	bool validWord;
	string comparison(""); 
	int distance=0;
	input="dummy";
	
	//Keep interacting with user until user quits
	while (input != "q") {
				
		//Get word from user and validate input
		validWord = false;
		while (!validWord) {
			cout << "Type in a word to compare against the dictionary: ";
			getline(cin, comparison);
			validWord = isValidWord(comparison);
		}

		//Get Levenshtein distance from user and validate input
		bool isValidDistance=false;
		while (!isValidDistance) {
			cout << "Degree of friendship (Levenshtein distance): ";
			getline(cin, input);
			isValidDistance = isValidInteger(input, 0, d.getArraySize());
			if (isValidDistance) {
				distance = atoi(input.c_str());
			}
		}
		
		//Output all words from dictionary with Levenshtein distance of 'distance'
		cout << "Using the base word \"" << comparison << ",\" "
			<< "the following dictionary entries " << endl << "have Levenshtein "
			<< "distance of " << distance << endl;
		d.findFamily(comparison,distance);
	
		//Ask if user wants to continue or quit
		input = "dummy";
		while (input != "q" && input != "y") {
			cout << "Would you like to compare more words[y] or quit[q]? " ;
			getline(cin, input);
			if (input != "q" && input != "y") {
				cout << "Unrecognized command" << endl;
			}
		}
		
	}
	return 0;
}