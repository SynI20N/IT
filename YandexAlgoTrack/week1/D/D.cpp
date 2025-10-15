#include <iostream>
#include <vector>
#include <cassert>
#include <map>

std::vector<int> max_cover(std::vector<int>& tasks, int k) {
    std::map<int, int> c;
    std::vector<int> res;
    for(int t : tasks) {
        c[t]++;
    }
    while(k > 0) {
        for(std::pair<int, int> p : c) {
            if(k == 0) {
                break;
            }
            if(p.second > 0) {
                res.push_back(p.first);
                c[p.first]--;
                k--;
            }
        }
    }
    return res;
}

void test1() {
    std::vector<int> tasks = {1, 1, 1, 2, 2};
    std::vector<int> res = {1, 2, 1};
    std::vector<int> cover = max_cover(tasks, 3);
    assert(res.size() == cover.size());
    for(size_t i = 0; i < res.size(); i++) {
        assert(res[i] == cover[i]);
    }
    std::cout << "OK!\n";
}

void test2() {
    std::vector<int> tasks = {8, 8, 8, 8, 8, 8, 8, 8, 2, 1};
    std::vector<int> res = {1, 2, 8, 8};
    std::vector<int> cover = max_cover(tasks, 4);
    assert(res.size() == cover.size());
    for(size_t i = 0; i < res.size(); i++) {
        assert(res[i] == cover[i]);
    }
    std::cout << "OK!\n";
}

void test3() {
    std::vector<int> tasks = {1, 8, 8, 8, 8, 8, 2, 8, 8};
    std::vector<int> res = {1, 2, 8, 8};
    std::vector<int> cover = max_cover(tasks, 4);
    assert(res.size() == cover.size());
    for(size_t i = 0; i < res.size(); i++) {
        assert(res[i] == cover[i]);
    }
    std::cout << "OK!\n";
}

void test4() {
    std::vector<int> tasks(100000, 1000000000);
    std::vector<int> res(90000, 1000000000);
    std::vector<int> cover = max_cover(tasks, 90000);
    assert(res.size() == cover.size());
    for(size_t i = 0; i < res.size(); i++) {
        assert(res[i] == cover[i]);
    }
    std::cout << "OK!\n";
}

void test5() {
    std::vector<int> tasks(100000, 1);
    tasks[90000] = 2;
    std::vector<int> res = {1, 2};
    std::vector<int> cover = max_cover(tasks, 2);
    assert(res.size() == cover.size());
    for(size_t i = 0; i < res.size(); i++) {
        assert(res[i] == cover[i]);
    }
    std::cout << "OK!\n";
}

void test6() {
    std::vector<int> tasks {8, 7, 3, 4, 5, 6, 7, 8};
    std::vector<int> res = {3, 4, 5, 6};
    std::vector<int> cover = max_cover(tasks, 4);
    assert(res.size() == cover.size());
    for(size_t i = 0; i < res.size(); i++) {
        assert(res[i] == cover[i]);
    }
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
    int n, k;
    std::cin >> n >> k;
    std::vector<int> tasks(n, 0);
    for(size_t t = 0; t < tasks.size(); t++) {
        std::cin >> tasks[t];
    }
    std::vector<int> res = max_cover(tasks, k);
    for(int r : res) {
        std::cout << r << ' ';
    }
    return 0;
}