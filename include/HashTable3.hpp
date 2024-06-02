#ifndef HASHTABLE3_HPP
#define HASHTABLE3_HPP

#include <iostream>

using namespace std;

struct Node {
    int key;
    string value;
    Node* left;
    Node* right;
    int height;

    Node(int k, string v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    int height(Node* N) {
        return (N == nullptr) ? 0 : N->height;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    int getBalance(Node* N) {
        return (N == nullptr) ? 0 : height(N->left) - height(N->right);
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }
public:
    Node* root;

    AVLTree() : root(nullptr) {}

    Node* insert(Node* node, int key, string value) {
        if (node == nullptr) {
            return new Node(key, value);
        }

        if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        } else {
            node->value = value;
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key) {
            return rightRotate(node);
        }
        if (balance < -1 && key > node->right->key) {
            return leftRotate(node);
        }
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* remove(Node* root, int key) {
        if (root == nullptr) return root;

        if (key < root->key) {
            root->left = remove(root->left, key);
        } else if (key > root->key) {
            root->right = remove(root->right, key);
        } else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                Node* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->value = temp->value;
                root->right = remove(root->right, temp->key);
            }
        }

        if (root == nullptr) return root;

        root->height = 1 + max(height(root->left), height(root->right));
        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0) {
            return rightRotate(root);
        }
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0) {
            return leftRotate(root);
        }
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void inOrder(Node* root) {
        if (root != nullptr) {
            inOrder(root->left);
            cout << "(" << root->value << ", " << root->key << ")" << endl;
            inOrder(root->right);
        }
    }
};

class HashTable {
private:
    static const int hashGroups = 10;
    AVLTree* table[hashGroups];

    int hashFunction(int key) {
        return key % hashGroups;
    }

public:
    HashTable() {
        for (int i = 0; i < hashGroups; i++) {
            table[i] = new AVLTree();
        }
    }

    ~HashTable() {
        for (int i = 0; i < hashGroups; i++) {
            delete table[i];
        }
    }

    void insert(int key, string value) {
        int hashValue = hashFunction(key);
        table[hashValue]->root = table[hashValue]->insert(table[hashValue]->root, key, value);
    }

    void remove(int key) {
        int hashValue = hashFunction(key);
        table[hashValue]->root = table[hashValue]->remove(table[hashValue]->root, key);
    }

    void display() {
        cout << "Separate Chaining:" << endl;
        for (int i = 0; i < hashGroups; i++) {
            if (table[i]->root != nullptr){
                table[i]->inOrder(table[i]->root);
            }
        }
    }
};

#endif
