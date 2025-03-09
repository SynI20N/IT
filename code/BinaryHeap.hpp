#ifndef BINARYHEAP_HPP
#define BINARYHEAP_HPP

#include <vector>
#include <stdexcept>
#include <iostream>

class BinaryHeap {
public:
    // Constructor and Destructor
    BinaryHeap();
    ~BinaryHeap();

    // Public methods
    void insert(int value);
    int getMin() const;
    void deleteMin();
    bool isEmpty() const;
    void print() const;

private:
    // Private methods
    void heapifyUp(int index);
    void heapifyDown(int index);
    void swap(int& a, int& b);

    // Heap storage
    std::vector<int> heap;
};

#endif // BINARYHEAP_HPP
