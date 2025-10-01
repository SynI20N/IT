#include <iostream>
#include <unordered_map>
#include <string>
#include <cassert>

long int cyber(std::string s) {
    int n = s.length();
    long int count = 0;
    std::unordered_map<char, long int> c;
    for(char sym : s) {
        c[sym]++;
    }
    for(char sym : s) {
        count += n - c[sym];
    }
    count >>= 1;
    return count + 1;
}

void test1() {
    long int h = cyber("abacaba");
    assert(h == 15);
    std::cout << "OK\n";
}

void test2() {
    long int h = cyber("aaaaaa");
    assert(h == 1);
    std::cout << "OK\n";
}

void test3() {
    std::string a(100000, 'a');
    long int h = cyber(a);
    assert(h == 1);
    std::cout << "OK\n";
}

void test4() {
    std::string a("z");
    long int h = cyber(a);
    assert(h == 1);
    std::cout << "OK\n";
}

void test5() {
    std::string a(100000, 'a');
    a[605] = 'z';
    long int h = cyber(a);
    assert(h == 100000);
    std::cout << "OK\n";
}

int main() {
#ifdef TEST
    test1();
    test2();
    test3();
    test4();
    test5();
    std::cout << "all tests passed!\n";
    return 0;
#endif
    std::string s;
    std::cin >> s;
    long int res = cyber(s);
    std::cout << res << '\n';
    return 0;
}