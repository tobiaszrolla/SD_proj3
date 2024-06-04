#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>
#include <algorithm>
#include <string>

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
    int height(Node* N);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    int getBalance(Node* N);
    Node* minValueNode(Node* node);

public:
    Node* root;

    AVLTree() : root(nullptr) {}
    Node* insert(Node* node, int key, string value);
    Node* remove(Node* root, int key);
    void inOrder(Node* root);
};

#endif // AVLTREE_HPP