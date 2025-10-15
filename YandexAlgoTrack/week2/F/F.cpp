#include <iostream>
#include <cassert>
#include <vector>
#include <iomanip>

struct cell {
	bool game_over;
	int max_coins;
};

int game(std::vector<std::vector<char>>& field) {
	int n = field.size();
	std::vector<std::vector<cell>> dp(n, std::vector<cell>(3, {false, 0}));
	int res = 0;
	for(int k = 0; k < 3; k++) {
		if(field[0][k] == 'W') {
			dp[0][k] = {true, 0};
		}
		else if(field[0][k] == 'C') {
			dp[0][k] = {false, 1};
		}
		else {
			dp[0][k] = {false, 0};
		}
		if(dp[0][k].max_coins > res && dp[0][k].game_over != true) {
			res = dp[0][k].max_coins;
		}
	}
	int max_zero;
	for(int i = 1; i < n; i++) {
		dp[i][0] = dp[i-1][0];
		max_zero = -1;
		for(int d = 0; d < 2; d++) {
			if(
				dp[i-1][d].max_coins > max_zero &&
				dp[i-1][d].game_over != true
			) {
				dp[i][0] = dp[i-1][d];
				max_zero = dp[i][0].max_coins;
			}
		}

		dp[i][1] = dp[i-1][0];
		max_zero = -1;
		for(int d = 0; d < 3; d++) {
			if(
				dp[i-1][d].max_coins > max_zero &&
				dp[i-1][d].game_over != true
			) {
				dp[i][1] = dp[i-1][d];
				max_zero = dp[i][1].max_coins;
			}
		}

		dp[i][2] = dp[i-1][1];
		max_zero = -1;
		for(int d = 1; d < 3; d++) {
			if(
				dp[i-1][d].max_coins > max_zero &&
				dp[i-1][d].game_over != true
			) {
				dp[i][2] = dp[i-1][d];
				max_zero = dp[i][2].max_coins;
			}
		}

		for(int j = 0; j < 3; j++) {
			if(field[i][j] == 'W') {
				dp[i][j].game_over = true;
			}
			else if(field[i][j] == 'C') {
				dp[i][j].max_coins++;
			}
			if(dp[i][j].max_coins > res && dp[i][j].game_over != true) {
				res = dp[i][j].max_coins;
			}
		}
	}
	return res;
}

void test1() {
	std::vector<std::vector<char>> field = {
		{'W', '.', 'W'},
		{'C', '.', 'C'},
		{'W', 'W', '.'},
		{'C', 'C', '.'},
		{'C', 'W', 'W'}
	};
	int res = game(field);
	int answ = 3;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test2() {
	std::vector<std::vector<char>> field = {
		{'W', '.', 'W'},
		{'C', 'W', 'C'},
		{'W', '.', 'W'},
		{'C', 'W', 'W'},
	};
	int res = game(field);
	int answ = 2;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test3() {
	std::vector<std::vector<char>> field = {
		{'C', '.', 'W'},
		{'C', '.', 'C'},
		{'W', 'W', 'W'},
		{'C', 'C', '.'},
		{'C', '.', 'C'},
		{'C', '.', 'C'},
		{'.', '.', 'W'}
	};
	int res = game(field);
	int answ = 2;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test4() {
	std::vector<std::vector<char>> field = {
		{'W', 'W', 'W'}
	};
	int res = game(field);
	int answ = 0;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test5() {
	std::vector<std::vector<char>> field(1000, std::vector<char>(3, 'C'));
	int res = game(field);
	int answ = 1000;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test6() {
	std::vector<std::vector<char>> field = {
		{'W', 'W', '.'},
		{'W', '.', 'W'},
		{'C', 'W', 'W'},
		{'W', '.', 'W'},
		{'W', 'W', 'C'},
		{'W', 'C', 'W'},
		{'.', 'W', 'W'},
		{'W', '.', 'W'},
		{'W', 'W', '.'},
		{'.', 'W', 'W'},
		{'.', 'W', 'W'},
		{'W', '.', 'W'},
		{'W', 'W', '.'},
		{'W', 'C', 'W'},
	};
	int res = game(field);
	int answ = 3;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test7() {
	std::vector<std::vector<char>> field = {
		{'C', 'W', 'C'},
		{'C', 'W', '.'},
		{'C', 'W', '.'},
		{'C', 'W', 'C'},
		{'.', 'W', 'C'},
		{'.', 'W', '.'},
		{'.', 'W', 'C'},
		{'W', 'W', '.'},
		{'C', 'W', 'C'},
		{'W', 'W', '.'},
		{'.', 'C', 'C'},
		{'C', '.', '.'},
		{'.', 'C', 'W'},
		{'W', 'W', '.'},
	};
	int res = game(field);
	int answ = 8;
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
	std::cout << "all tests passed!\n";	
	return 0;
#endif
	int n;
	std::cin >> n;
	std::vector<std::vector<char>> field(n, std::vector<char>(3, ' '));
	for(int i = 0; i < n; i++) {
		for(int k = 0; k < 3; k++) {
			std::cin >> field[i][k];
		}
	}
	int res = game(field);
	std::cout << res;
	return 0;
}
