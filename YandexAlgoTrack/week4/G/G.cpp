#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

long long compute(int e, std::vector<int>& s, std::vector<int>& a) {
	long long res = 0;
	for(int i = 0; i < s.size(); i++) {
		res += (long long)a[i] * (long long)abs(e - s[i]);
	}
	return res;
}

std::pair<int, long long> series(std::vector<int>& s, std::vector<int>& a) {
	int lo = *std::min_element(s.begin(), s.end());
	int hi = *std::max_element(s.begin(), s.end());
	int mi;
	int res_p = 0;
	long long res = compute(0, s, a);
	while(lo <= hi) {
		mi = (lo + hi) / 2;
		long long left = compute(mi - 1, s, a);
		long long right = compute(mi + 1, s, a);
		long long inter = compute(mi, s, a);
		if(inter < res) {
			res = inter;
			res_p = mi;
		}
		if(left == right) {
			hi = mi - 1;
		}
		else if(left < right) {
			hi = mi - 1;
		}
		else {
			lo = mi + 1;
		}
	}
	return {res_p, res};
} 

void test1() {
	std::vector<int> s {6, 7, 8, 8, 7, 7};
	std::vector<int> p {10, 6, 3, 1, 1, 4};
	std::pair<int, long long> res = series(s, p);
	std::pair<int, long long> answ = {7, 14};
	assert(res.first == answ.first);
	assert(res.second == answ.second);
	std::cout << "OK!\n";
}

void test2() {
	std::vector<int> s {7, 5, 7, 9, 8};
	std::vector<int> p {10, 8, 7, 8, 5};
	std::pair<int, long long> res = series(s, p);
	std::pair<int, long long> answ = {7, 37};
	assert(res.first == answ.first);
	assert(res.second == answ.second);
	std::cout << "OK!\n";
}

void test3() {
	std::vector<int> s {8, 5, 10, 9, 7};
	std::vector<int> p {2, 5, 4, 8, 4};
	std::pair<int, long long> res = series(s, p);
	std::pair<int, long long> answ = {9, 34};
	assert(res.first == answ.first);
	assert(res.second == answ.second);
	std::cout << "OK!\n";
}

void test4() {
	std::vector<int> s {1};
	std::vector<int> p {1};
	std::pair<int, long long> res = series(s, p);
	std::pair<int, long long> answ = {1, 0};
	assert(res.first == answ.first);
	assert(res.second == answ.second);
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
	int n;
	std::cin >> n;
	std::vector<int> s(n, 0);
	std::vector<int> p(n, 0);
	for(int i = 0; i < n; i++) {
		std::cin >> s[i];
	}
	for(int i = 0; i < n; i++) {
		std::cin >> p[i];
	}
	std::pair<int, long long> res = series(s, p);
	std::cout << res.first << ' ' << res.second << '\n';
	return 0;
}
