#include "ProbingHashTable.h"
#include <fstream>
#include <exception>
#include <iostream>

unsigned int ProbingHashTable::hash(std::string key) {
    return Hash::PRH24(key) % capacity;
}

void ProbingHashTable::insert(std::string key, int val) {
    unsigned index = hash(key);

    // probe down for an empty spot to insert or if found key, update val
    for (int i = 0; i < capacity; i++) {
        if (data[index].key == "") {
            data[index].value = val;
            data[index].key = key;
            size ++;
            return;
        }
        if (data[index].key == key) {
            data[index].value ++;
            return;
        }
        index = (index + 1) % capacity;
    }

}


int ProbingHashTable::remove(std::string key) {

    unsigned index = hash(key);

    // if found at hash
    if ((data + index)->key == key) {
        (data + index)->key = "";
        int val = (data + index)->value;
        (data + index)->value = 0;
        size --;
        return val;
    }

    // if not found at hash, probe down array 
    for (int i = 1; i <= capacity; i++) {
        index = (index + i) % capacity;

        if ( (data + index)->key == key) {
            (data + index)->key = "";
            int val = (data + index)->value;
            (data + index)->value = 0;
            size --;
            return val;
        }
    }

    throw std::runtime_error("key to remove not found");
}


int ProbingHashTable::get(std::string key) {
    unsigned index = hash(key);

    for (int i = 0; i <= capacity; i++) {
        index = (index + i) % capacity;
        if (data[index].key == key) 
            return data[index].value;
        if (data[index].key == "")
            return 0; 
    }

    return 0;
} 


void ProbingHashTable::printAll(std::string filename) {

    std::ofstream output_file_stream;

    // opens file
    output_file_stream.open(filename);

    // file validation
    if (!output_file_stream.is_open()) {
        std::cerr << "Unable to open output file." << std::endl;
        return;
    }
    
    for (int i = 0; i < capacity; i++) {
        output_file_stream << "[" << i << "]     ";

        if ((data + i)->key != "") {

            if (hash((data + i)->key) != i) {
                output_file_stream << "   ---- (PROBED DOWN) ----   ";
            }

            output_file_stream << "[KEY: " << (data + i)->key << "   VALUE: " << (data + i)->value 
            << "   HASH: " << hash((data + i)->key) << "]";
        }

        output_file_stream << "\n";        
    }
}
