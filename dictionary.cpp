#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cctype>
#include "dictionary.h"
using namespace std;

//Constructor
//Requires the length of the longest string that you will load
Dictionary::Dictionary(int size) {
	arraySize = size;
	index = new Word*[size];
	for (int i = 0; i < size; i++) {
		index[i] = NULL;
	}
}

int Dictionary::getArraySize() {
	return arraySize;
}

//Adds a new word to the dictionary
void Dictionary::add(string str2) {
	int length = str2.length();
	Word * newElt = new Word;
	if (index[length-1] != NULL) {
		newElt->next = index[length-1];
	} else {
		newElt->next = NULL;
	}
	newElt->str = str2;
	index[length-1] = newElt;
}

//Prints all the words in the dictionary that have
//Levenshtein distance of 'degree' compared to 'base'
void Dictionary::findFamily(string base, int degree) {
	int min = base.length()-degree;
	int max = base.length()+degree;
	if (min < 1) {
		min=degree;
	}
	if (max > arraySize) {
		max = arraySize;
	}
	Word *next = NULL;
	string temp = "";
	for (int i=min; i<=max; i++) {
		next = index[i-1];
		while (next != NULL) {
			temp = next->str;
			if (degree == getDistance(base, temp)) {
				cout << temp << endl;
			}
			next = next->next;
		}	
	}
	cout << endl;
}

//Get the Levenshtein distance between two strings
int Dictionary::getDistance(string s1, string s2) {
	int size1 = s1.length();
	int size2 = s2.length();
	int levArray[size1+1][size2+1];
	levArray[0][0] = 0;
	for (int i=1; i <= size1; i++) {
		levArray[i][0] = i;
	}
	for (int i=1; i<=size2; i++) {
		levArray[0][i] = i;
	}

	for(int row=1; row<=size1; row++) {
		for (int col=1; col <= size2; col++) {
			levArray[row][col] = min( 
									min(levArray[row-1][col]+1, levArray[row][col-1]+1),
										levArray[row-1][col-1]+(s1[row-1]==s2[col-1] ? 0 : 1)); 
		}
	} 	
	return levArray[size1][size2];
}

void Dictionary::printAll() {
	for (int i=0; i < arraySize; i++) {
		cout << endl << "WORDS OF SIZE " << i+1 << endl;
		Word * next = index[i]; 
		while (next !=NULL) {
			cout << next->str << endl;
			next = next->next;
		}
	}
}

