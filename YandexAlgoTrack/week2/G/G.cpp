#include <iostream>
#include <cassert>
#include <vector>

int ladders(int n) {
	std::vector<std::vector<int>> dp(n+2, std::vector<int>(n+1, 0));
	for(int i = 1; i < n+2; i++) {
		dp[i][0] = 1;
	}
	for(int i = 1; i < n+2; i++) {
		for(int j = 1; j < n+1; j++) {
			int h = std::min(j, i-1);
			for(int k = 0; k <= h; k++) {
				dp[i][j] += dp[k][j-k];
			}
		}
	}
	return dp[n+1][n];
}

void test1() {
	int res = ladders(3);
	assert(res == 2);
	std::cout << "OK!\n";
}

void test2() {
	int res = ladders(2);
	assert(res == 1);
	std::cout << "OK!\n";
}

void test3() {
	int res = ladders(1);
	assert(res == 1);
	std::cout << "OK!\n";
}

void test4() {
	int res = ladders(9);
	assert(res == 8);
	std::cout << "OK!\n";
}

int main() {
#ifdef TEST
	test1();
	test2();
	test3();
	test4();
	std::cout << "all tests passed!\n";	
	return 0;
#endif
	int N;
	std::cin >> N;
	std::cout << ladders(N);
	return 0;
}
