#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <iomanip>

struct rect {
	double w;
	double h;
};

bool canmake(double k, std::vector<rect>& words, double W, double H) {
	rect curr = {k * words[0].w, k * words[0].h};
	double t_h = curr.h;
	if(curr.w > W) {
		return false;
	}
	for(int i = 1; i < words.size(); i++) {
		double w_i = k * words[i].w;
		double h_i = k * words[i].h;
		if(h_i == curr.h && curr.w + w_i <= W) {
			curr.w += w_i;
		}
		else {
			curr = {w_i, h_i};
			t_h += curr.h;
		}
	}
	if(t_h <= H) {
		return true;
	}
	return false;
}

double makeup(std::vector<rect>& words, double W, double H) {
	double lo = 0.0;
	double hi = 10e10;
	double mi;
	while(hi - lo > 1e-6) {
		mi = (lo + hi) / 2;
		if(canmake(mi, words, W, H)) {
			lo = mi;
		}
		else {
			hi = mi;
		}
	}
	return lo;
}

void test1() {
	std::vector<rect> words {
		{4, 3},
		{3, 2},
		{4, 2}
	};
	double res = makeup(words, 10, 7);
	double answ = 1.400000000000199973;
	assert(fabs(res - answ) / std::max(fabs(res), 1.0) <= 10e-6);
	std::cout << "OK!\n";
}

void test2() {
	std::vector<rect> words {
		{2, 1},
		{3, 2},
	};
	double res = makeup(words, 10, 1);
	double answ = 0.333333333333666715;
	assert(fabs(res - answ) / std::max(fabs(res), 1.0) <= 10e-6);
	std::cout << "OK!\n";
}

void test3() {
	std::vector<rect> words {
		{2, 1},
	};
	double res = makeup(words, 1, 10);
	double answ = 0.5;
	assert(fabs(res - answ) / std::max(fabs(res), 1.0) <= 10e-6);
	std::cout << "OK!\n";
}

void test4() {
	std::vector<rect> words {
		{6, 8},
		{4, 7},
		{3, 5},
		{10, 4},
		{3, 6},
		{9, 10},
		{8, 1},
		{5, 4},
		{8, 4},
		{6, 10}
	};
	double res = makeup(words, 316661689, 537133372);
	double answ = 0.5;
	assert(fabs(res - answ) / std::max(fabs(res), 1.0) <= 10e-6);
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
	int N, W, H;
	std::cin >> N >> W >> H;
	std::vector<rect> words(N);
	for(int i = 0; i < words.size(); i++) {
		std::cin >> words[i].w >> words[i].h;
	}
	double res = makeup(words, W, H);
	std::cout << std::setprecision(12) << res;
	return 0;
}
