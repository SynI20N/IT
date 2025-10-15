#include <iostream>
#include <cassert>
#include <vector>
#include <chrono>
#include <algorithm>

struct table_element {
	int value;
	int chain;
	int i, j;
};

int chain(std::vector<std::vector<int>>& table) {
	int n = table.size();
    int m = table[0].size();
    std::vector<table_element> data(n * m);
	int k = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            data[k] = {table[i][j], 1, i, j};
			k++;
        }
    }
    std::sort(data.begin(), data.end(), [](const table_element& a, const table_element& b) {
        return a.value < b.value;
    });
    std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));
    int max_chain = 1;
    for(const auto& elem : data) {
        int i = elem.i;
        int j = elem.j;
        int current_chain = 1;

        if(i > 0 && table[i-1][j] == elem.value - 1)
            current_chain = std::max(current_chain, dp[i-1][j] + 1);
        if(i < n-1 && table[i+1][j] == elem.value - 1)
            current_chain = std::max(current_chain, dp[i+1][j] + 1);
        if(j > 0 && table[i][j-1] == elem.value - 1)
            current_chain = std::max(current_chain, dp[i][j-1] + 1);
        if(j < m-1 && table[i][j+1] == elem.value - 1)
            current_chain = std::max(current_chain, dp[i][j+1] + 1);
        
        dp[i][j] = current_chain;
        max_chain = std::max(max_chain, current_chain);
    }
    
    return max_chain;
}

void test1() {
	std::vector<std::vector<int>> input = {
		{1, 2, 3},
		{6, 5, 4},
		{7, 8, 9}
	};
	int answ = 9;
	int res = chain(input);
	assert(answ == res);
	std::cout << "OK!\n";
}

void test2() {
	std::vector<std::vector<int>> input = {
		{2, 2, 2},
		{2, 3, 2},
		{2, 2, 2}
	};
	int answ = 2;
	int res = chain(input);
	assert(answ == res);
	std::cout << "OK!\n";
}

void test3() {
	std::vector<std::vector<int>> input = {
		{1337}
	};
	int answ = 1;
	int res = chain(input);
	assert(answ == res);
	std::cout << "OK!\n";
}

void test4() {
	std::vector<std::vector<int>> input(1000, std::vector<int>(1000, 10e8));
	int answ = 1;
	int res = chain(input);
	assert(answ == res);
	std::cout << "OK!\n";
}

void test5() {
	std::vector<std::vector<int>> input = {
		{1, 2, 3},
		{8, 9, 4},
		{7, 6, 5},
		{6, 7, 8},
		{5, 4, 3}
	};
	int answ = 9;
	int res = chain(input);
	assert(answ == res);
	std::cout << "OK!\n";
}

void test6() {
	std::vector<std::vector<int>> input = {
		{1, 2, 3},
		{8, 9, 4},
		{7, 6, 5},
		{8, 7, 8},
		{9, 10, 2}
	};
	int answ = 10;
	int res = chain(input);
	assert(answ == res);
	std::cout << "OK!\n";
}

void test7() {
	std::vector<std::vector<int>> input = {
		{5, 6, 7},
		{4, 3, 4},
		{7, 2, 1}
	};
	int answ = 7;
	int res = chain(input);
	assert(answ == res);
	std::cout << "OK!\n";
}

void test8() {
	std::vector<std::vector<int>> input(1000, std::vector<int>(1000, 1));
	for(int i = 0; i < input.size(); i += 2) {
		for(int j = 0; j < input[0].size(); j++) {
			input[i][j] = i * 1000 + j + 1;
		}
	}
	for(int i = 1; i < input.size(); i += 2) {
		for(int j = 0; j < input[0].size(); j++) {
			input[i][j] = i * 1000 + 999 - j + 1;
		}
	}
	int answ = 1000000;
	int res = chain(input);
	assert(answ == res);
	std::cout << "OK!\n";
}

void test9() {
	std::vector<std::vector<int>> input(1000, std::vector<int>(1000, 1));
	for(int i = 0; i < 1000; i++) {
		for(int k = 0; k < 10; k++) {
			for(int j = 100 * k; j < 100*(k+1); j++) {
				input[i][j] = i + k + 1;
			}
		}
	}
	int answ = 1001;
	int res = chain(input);
	assert(answ == res);
	std::cout << "OK!\n";
}

void test10() {
	std::vector<std::vector<int>> input = {
		{3, 10, 2, 11},
		{10, 4, 11, 12},
		{11, 5, 10, 9},
		{11, 6, 7,  8},
	};
	int answ = 9;
	int res = chain(input);
	assert(answ == res);
	std::cout << "OK!\n";
}

void test11() {
	std::vector<std::vector<int>> input(1000, std::vector<int>(1000, 1));
	for(int i = 0; i < 500; i++) {
		for(int j = 0; j < 1000; j++) {
			input[i][j] = 99;
		}
	}
	for(int i = 500; i < 1000; i++) {
		for(int j = 0; j < 1000; j++) {
			input[i][j] = 100;
		}
	}
	int answ = 2;
	int res = chain(input);
	assert(answ == res);
	std::cout << "OK!\n";
}

void timed(void func()) {
	auto start = std::chrono::high_resolution_clock::now();
	func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "test time: " << elapsed.count() << '\n';
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
	test10();
	timed(test9);
	timed(test11);
	std::cout << "all tests passed!\n";	
	return 0;
#endif
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int>> table(n, std::vector<int>(m, 0));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			std::cin >> table[i][j];
		}
	}
	int res = chain(table);
	std::cout << res;
	return 0;
}
