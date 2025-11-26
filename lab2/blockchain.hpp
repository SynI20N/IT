#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <list>
#include <string>
#include <vector>
#include <mutex>

/**
 * @brief Цепь для хранения транзакций
 * @private max_trans_ Максимальное количество транзакций в каждой цепи
 * @private transactions_chain_ Цепь для сохранения транзакций
 * @private o_ Поток вывода (сохранения) данных
 */
class ConcurrentBlockChain {
public:
    ConcurrentBlockChain(std::ostream& output, int chain_count, size_t max_transaction);
    virtual void write(int account_id, int prev_amount, int new_amount);
    virtual ~ConcurrentBlockChain();
protected:
    std::mutex mutex_;
private:
    size_t max_trans_;
    std::vector<std::list<std::string>> transactions_chain_;
    std::ostream& o_;
#ifdef TEST
public:
#endif
    void archive(int chain_idx);
};

#endif