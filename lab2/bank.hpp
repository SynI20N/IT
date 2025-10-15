#include "bank_account.hpp"

class Bank {
public:
    Bank(int num_clients);
    void Simulate(int num_threads);
private:
    std::vector<BankAccount> accounts_;
    ConcurrentBlockChain blockchain_;
};