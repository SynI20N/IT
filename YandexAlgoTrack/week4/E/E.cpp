#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

struct data {
	int a;
	int b;
};

struct inter {
	int l;
	int r;
};

long long mindisc(std::vector<int>& holes, std::vector<inter>& trips, long long k) {
	int n = holes.size();
	int m = trips.size();
	std::vector<data> greedy(n, {0, 0});
	for(int i = 0; i < n; i++) {
		greedy[i].a = holes[i];
	}
	std::vector<int> trips_pre(n, 0);
	for(int i = 0; i < m; i++) {
		trips_pre[trips[i].l - 1]++;
		if(trips[i].r < n) {
			trips_pre[trips[i].r]--;
		}
	}
	greedy[0].b = trips_pre[0];
	for(int i = 1; i < n; i++) {
		greedy[i].b = greedy[i-1].b + trips_pre[i];
	}
	std::sort(greedy.begin(), greedy.end(), [](const data& l, const data& r) {
		return l.b > r.b; 
	});
	int ptr = 0;
	while(k > 0 && ptr < n) {
		int take = std::min((long long)greedy[ptr].a, k);
		greedy[ptr].a -= take;
		k -= take;
		ptr++;
	}
	long long res = 0;
	for(int i = 0; i < n; i++) {
		res += (long long)greedy[i].a * (long long)greedy[i].b;
	}
	return res;
}

void test1() {
	long long k = 2;
	std::vector<int> holes {1, 2, 3, 4};
	std::vector<inter> trips {
		{1, 4},
		{3, 4}
	};
	long long res = mindisc(holes, trips, k);
	long long answ = 13;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test2() {
	long long k = 5;
	std::vector<int> holes {1, 2, 0, 0};
	std::vector<inter> trips {
		{1, 4},
		{3, 4}
	};
	long long res = mindisc(holes, trips, k);
	long long answ = 0;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test3() {
	long long k = 2;
	std::vector<int> holes {3364287};
	std::vector<inter> trips(33017, {1, 1});
	long long res = mindisc(holes, trips, k);
	long long answ = 33017L * 3364285L;
	assert(res == answ);
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
	int n, m;
	long long k;
	std::cin >> n >> m >> k;
	std::vector<int> holes(n);
	for(int i = 0; i < n; i++) {
		std::cin >> holes[i];
	}
	std::vector<inter> trips(m);
	for(int i = 0; i < m; i++) {
		std::cin >> trips[i].l >> trips[i].r;
	}
	long long res = mindisc(holes, trips, k);
	std::cout << res << '\n';
	return 0;
}
