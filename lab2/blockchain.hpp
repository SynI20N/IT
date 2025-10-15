#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <list>
#include <string>
#include <vector>
#include <mutex>

class ConcurrentBlockChain {
public:
    ConcurrentBlockChain(std::ostream& output, int chain_count, int max_transaction);
    void write(int account_id, int prev_amount, int new_amount);
private:
    int max_trans_;
    std::recursive_mutex mutex_;
    std::vector<std::list<std::string>> transactions_chain_;
    std::ostream& o_;
    void archive(int chain_idx);
};

#endif