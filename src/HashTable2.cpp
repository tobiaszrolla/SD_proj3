#include "../include/HashTable2.hpp"

void HashTable2::rehash() {
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

size_t HashTable2::hash_function1(const int& key) const {
    return hash1(key) % table_size;
}

size_t HashTable2::hash_function2(const int& key) const {
    return hash2(key) % table_size;
}

void HashTable2::swap(Entry& a, int& key, string& value) {
    int temp_key = a.key;
    string temp_value = a.value;

    a.key = key;
    a.value = value;

    key = temp_key;
    value = temp_value;
}

HashTable2::HashTable2(size_t initial_size)
    : table_size(initial_size) {
    tables = vector<vector<Entry>>(2, vector<Entry>(table_size));
}

HashTable2::~HashTable2() {}

void HashTable2::insert(int key, string value) {
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

void HashTable2::remove(int key) {
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

void HashTable2::display(){
    cout << "Cuckoo Hashing:" << endl;
    for (size_t i = 0; i < table_size; ++i) {
        if (tables[0][i].occupied) {
            cout << "(" << tables[0][i].value << ", " << tables[0][i].key << ")" << endl;
        }
    }
}

HashTable2::HashTable2(const HashTable2& other)
    : table_size(other.table_size), hash1(other.hash1), hash2(other.hash2) {
        /*
            Konstruktor kopiujący głęboki
        */
    tables = other.tables; 
}

HashTable2* HashTable2::clone() const {
    /*
        Pozwala na kopiowanie klasie bazowej
    */
    return new HashTable2(*this); 
}
