#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <stack>

// Template for Node
template <typename T>
struct Node {
    T data;
    Node* left;
    Node* right;

    Node(T value) : data(value), left(nullptr), right(nullptr) {}
};

// Template for Binary Search Tree
template <typename T>
class BST {
private:
    Node<T>* root;

    void deleteTree(Node<T>* node);
    Node<T>* remove(Node<T>* node, T value);

public:
    BST();
    ~BST();

    void insert(T value);
    bool search(T value) const;
    void inOrderTraversal() const;
    void remove(T value);

    void clear();
};

#endif // BST_HPP
