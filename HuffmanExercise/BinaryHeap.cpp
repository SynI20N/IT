#include "BinaryHeap.hpp"

// Constructor to initialize an empty heap
BinaryHeap::BinaryHeap() {
    heap.push_back(0);
}

BinaryHeap::BinaryHeap(std::vector<Node<int>> data) {
    heap.push_back(0);
    heap.resize(1 + data.size());
    std::copy(data.begin(), data.end(), heap.end());
    int n = data.size();
    for (int i = floor(n / 2); i >= 1; --i) {
        heapify(i);
    }
}

// Destructor (no dynamic memory to free since we're using a vector)
BinaryHeap::~BinaryHeap() {}

// Insert a value into the heap
void BinaryHeap::insert(Node<int> value) {
    heap.push_back(value);
    heapify(heap.size() - 1);
}

// Get the minimum value from the heap (the root of the heap)
Node<int> BinaryHeap::getMin() const {
    if (heap.size() <= 1) {
        throw std::out_of_range("Heap is empty.");
    }
    return heap[1];
}

size_t BinaryHeap::getSize() const {
    return heap.size();
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
    heapify(1);
}

// Check if the heap is empty
bool BinaryHeap::isEmpty() const {
    return heap.size() <= 1;
}

// Print the elements in the heap (excluding the dummy element at index 0)
void BinaryHeap::print() const {
    for (size_t i = 1; i < heap.size(); ++i) {
        std::cout << heap[i].freq << " ";
    }
    std::cout << std::endl;
}

// Heapify the element at index `i` downwards to restore heap property
void BinaryHeap::heapify(int index) {
    int leftChild = 2 * index;
    int rightChild = 2 * index + 1;
    int smallest = index;

    if (leftChild < heap.size() && heap[leftChild].freq < heap[smallest].freq) {
        smallest = leftChild;
    }
    if (rightChild < heap.size() && heap[rightChild].freq < heap[smallest].freq) {
        smallest = rightChild;
    }

    if (smallest != index) {
        swap(heap[index], heap[smallest]);
        heapify(smallest);
    }
}

// Swap two elements in the heap
void BinaryHeap::swap(Node<int>& a, Node<int>& b) {
    Node<int> temp = a;
    a = b;
    b = temp;
}
