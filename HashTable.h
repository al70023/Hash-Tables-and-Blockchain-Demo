#pragma once

// data struct for holding cell information
template <typename T, typename U>
struct Cell {
	T key;
	U value;
	Cell* next;
	Cell() : key(), value(), next(nullptr) {};
	Cell(T k, U v, Cell* n) : key(k), value(v), next(n) {};
};

// hash table base
// TODO: add templated key and value types for base HashTable class

template <typename T, typename U>
class HashTable{
protected:
	int size;
	int capacity;

public: 
	HashTable() : size(0), capacity(0) {}

	bool empty() const {return size == 0;}
	// TODO: overload the subscript operator, which is operator[]
	// The delcaration will look similar to U operator[](T k) for templated types T and U
	// Define the function to simply return the get() operation on the key
	U operator[] (T key) { return get(key); }

	virtual ~HashTable() {}

	virtual unsigned int hash(T key) = 0;

	// TODO: complete the pure virtual declarations for insert, remove, and get
	virtual void insert (T key, U val) = 0;
	virtual U remove(T key) = 0;
	virtual U get(T key) = 0;
};