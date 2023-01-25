#ifndef CHAINING_H
#define CHAINING_H

#include "HashTable.h"
#include "Hash.h"
#include <string>
#include <vector>

// Linear Chaining hash table class
// TODO: modify the class to use public inheritance from the base class HashTable
// Note that you'll need to specify the key and value types to instantiate the template
class ChainingHashTable:public HashTable<std::string, int> {
private:
    // TODO: create the table data member, should be a list of Cell objects (defined in HashTable.h)
    // You may create a pointer and use a dynamic array or vector
    // For the dynamic array, manage new and delete with the constructors and destructors
    // For the vector, be sure to set the size to capacity in the constructor so you can direct index
    Cell<std::string, int>* data;

public: 
    // TODO: add the constructors & destructors as specified
    ChainingHashTable() : data(new Cell<std::string, int>[0]) {
        capacity = 0;
        size = 0;
    }

    ChainingHashTable(int cap) : data(new Cell<std::string, int>[cap]) {
        capacity = cap;
        size = 0;
    }

    ~ChainingHashTable() {
        Cell<std::string, int>* root = nullptr;
		Cell<std::string, int>* curr = nullptr;

		for (int i = 0; i < capacity; i++) {
			root = data + i;
			curr = root->next;
			while (curr) {
				Cell<std::string, int>* next = curr->next;
				delete curr;
				curr = next;
			}
		}

        size = 0;
        capacity = 0;
		delete[] data;
    }

    unsigned int hash(std::string key);
    void insert(std::string key, int val); 
    int remove(std::string key); 
    int get(std::string key); 
    void printAll(std::string filename);


    // TODO: include declarations to override the pure vritual functions from the base class
};

#endif