#include <iostream>
#include <cassert>

long int drive(int x, int y, int f, int g) {
    int dv = abs(f - x);
    int dh = abs(g - y);
    long int min_v = 3L*(dv - 1L) > 0L ? 3L*(dv - 1L) : 0L;
    long int min_h = 3L*(dh - 1L) > 0L ? 3L*(dh - 1L) : 0L;
    long int res = min_v + min_h;
    if(dv != 0 && dh != 0) {
        res++;
    }
    return res;
}

void test1() {
    int res = drive(8, 7, 3, 4);
    int answ = 19;
    assert(res == answ);
    std::cout << "OK\n";
}

void test2() {
    int res = drive(3, 4, 4, 3);
    int answ = 1;
    assert(res == answ);
    std::cout << "OK\n";
}

void test3() {
    int res = drive(2, 4, 5, 4);
    int answ = 6;
    assert(res == answ);
    std::cout << "OK\n";
}

void test4() {
    int res = drive(1, 1, 1, 1);
    int answ = 0;
    assert(res == answ);
    std::cout << "OK\n";
}

void test5() {
    int res = drive(3, 3, 3, 4);
    int answ = 0;
    assert(res == answ);
    std::cout << "OK\n";
}

void test6() {
    long int res = drive(1000000000L, 1000000000L, 1000000000L, 1);
    long int answ = 3L*999999998L;
    assert(res == answ);
    std::cout << "OK\n";
}

void test7() {
    int res = drive(1, 2, 4, 4);
    int answ = 10;
    assert(res == answ);
    std::cout << "OK\n";
}

void test8() {
    long int res = drive(1L, 1L, 1000000000L, 1000000000L);
    long int answ = 3L*999999998L + 1L + 3L*999999998L;
    assert(res == answ);
    std::cout << "OK\n";
}

void test9() {
    long int res = drive(3, 1, 1, 3);
    long int answ = 7;
    assert(res == answ);
    std::cout << "OK\n";
}

void test10() {
    long int res = drive(3, 1, 1, 1);
    long int answ = 3;
    assert(res == answ);
    std::cout << "OK\n";
}
int main() {
#ifdef TEST
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    std::cout << "all tests passed!\n";
    return 0;
#endif
    int x, y;
    int f, g;
    std::cin >> x >> y;
    std::cin >> f >> g;
    long int res = drive(x, y, f, g);
    std::cout << res;
    return 0;
}