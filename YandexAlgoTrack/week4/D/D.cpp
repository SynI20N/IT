#include <iostream>
#include <cassert>
#include <vector>

struct result {
	long long min;
	int l;
	int r;
};

result friendship(std::vector<int>& sweets) {
	int left = 0;
	int right = sweets.size() - 1;
	long long sum_l = sweets[left];
	long long sum_r = sweets[right];
	result res = {abs(sum_l - sum_r), left, right};
	while(left < right) {
		long long curr_min = abs(sum_l - sum_r);
		if(curr_min < res.min) {
			res.min = curr_min;
			res.l = left;
			res.r = right;
		}
		if(sum_l < sum_r) {
			left++;
			sum_l += sweets[left];
		}
		else if(sum_l > sum_r) {
			right--;
			sum_r += sweets[right];
		}
		else {
			return {0, left + 1, right + 1};
		}
	}
	res.l++;
	res.r++;
	return res;
}

void test1() {
	std::vector<int> input {5, 1, 1, 1, 1};
	result res = friendship(input);
	result answ = {1, 1, 2};
	assert(res.min == answ.min);
	assert(res.l == answ.l);
	assert(res.r == answ.r);
	std::cout << "OK!\n";
}

void test2() {
	std::vector<int> input {1, 2, 3, 4};
	result res = friendship(input);
	result answ = {1, 2, 4};
	assert(res.min == answ.min);
	assert(res.l == answ.l);
	assert(res.r == answ.r);
	std::cout << "OK!\n";
}

void test3() {
	std::vector<int> input {5, 1, 1, 1, 1, 100, 2, 1};
	result res = friendship(input);
	result answ = {2, 1, 7};
	assert(res.min == answ.min);
	assert(res.l == answ.l);
	assert(res.r == answ.r);
	std::cout << "OK!\n";
}

void test4() {
	std::vector<int> input {1000, 1199, 200, 200, 200, 200, 200, 200, 200, 200};
	result res = friendship(input);
	result answ = {0, 1, 6};
	assert(res.min == answ.min);
	assert(res.l == answ.l);
	assert(res.r == answ.r);
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
	std::vector<int> input(n, 0);
	for(int i = 0; i < n; i++) {
		std::cin >> input[i];
	}
	result res = friendship(input);
	std::cout << res.min << ' ' << res.l << ' ' << res.r << '\n';
	return 0;
}
