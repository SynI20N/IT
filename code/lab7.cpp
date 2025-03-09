#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <ctime>
#include "Treap.hpp"
#include "AVL.hpp"

using namespace std;
using namespace chrono;

namespace lab7
{

    // Функция для замера максимальной глубины дерева
    int getMaxDepth(Treap::Node* node) {
        if (node == nullptr) return 0;
        int leftDepth = getMaxDepth(node->left);
        int rightDepth = getMaxDepth(node->right);
        return max(leftDepth, rightDepth) + 1;
    }

    // Функция для замера времени на 1000 операций вставки
    double measureInsertionTime(Treap& treap, const vector<int>& data) {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < 1000; ++i) {
            treap.insert(data[i % data.size()]);
        }
        auto end = high_resolution_clock::now();
        return duration_cast<microseconds>(end - start).count() / 1000000.0;
    }

    // Функция для замера времени на 1000 операций удаления
    double measureDeletionTime(Treap& treap, const vector<int>& data) {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < 1000; ++i) {
            treap.remove(data[i % data.size()]);
        }
        auto end = high_resolution_clock::now();
        return duration_cast<microseconds>(end - start).count() / 1000000.0;
    }

    // Функция для замера времени на 1000 операций поиска
    double measureSearchTime(Treap& treap, const vector<int>& data) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, data.size() - 1);

        auto start = high_resolution_clock::now();
        for (int i = 0; i < 1000; ++i) {
            int value = data[dis(gen)];
            treap.search(value);
        }
        auto end = high_resolution_clock::now();
        return duration_cast<microseconds>(end - start).count() / 1000000.0;
    }

    // Функция для замера глубины всех веток дерева
    double measureBranchDepths(Treap& treap) {
        // Допустим, что вы хотите вывести все глубины веток:
        vector<int> depths;
        treap.getAllBranchesDepths(depths);
        double mean = 0.0f;
        for (int depth : depths) {
            mean += depth;
        }
        mean /= depths.size();
        return mean;
    }

    double measureInsertion(AVLTree& avlTree, const vector<int>& data) {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < 1000; ++i) {
            avlTree.insert(data[i % data.size()]);
        }
        auto end = high_resolution_clock::now();
        return duration_cast<microseconds>(end - start).count() / 1000000.0;
    }

    // Функция для замера времени удаления
    double measureDeletion(AVLTree& avlTree, const vector<int>& data) {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < 1000; ++i) {
            avlTree.remove(data[i % data.size()]);
        }
        auto end = high_resolution_clock::now();
        return duration_cast<microseconds>(end - start).count() / 1000000.0;
    }

    // Функция для замера времени поиска
    double measureSearch(AVLTree& avlTree, const vector<int>& data) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, data.size() - 1);

        auto start = high_resolution_clock::now();
        for (int i = 0; i < 1000; ++i) {
            int value = data[dis(gen)];
            avlTree.search(value);
        }
        auto end = high_resolution_clock::now();
        return duration_cast<microseconds>(end - start).count() / 1000000.0;
    }

    int measureMaxDepth(AVLTree& avlTree)
    {
        return avlTree.getMaxDepth();
    }

    // Функция для замера глубины всех веток дерева
    double measureMeanBranchDepths(AVLTree& avlTree) {
        // Допустим, что вы хотите вывести все глубины веток:
        vector<int> depths;
        avlTree.getAllBranchesDepths(depths);
        double mean = 0.0f;
        for (int depth : depths) {
            mean += depth;
        }
        mean /= depths.size();
        return mean;
    }
}

//// Основная функция для тестирования
//int main() {
//    ofstream outFile("lab7_results.csv");
//
//    // Заголовок для CSV
//    outFile << "Series, N, Max Depth, Insertion Time, Deletion Time, Search Time, Mean Depth\n";
//
//    // Повторяем для разных значений N = 2^i от i = 10 до 18
//    for (int i = 10; i <= 18; ++i) {
//        int N = 1 << i;  // N = 2^i
//        vector<int> data(N);
//        iota(data.begin(), data.end(), 0);  // Генерация последовательности от 0 до N-1
//
//        // Генерация случайных чисел
//        random_device rd;
//        mt19937 gen(rd());
//        shuffle(data.begin(), data.end(), gen);  // Перемешиваем данные для случайного порядка
//
//        Treap treap;
//
//        // Заполняем два дерева одинаковыми данными
//        for (int j = 0; j < N; ++j) {
//            treap.insert(data[j]);
//        }
//
//        // Замеряем максимальную глубину
//        int maxDepth1 = lab7::getMaxDepth(treap.get_root());
//
//        // Замеряем время для 1000 вставок, удалений и поисков
//        double insertTime1 = lab7::measureInsertionTime(treap, data);
//        double deleteTime1 = lab7::measureDeletionTime(treap, data);
//        double searchTime1 = lab7::measureSearchTime(treap, data);
//
//        double meanDepth1 = lab7::measureBranchDepths(treap);
//
//        // Записываем результаты в CSV
//        outFile << (i - 10 + 1) << ","
//            << N << ","
//            << maxDepth1 << ","
//            << insertTime1 << ","
//            << deleteTime1 << ","
//            << searchTime1 << ","
//            << meanDepth1 << "\n";
//    }
//
//    outFile << "Series, N, Max Depth, Insertion Time, Deletion Time, Search Time, Mean Depth\n";
//
//    for (int i = 10; i <= 18; ++i) {
//        int N = 1 << i;  // N = 2^i
//        vector<int> data(N);
//        iota(data.begin(), data.end(), 0);  // Генерация последовательности от 0 до N-1
//
//        // Генерация случайных чисел
//        random_device rd;
//        mt19937 gen(rd());
//        shuffle(data.begin(), data.end(), gen);  // Перемешиваем данные для случайного порядка
//
//        AVLTree avl;
//
//        // Заполняем два дерева одинаковыми данными
//        for (int j = 0; j < N; ++j) {
//            avl.insert(data[j]);
//        }
//
//        // Замеряем максимальную глубину
//        int maxDepth2 = lab7::measureMaxDepth(avl);
//
//        double insertTime2 = lab7::measureInsertion(avl, data);
//        double deleteTime2 = lab7::measureDeletion(avl, data);
//        double searchTime2 = lab7::measureSearch(avl, data);
//
//        double meanDepths = lab7::measureMeanBranchDepths(avl);
//
//        // Записываем результаты в CSV
//        outFile << (i - 10 + 1) << ","
//            << N << ","
//            << maxDepth2 << ","
//            << insertTime2 << ","
//            << deleteTime2 << ","
//            << searchTime2 << ','
//            << meanDepths << "\n";
//    }
//
//    outFile.close();
//    return 0;
//}
