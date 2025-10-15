#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

bool prime(int n) {
	if(n == 1) {
		return false;
	}
	for(int i = 2; i <= sqrt(n); i++) {
		if(n % i == 0) {
			return false;
		}
	}
	return true;
}

int matches(int n) {
	std::vector<std::vector<short>> dp(3, std::vector<short>(n+1, 0));
	dp[1][1] = 1;
	dp[1][2] = 1;
	dp[1][3] = 1;
	dp[2][1] = 2;
	dp[2][2] = 2;
	dp[2][3] = 2;
	for(int i = 1; i <= n-3; i++) {
		short f[3] = {0, 0, 0};
		short s[3] = {0, 0, 0};
		for(int k = 0; k < 3; k++) {
			if(!prime(k+i)) {
				f[k] = dp[1][k+i];
				s[k] = dp[2][k+i];
			}
		}
		dp[2][i+3] = 1;
		dp[1][i+3] = 2;
		for(int k = 0; k < 3; k++) {
			if(f[k] == 2) {
				dp[2][i+3] = 2;
			}
			if(s[k] == 1) {
				dp[1][i+3] = 1;
			}
		}
	}
	return dp[1][n];
}

void test1() {
	int res = matches(1);
	assert(res == 1);
	std::cout << "OK!\n";
}

void test2() {
	int res = matches(2);
	assert(res == 1);
	std::cout << "OK!\n";
}

void test3() {
	int res = matches(4);
	assert(res == 2);
	std::cout << "OK!\n";
}

void test4() {
	int res = matches(10);
	assert(res == 1);
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
	std::cout << matches(N);
	return 0;
}
