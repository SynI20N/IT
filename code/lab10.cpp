#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>

const float M_PI = 3.14157;

// Функция для вычисления F(x)
double F(double x) {
    return x * x + 10 - 10 * cos(2 * M_PI * x);
}

// Алгоритм отжига
double simulated_annealing(double T0, double T_min, int max_iterations) {
    // Начальная точка x0 (случайно выбранная)
    double x_current = (rand() / (double)RAND_MAX) * 10 - 5;  // Случайное значение от -5 до 5
    double F_current = F(x_current);

    double T = T0;  // Начальная температура

    double best_x = x_current;
    double best_F = F_current;

    for (int k = 1; k <= max_iterations; ++k) {
        // Генерация нового кандидата x[k+1] с учетом случайного шума (распределение Коши)
        double x_new = x_current + T * (rand() / (double)RAND_MAX * 2 - 1); // Случайный шум
        double F_new = F(x_new);

        // Вычисление разницы значений функции
        double dF = F_new - F_current;

        // Условие принятия нового решения
        if (dF < 0 || ((rand() / (double)RAND_MAX) < exp(-dF / T))) {
            x_current = x_new;
            F_current = F_new;

            // Обновление наилучшего решения
            if (F_current < best_F) {
                best_x = x_current;
                best_F = F_current;
            }
        }

        // Обновление температуры
        T = T0 / k;

        // Завершение, если температура ниже порога
        if (T < T_min) {
            break;
        }
    }

    return best_x;
}

//int main() {
//    // Инициализация генератора случайных чисел
//    srand(time(0));
//
//    // Параметры алгоритма
//    double T0 = 1000.0;  // Начальная температура
//    int max_iterations = 10000;  // Максимальное количество итераций
//
//    // Массив различных значений минимальной температуры
//    double T_min_values[] = { 1e-6, 1e-5, 1e-4, 1e-3, 1e-2, 1e-1, 1e0 };
//    int num_T_min_values = sizeof(T_min_values) / sizeof(T_min_values[0]);
//
//    // Открытие CSV файла для записи результатов
//    std::ofstream csv_file("simulated_annealing_results.csv");
//
//    // Запись заголовков в CSV
//    csv_file << "T_min,Best_x,Best_F,Execution_Time (seconds)\n";
//
//    // Замер времени для разных значений минимальной температуры
//    for (int i = 0; i < num_T_min_values; ++i) {
//        double T_min = T_min_values[i];
//
//        // Замер времени начала
//        auto start_time = std::chrono::high_resolution_clock::now();
//
//        // Запуск алгоритма
//        double best_x = simulated_annealing(T0, T_min, max_iterations);
//        double best_F = F(best_x);
//
//        // Замер времени окончания
//        auto end_time = std::chrono::high_resolution_clock::now();
//
//        // Вычисление времени работы алгоритма
//        std::chrono::duration<double> duration = end_time - start_time;
//
//        // Запись результатов в CSV файл
//        csv_file << T_min << "," << best_x << "," << best_F << "," << duration.count() << "\n";
//    }
//
//    // Закрытие CSV файла
//    csv_file.close();
//
//    std::cout << "Результаты записаны в файл 'simulated_annealing_results.csv'" << std::endl;
//
//    return 0;
//}
