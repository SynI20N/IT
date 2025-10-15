#include <iostream>
#include <cassert>
#include <vector>

int camp(std::string& river) {
	int n = river.size();
	std::vector<std::vector<int>> dp(2, std::vector<int>(n+1, 0));
	dp[0][0] = 1;
	dp[1][0] = 0;
	for(int i = 0; i < n; i++) {
		char sym = river[i];
		if(sym == 'B') {
			dp[0][i+1] = dp[0][i] + 1;
			dp[1][i+1] = dp[1][i] + 1;
		}
		else if(sym == 'L') {
			dp[0][i+1] = dp[0][i];
			dp[1][i+1] = dp[1][i] + 1;
		}
		else {
			dp[0][i+1] = dp[0][i] + 1;
			dp[1][i+1] = dp[1][i];
		}
		if(dp[1][i+1] + 1 < dp[0][i+1]) {
			dp[0][i+1] = dp[1][i+1] + 1;
		}
		if(dp[0][i+1] + 1 < dp[1][i+1]) {
			dp[1][i+1] = dp[0][i+1] + 1;
		}
	}
	return dp[0][n];
}

void test1() {
	std::string in = "LLBLRRBRL";
	int res = camp(in);
	assert(res == 5);
	std::cout << "OK!\n";
}

void test2() {
	std::string in = "";
	int res = camp(in);
	assert(res == 1);
	std::cout << "OK!\n";
}

void test3() {
	std::string in = std::string(200, 'L');
	int res = camp(in);
	assert(res == 1);
	std::cout << "OK!\n";
}

void test4() {
	std::string in = std::string(200, 'R');
	int res = camp(in);
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
	std::string s;
	std::cin >> s;
	std::cout << camp(s);
	return 0;
}
