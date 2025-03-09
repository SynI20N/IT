#ifndef TREAP_HPP
#define TREAP_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

class Treap {
public:
    Treap();                    // Constructor
    ~Treap();                   // Destructor

    void insert(int key);       // Insert function
    void remove(int key);       // Remove function
    bool search(int key) const; // Search function
    void inorder() const;       // Inorder traversal
    void getAllBranchesDepths(std::vector<int>& depths) const;

public:
    struct Node {
        int key;        // The key of the node
        int priority;   // The priority of the node (randomized)
        Node* left;     // Pointer to left child
        Node* right;    // Pointer to right child

        Node(int k) : key(k), priority(rand()), left(nullptr), right(nullptr) {}
    };
private:

    Node* root;
    void getAllBranchesDepths(Node* node, int currentDepth, std::vector<int>& depths) const;

    // Helper functions
    Node* insert(Node* node, int key);
    Node* remove(Node* node, int key);
    Node* search(Node* node, int key) const;
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    void inorder(Node* node) const;
    void destroyTree(Node* node);
public:
    Node* get_root() const;
};

#endif // TREAP_HPP
