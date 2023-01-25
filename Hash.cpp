#include "Hash.h"
#include <iostream>

// TODO: implement the hash function (remember to namespace to Hash::)

unsigned int Hash::PRH24(std::string str) {
    unsigned int hash = 0;

    unsigned int p = 1;
    unsigned int m = 16777215;

    for (auto i = str.begin(); i != str.end(); i++) {
        hash = (hash + (p * unsigned(*i)) ) % m;
        p = (p*137) % m;
    }

    return hash;
}