#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

bool canfit(int k, std::vector<int>& a_prev, std::vector<int>& b_prev) {
	std::vector<int> a = a_prev;
	std::vector<int> b = b_prev;
    int n = a.size();
	int b_ptr = 0;
	for (int a_ptr = 0; a_ptr < n; a_ptr++) {
        while (a[a_ptr] > 0) {
            while (b_ptr < n) {
				if(b[b_ptr] != 0 && b_ptr >= a_ptr - k) {
					break;
				}
				b_ptr++;
			}

            if (b_ptr >= n || std::abs(b_ptr - a_ptr) > k) {
                return false;
			}

            int take = std::min(a[a_ptr], b[b_ptr]);
            a[a_ptr] -= take;
            b[b_ptr] -= take;
        }
    }
    return true;
}

int maxrecruit(std::vector<int>& a, std::vector<int>& b) {
	int lo = 0;
	int hi = 1000000;
	int mi;
	int an = -1;
	while(lo <= hi) {
		mi = floor((lo + hi) >> 1);
		if(canfit(mi, a, b)) {
			an = mi;
			hi = mi - 1;
		}
		else {
			lo = mi + 1;
		}
	}
	return an;
}

void test1() {
	std::vector<int> a{6, 14, 70, 1};
	std::vector<int> b{70, 3, 16, 5};
	int res = maxrecruit(a, b);
	int answ = 2;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test2() {
	std::vector<int> a{2};
	std::vector<int> b{2};
	int res = maxrecruit(a, b);
	int answ = 0;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test3() {
	std::vector<int> a{3};
	std::vector<int> b{2};
	int res = maxrecruit(a, b);
	int answ = -1;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test4() {
	std::vector<int> a(1000000, 1);
	std::vector<int> b(1000000, 0);
	int res = maxrecruit(a, b);
	int answ = -1;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test5() {
    std::vector<int> a(1000000, 1000000000);
    std::vector<int> b(1000000, 1000000000);
    assert(maxrecruit(a, b) == 0);
    std::cout << "OK!\n";
}

void test6() {
	std::vector<int> a{1, 2, 2, 2, 2, 2, 2, 2, 1};
	std::vector<int> b{2, 2, 2, 2, 2, 2, 2, 2, 0};
	int res = maxrecruit(a, b);
	int answ = 1;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test7() {
	std::vector<int> a{6, 4, 9, 8, 6, 7, 4, 3, 6, 7};
	std::vector<int> b{8, 7, 7, 11, 6, 4, 6, 4, 7, 9};
	int res = maxrecruit(a, b);
	int answ = 1;
	assert(res == answ);
	std::cout << "OK!\n";
}

int main() {
#ifdef TEST
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	std::cout << "all tests passed!\n";	
	return 0;
#endif
	int n;
	std::cin >> n;
	std::vector<int> a(n, 0);
	for(int i = 0; i < n; i++) {
		std::cin >> a[i];
	}
	std::vector<int> b(n, 0);
	for(int i = 0; i < n; i++) {
		std::cin >> b[i];
	}
	int res = maxrecruit(a, b);
	std::cout << res;
	return 0;
}
