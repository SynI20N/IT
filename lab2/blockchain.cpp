#include "blockchain.hpp"
#include <random>
#include <mutex>

ConcurrentBlockChain::ConcurrentBlockChain(std::ostream& output, int chain_count, int max_transaction)
: transactions_chain_(chain_count), o_(output) {
    max_trans_ = max_transaction;
}

void ConcurrentBlockChain::write(int id, int prev, int curr) {
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    int i = rand() % transactions_chain_.size();
    std::string s;
    s += std::to_string(id) + ' ' + std::to_string(prev) + ' ' + std::to_string(curr) + '\n';
    transactions_chain_[i].push_back(s);
    if(transactions_chain_[i].size() == (size_t)max_trans_) {
        archive(i);
    }
}

void ConcurrentBlockChain::archive(int chain_idx) {
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    for(std::string s : transactions_chain_[chain_idx]) {
        o_ << s << std::to_string('\n');
    }
}