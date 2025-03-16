#ifndef BINARYHEAP_HPP
#define BINARYHEAP_HPP

#include <vector>
#include <stdexcept>
#include <iostream>
#include "BinaryTree.hpp"

class BinaryHeap {
public:
    BinaryHeap();
    BinaryHeap(std::vector<Node<int>> data);
    ~BinaryHeap();

    void insert(Node<int> value);
    Node<int> getMin() const;
    size_t getSize() const;
    void deleteMin();
    bool isEmpty() const;
    void print() const;

private:
    void heapify(int index);
    void swap(Node<int>& a, Node<int>& b);
    std::vector<Node<int>> heap;
};

#endif // BINARYHEAP_HPP
