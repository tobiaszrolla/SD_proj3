#ifndef HASHTABLE3_HPP
#define HASHTABLE3_HPP

#include <iostream>
#include "HashTable.hpp"
#include "AVLtree.hpp"

using namespace std;

class HashTable3 : public HashTable {
private:
    static const int hashGroups = 10;
    AVLTree* table[hashGroups];

    int hashFunction(int key);

public:
    HashTable3();
    ~HashTable3();

    void insert(int key, string value);
    void remove(int key);
    void display();
    HashTable3(const HashTable3 &other);
    HashTable3* clone() const;
};

#endif
