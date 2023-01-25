#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <cassert>

#include "ProbingHashTable.h"
// #include "ChainingHashTable.h"

using namespace std;

int main() {
	// open the text file
	ifstream readDictionary;
	readDictionary.open("dictionary.txt");
	string s;

	// make sure file is opened
	assert(readDictionary.is_open());
	cout << "file opened" << endl;

	// start timer
	auto start = std::chrono::high_resolution_clock::now();
	cout << "timer started" << endl;

	ProbingHashTable h = ProbingHashTable(60000);
	// ChainingHashTable h = ChainingHashTable(60000);

	cout << "new table made" << endl;

	// read the text file
	while (readDictionary >> s) {
		
		h.insert(s, h.get(s)+1);
	}

	cout << "table operations done" << endl; 

	auto stop = std::chrono::high_resolution_clock::now();
	cout << "timer stopped" << endl;

	cout << "results printed to file" << endl;
	h.printAll("output_probing.txt");

	readDictionary.close();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	cout << "DONE with elapsed time " << duration.count() << endl;

}