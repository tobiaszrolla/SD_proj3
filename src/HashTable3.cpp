#include "../include/HashTable3.hpp"

int HashTable3::hashFunction(int key) {
    return key % hashGroups;
}

HashTable3::HashTable3() {
    for (int i = 0; i < hashGroups; i++) {
        table[i] = new AVLTree();
    }
}

HashTable3::~HashTable3() {
    for (int i = 0; i < hashGroups; i++) {
        delete table[i];
    }
}

void HashTable3::insert(int key, string value) {
    int hashValue = hashFunction(key);
    table[hashValue]->root = table[hashValue]->insert(table[hashValue]->root, key, value);
}

void HashTable3::remove(int key) {
    int hashValue = hashFunction(key);
    table[hashValue]->root = table[hashValue]->remove(table[hashValue]->root, key);
}

void HashTable3::display() {
    cout << "Separate Chaining:" << endl;
    for (int i = 0; i < hashGroups; i++) {
        if (table[i]->root != nullptr) {
            table[i]->inOrder(table[i]->root);
        }
    }
}

HashTable3::HashTable3(const HashTable3 &other) {
    for (int i = 0; i < hashGroups; i++) {
        table[i] = new AVLTree();
        // głęboka kopia AVLTree, nie tylko przypisanie wskaźnika
        Node* current = other.table[i]->root;
        while (current) {
            insert(current->key, current->value);
            if (current->left) current = current->left;
            else if (current->right) current = current->right;
            else break;
        }
    }
}

HashTable3* HashTable3::clone() const {
    return new HashTable3(*this);
}