#include <iostream>
#include <vector>
#include <cassert>

bool win(std::vector<std::vector<char>>& M) {
    int n = M.size();
    int m = M[0].size();
    // Обход горизонталей
    for(int i = 0; i < n; i++) {
        int count = 1;
        for(int j = 1; j < m; j++) {
            if(M[i][j] == M[i][j-1] && M[i][j] != '.') {
                count++;
            }
            else {
                count = 1;
            }
            if(count == 5) {
                return true;
            }
        }
    }
    // Обход вертикалей
    for(int i = 0; i < m; i++) {
        int count = 1;
        for(int j = 1; j < n; j++) {
            if(M[j][i] == M[j-1][i] && M[j][i] != '.') {
                count++;
            }
            else {
                count = 1;
            }
            if(count == 5) {
                return true;
            }
        }
    }
    // Обход главных диагоналей
    for (int d = 0; d < n; ++d) {
        int count = 1;
        for (int i = 0, j = d; i < n && j < n; ++i, ++j) {
            if(i - 1 < 0 || i - 1 >= n || j - 1 < 0 || j - 1 >= m) {
                count = 1;
                continue;
            }
            if(M[i][j] == M[i-1][j-1] && M[i][j] != '.') {
                count++;
            }
            else {
                count = 1;
            }
            if(count == 5) {
                return true;
            }
        }
    }
    for (int d = 1; d < n; ++d) {
        int count = 1;
        for (int i = d, j = 0; i < n && j < n; ++i, ++j) {
            if(i - 1 < 0 || i - 1 >= n || j - 1 < 0 || j - 1 >= m) {
                count = 1;
                continue;
            }
            if(M[i][j] == M[i-1][j-1] && M[i][j] != '.') {
                count++;
            }
            else {
                count = 1;
            }
            if(count == 5) {
                return true;
            }
        }
    }
    // Обход побочных диагоналей
    for (int d = 0; d < n; ++d) {
        int count = 1;
        for (int i = 0, j = n - 1 - d; i < n && j >= 0; ++i, --j) {
            if(i - 1 < 0 || i - 1 >= n || j + 1 < 0 || j + 1 >= m) {
                count = 1;
                continue;
            }
            if(M[i][j] == M[i-1][j+1] && M[i][j] != '.') {
                count++;
            }
            else {
                count = 1;
            }
            if(count == 5) {
                return true;
            }
        }
    }
    for (int d = 1; d < n; ++d) {
        int count = 1;
        for (int i = d, j = n - 1; i < n && j >= 0; ++i, --j) {
            if(i - 1 < 0 || i - 1 >= n || j + 1 < 0 || j + 1 >= m) {
                count = 1;
                continue;
            }
            if(M[i][j] == M[i-1][j+1] && M[i][j] != '.') {
                count++;
            }
            else {
                count = 1;
            }
            if(count == 5) {
                return true;
            }
        }
    }
    return false;
}

void test1() {
    std::vector<std::vector<char>> M = {
        {'.', 'O', 'X', 'O', 'X', 'O'},
        {'O', 'X', 'X', '.', 'O', '.'},
        {'X', 'X', 'O', 'O', 'X', 'X'},
        {'.', '.', 'O', '.', '.', 'O'},
        {'O', 'O', 'X', 'X', '.', 'X'},
    };
    bool res = win(M);
    bool answ = true;
    assert(res == answ);
    std::cout << "OK!\n";
}

void test2() {
    std::vector<std::vector<char>> M = {
        {'X', 'X', '.', '.', '.', '.'},
        {'.', 'X', 'X', 'X', 'X', 'X'},
    };
    bool res = win(M);
    bool answ = true;
    assert(res == answ);
    std::cout << "OK!\n";
}

void test3() {
    std::vector<std::vector<char>> M = {
        {'X', 'X', 'X', 'O', 'X', '.'},
        {'O', 'X', 'X', 'X', 'O', '.'},
        {'O', 'X', 'X', 'O', 'X', 'X'},
        {'X', '.', '.', 'X', 'O', '.'},
        {'O', 'O', 'X', 'X', 'X', 'X'},
    };
    bool res = win(M);
    bool answ = true;
    assert(res == answ);
    std::cout << "OK!\n";
}

void test4() {
    std::vector<std::vector<char>> M = {
        {'.', 'O', 'X', 'O', 'X', 'O'},
        {'O', 'X', 'X', '.', 'X', '.'},
        {'X', 'X', 'O', 'O', 'X', 'X'},
        {'.', '.', '.', '.', '.', 'O'},
        {'O', 'O', 'X', 'X', '.', 'X'},
    };
    bool res = win(M);
    bool answ = false;
    assert(res == answ);
    std::cout << "OK!\n";
}

void test5() {
    std::vector<std::vector<char>> M(1000, std::vector<char>(1000, '.'));
    bool res = win(M);
    bool answ = false;
    assert(res == answ);
    std::cout << "OK!\n";
}

void test6() {
    std::vector<std::vector<char>> M = {
        {'.', 'O', 'X', 'O', 'X', 'O'},
        {'O', '.', '.', 'X', '.', 'X'},
        {'O', 'X', 'X', 'X', '.', 'X'},
        {'O', 'O', 'X', 'X', '.', 'X'},
        {'O', 'O', 'X', '.', 'X', '.'},
        {'X', 'O', 'O', 'O', 'X', 'X'},
        {'.', 'O', '.', '.', '.', 'O'},
        {'O', 'O', 'X', 'X', '.', 'X'},
        {'O', 'X', 'O', 'X', 'X', 'X'},
    };
    bool res = win(M);
    bool answ = true;
    assert(res == answ);
    std::cout << "OK!\n";
}

void test7() {
    std::vector<std::vector<char>> M = {
        {'.', 'O', 'X', 'O', 'X', 'O'},
        {'O', '.', '.', 'X', '.', 'X'},
        {'O', 'X', 'O', 'X', 'X', '.'},
        {'O', 'O', 'X', 'X', '.', 'X'},
        {'O', 'O', 'X', '.', 'X', '.'},
        {'X', 'X', 'O', 'O', 'X', 'X'},
        {'.', 'O', '.', '.', '.', 'O'},
        {'O', 'O', 'X', 'X', '.', 'X'},
        {'O', 'X', 'O', 'X', 'X', 'X'},
    };
    bool res = win(M);
    bool answ = true;
    assert(res == answ);
    std::cout << "OK!\n";
}

void test8() {
    std::vector<std::vector<char>> M = {
        {'.'}
    };
    bool res = win(M);
    bool answ = false;
    assert(res == answ);
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
    std::vector<std::vector<char>> M(n, std::vector<char>(m, ' '));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            std::cin >> M[i][j];
        }
    }
    bool res = win(M);
    if(res) {
        std::cout << "Yes";
    }
    else {
        std::cout << "No";
    }
    return 0;
}