#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cctype>
using namespace std;

struct Word {
	Word * next;
	string str;
};

class Dictionary {
	public:
		Dictionary(int size);
		void add(string str2);
		void printAll();
		void findFamily(string base, int degree);
		int getArraySize();
	private:
		Word ** index;
		int arraySize;
		int getDistance(string s1, string s2);
};