#include <iostream>
#include <cassert>

void test1() {
	std::cout << "OK!\n";
}

void test2() {
	std::cout << "OK!\n";
}

void test3() {
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

	return 0;
}
