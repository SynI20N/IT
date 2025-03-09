#include "BinaryHeap.hpp"
#include "BHeap.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <cmath>

using namespace std;
using namespace std::chrono;

namespace lab8 {
    vector<int> generateRandomNumbers(int n, int lower = 0, int upper = 100) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(lower, upper);

        vector<int> numbers(n);
        for (int i = 0; i < n; ++i) {
            numbers[i] = dis(gen);
        }

        return numbers;
    }

    template <typename F>
    double measureTime(F func, int iterations) {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            func();
        }
        auto end = high_resolution_clock::now();
        duration<double> duration = end - start;
        return duration.count();
    }

    void testBinaryHeap(int N, ofstream& outputFile) {
        BinaryHeap heap;
        vector<int> numbers = generateRandomNumbers(N);

        // Fill the heap
        for (int num : numbers) {
            heap.insert(num);
        }

        // Test finding minimum
        auto findMinFunc = [&heap]() {
            int minVal = heap.getMin();  // Find minimum
            };
        double findMinTime = measureTime(findMinFunc, 1000);

        // Test deleting minimum
        auto deleteMinFunc = [&heap]() {
            heap.deleteMin();  // Delete minimum
            };
        double deleteMinTime = measureTime(deleteMinFunc, 1000);

        // Test inserting element
        auto insertFunc = [&heap, &numbers]() {
            heap.insert(numbers[rand() % numbers.size()]);  // Insert random element
            };
        double insertTime = measureTime(insertFunc, 1000);

        // Measure maximum insert time
        vector<double> times;
        for (int i = 0; i < 1000; ++i) {
            auto insertSingle = [&heap, &numbers]() {
                heap.insert(numbers[rand() % numbers.size()]);
                };
            times.push_back(measureTime(insertSingle, 1));  // Measure single insert time
        }

        // Get max insert time
        double maxInsertTime = *max_element(times.begin(), times.end());

        // Log results for BinaryHeap
        outputFile << "BinaryHeap," << N << ","
            << findMinTime / 1000 << ","
            << deleteMinTime / 1000 << ","
            << insertTime / 1000 << ","
            << maxInsertTime << endl;
    }

    void testBinomialHeap(int N, ofstream& outputFile) {
        BinomialHeap heap;
        vector<int> numbers = generateRandomNumbers(N);

        // Fill the heap
        heap.insertBatch(numbers);

        // Test finding minimum
        auto findMinFunc = [&heap]() {
            int minVal = heap.getMin();  // Find minimum
            };
        double findMinTime = measureTime(findMinFunc, 1000);

        // Test deleting minimum
        auto deleteMinFunc = [&heap]() {
            heap.deleteMin();  // Delete minimum
            };
        double deleteMinTime = measureTime(deleteMinFunc, 1000);

        // Test inserting element
        auto insertFunc = [&heap, &numbers]() {
            heap.insert(numbers[rand() % numbers.size()]);  // Insert random element
            };
        double insertTime = measureTime(insertFunc, 1000);

        // Measure maximum insert time
        vector<double> times;
        for (int i = 0; i < 1000; ++i) {
            auto insertSingle = [&heap, &numbers]() {
                heap.insert(numbers[rand() % numbers.size()]);
                };
            times.push_back(measureTime(insertSingle, 1));  // Measure single insert time
        }

        // Get max insert time
        double maxInsertTime = *max_element(times.begin(), times.end());

        // Log results for BinomialHeap
        outputFile << "BinomialHeap," << N << ","
            << findMinTime / 1000 << ","
            << deleteMinTime / 1000 << ","
            << insertTime / 1000 << ","
            << maxInsertTime << endl;
    }
}

//int main() {
//    ofstream outputFile("heap_performance_comparison.csv");
//    if (!outputFile.is_open()) {
//        cerr << "Error opening file for writing." << endl;
//        return 1;
//    }
//
//    outputFile << "Heap Type,N,Find Min Time (sec per op),Delete Min Time (sec per op),Insert Time (sec per op),Max Insert Time (sec)" << endl;
//
//    // Test for BinaryHeap and BinomialHeap for different values of N (10^3, 10^4, 10^5, 10^6)
//    for (int i = 3; i <= 6; ++i) {
//        int N = pow(10, i);
//        cout << "Testing with N = " << N << endl;
//
//        // Test BinaryHeap
//        lab8::testBinaryHeap(N, outputFile);
//
//        // Test BinomialHeap
//        lab8::testBinomialHeap(N, outputFile);
//
//        cout << "Completed for N = " << N << endl;
//    }
//
//    outputFile.close();
//    cout << "Performance data saved to heap_performance_comparison.csv" << endl;
//
//    return 0;
//}
