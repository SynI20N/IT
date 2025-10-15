#include <iostream>
#include <cassert>
#include <vector>

struct case_dp {
	std::vector<int> towers;
	int defence;
};

int def(std::vector<int>& blocks, int l, int r) {
	int res = 0;
	int min = blocks[l];
	for(int i = l; i <= r; i++) {
		res += blocks[i];
		if(blocks[i] < min) {
			min = blocks[i];
		}
	}
	return res * min;
}

std::vector<int> towers(int K, std::vector<int>& blocks) {
	int N = blocks.size();
	std::vector<case_dp> dp(N, {{},0});
	dp[K-1].defence = def(blocks, 0, K-1);
	dp[K-1].towers = {1};
	for(int i = K; i < N; i++) {
		int start_index = i - K + 1;
		if(dp[i-K].defence + def(blocks, start_index, i) > dp[i-1].defence) {
			dp[i] = dp[i-K];
			dp[i].towers.push_back(start_index + 1);
			dp[i].defence += def(blocks, start_index, i);
		}
		else {
			dp[i] = dp[i-1];
		}
	}
	return dp[N-1].towers;
}


void test1() {
	std::vector<int> field = {1};
	std::vector<int> res = towers(1, field);
	std::vector<int> answ = {1};
	for(int i = 0; i < res.size(); i++) {
		std::cout << res[i] << ' ';
	}
	std::cout << '\n';
	assert(res.size() == answ.size());
	for(int i = 0; i < res.size(); i++) {
		assert(res[i] == answ[i]);
	}
	std::cout << "OK!\n";
}

void test2() {
	std::vector<int> field = {1, 1000};
	std::vector<int> res = towers(1, field);
	std::vector<int> answ = {1, 2};
	for(int i = 0; i < res.size(); i++) {
		std::cout << res[i] << ' ';
	}
	std::cout << '\n';
	assert(res.size() == answ.size());
	for(int i = 0; i < res.size(); i++) {
		assert(res[i] == answ[i]);
	}
	std::cout << "OK!\n";
}

void test3() {
	std::vector<int> field = {1, 2, 3, 4, 1, 6, 7, 8};
	std::vector<int> res = towers(3, field);
	std::vector<int> answ = {2, 6};
	assert(res.size() == answ.size());
	for(int i = 0; i < res.size(); i++) {
		assert(res[i] == answ[i]);
	}
	std::cout << "OK!\n";
}

int main() {
#ifdef TEST
	test1();
	test2();
	test3();
	std::cout << "all tests passed!\n";	
	return 0;
#endif
	int n, k;
	std::cin >> n >> k;
	std::vector<int> blocks(n, 0);
	for(int i = 0; i < n; i++) {
		std::cin >> blocks[i];
	}
	std::vector<int> res = towers(k, blocks);
	std::cout << res.size() << '\n';
	for(int i = 0; i < res.size(); i++) {
		std::cout << res[i] << ' ';
	}
	return 0;
}
