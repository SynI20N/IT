#include "BST.hpp"

// Constructor initializes the root as nullptr
template <typename T>
BST<T>::BST() : root(nullptr) {}

// Destructor ensures the tree is deleted when the BST object is destroyed
template <typename T>
BST<T>::~BST() {
    deleteTree(root);  // Automatically clears the tree when the object goes out of scope
}

// Insert a value into the tree iteratively
template <typename T>
void BST<T>::insert(T value) {
    Node<T>* newNode = new Node<T>(value);
    if (root == nullptr) {
        root = newNode;
        return;
    }

    Node<T>* current = root;
    Node<T>* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (value < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    // Attach the new node to the parent
    if (value < parent->data) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }
}

// Search for a value in the tree iteratively
template <typename T>
bool BST<T>::search(T value) const {
    Node<T>* current = root;
    while (current != nullptr) {
        if (value == current->data) {
            return true;
        }
        else if (value < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return false;
}

// In-order traversal of the tree iteratively
template <typename T>
void BST<T>::inOrderTraversal() const {
    if (root == nullptr) return;

    std::stack<Node<T>*> stack;
    Node<T>* current = root;

    while (current != nullptr || !stack.empty()) {
        // Reach the leftmost node of the current node
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }

        // Current must be null at this point
        current = stack.top();
        stack.pop();

        std::cout << current->data << " ";

        // Visit the right subtree
        current = current->right;
    }
}

// Remove a value from the tree iteratively
template <typename T>
Node<T>* BST<T>::remove(Node<T>* node, T value) {
    Node<T>* parent = nullptr;
    Node<T>* current = node;

    // Find the node to be deleted and its parent
    while (current != nullptr && current->data != value) {
        parent = current;
        if (value < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    if (current == nullptr) return node;  // Value not found

    // Case 1: Node has no children (leaf node)
    if (current->left == nullptr && current->right == nullptr) {
        if (current != node) {
            if (parent->left == current) {
                parent->left = nullptr;
            }
            else {
                parent->right = nullptr;
            }
        }
        else {
            node = nullptr;
        }
        delete current;
    }
    // Case 2: Node has one child
    else if (current->left == nullptr || current->right == nullptr) {
        Node<T>* child = (current->left != nullptr) ? current->left : current->right;

        if (current != node) {
            if (parent->left == current) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }
        }
        else {
            node = child;
        }
        delete current;
    }
    // Case 3: Node has two children
    else {
        Node<T>* successorParent = current;
        Node<T>* successor = current->right;

        // Find the leftmost node in the right subtree (in-order successor)
        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        // Copy the successor's content to the current node
        current->data = successor->data;

        // Delete the successor node
        if (successorParent->left == successor) {
            successorParent->left = successor->right;
        }
        else {
            successorParent->right = successor->right;
        }

        delete successor;
    }

    return node;
}

template <typename T>
void BST<T>::remove(T value) {
    root = remove(root, value);
}

// Helper function to recursively delete the tree
template <typename T>
void BST<T>::deleteTree(Node<T>* node) {
    if (node == nullptr) return;

    std::stack<Node<T>*> stack;
    std::stack<Node<T>*> visited;

    // Push root onto the stack
    stack.push(node);

    while (!stack.empty()) {
        Node<T>* current = stack.top();
        stack.pop();

        visited.push(current);

        // Push right and left children onto the stack
        if (current->right != nullptr) {
            stack.push(current->right);
        }
        if (current->left != nullptr) {
            stack.push(current->left);
        }
    }

    // Now, pop nodes from the visited stack and delete them
    while (!visited.empty()) {
        Node<T>* nodeToDelete = visited.top();
        visited.pop();
        delete nodeToDelete;
    }
}

// Clear function to delete all nodes in the tree
template <typename T>
void BST<T>::clear() {
    deleteTree(root);  // Use deleteTree to delete all nodes
    root = nullptr;    // Reset the root pointer to nullptr after clearing the tree
}

template class BST<int>;
