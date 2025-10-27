#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>

struct train {
	int a;
	int b;
	int v;
};

struct event {
	double time;
	int diff;
};

struct inter {
	double left;
	double right;
	int val;
};

std::vector<double> trespass(std::vector<train>& trains, std::vector<int>& times, int x) {
	std::vector<event> events;
	for(train t : trains) {
		event e_in;
		event e_out; 
		if(t.a < t.b && t.a <= x) {
			e_in.time = t.b - x < 0 ? (double)abs(t.b - x) / (double)t.v : 0;
			e_in.diff = +1;
			e_out.time = (double)abs(t.a - x) / (double)t.v;
			e_out.diff = -1;
			events.push_back(e_in);
			events.push_back(e_out);
		}
		if(t.a > t.b && t.a >= x) {
			e_in.time = t.b - x > 0 ? (double)abs(t.b - x) / (double)t.v : 0;
			e_in.diff = +1;
			e_out.time = (double)abs(t.a - x) / (double)t.v;
			e_out.diff = -1;
			events.push_back(e_in);
			events.push_back(e_out);
		}
	}
	events.push_back({0.0, 0});
	events.push_back({1000000001.0, 0});
	std::sort(events.begin(), events.end(), [](const event& a, const event& b) {
		return a.time < b.time;
	});
	std::vector<inter> time_intervals;
	double left = 0;
	int prefix = 0;
	for(int i = 1; i < events.size(); i++) {
		prefix += events[i-1].diff;
		inter t;
		if(events[i-1].time == events[i].time) {
			continue;
		}
		if(prefix > 0) {
			t.left = events[i-1].time;
			t.right = events[i].time;
			t.val = 1;
		}
		else {
			t.left = events[i-1].time;
			t.right = events[i].time;
			t.val = 0;
		}
		if(time_intervals.size() > 0) {
			inter& t_prev = time_intervals.back();
			if(t_prev.right == t.left && t_prev.val == t.val) {
				t_prev.right = t.right;
			}
			else {
				time_intervals.push_back(t);
			}
		}
		else {
			time_intervals.push_back(t);
		}
	}
	std::vector<double> res;
	for(int t : times) {
		int lo = 0;
		int hi = time_intervals.size() - 1;
		int mi;
		while(lo <= hi) {
			mi = (lo + hi) / 2;
			if(time_intervals[mi].left == (double)t) {
				hi = mi;
				break;
			}
			else if(time_intervals[mi].left < (double)t) {
				lo = mi + 1;
			}
			else {
				hi = mi - 1;
			}
		}
		if(time_intervals[hi].val == 0) {
			res.push_back(t);
		}
		else {
			res.push_back(time_intervals[hi].right);
		}
	}
	return res;
}

void test1() {
	std::vector<train> trains{
		{-4, -1, 1},
		{13, 6, 3},
		{-7, -6, 1}
	};
	std::vector<int> times{1, 5};
	int x = 0;
	std::vector<double> res = trespass(trains, times, x);
	std::vector<double> answ = {4.333333333, 5.000000000};
	assert(res.size() == answ.size());
	for(int i = 0; i < res.size(); i++) {
		assert(fabs(res[i] - answ[i]) < 10e-6);
	}
	std::cout << "OK!\n";
}

void test2() {
	std::vector<train> trains{
		{4, 2, 1},
		{-11, -8, 2}
	};
	std::vector<int> times{2, 6};
	int x = 0;
	std::vector<double> res = trespass(trains, times, x);
	std::vector<double> answ = {5.500000000, 6.000000000};
	assert(res.size() == answ.size());
	for(int i = 0; i < res.size(); i++) {
		assert(fabs(res[i] - answ[i]) < 10e-6);
	}
	std::cout << "OK!\n";
}

void test3() {
	std::vector<train> trains{
		{-1000000000, +1000000000, 1},
	};
	std::vector<int> times{5};
	int x = 0;
	std::vector<double> res = trespass(trains, times, x);
	std::vector<double> answ = {1000000000.0000000};
	assert(res.size() == answ.size());
	for(int i = 0; i < res.size(); i++) {
		assert(fabs(res[i] - answ[i]) < 10e-6);
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
	std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int n, m, x;
    in >> n >> m >> x;

    std::vector<train> trains(n, {0, 0, 0});
    for (int i = 0; i < n; i++) {
        in >> trains[i].a >> trains[i].b >> trains[i].v;
    }

    std::vector<int> times(m, 0);
    for (int i = 0; i < m; i++) {
        in >> times[i];
    }

    std::vector<double> res = trespass(trains, times, x);
	
    out << std::setprecision(9) << std::fixed;
    for (const double& f : res) {
        out << f << '\n';
    }

    in.close();
    out.close();

    return 0;
}
