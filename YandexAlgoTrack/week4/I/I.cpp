#include <iostream>
#include <cassert>
#include <vector>
//#include <set>
#include <cmath>
#include <unordered_set>

struct point {
	int x;
	int y;
};

bool operator<(const point& a, const point& b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

struct PointHash {
    std::size_t operator()(const point& p) const {
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
};

struct PointEqual {
    bool operator()(const point& a, const point& b) const {
        return a.x == b.x && a.y == b.y;
    }
};

long long findpairs(std::vector<point>& trees, int d) {
    std::unordered_set<point, PointHash, PointEqual> points;
    for(const point& t : trees) {
        points.insert(t);
    }
    std::vector<std::pair<int, int>> possible_pairs;
    for(int a = 0; a * a <= d; a++) {
		int b_s = d - a * a;
        int b = (int)std::sqrt(b_s);
        if(b * b == b_s) {
			possible_pairs.emplace_back(a, b);
        }
    }
	long long res = 0;
    for(const point& t : trees) {
        for(const auto& [a, b] : possible_pairs) {
            res += points.count({t.x + a, t.y + b});
            if (a != 0) res += points.count({t.x - a, t.y + b});
            if (b != 0) res += points.count({t.x + a, t.y - b});
            if (a != 0 && b != 0) res += points.count({t.x - a, t.y - b});
        }
    }
    return res / 2;
}

void test1() {
	std::vector<point> trees{
		{0, 0},
		{1, 0},
		{1, 1},
		{0, 1},
		{-1, 1},
		{-1, 0},
		{-1, -1},
		{0, -1},
		{1, -1}
	};
	long long res = findpairs(trees, 1);
	long long answ = 12;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test2() {
	std::vector<point> trees{
		{0, 0},
		{1, 0},
		{1, 1},
		{0, 1},
		{-1, 1},
		{-1, 0},
		{-1, -1},
		{0, -1},
		{1, -1}
	};
	long long res = findpairs(trees, 10e8);
	long long answ = 0;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test3() {
	std::vector<point> trees{
		{0, 0},
	};
	long long res = findpairs(trees, 1);
	long long answ = 0;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test4() {
	std::vector<point> trees(100000, {0, 0});
	for(int i = 0; i < 100000; i++) {
		trees[i] = {-100000000 + i, 100000000 - i};
	}
	long long res = findpairs(trees, 100000000);
	long long answ = 0;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test5() {
	srand(time(0));
    std::vector<point> trees(100000);
    for(int i = 0; i < 100000; i++) {
        trees[i].x = rand() % 200000001 - 100000000;
        trees[i].y = rand() % 200000001 - 100000000;
    }
    
    int d = 100000000;
    
    clock_t start = clock();
    long long res = findpairs(trees, d);
    clock_t end = clock();
    
    double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
    assert(elapsed_secs < 7);
    assert(res >= 0);

    std::cout << "OK! Time: " << elapsed_secs << " seconds\n";
}

void test6() {
	std::vector<point> trees{
		{0, 0},
		{0, 100},
		{-100, -100}
	};
	long long res = findpairs(trees, 10000);
	long long answ = 1;
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
	std::cout << "all tests passed!\n";	
	return 0;
#endif
	int n, d;
	std::cin >> n >> d;
	std::vector<point> points(n, {0, 0});
	for (int i = 0; i < n; i++) {
        std::cin >> points[i].x >> points[i].y;
    }
	long long res = findpairs(points, d);
	std::cout << res << '\n';
	return 0;
}
