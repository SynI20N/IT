#include "count_parallel.hpp"

int main() {
    // Измеряем время работы программы для разных N (1, 2, 4, 10)
    for (int N : {1, 2, 4, 10}) {
        measureTimeForThreads(N);
    }

    return 0;
}
