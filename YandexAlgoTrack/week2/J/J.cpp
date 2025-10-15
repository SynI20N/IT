#include <iostream>
#include <cassert>
#include <vector>

struct shop {
	int P, R, Q, F;
};

std::pair<int, std::vector<int>> minbuy(std::vector<shop>& shops, int L) {
	int max_length = 200;
	std::vector<int> zeroes(shops.size(), 0);
	std::vector<std::pair<int, std::vector<int>>> dp(max_length, {0, zeroes});
	for(int i = 1; i < max_length; i++) {
		for(int k = 1; k <= i; k++) {
			std::vector<int> meters = dp[i-k].second;
			int curr_price_all = dp[i-k].first;
			std::vector<int> new_prices(shops.size());
			for(int j = 0; j < new_prices.size(); j++) {
				shop s = shops[j];
				int curr_meters = meters[j];
				if(curr_meters + k <= s.F) {
					if(curr_meters + k < s.R) {
						new_prices[j] = curr_price_all + k * s.P;
					}
					else if(curr_meters < s.R) {
						new_prices[j] = curr_price_all + curr_meters*(s.Q - s.P) + k * s.Q;
					}
					else {
						new_prices[j] = curr_price_all + k * s.Q;
					}
				}
				else {
					new_prices[j] = INT32_MAX;
				}
			}
			int min_index = 0;
			int min_price = new_prices[0];
			for(int i = 0; i < new_prices.size(); i++) {
				if(new_prices[i] < min_price) {
					min_price = new_prices[i];
					min_index = i;
				}
			}
			if(k > 1) {
				if(min_price < dp[i].first) {
					meters[min_index] += k;
					dp[i].first = min_price;
					dp[i].second = meters;
				}
			}
			else {
				meters[min_index] += k;
				dp[i].first = min_price;
				dp[i].second = meters;
			}
		}
	}
	std::pair<int, std::vector<int>> best = dp[L];
	for(int i = L; i < max_length; i++) {
		if(dp[i].first < best.first) {
			best = dp[i];
		}
	}
	if(best.first == INT32_MAX) {
		best.first = -1;
	}
	return best;
}

void test1() {
	std::vector<shop> shops{
		{7,9,6,10},
		{7,8,6,10}
	};
	int L = 14;
	std::pair<int, std::vector<int>> res = minbuy(shops, L);
	std::cout << res.first << ' ' << res.second[0] << ' ' << res.second[1] << '\n';
	std::pair<int, std::vector<int>> answ{88, {4, 10}};
	assert(res.first == answ.first);
	assert(res.second.size() == answ.second.size());
	for(int i = 0; i < res.second.size(); i++) {
		assert(res.second[i] == answ.second[i]);
	}
	std::cout << "OK!\n";
}

void test2() {
	std::vector<shop> shops{
		{1,1,1,1},
	};
	int L = 20;
	std::pair<int, std::vector<int>> res = minbuy(shops, L);
	std::pair<int, std::vector<int>> answ{-1, {1}};
	assert(res.first == answ.first);
	std::cout << "OK!\n";
}

void test3() {
	std::vector<shop> shops{
		{8,7,6,5},
		{7,3,4,5},
		{7,1,2,5}
	};
	int L = 14;
	std::pair<int, std::vector<int>> res = minbuy(shops, L);
	std::pair<int, std::vector<int>> answ{62, {4, 5, 5}};
	assert(res.first == answ.first);
	assert(res.second.size() == answ.second.size());
	for(int i = 0; i < res.second.size(); i++) {
		assert(res.second[i] == answ.second[i]);
	}
	std::cout << "OK!\n";
}

void test4() {
	std::vector<shop> shops{
		{1,1,1,1},
		{1,1,1,1},
		{1,1,1,1}
	};
	int L = 0;
	std::pair<int, std::vector<int>> res = minbuy(shops, L);
	std::pair<int, std::vector<int>> answ{0, {0, 0, 0}};
	assert(res.first == answ.first);
	assert(res.second.size() == answ.second.size());
	for(int i = 0; i < res.second.size(); i++) {
		assert(res.second[i] == answ.second[i]);
	}
	std::cout << "OK!\n";
}

void test5() {
	std::vector<shop> shops{
		{5,3,2,5},
		{7,3,3,4},
	};
	int L = 7;
	std::pair<int, std::vector<int>> res = minbuy(shops, L);
	std::pair<int, std::vector<int>> answ{17, {4, 3}};
	assert(res.first == answ.first);
	assert(res.second.size() == answ.second.size());
	for(int i = 0; i < res.second.size(); i++) {
		assert(res.second[i] == answ.second[i]);
	}
	std::cout << "OK!\n";
}

void test6() {
	std::vector<shop> shops{
		{15,3,2,4},
		{17,3,3,4},
	};
	int L = 5;
	std::pair<int, std::vector<int>> res = minbuy(shops, L);
	std::pair<int, std::vector<int>> answ{15, {3, 3}};
	assert(res.first == answ.first);
	assert(res.second.size() == answ.second.size());
	for(int i = 0; i < res.second.size(); i++) {
		assert(res.second[i] == answ.second[i]);
	}
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
	std::cout << "all tests passed!\n";	
	return 0;
#endif
	int N, L;
	std::cin >> N >> L;
	std::vector<shop> shops(N);
	for(int i = 0; i < N; i++) {
		std::cin >> shops[i].P >> shops[i].R >> shops[i].Q >> shops[i].F;
	}
	std::pair<int, std::vector<int>> res = minbuy(shops, L);
	std::cout << res.first << '\n';
	if(res.first == -1) {
		return 0;
	}
	for(int i = 0; i < res.second.size(); i++) {
		std::cout << res.second[i] << ' ';
	}
	return 0;
}
