#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cmath>

struct interval {
	double begin;
	double end;
	double weight;
};

int binary_search(const std::vector<interval>& data, int i) {
	int low = 0, high = i - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (data[mid].end <= data[i].begin) {
			if (data[mid + 1].end <= data[i].begin)
				low = mid + 1;
			else
				return mid;
		} else {
			high = mid - 1;
		}
	}
	return -1;
}

double inter(std::vector<interval>& data) {
	int n = data.size();
	if (n == 0) return 0;
	std::sort(data.begin(), data.end(), [](const interval& a, const interval& b) {
		return a.end < b.end;
	});
	std::vector<double> dp(n);
	dp[0] = data[0].weight;
	for (int i = 1; i < n; ++i) {
		double curr_weight = data[i].weight;
		int l = binary_search(data, i);
		if(l != -1) {
			curr_weight += dp[l];
		}
		dp[i] = std::max(dp[i - 1], curr_weight);
	}
	return dp[n - 1];
}

void test1() {
	std::vector<interval> data = {
		{0, 1, 1},
		{0.5, 1.5, 1.5},
		{1, 2, 1}
	};
	double res = inter(data);
	double answ = 2;
	assert(fabs(res-answ) < 1e-4);
	std::cout << "OK!\n";
}

void test2() {
	std::vector<interval> data = {
		{0, 2, 10},
		{0.5, 1.5, 1.5},
		{1, 2, 1},
		{1, 10, 25}
	};
	double res = inter(data);
	double answ = 25;
	assert(fabs(res-answ) < 1e-4);
	std::cout << "OK!\n";
}

void test3() {
	std::vector<interval> data;
	double res = inter(data);
	double answ = 0;
	assert(fabs(res-answ) < 1e-4);
	std::cout << "OK!\n";
}

void test4() {
	std::vector<interval> data = {
		{0, 2, 10.1235},
		{0, 2, 15.6677},
		{0, 2, 13.3338}
	};
	double res = inter(data);
	double answ = 15.6677;
	assert(fabs(res-answ) < 1e-4);
	std::cout << "OK!\n";
}

void test5() {
	std::vector<interval> data = {
		{0, 1, 100},
	};
	double res = inter(data);
	double answ = 100;
	assert(fabs(res-answ) < 1e-4);
	std::cout << "OK!\n";
}

void test6() {
	std::vector<interval> data = {
		{0, 2, 10},
		{1, 3, 20},
		{1.5, 4, 30},
		{2, 5, 40},
	};
	double res = inter(data);
	double answ = 50;
	assert(fabs(res-answ) < 1e-4);
	std::cout << "OK!\n";
}

void test7() {
	std::vector<interval> data = {
		{0, 1, 1},
		{1, 2, 1},
		{2, 3, 1},
		{3, 4, 1},
		{4, 5, 1}
	};
	double res = inter(data);
	double answ = 5;
	assert(fabs(res-answ) < 1e-4);
	std::cout << "OK!\n";
}

void test8() {
	std::vector<interval> data = {
		{0.1, 0.5, 0.5},
		{0.2, 0.3, 0.7},
		{0.3, 0.6, 0.6},
		{0.5, 1.4, 0.6}
	};
	double res = inter(data);
	double answ = 1.3;
	assert(fabs(res-answ) < 1e-4);
	std::cout << "OK!\n";
}

void test9() {
	std::vector<interval> data = {
		{1, 2, 10.1235},
		{1.5, 2, 13.3338},
		{-1.33, 2, 15.6677}
	};
	double res = inter(data);
	double answ = 15.6677;
	assert(fabs(res-answ) < 1e-4);
	std::cout << "OK!\n";
}

void test10() {
	std::vector<interval> data = {
		{1, 10, 100.53},
		{1.5, 2, 13},
		{-1.33, 2, 15},
		{1.33, 2, 15},
		{3.33, 5, 15},
	};
	double res = inter(data);
	double answ = 100.53;
	assert(fabs(res-answ) < 1e-4);
	std::cout << "OK!\n";
}

void test11() {
	std::vector<interval> data = {
		{1, 10, 100},
		{1000, 100000, 500},
	};
	double res = inter(data);
	double answ = 600;
	assert(fabs(res-answ) < 1e-4);
	std::cout << "OK!\n";
}

void test12() {
	std::vector<interval> data = {
		{0, 3, 5},
		{1, 4, 10},
		{4, 6, 7},
	};
	double res = inter(data);
	double answ = 17;
	assert(fabs(res - answ) < 1e-4);
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
	test9();
	test10();
	test11();
	test12();
	std::cout << "all tests passed!\n";	
	return 0;
#endif
	int n;
	std::cin >> n;
	std::vector<interval> data(n);
	for(int i = 0; i < n; i++) {
		std::cin >> data[i].begin >> data[i].end >> data[i].weight;
	}
	double res = inter(data);
	std::cout << res;
	return 0;
}
