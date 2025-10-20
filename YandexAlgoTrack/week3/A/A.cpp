#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

int cut(int a, int b, int S) {
	std::vector<int> search;
	for(int i = 1; i <= S; i++) {
		float x = i - (float)S / i;
		if(roundf(x) == x) {
			if(roundf(x) == b - a) {
				return i + a;
			}
		}
	}
	return -1;
}

void test1() {
	int res = cut(1,1,1);
	int answ = 2;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test2() {
	int res = cut(2,3,12);
	int answ = 6;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test3() {
	int res = cut(1,1,2);
	int answ = -1;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test4() {
	int res = cut(0,0,100000000);
	int answ = 10000;
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
	int a, b, S;
	std::cin >> a >> b >> S;
	std::cout << cut(a, b, S);
	return 0;
}
