#include "bank.hpp"
#include <thread>
#include <fstream>

int main() {
    srand(time(0));
    std::ofstream out("output.txt");
    ConcurrentBlockChain chain(out, 10, 100);
    Bank bank(1000000, chain);
    bank.simulate(8);
    out.close();
    return 0;
}