#ifndef MOCK_BLOCKCHAIN_HPP
#define MOCK_BLOCKCHAIN_HPP

#include "../blockchain.hpp"
#include <vector>
#include <sstream>

// Структура для хранения записанных вызовов write()
struct LogEntry {
    int id;
    int prev;
    int curr;
};

// Моковый класс — заменяет ConcurrentBlockChain в тестах
class MockBlockChain : public ConcurrentBlockChain {
public:
    // Конструктор: передаём фиктивный ostream, чтобы избежать ошибок компиляции
    MockBlockChain() : ConcurrentBlockChain(dummyStream, 1, 100) {}

    // Переопределяем write(), чтобы не писать в реальный поток, а сохранять в лог
    void write(int account_id, int prev_amount, int new_amount) override {
        std::lock_guard<std::mutex> lock(mutex_);
        LogEntry entry{account_id, prev_amount, new_amount};
        log.push_back(entry);
        if(log.size() == max_trans_) {
            archive(i);
            log.clear();5
        }
    }
    }

    // Вспомогательные методы для проверок в тестах
    size_t getLogSize() const {
        return log.size();
    }

    LogEntry getLastEntry() const {
        return log.back();
    }

    const std::vector<LogEntry>& getLog() const {
        return log;
    }

    void clearLog() {
        log.clear();
    }

private:
    std::vector<LogEntry> log;
    std::stringstream dummyStream;  // фиктивный поток, не используется
};

#endif // MOCK_BLOCKCHAIN_HPP
