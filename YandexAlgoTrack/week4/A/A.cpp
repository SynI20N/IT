#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

struct trip {
	int from;
	int to;
}; // max = 24 * 60 = 1440 

trip convert_to_trip(std::string& info) {
	int st_hours = std::stoi(info.substr(0, 2));
	int st_mins = std::stoi(info.substr(3, 2));
	int en_hours = std::stoi(info.substr(6, 2));
	int en_mins = std::stoi(info.substr(9, 2));
	return {st_hours * 60 + st_mins, en_hours * 60 + en_mins};
}

int minbuses(std::vector<trip>& N, std::vector<trip>& M) {
	int max_minutes = 1440;
	int minutes1[max_minutes] = {0};
	int minutes2[max_minutes] = {0};
	for(trip p : N) {
		minutes1[p.from]++;
		minutes2[p.to]--;
	}
	for(trip p : M) {
		minutes2[p.from]++;
		minutes1[p.to]--;
	}
	int buses1[max_minutes] = {0};
	buses1[0] = minutes1[0];
	for(int i = 1; i < max_minutes - 1; i++) {
		buses1[i] = buses1[i-1] + minutes1[i];
	}
	int buses2[max_minutes] = {0};
	buses2[0] = minutes2[0];
	for(int i = 1; i < max_minutes - 1; i++) {
		buses2[i] = buses2[i-1] + minutes2[i];
	}
	int max1 = buses1[0];
	int max2 = buses2[0];
	for(int i = 0; i < max_minutes - 1; i++) {
		if(buses1[i] > max1) {
			max1 = buses1[i];
		}
		if(buses2[i] > max2) {
			max2 = buses2[i];
		}
	}
	max1 = max1 > 0 ? max1 : 0;
	max2 = max2 > 0 ? max2 : 0;
	return max1 + max2;
}

void test1() {
	std::vector<std::string> to_office{
		"06:45-10:20",
		"07:36-11:26",
		"19:00-22:35",
		"20:08-23:58"
	};
	std::vector<std::string> from_office{
		"06:35-10:10",
		"07:15-11:10",
		"11:00-14:48",
		"14:00-17:48",
		"15:40-19:28",
		"18:35-22:23",
		"20:20-23:55"
	};
	std::vector<trip> N;
	for(std::string& s : to_office) {
		N.push_back(convert_to_trip(s));
	}
	std::vector<trip> M;
	for(std::string& s : from_office) {
		M.push_back(convert_to_trip(s));
	}
	int res = minbuses(N, M);
	int answ = 7;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test2() {
	std::vector<std::string> to_office{
		"10:00-12:00",
		"15:00-17:00"
	};
	std::vector<std::string> from_office{
		"12:30-14:30",
		"17:30-19:30"
	};
	std::vector<trip> N;
	for(std::string s : to_office) {
		N.push_back(convert_to_trip(s));
	}
	std::vector<trip> M;
	for(std::string s : from_office) {
		M.push_back(convert_to_trip(s));
	}
	int res = minbuses(N, M);
	int answ = 1;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test3() {
	std::vector<std::string> to_office{
		"10:10-10:11",
		"10:10-10:11"
	};
	std::vector<std::string> from_office{
		"10:11-10:12",
		"10:11-10:12"
	};
	std::vector<trip> N;
	for(std::string s : to_office) {
		N.push_back(convert_to_trip(s));
	}
	std::vector<trip> M;
	for(std::string s : from_office) {
		M.push_back(convert_to_trip(s));
	}
	int res = minbuses(N, M);
	int answ = 2;
	assert(res == answ);
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
	int n;
	std::cin >> n;
	std::vector<trip> N(n);
	for(int i = 0; i < n; i++) {
		std::string s;
		std::cin >> s;
		N[i] = convert_to_trip(s);
	}
	int m;
	std::cin >> m;
	std::vector<trip> M(m);
	for(int i = 0; i < m; i++) {
		std::string s;
		std::cin >> s;
		M[i] = convert_to_trip(s);
	}
	int res = minbuses(N, M);
	std::cout << res << '\n';
	return 0;
}
