#include "bank.hpp"
#include <thread>

std::mt19937 mt(rand());

Bank::Bank(int num_clients, ConcurrentBlockChain& chain) 
: accounts_(num_clients, BankAccount(100, chain)), blockchain_(chain) {

}

void Bank::process_accounts(int begin, int end) {
    for (int i = begin; i < end; i++) {
        int random_op = std::uniform_int_distribution<int>(0, 1)(mt);
        if(random_op == 0) {
            accounts_[i].add_random();
        }
        else {
            accounts_[i].take_random();
        }
    }
}

void Bank::simulate(int num_threads) {
    std::thread threads[num_threads];

    int count = accounts_.size() / num_threads;
    
    for(int i = 0; i < num_threads; i++) {
        int begin = i * count;
        int end = std::min((i + 1) * count, static_cast<int>(accounts_.size()));
        threads[i] = std::thread(&Bank::process_accounts, this, begin, end);
    }

    for(auto& thread : threads) {
        thread.join();
    }
}