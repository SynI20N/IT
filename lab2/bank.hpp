#ifndef BANK_HPP
#define BANK_HPP

#include "bank_account.hpp"

class Bank {
public:
    Bank(int num_clients, ConcurrentBlockChain& chain);
    void simulate(int num_threads);
    size_t get_accounts_count() const;
    BankAccount get_account(int i);
private:
    std::vector<BankAccount> accounts_;
    ConcurrentBlockChain& blockchain_;
#ifdef TEST
public:
#endif
    void process_accounts(int begin, int end);
};

#endif