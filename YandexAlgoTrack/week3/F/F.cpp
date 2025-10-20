#include <iostream>
#include <cassert>
#include <unordered_map>
#include <vector>

struct pair {
    int a;
    int b;
};

std::vector<int> in_time;
std::vector<int> out_time;
int timer;

std::vector<std::vector<int>> build(std::unordered_map<int, int>& tree) {
	int n = tree.size() + 1;
    std::vector<std::vector<int>> graph(n);
    for (const auto& [child, parent] : tree) {
        graph[parent].push_back(child);
    }
    return graph;
}

void dfs(int node, std::vector<std::vector<int>>& graph) {
    in_time[node] = timer++;
    for (int child : graph[node]) {
        dfs(child, graph);
    }
    out_time[node] = timer++;
}

void preprocess(std::unordered_map<int, int>& tree) {
	int n = tree.size() + 1;
    in_time.assign(n, 0);
    out_time.assign(n, 0);
    timer = 0;

    std::vector<std::vector<int>> graph = build(tree);
    dfs(0, graph);
}

bool check(int a, int b) {
    return in_time[a] <= in_time[b] && in_time[b] <= out_time[a];
}

std::vector<bool> check_all(
	std::unordered_map<int, int>& tree, 
	std::vector<pair>& queries
) {
    preprocess(tree);

    std::vector<bool> res(queries.size(), 0);
    for (int i = 0; i < queries.size(); i++) {
        res[i] = check(queries[i].a, queries[i].b);
    }
    return res;
}

void test1() {
    std::unordered_map<int, int> tree{{1,0}, {2,1}, {3,1}, {4,2}, {5,3}, {6,3}};
    std::vector<pair> input{{4,1}, {1,4}, {3,6}, {2,6}, {6,5}};
    std::vector<bool> res = check_all(tree, input);
    std::vector<bool> answ{0, 1, 1, 0, 0};
    assert(res == answ);
    std::cout << "OK\n";
}

void test2() {
    std::unordered_map<int, int> tree{{1,0}, {2,1}};
    std::vector<pair> input{{1,2}};
    std::vector<bool> res = check_all(tree, input);
    std::vector<bool> answ{1};
    assert(res == answ);
    std::cout << "OK\n";
}

void test3() {
    std::unordered_map<int, int> tree;
    for (int i = 1; i <= 100000; i++) tree[i] = i - 1;
    std::vector<pair> input(100000, {1, 100000});
    std::vector<bool> res = check_all(tree, input);
    std::vector<bool> answ(100000, true);
    assert(res == answ);
    std::cout << "OK\n";
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
	std::unordered_map<int, int> tree;
	for(int i = 0; i < n; i++) {
		std::cin >> tree[i+1];
	}
	int m;
	std::cin >> m;
	std::vector<pair> input(m);
	for(int i = 0; i < m; i++) {
		std::cin >> input[i].a >> input[i].b;
	}
	std::vector<bool> res = check_all(tree, input);
	for(bool b : res) {
		std::cout << b << '\n';
	}
	return 0;
}
