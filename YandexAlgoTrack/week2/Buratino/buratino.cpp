#include <iostream>
#include <cassert>
#include <vector>

/***
 * @brief convert known time to seconds
 */
int time_to_secs(int hours, int mins, int secs) {
	return hours * 3600 + mins * 60 + secs;
}

/**
 * @brief convert symbol to digit
 */
int to_digit(char sym) {
	return sym - 48;
}

int nails(std::vector<std::pair<int, int>>& timetable) {
	return 8;
}

void test1() {
	std::vector<std::pair<int, int>> timetable = { 
		{9 * 3600, 3600},
		{14 * 3600, 3600}
	};
	int res = nails(timetable);
	assert(res == 8);
	std::cout << "OK!\n";
}

void test2() {
	std::vector<std::pair<int, int>> timetable = { 
		{time_to_secs(9,0,0), 1800},
		{time_to_secs(12,59,31), 10},
		{time_to_secs(13,45,23), 1800},
		{time_to_secs(15,0,0), 3600}
	};
	int res = nails(timetable);
	assert(res == 14);
	std::cout << "OK!\n";
}

int main() {
#ifdef TEST
	test1();
	test2();
	std::cout << "all tests passed!\n";
	return 0;
#endif
	int n;
	std::cin >> n;
	std::vector<std::pair<int, int>> times(n, {0,0});
	for(int i = 0; i < n; i++) {
		std::string time;
		std::cin >> time;
		int hours, mins, secs;
		hours = to_digit(time[0]) * 10 + to_digit(time[1]); // time[2] == ":"
		mins = to_digit(time[3]) * 10 + to_digit(time[4]); //time[5] == ":"
		secs = to_digit(time[6]) * 10 + to_digit(time[7]);
		int t;
		std::cin >> t;
		times[i] = {hours * 3600 + mins * 60 + secs, t};
	}
	int res = nails(times);
	std::cout << res;
	return 0;
}
