#include "bank.hpp"
#include <thread>

int main() {
    Bank bank(10e6);
    bank.Simulate(8);
    return 0;
}