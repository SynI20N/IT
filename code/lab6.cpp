#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include "BST.hpp"
#include "AVL.hpp"

using namespace std;
using namespace chrono;

namespace lab6_avl
{
    // Function to measure insertion time
    template <typename T>
    double measureInsertionTime(AVLTree& tree, const vector<T>& data) {
        auto start = high_resolution_clock::now();
        for (const auto& value : data) {
            tree.insert(value);
        }
        auto end = high_resolution_clock::now();
        return duration_cast<microseconds>(end - start).count() / 1000000.0;  // Time in seconds
    }

    // Function to measure search time
    template <typename T>
    double measureSearchTime(AVLTree& tree, const vector<T>& data) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, data.size() - 1);

        auto start = high_resolution_clock::now();
        for (int i = 0; i < 1000; ++i) {
            T value = data[dis(gen)];
            tree.search(value);
        }
        auto end = high_resolution_clock::now();
        return duration_cast<microseconds>(end - start).count() / 1000000.0;  // Time in seconds
    }

    // Function to measure deletion time
    template <typename T>
    double measureDeletionTime(AVLTree& tree, vector<T>& data) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, data.size() - 1);

        auto start = high_resolution_clock::now();
        for (int i = 0; i < 1000; ++i) {
            T value = data[dis(gen)];
            tree.remove(value);
        }
        auto end = high_resolution_clock::now();
        return duration_cast<microseconds>(end - start).count() / 1000000.0;  // Time in seconds
    }
}

namespace lab6
{
    
    // Функция для замера времени вставки в дерево
    template <typename T>
    double measureInsertionTime(BST<T>& tree, const vector<T>& data) {
        auto start = high_resolution_clock::now();
        for (const auto& value : data) {
            tree.insert(value);
        }
        auto end = high_resolution_clock::now();
        return duration_cast<microseconds>(end - start).count() / 1000000.0;  // Время в секундах
    }

    // Функция для замера времени поиска
    template <typename T>
    double measureSearchTime(BST<T>& tree, const vector<T>& data) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, data.size() - 1);

        auto start = high_resolution_clock::now();
        for (int i = 0; i < 1000; ++i) {
            T value = data[dis(gen)];
            tree.search(value);
        }
        auto end = high_resolution_clock::now();
        return duration_cast<microseconds>(end - start).count() / 1000000.0;  // Время в секундах
    }

    // Функция для замера времени удаления
    template <typename T>
    double measureDeletionTime(BST<T>& tree, vector<T>& data) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, data.size() - 1);

        auto start = high_resolution_clock::now();
        for (int i = 0; i < 1000; ++i) {
            T value = data[dis(gen)];
            tree.remove(value);
        }
        auto end = high_resolution_clock::now();
        return duration_cast<microseconds>(end - start).count() / 1000000.0;  // Время в секундах
    }
}

void writeResultsToCSV(std::ofstream& outFile, int i, int size,
    double randomInsertTime, double sortedInsertTime,
    double randomSearchTime, double sortedSearchTime,
    double randomDeleteTime, double sortedDeleteTime) {
    // Output the results in CSV format
    outFile << (i + 1) << ","  // Series number
        << size << ","  // Array size
        << randomInsertTime << ","  // Time for random tree insertions
        << sortedInsertTime << ","  // Time for sorted tree insertions
        << randomSearchTime / 1000.0 << ","  // Time per search operation in random tree
        << sortedSearchTime / 1000.0 << ","  // Time per search operation in sorted tree
        << randomDeleteTime / 1000.0 << ","  // Time per delete operation in random tree
        << sortedDeleteTime / 1000.0 << "\n";  // Time per delete operation in sorted tree
}

