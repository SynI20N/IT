#include <iostream>
#include <cassert>
#include <vector>

struct tax {
	int power;
	int tax_rate;
};

std::vector<long long> solve(std::vector<tax>& table, std::vector<int> powers) {
	std::vector<long long> res;
	for(int p : powers) {
		int lo = 0;
		int hi = table.size() - 1;
		int mi;
		while(lo <= hi) {
			mi = (lo + hi) / 2;
			if(table[mi].power == p) {
				hi = mi - 1;
			}
			else if(table[mi].power > p) {
				hi = mi - 1;
			}
			else {
				lo = mi + 1;
			}
		}
		res.push_back((long long)table[(lo + hi) / 2].tax_rate * (long long)p);
	}
	return res;
}

void test1() {
	std::vector<tax> taxes{
		{0, 24},
		{100, 35},
		{150, 50},
		{200, 75},
		{250, 150}
	};
	std::vector<int> powers {
		107, 143, 152, 170, 150
	};
	std::vector<long long> res = solve(taxes, powers);
	std::vector<long long> answ {
		3745, 5005, 7600, 8500, 5250
	};
	assert(res.size() == answ.size());
	for(int i = 0; i < res.size(); i++) {
		assert(res[i] == answ[i]);
	}
	std::cout << "OK!\n";
}

void test2() {
	std::vector<tax> taxes;
	for(int i = 100000000; i < 100100000; i++) {
		taxes.push_back({i - 100000000, i});
	}
	std::vector<int> powers(100000, 1000);
	std::vector<long long> res = solve(taxes, powers);
	std::vector<long long> answ(100000, 100000999L * 1000L);
	assert(res.size() == answ.size());
	for(int i = 0; i < res.size(); i++) {
		assert(res[i] == answ[i]);
	}
	std::cout << "OK!\n";
}

void test3() {
	std::vector<tax> taxes{{0, 20}};
	std::vector<int> powers(1, 1);
	std::vector<long long> res = solve(taxes, powers);
	std::vector<long long> answ(1, 20);
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
	int n;
	std::cin >> n;
	std::vector<tax> taxes(n);
	for(int i = 0; i < n; i++) {
		std::cin >> taxes[i].power >> taxes[i].tax_rate;
	}
	int m;
	std::cin >> m;
	std::vector<int> powers(m);
	for(int i = 0; i < m; i++) {
		std::cin >> powers[i];
	}
	std::vector<long long> res = solve(taxes, powers);
	for(long long l : res) {
		std::cout << l << '\n';
	}
	return 0;
}
