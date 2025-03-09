#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <vector>

class AVLTree {
public:
    AVLTree();                    // Constructor
    ~AVLTree();                   // Destructor

    void insert(int key);         // Function to insert an element
    void remove(int key);         // Function to remove an element
    bool search(int key);         // Function to search for an element
    void inorder() const;         // Function for inorder traversal
    void preorder() const;        // Function for preorder traversal
    void postorder() const;       // Function for postorder traversal
    void getAllBranchesDepths(std::vector<int>& depths) const;
    int getMaxDepth() const;

private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        int height;

        Node(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    int getMaxDepth(Node* node) const;
    void getAllBranchesDepths(Node* node, int currentDepth, std::vector<int>& depths) const;

    // Helper functions
    Node* insert(Node* node, int key);
    Node* remove(Node* node, int key);
    Node* search(Node* node, int key) const;
    Node* minNode(Node* node) const;
    int height(Node* node) const;
    int balanceFactor(Node* node) const;
    Node* rotateLeft(Node* x);
    Node* rotateRight(Node* y);
    Node* balance(Node* node);
    void inorder(Node* node) const;
    void preorder(Node* node) const;
    void postorder(Node* node) const;
    void destroyTree(Node* node);
};

#endif // AVLTREE_HPP
