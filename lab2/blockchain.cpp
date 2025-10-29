#include "blockchain.hpp"
#include <random>
#include <iostream>

extern std::random_device rand_dev;
extern std::mt19937 mt;

ConcurrentBlockChain::ConcurrentBlockChain(std::ostream& output, int chain_count, size_t max_transaction)
: transactions_chain_(chain_count), o_(output) {
    max_trans_ = max_transaction;
}

void ConcurrentBlockChain::write(int id, int prev, int curr) {
    std::lock_guard<std::mutex> lock(mutex_);
    int i = std::uniform_int_distribution<int>(0, transactions_chain_.size() - 1)(mt);
    std::string s;
    s += '>' + std::to_string(id) + ':' + std::to_string(prev) + ':' + std::to_string(curr) + '\n';
    transactions_chain_[i].push_back(s);
    if(transactions_chain_[i].size() == max_trans_) {
        archive(i);
        transactions_chain_[i].clear();
    }
    //
}

ConcurrentBlockChain::~ConcurrentBlockChain() {
    o_.clear();
}

void ConcurrentBlockChain::archive(int chain_idx) {
    o_ << "archiving chain " << chain_idx << '\n';
    for(std::string s : transactions_chain_[chain_idx]) {
        o_ << s;
    }
}