*** LEVENSHTEIN DISTANCE ***

This program calculates the Levenshtein Distance for strings.  Given a user-specified string s, and a user-specified distance d, this program will print all words from the dictionary whose Levenshtein distance is d.

COMPILING
This program can be compiled on a unix-based machine using g++.  Given that "dictionary.cpp", "main.cpp", and "dictionary.h" are in the same directory, compile the program using "g++ main.cpp dictionary.cpp".  On most machines, the executable will be called "./a.out"

EXECUTION

Calling the program must be of the form: <PROGRAM_NAME> <INTEGER> <FILENAME> 
	Example: %  ./a.out 45 words.csv


As demonstrated above, the executable must take two arguments (besides the program's own name). All arguments must be separated by any number of spaces.  Program arguments are as follows:
	1) FIRST ARGUMENT: An integer of at least 1.  This integer is the length of the longest string that the dictionary contains.  If this integer is smaller than the longest string, the program will exit.
	2) SECOND ARGUMENT: The name of a plain text file which contains a list of words to load into the dictionary.  The file must be located in the same directory as the executable.  The file must contain one word per line, and cannot have superfluous whitespace.  In other words, the file's first line must contain a word, the file's last line must contain a word, and there can be any number of words between the first and last words in the file. Each word, except for the last word, must be followed by one and only one newline.  The definition of a word is explicated below.

The program is interactive, in that it will ask the user for a string to
compare with, and an integer value which represents a Levenshtein distance.
Once the user gives a word and an integer value N, the program will compare the
user's word with each word in the dictionary, returning only those words which
have a Levenshtein distance N.  After printing to standard output, the program
will ask whether the user wants to continue comparing words, or exit.

A complimentary dictionary is bundled with this folder.

DEFINITIONS

*Words*
A word is defined recursively as follows:
-A sequence of one or more letters, followed by another letter or the empty string
-If a letter is followed by the empty string, then this letter is the last letter of the word
*Note that a letter is always lower case, and is found in the set {a,b,...,z}; note also that the empty string is neither a word nor a letter.

*Dictionary*
The dictionary is an object which contains a list of words.  For this specific
program, the dictionary must first be loaded from a file, and
the dictionary remains in memory until the program exits. 
