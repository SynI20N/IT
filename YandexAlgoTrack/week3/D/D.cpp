#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <algorithm>

struct data {
	int i;
	int j;
	double value;
};

struct save_order {
	int i;
	int value;
};

double eval(std::vector<save_order>& tabs, int i, int j) {
	return (double)tabs[i].value / (double)tabs[j].value;
}

int modified_binary_search(std::vector<save_order>& tabs, int i, double x) {
	int lo = 0;
	int hi = tabs.size() - 1;
	int mi;
	int min_mi = 0;
	double R_min = fabs(eval(tabs, i , 0) - x);
	while(lo <= hi) {
		mi = floor((lo + hi) >> 1);
		double R = fabs(eval(tabs, i , mi) - x);
		if(R < R_min) {
			R_min = R;
			min_mi = mi;
		}
		if(eval(tabs, i, mi) == x) {
			return mi;
		}
		else if(eval(tabs, i, mi) > x) {
			lo = mi + 1;
		}
		else {
			hi = mi - 1;
		}
	}
	return min_mi;
}

std::pair<int, int> bestfit(std::vector<int>& tabs, int p) {
	std::vector<save_order> save;
	for(int i = 0; i < tabs.size(); i++) {
		save.push_back({i + 1, tabs[i]});
	}
	std::sort(save.begin(), save.end(), [](const save_order& a, const save_order& b) {
		return a.value < b.value;
	});
	std::vector<data> int_res;
	for(int i = 0; i < save.size(); i++) {
		int k = modified_binary_search(save, i, p);
		if(k != i) {
			int_res.push_back({save[i].i, save[k].i, eval(save, i, k)});
		}
	}
	std::pair<int, int> res = {int_res[0].i,  int_res[0].j};
	double best = int_res[0].value;
	for(int i = 1; i < int_res.size(); i++) {
		if(fabs((double)int_res[i].value - (double)p) < fabs((double)best - (double)p)) {
			best = int_res[i].value;
			res = {int_res[i].i,  int_res[i].j};
		}
	}
	return res;
}

void test1() {
	std::vector<int> input{1, 6, 3};
	int p = 2;
	std::pair<int, int> res = bestfit(input, p);
	std::pair<int, int> answ = {2, 3};
	assert(res.first == answ.first);
	assert(res.second == answ.second);
	std::cout << "OK!\n";
}

void test2() {
	std::vector<int> input{2, 3, 4, 5};
	int p = 3;
	std::pair<int, int> res = bestfit(input, p);
	std::pair<int, int> answ = {4, 1};
	assert(res.first == answ.first);
	assert(res.second == answ.second);
	std::cout << "OK!\n";
}

void test3() {
	std::vector<int> input{1, 10};
	int p = 7;
	std::pair<int, int> res = bestfit(input, p);
	std::pair<int, int> answ = {2, 1};
	assert(res.first == answ.first);
	assert(res.second == answ.second);
	std::cout << "OK!\n";
}

void test4() {
	std::vector<int> input(100000, 10);
	int p = 2;
	std::pair<int, int> res = bestfit(input, p);
	std::pair<int, int> answ = {1, 1};
	assert(res.first == answ.first);
	assert(res.second == answ.second);
	std::cout << "OK!\n";
}

void test5() {
	std::vector<int> input{2, 3, 4, 5};
	int p = 1000000000;
	std::pair<int, int> res = bestfit(input, p);
	std::pair<int, int> answ = {4, 1};
	assert(res.first == answ.first);
	assert(res.second == answ.second);
	std::cout << "OK!\n";
}

void test6() {
	std::vector<int> input{
		592871530, 953378019, 261828205,
		29415, 34720, 28032, 669900214, 430846897,
		987069427, 57536114, 1400, 901, 185150389,
		495808512, 40663, 205724613, 157056091, 895667559,
		60621, 141263709, 612190254, 20830, 327126452,
		195885099, 21455, 48624, 564892165, 887461531,
		48902, 675086867, 60882, 161502996, 977048557, 
		56002, 33147, 61890621, 432831915, 635946898,
		116273140, 2596, 392787896, 45140, 57165, 12918,
		34492, 23332, 36791, 39540, 51586, 589785058, 23715,
		13535, 31606, 12670, 45579, 11746, 43063, 32660, 12234, 
		366667586, 23844, 826891985, 55559, 54530, 512967828, 
		313752760, 81830275, 89595293, 24807, 4949, 298958450,
		44322, 579805688, 600801250
	};
	std::cout << input[65] / input[57] << '\n';
	int p = 9603;
	std::pair<int, int> res = bestfit(input, p);
	std::pair<int, int> answ = {66, 58};
	assert(res.first == answ.first);
	assert(res.second == answ.second);
	std::cout << "OK!\n";
}

int main() {
#ifdef TEST
	test1();
	test2();
	test3();
	//test4();
	test5();
	test6();
	std::cout << "all tests passed!\n";	
	return 0;
#endif
	int n, p;
	std::cin >> n >> p;
	std::vector<int> c(n, 0);
	for(int i = 0; i < n; i++) {
		std::cin >> c[i];
	}
	std::pair<int, int> res = bestfit(c, p);
	std::cout << res.first << ' ' << res.second;
	return 0;
}
