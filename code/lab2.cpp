#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <iomanip>  // For controlling output precision
#include <climits>  // For INT_MAX


namespace lab2
{
    // Global variables to track the subcalls and recursion depth
    unsigned long long subcalls = 0;
    int max_recursion_depth = 0;

    // Merge function to combine two sorted halves
    void merge(std::vector<double>& arr, int left, int mid, int right, unsigned long long& swap_count) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<double> L(n1), R(n2);

        // Copy data to temp arrays L[] and R[]
        for (int i = 0; i < n1; ++i)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; ++j)
            R[j] = arr[mid + 1 + j];

        // Merge the temp arrays back into arr[]
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                ++i;
            }
            else {
                arr[k] = R[j];
                ++j;
                ++swap_count;  // Counting the swaps
            }
            ++k;
        }

        // Copy remaining elements of L[], if any
        while (i < n1) {
            arr[k] = L[i];
            ++i;
            ++k;
        }

        // Copy remaining elements of R[], if any
        while (j < n2) {
            arr[k] = R[j];
            ++j;
            ++k;
        }
    }

    // Merge Sort function
    void mergeSort(std::vector<double>& arr, int left, int right, unsigned long long& pass_count, unsigned long long& swap_count, int current_depth, int& max_depth, unsigned long long& max_memory_usage) {
        ++subcalls;  // Counting subcalls

        // Update max depth of recursion
        max_depth = std::max(max_depth, current_depth);

        // Calculate memory usage
        unsigned long long memory_usage = sizeof(double) * (right - left + 1);
        max_memory_usage = std::max(max_memory_usage, memory_usage);

        if (left < right) {
            int mid = left + (right - left) / 2;

            // Recursively sort the two halves
            mergeSort(arr, left, mid, pass_count, swap_count, current_depth + 1, max_depth, max_memory_usage);
            mergeSort(arr, mid + 1, right, pass_count, swap_count, current_depth + 1, max_depth, max_memory_usage);

            // Merge the sorted halves
            ++pass_count;
            merge(arr, left, mid, right, swap_count);
        }
    }

    // Function to generate random numbers in range [-1.0, 1.0]
    void generation(std::vector<double>& arr) {
        for (auto& val : arr) {
            val = (2.0 * rand() / RAND_MAX) - 1.0;
        }
    }

    void measure(int m, int s, std::ofstream& file) {
        std::vector<double> arr(m);
        double ttime = 0.0;
        clock_t start_time, end_time;

        // Write array size to file
        file << "\n--- MASSIVE " << m << " ---\n";
        std::cout << "\n" << m << std::endl;
        file << "TRY TIME PASS SWAP SUBCALLS MAX_DEPTH MAX_MEMORY\n";

        for (int i = 0; i < s; ++i) {
            unsigned long long pass_count = 0, swap_count = 0;  // Reset counters each iteration
            subcalls = 0;  // Reset subcalls for each pass
            max_recursion_depth = 0;  // Reset recursion depth
            unsigned long long max_memory_usage = 0;  // Reset memory tracking

            generation(arr);  // Generate random data
            start_time = clock();

            // Call merge sort and track metrics
            mergeSort(arr, 0, arr.size() - 1, pass_count, swap_count, 1, max_recursion_depth, max_memory_usage);

            end_time = clock();

            ttime = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
            file << std::fixed << std::setprecision(10)
                << i + 1 << " " << ttime << " " << pass_count << " " << swap_count
                << " " << subcalls << " " << max_recursion_depth << " " << max_memory_usage << "\n";  // Write results to file
            std::cout << i + 1 << " ";  // Output the current trial number
        }
    }
}

//int main() {
//    srand(time(nullptr));  // Initialize the random number generator
//
//    std::vector<int> sizes = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000 };
//    int num_sizes = sizes.size(), series = 20;
//
//    std::ofstream file("times.txt", std::ios::app);
//    if (!file.is_open()) {
//        std::cerr << "Error opening file\n";
//        return 1;
//    }
//
//    for (int i = 0; i < num_sizes; ++i) {
//        lab2::measure(sizes[i], series, file);
//    }
//
//    file.close();
//    return 0;
//}