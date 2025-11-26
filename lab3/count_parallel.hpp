#ifndef COUNT_DIGITS_HPP
#define COUNT_DIGITS_HPP

#include <vector>
#include <string>

// Структура для хранения результатов
struct CountResult {
    int evenCount;
    int oddCount;
};

// Функция для генерации строки из случайных цифр
std::string generateRandomDigits(int length);

// Функция для подсчета четных и нечетных цифр в строке
CountResult countEvenOdd(const std::string& str);

// Функция для многозадачной обработки строк
void processRows(const std::vector<std::string>& rows, 
                 std::vector<CountResult>& results, 
                 int startIdx, 
                 int endIdx);

// Функция для измерения времени работы программы
void measureTimeForThreads(int numThreads);

#endif // COUNT_DIGITS_HPP
