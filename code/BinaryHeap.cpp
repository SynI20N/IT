#include "BinaryHeap.hpp"

// Constructor to initialize an empty heap
BinaryHeap::BinaryHeap() {
    heap.push_back(0); // To make the heap 1-indexed
}

// Destructor (no dynamic memory to free since we're using a vector)
BinaryHeap::~BinaryHeap() {}

// Insert a value into the heap
void BinaryHeap::insert(int value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

// Get the minimum value from the heap (the root of the heap)
int BinaryHeap::getMin() const {
    if (heap.size() <= 1) {
        throw std::out_of_range("Heap is empty.");
    }
    return heap[1];
}

// Remove the minimum value (root) from the heap
void BinaryHeap::deleteMin() {
    if (heap.size() <= 1) {
        throw std::out_of_range("Heap is empty.");
    }

    // Replace the root with the last element in the heap
    heap[1] = heap.back();
    heap.pop_back();

    // Restore the heap property by heapifying down
    heapifyDown(1);
}

// Check if the heap is empty
bool BinaryHeap::isEmpty() const {
    return heap.size() <= 1;
}

// Print the elements in the heap (excluding the dummy element at index 0)
void BinaryHeap::print() const {
    for (size_t i = 1; i < heap.size(); ++i) {
        std::cout << heap[i] << " ";
    }
    std::cout << std::endl;
}

// Heapify the element at index `i` upwards to restore heap property
void BinaryHeap::heapifyUp(int index) {
    while (index > 1 && heap[index] < heap[index / 2]) {
        swap(heap[index], heap[index / 2]);
        index /= 2;
    }
}

// Heapify the element at index `i` downwards to restore heap property
void BinaryHeap::heapifyDown(int index) {
    int leftChild = 2 * index;
    int rightChild = 2 * index + 1;
    int smallest = index;

    if (leftChild < heap.size() && heap[leftChild] < heap[smallest]) {
        smallest = leftChild;
    }
    if (rightChild < heap.size() && heap[rightChild] < heap[smallest]) {
        smallest = rightChild;
    }

    if (smallest != index) {
        swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

// Swap two elements in the heap
void BinaryHeap::swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
