#include "bank.hpp"
#include <fstream>
#ifdef TEST
#include "gtest/gtest.h"
#endif

int main(int argc, char** argv) {
#ifdef TEST
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif
    std::ofstream out("output.txt");
    ConcurrentBlockChain chain(out, 10, 100);
    Bank bank(1000000, chain);
    bank.simulate(8);
    out.close();
    return 0;
}