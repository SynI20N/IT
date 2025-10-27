#include <iostream>
#include <cassert>
#include <vector>

long long premium(std::vector<int>& a) {
	int n = a.size();
	std::vector<int> h(n, 0);
	for(int i = 0; i < n; i++) {
		if(a[i] + i > i + 1) {
			if(i < n - 1) {
				h[i+1] += 1;
			}
			if(a[i] + i < n) {
				h[a[i] + i] -= 1;
			}
		}
	}
	std::vector<int> prefix(n, 0);
	prefix[0] = h[0];
	for(int i = 1; i < n; i++) {
		prefix[i] = prefix[i-1] + h[i];
	}
	long long res = 0;
	for(int i = 0; i < n; i++) {
		res += (long long)prefix[i] * (long long)a[i];
	}
	return res;
}

void test1() {
	std::vector<int> a {4, 2, 2, 4};
	long long res = premium(a);
	long long answ = 14;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test2() {
	std::vector<int> a {1};
	long long res = premium(a);
	long long answ = 0;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test3() {
	std::vector<int> a(100000, 100000);
	long long res = premium(a);
	long long answ = 499995000000000L;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test4() {
	std::vector<int> a {5, 5, 5, 5, 5};
	long long res = premium(a);
	long long answ = 50;
	assert(res == answ);
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
	std::vector<int> a(n, 0);
	for(int i = 0; i < n; i++) {
		std::cin >> a[i];
	}
	std::cout << premium(a) << '\n';
	return 0;
}
