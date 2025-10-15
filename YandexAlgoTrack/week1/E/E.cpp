#include <iostream>
#include <cassert>

long int tableau(long int n, int k) {
    short last = n % 10;
    int k_even = k >> 1;
    int sec = 0;
    for(; sec < k_even; sec++) {
        switch (last)
        {
        case 1:
            n += 3;
            last = 4;
            break;
        case 2:
            n += 6;
            last = 8;
            break;
        case 3:
            n += 9;
            last = 2;
            break;
        case 4:
            n += 12;
            last = 6;
            break;
        case 5:
            n += 5;
            last = 0;
            break;
        case 6:
            n += 8;
            last = 4;
            break;
        case 7:
            n += 11;
            last = 8;
            break;
        case 8:
            n += 14;
            last = 2;
            break;
        case 9:
            n += 17;
            last = 6;
            break;
        default:
            return n;
            break;
        }
    }
    k -= k_even * 2;
    for(sec = 0; sec < k; sec++) {
        n += last;
        last <<= 1;
        if(last >= 10) {
            last -= 10;
        }
    }
    return n;
}

// long int tableau(long int n, int k) {
//     long last = n % 10;
//     for(int sec = 0; sec < k; sec++) {
//         n += last;
//         last <<= 1;
//         if(last >= 10) {
//             last -= 10;
//         }
//     }
//     return n;
// }

void test1() {
    long int res = tableau(1, 10);
    assert(res == 44);
    std::cout << "OK!\n";
}

void test2() {
    long int res = tableau(5, 1);
    assert(res == 10);
    std::cout << "OK!\n";
}

void test3() {
    long int res = tableau(2335, 1000000000);
    assert(res == 2340);
    std::cout << "OK!\n";
}

void test4() {
    long int res = tableau(999999998, 1000000000);
    assert(res == 5999999998);
    std::cout << "OK!\n";
}

void test5() {
    long int res = tableau(3, 3);
    assert(res == 14);
    std::cout << "OK!\n";
}

void test6() {
    long int res = tableau(7, 10);
    assert(res == 58);
    std::cout << "OK!\n";
}

void test7() {
    long int res = tableau(9, 11);
    assert(res == 72);
    std::cout << "OK!\n";
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
    std::cout << "all tests passed!\n";
    return 0;
#endif
    int n, k;
    std::cin >> n >> k;
    long int res = tableau(n, k);
    std::cout << res;
    return 0;
}