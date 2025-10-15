#include <iostream>
#include <iomanip>
#include <cassert>
#include <unordered_map>
#include <vector>

std::string table(std::string& text, int i, int j) {
	std::string buf;
	for(int k = i; k < j + 1; k++) {
		buf += text[k];
	}
	return buf;
}

std::string dictionary(std::string& text, std::unordered_map<std::string, bool>& map) {
	int n = text.length();
	if(n == 0) {
		return "";
	}
	if(n == 1) {
		return std::to_string(text[0]) + ' ';
	}
	std::vector<std::vector<std::string>> dp(n, std::vector<std::string>(n, "?"));
	for(int i = 0; i < n; i++) {
		std::string word(1, text[i]);
		if(map[word]) {
			dp[i][i] = word + ' ';
		}
	}
	for(int d = 1; d < n; d++) {
		for(int i = 0, j = d; i < n, j < n; i++, j++) {
			std::string word = table(text, i, j);
			if(map[word]) {
				dp[i][j] = word + ' ';
			}
			else {
				int k = 0;
				while(k < j) {
					int i1 = i, j1 = k;
					int i2 = k + 1, j2 = j;
					if(dp[i1][j1] != "?" && dp[i2][j2] != "?") {
						dp[i][j] = dp[i1][j1] + dp[i2][j2];
					}
 					k++;
				}
			}
		}
	}
	return dp[0][n-1];
}

void test1() {
	std::string input = "whatcanido";
	std::string answ = "what can i do ";
	std::unordered_map<std::string, bool> map = {
		{"a", true},
		{"an", true},
		{"can", true},
		{"do", true},
		{"i", true},
		{"what", true},
	};
	std::string res = dictionary(input, map);
	assert(res == answ);
	std::cout << "OK!\n";
}

void test2() {
	std::string input = "";
	std::string answ = "";
	std::unordered_map<std::string, bool> map = {
		{"a", true},
		{"an", true},
		{"can", true},
		{"do", true},
		{"i", true},
		{"what", true},
	};
	std::string res = dictionary(input, map);
	assert(res == answ);
	std::cout << "OK!\n";
}

void test3() {
	std::string input = "abcdef";
	std::string answ = "abc d ef ";
	std::unordered_map<std::string, bool> map = {
		{"abc", true},
		{"ef", true},
		{"def", true},
		{"cdef", true},
		{"d", true},
	};
	std::string res = dictionary(input, map);
	assert(res == answ);
	std::cout << "OK!\n";
}

void test4() {
	int count = 300;
	std::string input(count, 'z');
	std::string answ;
	for(int i = 0; i < count; i++) {
		answ += "z ";
	}
	std::unordered_map<std::string, bool> map = {
		{"z", true},
	};
	std::string res = dictionary(input, map);
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
	std::string text;
	std::cin >> text;
	int n;
	std::cin >> n;
	std::unordered_map<std::string, bool> map;
	for(int i = 0; i < n; i++) {
		std::string word;
		std::cin >> word;
		map[word] = true;
	}
	std::cout << dictionary(text, map);
	return 0;
}
