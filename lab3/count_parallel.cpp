#include "count_parallel.hpp"
#include <iostream>
#include <random>
#include <chrono>
#include <omp.h>

// Генерация строки из случайных цифр
std::string generateRandomDigits(int length) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);
    
    std::string digits;
    for (int i = 0; i < length; ++i) {
        digits += std::to_string(dis(gen));
    }
    return digits;
}

// Подсчет четных и нечетных цифр в строке
CountResult countEvenOdd(const std::string& str) {
    int evenCount = 0;
    int oddCount = 0;
    
    for (char ch : str) {
        if ((ch - '0') % 2 == 0) {
            ++evenCount;
        } else {
            ++oddCount;
        }
    }
    
    return {evenCount, oddCount};
}

// Многозадачная обработка строк
void processRows(const std::vector<std::string>& rows, 
                 std::vector<CountResult>& results, 
                 int startIdx, 
                 int endIdx) {
    for (int i = startIdx; i < endIdx; ++i) {
        results[i] = countEvenOdd(rows[i]);
    }
}

// Функция для измерения времени работы программы для разных N потоков
void measureTimeForThreads(int numThreads) {
    const int numRows = 300;         // Количество строк
    const int numDigits = 200000;    // Количество цифр в строке

    // Генерация массива из случайных строк
    std::vector<std::string> rows(numRows);
    for (int i = 0; i < numRows; ++i) {
        rows[i] = generateRandomDigits(numDigits);
    }

    // Измеряем время работы программы для заданного N
    std::vector<CountResult> results(numRows);
    
    // Засекаем время начала выполнения
    auto start = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for num_threads(numThreads) schedule(static)
    for (int i = 0; i < numRows; ++i) {
        results[i] = countEvenOdd(rows[i]);
    }

    // Засекаем время завершения выполнения
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    
    // Выводим результаты
    std::cout 
        << "Время работы для " 
        << numThreads 
        << " потоков: " 
        << duration.count() 
        << " секунд" << '\n';
    
    // (Опционально) Выводим несколько первых результатов
    for (int i = 0; i < 5 && i < numRows; ++i) {
        std::cout 
            << "Строка " 
            << i 
            << ": четных - " 
            << results[i].evenCount 
            << ", нечетных - " 
            << results[i].oddCount 
            << '\n';
    }
    std::cout << '\n';
}