//int main() {
//    ofstream outFile("BST.csv");
//
//    // Выводим заголовок таблицы
//    outFile << "Серия,Размер,Рандомная вставка,Отсортированная вставка,Рандомный поиск,Отсортированный поиск,Рандомное удаление,Отсортированное удаление\n";
//
//    BST<int> randomBST;
//    BST<int> sortedBST;
//
//    for (int i = 0; i < 6; ++i) {
//        // Размер массива для текущей серии
//        int size = 1 << (10 + i);  // 2^(10 + i)
//
//        // Генерация массива
//        vector<int> data(size);
//        iota(data.begin(), data.end(), 0);  // Заполняем массив от 0 до size-1
//
//        vector<int> rand_data(size);
//        iota(rand_data.begin(), rand_data.end(), 0);
//
//        random_device rd;
//        mt19937 gen(rd());
//        shuffle(rand_data.begin(), rand_data.end(), gen);
//
//        // Измеряем время на вставку для случайного массива
//        double randomInsertTime = lab6::measureInsertionTime(randomBST, rand_data);
//        // Измеряем время на вставку для отсортированного массива
//        double sortedInsertTime = lab6::measureInsertionTime(sortedBST, data);
//
//        // Измеряем время на 1000 операций поиска в обоих деревьях
//        double randomSearchTime = lab6::measureSearchTime(randomBST, rand_data);
//        double sortedSearchTime = lab6::measureSearchTime(sortedBST, data);
//
//        // Измеряем время на 1000 операций удаления в обоих деревьях
//        double randomDeleteTime = lab6::measureDeletionTime(randomBST, rand_data);
//        double sortedDeleteTime = lab6::measureDeletionTime(sortedBST, data);
//
//        writeResultsToCSV(outFile, i, size, randomInsertTime, sortedInsertTime,
//            randomSearchTime, sortedSearchTime,
//            randomDeleteTime, sortedDeleteTime);
//        randomBST.clear();
//        sortedBST.clear();
//    }
//
//    outFile.close();
//
//    ofstream outFile2("AVLTree.csv");
//
//    // Output the header for the CSV file
//    outFile2 << "Серия,Размер,Рандомная вставка,Отсортированная вставка,Рандомный поиск,Отсортированный поиск,Рандомное удаление,Отсортированное удаление\n";
//
//    AVLTree randomAVLTree;
//    AVLTree sortedAVLTree;
//
//    for (int i = 0; i < 6; ++i) {
//        // Array size for the current series
//        int size = 1 << (10 + i);  // 2^(10 + i)
//
//        // Generate an array for the current size
//        vector<int> data(size);
//        iota(data.begin(), data.end(), 0);  // Fill the array with 0, 1, 2, ..., size-1
//
//        vector<int> rand_data(size);
//        iota(rand_data.begin(), rand_data.end(), 0);
//
//        random_device rd;
//        mt19937 gen(rd());
//        shuffle(rand_data.begin(), rand_data.end(), gen);
//
//        // Measure insertion time for random array
//        double randomInsertTime = lab6_avl::measureInsertionTime(randomAVLTree, rand_data);
//        // Measure insertion time for sorted array
//        double sortedInsertTime = lab6_avl::measureInsertionTime(sortedAVLTree, data);
//
//        // Measure time for 1000 search operations in both trees
//        double randomSearchTime = lab6_avl::measureSearchTime(randomAVLTree, rand_data);
//        double sortedSearchTime = lab6_avl::measureSearchTime(sortedAVLTree, data);
//
//        // Measure time for 1000 delete operations in both trees
//        double randomDeleteTime = lab6_avl::measureDeletionTime(randomAVLTree, rand_data);
//        double sortedDeleteTime = lab6_avl::measureDeletionTime(sortedAVLTree, data);
//
//        // Write the results to CSV
//        writeResultsToCSV(outFile2, i, size, randomInsertTime, sortedInsertTime,
//            randomSearchTime, sortedSearchTime,
//            randomDeleteTime, sortedDeleteTime);
//    }
//
//    outFile2.close();
//    return 0;
//}
