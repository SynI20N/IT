#include "AVL.hpp"
#include <iostream>
#include <vector>

// Constructor
AVLTree::AVLTree() : root(nullptr) {}

// Destructor
AVLTree::~AVLTree() {
    destroyTree(root);
}

// Helper function to destroy the tree
void AVLTree::destroyTree(Node* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Insert function
void AVLTree::insert(int key) {
    root = insert(root, key);
}

AVLTree::Node* AVLTree::insert(Node* node, int key) {
    if (node == nullptr) {
        return new Node(key);
    }

    if (key < node->data) {
        node->left = insert(node->left, key);
    }
    else if (key > node->data) {
        node->right = insert(node->right, key);
    }
    else {
        return node; // Duplicate keys are not allowed
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    return balance(node);
}

// Remove function
void AVLTree::remove(int key) {
    root = remove(root, key);
}

AVLTree::Node* AVLTree::remove(Node* node, int key) {
    if (node == nullptr) {
        return node;
    }

    if (key < node->data) {
        node->left = remove(node->left, key);
    }
    else if (key > node->data) {
        node->right = remove(node->right, key);
    }
    else {
        if (node->left == nullptr || node->right == nullptr) {
            Node* temp = node->left ? node->left : node->right;

            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            }
            else {
                *node = *temp;
            }

            delete temp;
        }
        else {
            Node* temp = minNode(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
    }

    if (node == nullptr) {
        return node;
    }

    node->height = 1 + std::max(height(node->left), height(node->right));
    return balance(node);
}

// Search function
bool AVLTree::search(int key) {
    return search(root, key) != nullptr;
}

AVLTree::Node* AVLTree::search(Node* node, int key) const {
    if (node == nullptr || node->data == key) {
        return node;
    }

    if (key < node->data) {
        return search(node->left, key);
    }
    else {
        return search(node->right, key);
    }
}

// Function to get the minimum node
AVLTree::Node* AVLTree::minNode(Node* node) const {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Function to get the height of a node
int AVLTree::height(Node* node) const {
    return node == nullptr ? 0 : node->height;
}

// Function to get the balance factor of a node
int AVLTree::balanceFactor(Node* node) const {
    return node == nullptr ? 0 : height(node->left) - height(node->right);
}

// Left rotation
AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

// Right rotation
AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

// Balance the node
AVLTree::Node* AVLTree::balance(Node* node) {
    int balance = balanceFactor(node);

    if (balance > 1 && node->data > node->left->data) {
        return rotateRight(node);
    }

    if (balance < -1 && node->data < node->right->data) {
        return rotateLeft(node);
    }

    if (balance > 1 && node->data < node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && node->data > node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Inorder traversal
void AVLTree::inorder() const {
    inorder(root);
    std::cout << std::endl;
}

void AVLTree::inorder(Node* node) const {
    if (node) {
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }
}

// Preorder traversal
void AVLTree::preorder() const {
    preorder(root);
    std::cout << std::endl;
}

void AVLTree::preorder(Node* node) const {
    if (node) {
        std::cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }
}

// Postorder traversal
void AVLTree::postorder() const {
    postorder(root);
    std::cout << std::endl;
}

void AVLTree::postorder(Node* node) const {
    if (node) {
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << " ";
    }
}

// Function to get maximum depth of the tree
int AVLTree::getMaxDepth() const {
    return getMaxDepth(root);
}

int AVLTree::getMaxDepth(Node* node) const {
    if (node == nullptr) {
        return 0;
    }
    int leftDepth = getMaxDepth(node->left);
    int rightDepth = getMaxDepth(node->right);
    return std::max(leftDepth, rightDepth) + 1;
}

// Function to get depths of all branches
void AVLTree::getAllBranchesDepths(std::vector<int>& depths) const {
    getAllBranchesDepths(root, 0, depths);
}

void AVLTree::getAllBranchesDepths(Node* node, int currentDepth, std::vector<int>& depths) const {
    if (node == nullptr) {
        return;
    }
    // If it's a leaf node, record the depth
    if (node->left == nullptr && node->right == nullptr) {
        depths.push_back(currentDepth);
    }
    getAllBranchesDepths(node->left, currentDepth + 1, depths);
    getAllBranchesDepths(node->right, currentDepth + 1, depths);
}
