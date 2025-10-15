#include "blockchain.hpp"
#include <random>

class BankAccount {
public:
    BankAccount(int amount, ConcurrentBlockChain& logger);
    ~BankAccount();
    void Add(int money);
    void Take(int money);
private:
    static std::mt19937* mt_;
    ConcurrentBlockChain& logger_;
    long long amount_;
    int id_;
};