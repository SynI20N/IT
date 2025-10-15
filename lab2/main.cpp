#include "bank.hpp"
#include <fstream>

int main() {
    std::ofstream out("output.txt");
    ConcurrentBlockChain chain(out, 10, 100);
    Bank bank(1000, chain);
    bank.simulate(8);
    out.close();
    return 0;
}