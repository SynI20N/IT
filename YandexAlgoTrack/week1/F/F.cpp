#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int pluses(std::vector<std::vector<char>>& M) {
    std::vector<int> rows(M.size(), 0);
    std::vector<int> columns(M[0].size(), 0);
    for(size_t i = 0; i < M.size(); i++) {
        for(size_t j = 0; j < M[0].size(); j++) {
            if(M[i][j] == '?') {
                rows[i]++;
                columns[j]--;
            }
            else if(M[i][j] == '+') {
                rows[i]++;
                columns[j]++;
            }
            else {
                rows[i]--;
                columns[j]--;
            }
        }
    }
    int res = INT32_MIN;
    for(size_t i = 0; i < M.size(); i++) {
        for(size_t j = 0; j < M[0].size(); j++) {
            int row_max = rows[i];
            int column_min = columns[j];
            int ro = 0;
            if(M[i][j] == '?') {
                ro = -2;
            }
            int new_res = row_max - column_min + ro;
            if(new_res > res) {
                res = new_res;
            }
        }
    }
    return res;
}

void test1() {
    std::vector<std::vector<char>> input = {
        {'+', '-', '+'},
        {'?', '?', '-'},
        {'?', '-', '?'},
        {'+', '+', '?'},
    };
    int res = pluses(input);
    assert(res == 5);
    std::cout << "OK!\n";
}

void test2() {
    std::vector<std::vector<char>> input = {
        {'?', '?', '+', '+', '+', '-', '?', '-', '?', '-'},
        {'-', '?', '?', '+', '?', '?', '?', '-', '-', '+'},
        {'?', '-', '+', '?', '+', '-', '?', '+', '-', '-'},
        {'?', '?', '?', '?', '?', '?', '-', '-', '?', '+'},
        {'+', '+', '-', '-', '?', '-', '-', '+', '-', '?'},
        {'?', '-', '?', '+', '+', '+', '?', '+', '-', '?'},
    };
    int res = pluses(input);
    assert(res == 12);
    std::cout << "OK!\n";
}

void test3() {
    std::vector<std::vector<char>> input(1000, std::vector<char>(1000, '?'));
    int res = pluses(input);
    assert(res == 1998);
    std::cout << "OK!\n";
}

void test4() {
    std::vector<std::vector<char>> input(1000, std::vector<char>(1, '-'));
    int res = pluses(input);
    assert(res == 999);
    std::cout << "OK!\n";
}

void test5() {
    std::vector<std::vector<char>> input = {
        {'+', '?', '?'},
        {'-', '?', '?'},
        {'+', '?', '?'},
    };
    int res = pluses(input);
    assert(res == 4);
    std::cout << "OK!\n";
}

void test6() {
    std::vector<std::vector<char>> input(1000, std::vector<char>(1000, '?'));
    input[500] = std::vector<char> (1000, '-');
    int res = pluses(input);
    assert(res == 1998);
    std::cout << "OK!\n";
}

void test7() {
    std::vector<std::vector<char>> input = {
        {'-', '-', '+', '-'},
        {'-', '?', '+', '+'},
        {'-', '-', '?', '+'},
        {'-', '-', '-', '?'},
    };
    int res = pluses(input);
    assert(res == 6);
    std::cout << "OK!\n";
}

void test8() {
    std::vector<std::vector<char>> input = {
        {'+', '+', '?', '+'},
        {'+', '+', '+', '+'},
        {'+', '+', '+', '+'},
        {'+', '+', '+', '+'},
    };
    int res = pluses(input);
    assert(res == 2);
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
    test8();
    std::cout << "all tests passed!\n";
    return 0;
#endif
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<char>> M(n, std::vector<char>(m, '-'));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            std::cin >> M[i][j];
        }
    }
    int res = pluses(M);
    std::cout << res;
    return 0;
}