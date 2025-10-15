#ifndef BANK_HPP
#define BANK_HPP

#include "bank_account.hpp"

class Bank {
public:
    Bank(int num_clients, ConcurrentBlockChain& chain);
    void simulate(int num_threads);
private:
    std::vector<BankAccount> accounts_;
    ConcurrentBlockChain& blockchain_;
    void process_accounts(int begin, int end);
};

#endif