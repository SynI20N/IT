#ifndef BINOMIAL_HEAP_HPP
#define BINOMIAL_HEAP_HPP

#include <vector>
#include <iostream>
#include <limits.h>

class BinomialHeap {
private:
    struct Node {
        int value;
        int degree;
        Node* parent;
        Node* child;
        Node* sibling;

        Node(int val) : value(val), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
    };

    Node* head;

    Node* mergeHeaps(Node* h1, Node* h2);
    void link(Node* y, Node* z);
    void consolidate();
    Node* findMinNode();
    void cut(Node* x);
    void decreaseKey(Node* x, int newKey);
    void deleteNode(Node* x);

public:
    BinomialHeap();
    ~BinomialHeap();
    void insert(int value);
    void insertBatch(const std::vector<int>& values);
    int getMin();
    void deleteMin();
    void merge(BinomialHeap& other);
    bool isEmpty();
    void print();
};

#endif // BINOMIAL_HEAP_HPP
