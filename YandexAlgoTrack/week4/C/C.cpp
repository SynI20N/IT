#include <iostream>
#include <cassert>
#include <vector>
#include <queue>

struct event {
	char type;
	int query;
};

struct inter {
	int left;
	int right;
};

std::vector<int> fitcand(std::vector<int>& cands, int x, std::vector<event>& events) {
	std::vector<char> fit;
	for(int i : cands) {
		fit.push_back(i >= x);
	}
	int low = 0;
	std::queue<inter> queries;
	for(event e : events) {
		if(e.type == 2) {
			low++;
		}
		if(e.type == 1) {
			fit.push_back(e.query >= x);
		}
		if(e.type == 3) {
			queries.push({low, low + e.query - 1});
		}
	}
	std::vector<int> prefix(fit.size());
	prefix[0] = fit[0];
	for(int i = 1; i < fit.size(); i++) {
		prefix[i] = prefix[i-1] + fit[i];
	}
	std::vector<int> res;
	while(!queries.empty()) {
		inter i = queries.front();
		if(i.right < i.left) {
			res.push_back(0);
			queries.pop();
			continue;
		}
		int fit_count = prefix[i.right] - prefix[i.left] + fit[i.left];
		res.push_back(fit_count);
		queries.pop();
	}
	return res;
}

void test1() {
	std::vector<int> cands{3};
	std::vector<event> events{
		{1, 2},
		{1, 1},
		{3, 0},
		{3, 1},
		{3, 2}
	};
	int x = 2;
	std::vector<int> res = fitcand(cands, x, events);
	std::vector<int> answ = {0, 1, 2};
	assert(res.size() == answ.size());
	for(int i = 0; i < res.size(); i++) {
		assert(res[i] == answ[i]);
	}
	std::cout << "OK!\n";
}

void test2() {
	std::vector<int> cands{1, 2};
	std::vector<event> events{
		{3, 0},
		{3, 1},
		{2, -1},
		{3, 0},
		{1, 3},
		{3, 0},
		{3, 1}
	};
	int x = 2;
	std::vector<int> res = fitcand(cands, x, events);
	std::vector<int> answ = {0, 0, 0, 0, 1};
	assert(res.size() == answ.size());
	for(int i = 0; i < res.size(); i++) {
		assert(res[i] == answ[i]);
	}
	std::cout << "OK!\n";
}

void test3() {
	std::vector<int> cands{1000000000};
	std::vector<event> events{
		{3, 1},
	};
	int x = 50000;
	std::vector<int> res = fitcand(cands, x, events);
	std::vector<int> answ = {1};
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
	int n, x;
	std::cin >> n >> x;
	std::vector<int> cands(n, 0);
	for(int i = 0; i < n; i++) {
		std::cin >> cands[i];
	}
	int m;
	std::cin >> m;
	std::vector<event> events(m, {0,0});
	for(int i = 0; i < m; i++) {
		int type;
		std::cin >> type;
		events[i].type = type;
		if(type != 2) {
			std::cin >> events[i].query;
		}
	}
	std::vector<int> res = fitcand(cands, x, events);
	for(const int& i : res) {
		std::cout << i << '\n';
	}
	return 0;
}
