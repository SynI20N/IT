#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>
//#include <chrono>

struct data {
	long long sum;
	int count;
};

long long gravity(const std::vector<int>& A, const std::vector<int>& B) {
    std::unordered_map<int, data> sum_A;
    std::unordered_map<int, data> sum_B;
    for(size_t i = 0; i < A.size(); i++) {
		sum_A[A[i]].count++;
        sum_A[A[i]].sum += i + 1;
    }
    for(size_t i = 0; i < B.size(); i++) {
		sum_B[B[i]].count++;
        sum_B[B[i]].sum += i + 1;
    }
    long long res = 0;
    for(const auto& [val_a, sum_a] : sum_A) {
        for(const auto& [val_b, sum_b] : sum_B) {
            int R = std::abs(val_a - val_b);
            res += R * (sum_b.count*sum_a.sum - sum_a.count*sum_b.sum);
        }
    }
    return res;
}

#ifdef TEST
void timed(void func()) {
	auto start = std::chrono::high_resolution_clock::now();
	func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "test time: " << elapsed.count() << '\n';
}

void test1() {
	std::vector<int> A = {1, 2, 3};
	std::vector<int> B = {1, 2, 3};
	long long res = gravity(A, B);
	long long answ = 0;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test2() {
	std::vector<int> A = {1, 4, 3, 6};
	std::vector<int> B = {8, 1, 1};
	long long res = gravity(A, B);
	long long answ = 34;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test3() {
	std::vector<int> A = {6};
	std::vector<int> B = {10};
	long long res = gravity(A, B);
	long long answ = 0;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test4() {
	std::vector<int> A(100000, 10000);
	std::vector<int> B(100000, 10000);
	long long res = gravity(A, B);
	long long answ = 0;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test5() {
	std::vector<int> A;
	for(int i = 0; i < 10; i++) {
		for(int j = 1; j <= 10000; j++) {
			A.push_back(j);
		}
	}
	std::vector<int> B;
	for(int i = 0; i < 10; i++) {
		for(int j = 10000; j >= 1; j--) {
			B.push_back(j);
		}
	}
	long long res = gravity(A, B);
	long long answ = 0;
	assert(res == answ);
	std::cout << "OK!\n";
}
#endif

int main() {
#ifdef TEST
	test1();
	test2();
	test3();
	test4();
	timed(test5);
	std::cout << "all tests passed!\n";	
	return 0;
#endif
	int n;
	std::cin >> n;
	std::vector<int> A(n, 0);
	for(int i = 0; i < A.size(); i++) {
		std::cin >> A[i];
	}
	int m;
	std::cin >> m;
	std::vector<int> B(m, 0);
	for(int i = 0; i < B.size(); i++) {
		std::cin >> B[i];
	}
	long long res = gravity(A, B);
	std::cout << res;
	return 0;
}
