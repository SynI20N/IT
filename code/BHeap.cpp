#include "Bheap.hpp"
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

BinomialHeap::BinomialHeap() : head(nullptr) {}

BinomialHeap::~BinomialHeap() {
    Node* current = head;
    while (current) {
        Node* next = current->sibling;
        delete current;
        current = next;
    }
}

void BinomialHeap::insert(int value) {
    Node* newNode = new Node(value);
    head = mergeHeaps(head, newNode);
}

void BinomialHeap::insertBatch(const std::vector<int>& values) {
    std::vector<Node*> nodes;
    for (int value : values) {
        Node* newNode = new Node(value);
        nodes.push_back(newNode);
    }
    while (nodes.size() > 1) {
        std::vector<Node*> nextNodes;

        for (size_t i = 0; i < nodes.size(); i += 2) {
            if (i + 1 < nodes.size()) {
                head = mergeHeaps(nodes[i], nodes[i + 1]);
                nextNodes.push_back(head);
            }
            else {
                nextNodes.push_back(nodes[i]);
            }
        }

        nodes.clear();
        for (Node* node : nextNodes) {
            nodes.push_back(node);
        }

        consolidate();
    }
}

int BinomialHeap::getMin() {
    Node* minNode = findMinNode();
    return minNode ? minNode->value : INT_MAX;
}

void BinomialHeap::deleteMin() {
    Node* minNode = findMinNode();
    if (minNode) {
        // Move children of the minNode into the main heap
        if (minNode->child) {
            Node* child = minNode->child;
            while (child) {
                Node* nextChild = child->sibling;
                child->parent = nullptr;
                child = nextChild;
            }
        }

        // Remove the minNode from the heap
        if (minNode == head) {
            head = minNode->sibling;
        }
        else {
            Node* prev = nullptr;
            Node* current = head;
            while (current != minNode) {
                prev = current;
                current = current->sibling;
            }
            if (prev) {
                prev->sibling = minNode->sibling;
            }
        }
        delete minNode;
        consolidate();
    }
}

void BinomialHeap::merge(BinomialHeap& other) {
    head = mergeHeaps(head, other.head);
    other.head = nullptr;
}

bool BinomialHeap::isEmpty() {
    return head == nullptr;
}

void BinomialHeap::print() {
    Node* current = head;
    while (current) {
        std::cout << current->value << " ";
        current = current->sibling;
    }
    std::cout << std::endl;
}

BinomialHeap::Node* BinomialHeap::mergeHeaps(Node* h1, Node* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    Node* newHead = nullptr;
    Node* tail = nullptr;
    Node* temp1 = h1;
    Node* temp2 = h2;

    while (temp1 && temp2) {
        Node* smaller = nullptr;
        if (temp1->degree <= temp2->degree) {
            smaller = temp1;
            temp1 = temp1->sibling;
        }
        else {
            smaller = temp2;
            temp2 = temp2->sibling;
        }

        if (!newHead) {
            newHead = smaller;
            tail = newHead;
        }
        else {
            tail->sibling = smaller;
            tail = tail->sibling;
        }
    }

    while (temp1) {
        tail->sibling = temp1;
        tail = tail->sibling;
        temp1 = temp1->sibling;
    }

    while (temp2) {
        tail->sibling = temp2;
        tail = tail->sibling;
        temp2 = temp2->sibling;
    }

    return newHead;
}

void BinomialHeap::link(Node* y, Node* z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
}

void BinomialHeap::consolidate() {
    if (!head) return;

    std::vector<Node*> degrees(32, nullptr); // Max degree should be limited to log(n)
    Node* prev = nullptr;
    Node* current = head;

    while (current) {
        Node* next = current->sibling;
        int d = current->degree;

        while (degrees[d]) {
            Node* other = degrees[d];
            if (other->value < current->value) {
                std::swap(current, other);
            }
            link(other, current);
            degrees[d] = nullptr;
            d++;
        }

        degrees[d] = current;
        current = next;
    }

    head = nullptr;
    for (Node* node : degrees) {
        if (node) {
            if (!head) {
                head = node;
            }
            else {
                node->sibling = head;
                head = node;
            }
        }
    }
}

BinomialHeap::Node* BinomialHeap::findMinNode() {
    if (!head) return nullptr;

    Node* minNode = head;
    Node* current = head->sibling;
    while (current) {
        if (current->value < minNode->value) {
            minNode = current;
        }
        current = current->sibling;
    }
    return minNode;
}

void BinomialHeap::cut(Node* x) {
    if (x->parent) {
        Node* parent = x->parent;
        if (parent->child == x) {
            parent->child = x->sibling;
        }
        else {
            Node* sibling = parent->child;
            while (sibling->sibling != x) {
                sibling = sibling->sibling;
            }
            sibling->sibling = x->sibling;
        }
        parent->degree--;
        x->parent = nullptr;
        x->sibling = nullptr;
        head = mergeHeaps(head, x);
    }
}

void BinomialHeap::decreaseKey(Node* x, int newKey) {
    if (newKey > x->value) {
        std::cerr << "New key is larger than current key!" << std::endl;
        return;
    }
    x->value = newKey;
    Node* parent = x->parent;
    while (parent && x->value < parent->value) {
        std::swap(x->value, parent->value);
        x = parent;
        parent = x->parent;
    }
}

void BinomialHeap::deleteNode(Node* x) {
    decreaseKey(x, INT_MIN);
    deleteMin();
}
