#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cassert>

std::vector<int> constr(std::string& s, std::vector<std::string>& p, int m) {
    std::unordered_map<std::string, std::vector<int>> slices;
    int n = s.length();
    int l = n / m;
    for(int k = 0; k < m; k++) {
        slices[p[k]].push_back(k + 1);
    }
    std::vector<int> res(m, 0);
    std::string buf(l, ' ');
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < l; j++) {
            buf[j] = s[l * i + j];
        }
        res[i] = slices[buf].back();
        slices[buf].pop_back();
    }
    return res;
}

void test1() {
    std::string s("cabacaqwerty");
    std::vector<std::string> p = {"erty", "caba", "caqw"};
    std::vector<int> res = constr(s, p, 3);
    std::vector<int> answ = {2, 3, 1};
    assert(res.size() == answ.size());
    for(int i = 0; i < res.size(); i++) {
        assert(res[i] == answ[i]);
    }
    std::cout << "OK!\n";
}

void test2() {
    std::string s(1000000, 'a');
    std::string st(10, 'a');
    std::vector<std::string> p(100000, st);
    std::vector<int> res = constr(s, p, 100000);
    std::vector<int> answ(100000, 1);
    for(int i = 0; i < 100000; i++) {
        answ[i] = 100000 - i;
    }
    assert(res.size() == answ.size());
    for(int i = 0; i < res.size(); i++) {
        assert(res[i] == answ[i]);
    }
    std::cout << "OK!\n";
}

void test3() {
    std::string s("z");
    std::vector<std::string> p = {"z"};
    std::vector<int> res = constr(s, p, 1);
    std::vector<int> answ = {1};
    assert(res.size() == answ.size());
    for(int i = 0; i < res.size(); i++) {
        assert(res[i] == answ[i]);
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
    int n, m;
    std::cin >> n >> m;
    std::string s;
    std::cin >> s;
    std::vector<std::string> pieces(m, "");
    for(int i = 0; i < pieces.size(); i++) {
        std::cin >> pieces[i];
    }
    std::vector<int> res = constr(s, pieces, m);
    for(int i : res) {
        std::cout << i << ' ';
    }
    return 0;
}