#ifndef HASHTABLE2_HPP
#define HASHTABLE2_HPP

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

//template <typename KeyType, typename ValueType>
class HashTable2 {
private:
    static const int MAX_LOOP = 50; 

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

    void rehash() {
        vector<pair<int, string>> old_elements;
        for (const auto& table : tables) {
            for (const auto& entry : table) {
                if (entry.occupied) {
                    old_elements.emplace_back(entry.key, entry.value);
                }
            }
        }
        table_size *= 2;
        tables = vector<vector<Entry>>(2, vector<Entry>(table_size));
        for (const auto& element : old_elements) {
            insert(element.first, element.second);
        }
    }

    size_t hash_function1(const int& key) const {
        return hash1(key) % table_size;
    }

    size_t hash_function2(const int& key) const {
        return hash2(key) % table_size;
    }

    void swap(Entry& a, int& key, string& value) {
        int temp_key = a.key;
        string temp_value = a.value;

        a.key = key;
        a.value = value;

        key = temp_key;
        value = temp_value;
    }

public:
    HashTable2(size_t initial_size = 16)
        : table_size(initial_size) {
        tables = vector<vector<Entry>>(2, vector<Entry>(table_size));
    }

    ~HashTable2() {}

    void insert(const int& key, const string& value) {
        int current_key = key;
        string current_value = value;
        int count = 0;

        while (count < MAX_LOOP) {
            size_t pos1 = hash_function1(current_key);
            if (!tables[0][pos1].occupied) {
                tables[0][pos1] = Entry(current_key, current_value, true);
                return;
            } else {
                swap(tables[0][pos1], current_key, current_value);
            }

            size_t pos2 = hash_function2(current_key);
            if (!tables[1][pos2].occupied) {
                tables[1][pos2] = Entry(current_key, current_value, true);
                return;
            } else {
                swap(tables[1][pos2], current_key, current_value);
            }

            count++;
        }

        rehash();
        insert(current_key, current_value);
    }

    void remove(const int& key) {
        size_t pos1 = hash_function1(key);
        if (tables[0][pos1].occupied && tables[0][pos1].key == key) {
            tables[0][pos1].occupied = false;
            return;
        }

        size_t pos2 = hash_function2(key);
        if (tables[1][pos2].occupied && tables[1][pos2].key == key) {
            tables[1][pos2].occupied = false;
            return;
        }
    }

    void display() const {
        cout << "Cuckoo Hashing:" << endl;
        for (size_t i = 0; i < table_size; ++i) {
            if (tables[0][i].occupied) {
                cout << "(" << tables[0][i].value << ", " << tables[0][i].key << ")" << endl;
            }
        }
    }
};

#endif
