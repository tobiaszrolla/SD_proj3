#ifndef HASHTABLE2_H
#define HASHTABLE2_H

#include <vector>
#include <string>
#include <functional>
#include "HashTable.hpp"

using namespace std;

class HashTable2 :public HashTable
{
private:
    static const int MAX_LOOP = 100;
    const double load_facor{0.3}; 

    struct Entry {
        int key;
        string value;
        bool occupied;

        Entry() : occupied(false) {}
        Entry(int k, string v, bool occ) : key(k), value(v), occupied(occ) {}
    };

    vector<vector<Entry>> tables;
    size_t table_size;
    hash<int> hash1;
    hash<int> hash2;

    void rehash();

    size_t hash_function1(const int& key) const;
    size_t hash_function2(const int& key) const;

    void swap(Entry& a, int& key, string& value);

public:
    HashTable2(size_t initial_size = 2);

    ~HashTable2();

    void insert(int key, string value);

    void remove(int key);

    void display();

    HashTable2(const HashTable2& other);

    HashTable2* clone() const;
};
#endif