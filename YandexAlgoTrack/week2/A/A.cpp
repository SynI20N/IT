#include <iostream>
#include <cassert>
#include <vector>

int ways(int n) {
	std::vector<int> dp(n + 1, 0);
	dp[0] = 1;
	dp[1] = 1;
	dp[2] = 2;
	for(int i = 3; i <= n; i++) {
		dp[i] = dp[i-1] + dp[i-2] + dp[i-3];
	}
	return dp[n];
}

void test1() {
	int res = ways(4);
	assert(res == 7);
	std::cout << "OK!\n";
}

void test2() {
	int res = ways(5);
	assert(res == 13);
	std::cout << "OK!\n";
}

void test3() {
	int res = ways(1);
	assert(res == 1);
	std::cout << "OK!\n";
}

int main() {
#ifdef TEST
	test1();
	test2();
	test3();
	//test4();
	std::cout << "all tests passed!\n";	
	return 0;
#endif
	int N;
	std::cin >> N;
	std::cout << ways(N);
	return 0;
}
