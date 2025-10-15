#include <list>
#include <string>
#include <vector>

class ConcurrentBlockChain {
public:
    ConcurrentBlockChain(int chain_count, int max_transaction);
    void Write(int account_id, int prev_amount, int new_amount);
private:
    int chain_c_;
    int max_trans_;
    std::vector<std::list<std::string>> transactions_chain_;
    void Archive(int chain_idx);
};