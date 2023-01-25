#pragma once
#include "Hash.h"
// #include "Hash.cpp"
#include <string>
#include <iostream>
#include <sstream>

// helper function to check if a hash begins with '2'
bool validate_hash(unsigned int h) {
	std::string proposed = std::to_string(h);
	if (proposed.rfind("2",0) == 0) { return true; }
	else { return false; }
}

// building block of a blockchain signed by the validator above (hashes start with '2')
class Block {
private:
	std::string transaction;

	Block* prev;
	unsigned int prev_hash;
	bool valid = false;

public:
	std::string nonce;
	unsigned int hash;

	// transaction and previous block setup at construction time and not changed
	Block(std::string t, Block* p) {
		transaction = t;
		prev = p;
		if (p) {
			prev_hash = p->hash;
		} else {
			prev_hash = 0; // first block in the chain has prev_hash of 0
		}
		nonce = "";
		hash = 0;
		valid = false;
	}

	// support singly-linked list operation
	Block* get_prev() {
		return prev;
	}

	// helper to get previous block hash (is 0 for first block with null prev)
	std::string get_prev_hash() {
		return std::to_string(prev_hash);
	}

	// sign the block using the provided nonce relative the hash requirement (start with '2')
	bool sign_block(std::string n) {
		std::string contents = transaction + get_prev_hash() + n;
		unsigned int h = Hash::PRH24(contents);
		if (validate_hash(h)) {
			nonce = n;
			hash = h;
			valid = true;
			return true;
		} else {
			valid = false;
			return false;
		}
	}

	void mining(std::string transaction) {
		std::string nonce = "!";
		bool valid  = sign_block(nonce);
		while (!valid) {
			std::stringstream ss;
			int a = int(nonce[0]);
			a += 1;
			ss << a;
			char x = char(a);
			nonce = x;
			valid = sign_block(nonce);
		}
	}

	// used to print comma-separated block contents
	friend std::ostream& operator<<(std::ostream& os, const Block& b);
};

std::ostream& operator<<(std::ostream& os, const Block& b) {
	os << "TRANSACTION: " << b.transaction 
		<< "\nPREV. HASH: " << b.prev_hash 
		<< "\nNONCE: " << b.nonce 
		<< "\nHASH: " << b.hash 
		<< std::endl;
	return os;
}