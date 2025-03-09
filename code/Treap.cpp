#include "Treap.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Constructor
Treap::Treap() : root(nullptr) {
    std::srand(std::time(nullptr)); // Seed for random number generation
}

// Destructor
Treap::~Treap() {
    destroyTree(root);
}

Treap::Node* Treap::get_root() const
{
    return root;
}

// Helper function to destroy the tree
void Treap::destroyTree(Node* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Insert function
void Treap::insert(int key) {
    root = insert(root, key);
}

Treap::Node* Treap::insert(Node* node, int key) {
    // Perform a standard BST insertion
    if (node == nullptr) {
        return new Node(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key);
    }

    // Ensure heap property by checking priority
    if (node->left && node->left->priority > node->priority) {
        node = rotateRight(node);
    }
    else if (node->right && node->right->priority > node->priority) {
        node = rotateLeft(node);
    }

    return node;
}

// Remove function
void Treap::remove(int key) {
    root = remove(root, key);
}

Treap::Node* Treap::remove(Node* node, int key) {
    if (node == nullptr) return nullptr;

    if (key < node->key) {
        node->left = remove(node->left, key);
    }
    else if (key > node->key) {
        node->right = remove(node->right, key);
    }
    else {
        if (node->left == nullptr || node->right == nullptr) {
            Node* temp = node;
            node = (node->left ? node->left : node->right);
            delete temp;
        }
        else {
            if (node->left->priority > node->right->priority) {
                node = rotateRight(node);
                node->right = remove(node->right, key);
            }
            else {
                node = rotateLeft(node);
                node->left = remove(node->left, key);
            }
        }
    }

    return node;
}

// Search function
bool Treap::search(int key) const {
    return search(root, key) != nullptr;
}

Treap::Node* Treap::search(Node* node, int key) const {
    if (node == nullptr || node->key == key) {
        return node;
    }

    if (key < node->key) {
        return search(node->left, key);
    }
    else {
        return search(node->right, key);
    }
}

// Left rotation (used to maintain heap property)
Treap::Node* Treap::rotateLeft(Node* node) {
    Node* new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;
    return new_root;
}

// Right rotation (used to maintain heap property)
Treap::Node* Treap::rotateRight(Node* node) {
    Node* new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;
    return new_root;
}

// Inorder traversal
void Treap::inorder() const {
    inorder(root);
    std::cout << std::endl;
}

void Treap::inorder(Node* node) const {
    if (node != nullptr) {
        inorder(node->left);
        std::cout << node->key << " ";
        inorder(node->right);
    }
}

// Function to get depths of all branches
void Treap::getAllBranchesDepths(std::vector<int>& depths) const {
    getAllBranchesDepths(root, 0, depths);
}

// Helper function to collect depths of all branches (leaf nodes)
void Treap::getAllBranchesDepths(Node* node, int currentDepth, std::vector<int>& depths) const {
    if (node == nullptr) {
        return;
    }

    // If it's a leaf node (both left and right are null), record the depth
    if (node->left == nullptr && node->right == nullptr) {
        depths.push_back(currentDepth);
    }

    // Recursively call on left and right subtrees, increasing the depth by 1
    getAllBranchesDepths(node->left, currentDepth + 1, depths);
    getAllBranchesDepths(node->right, currentDepth + 1, depths);
}
