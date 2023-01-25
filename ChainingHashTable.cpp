#include "ChainingHashTable.h"
#include <fstream>
#include <exception>
#include <iostream>

unsigned int ChainingHashTable::hash(std::string key) {
    return Hash::PRH24(key) % capacity;
}

void ChainingHashTable::insert(std::string key, int val) {

    unsigned int index = hash(key);
	Cell<std::string, int>* currnode = (data + index);

    // if empty space in data, just insert
    if (!currnode) {
        (data[index]).key = key;
		(data[index]).value = val;
        size++;
        return;
    }

    // loop thru chained linked list to find matching key
	while (currnode) {
		if (currnode->key == key) {
            currnode->value ++;
			return;
		}
		if (currnode->next == nullptr) break;
		else currnode = currnode->next;
	}

    // collision case chains at the end if not found key in chain
	Cell<std::string, int>* newNode = new Cell<std::string, int>(key, val, nullptr);
	currnode->next = newNode;

}


int ChainingHashTable::remove(std::string key) {

    unsigned int index = hash(key);
    Cell<std::string, int>* root = (data + index);
    Cell<std::string, int>* prevnode = (data + index);
    Cell<std::string, int>* currnode = (data + index);

    while (currnode) {
        if (currnode->key == key) {
            if (currnode == root && root->next == nullptr) {
                (data[index]).next = nullptr;
                size--;
                return currnode->value;
            } else if (currnode == root) {
                int val = currnode->value;
                (data[index]).value = root->next->value;
                (data[index]).key = root->next->key;
                (data[index]).next = root->next->next;
                size--;
                return val;
            }
            int val = currnode->value;
            prevnode->next = currnode->next;
            delete currnode;
            size--;
            return val;
        }
        prevnode = currnode;
        currnode = currnode->next;
    }
    throw std::runtime_error("key to remove not found");
}


int ChainingHashTable::get(std::string key) {
    int index = hash(key);
    Cell<std::string, int>* currnode = (data + index);

    while (currnode) {
        if (currnode->key == key)
            return currnode->value;
        currnode = currnode->next;
    }
    return 0;
} 


void ChainingHashTable::printAll(std::string filename) {

    std::ofstream output_file_stream;

    // opens file
    output_file_stream.open(filename);

    // file validation
    if (!output_file_stream.is_open()) {
        std::cerr << "Unable to open output file." << std::endl;
        return;
    }
    
    Cell<std::string, int>* currnode = data;
    for (int i = 1; i <= capacity; i++) {
        output_file_stream << "[" << i-1 << "]     ";
        while (currnode) {
          if (currnode->key != "") {
            output_file_stream << "[KEY: " << currnode->key << "   VALUE: " << currnode->value << "]";
            if (currnode->next) {
              output_file_stream << "  --->  ";
            }
          }
          currnode = currnode->next;
        }
        output_file_stream << "\n";
        currnode = data + i;
    }
}
