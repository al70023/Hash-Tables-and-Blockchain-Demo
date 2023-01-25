#include "Block.h"
#include <vector>
#include <fstream>

int main() {

    std::string transaction;

    std::vector<std::string> v;

    // get cin lines while cin is not empty
    while (getline(std::cin, transaction)) {
        if (transaction == "")
            break;
        v.push_back(transaction); 
        transaction = "";
    }

    Block* prev = nullptr;

    // loop thru vector of transactions and create linked blocks
    for (size_t i = 0; i < v.size(); i++) {
        Block* curr = new Block(v[i], prev);
        curr->mining(v[i]);
        prev = curr;
    }  

    Block* curr = prev;

    std::ofstream output_file_stream;

    // opens file
    output_file_stream.open("output_blockchain.txt");

    // file validation
    if (!output_file_stream.is_open()) {
        std::cerr << "Unable to open output file." << std::endl;
        return 0;
    }

    // print traversing backwards
    int i = v.size();
    while (curr) {
        output_file_stream << "BLOCK " << i << "\n";
        output_file_stream << "-----------" << "\n";
        output_file_stream << *curr << "\n";
        curr = curr->get_prev();
        i -= 1;
    }

    // free memory of blocks
    while (prev) {
        Block* nextprev = prev->get_prev();
        delete prev;
        prev = nextprev;
    }


    return 0;
}