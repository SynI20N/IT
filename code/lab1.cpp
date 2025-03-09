#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <iomanip>  // For controlling output precision

void generation(std::vector<double>& arr) {
    for (auto& val : arr) {
        val = (2.0 * rand() / RAND_MAX) - 1.0;
    }
}

void bubble(std::vector<double>& arr, unsigned long long& pass_count, unsigned long long& swap_count) {
    pass_count = 0;
    swap_count = 0;
    double temp;

    for (size_t i = 0; i < arr.size() - 1; ++i) {
        ++pass_count;
        for (size_t j = 0; j < arr.size() - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                ++swap_count;
            }
        }
    }
}

void measure(int m, int s, std::ofstream& file) {
    std::vector<double> arr(m);
    double ttime = 0.0;
    clock_t start_time, end_time;

    // Write array size to file
    file << "\n--- MASSIVE " << m << " ---\n";
    std::cout << "\n" << m << std::endl;
    file << "TRY TIME PASS SWAP\n";

    for (int i = 0; i < s; ++i) {
        unsigned long long pass_count = 0, swap_count = 0;  // Reset counters each iteration
        generation(arr);  // Generate random data
        start_time = clock();

        bubble(arr, pass_count, swap_count);  // Sorting with pass and swap counts

        end_time = clock();

        ttime = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
        file << std::fixed << std::setprecision(10)
            << i + 1 << " " << ttime << " " << pass_count << " " << swap_count << "\n";  // Write results to file
        std::cout << i + 1 << " ";  // Output the current trial number
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
//        measure(sizes[i], series, file);
//    }
//
//    file.close();
//    return 0;
//}