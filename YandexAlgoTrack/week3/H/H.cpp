#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

std::vector<std::vector<int>> g;
std::vector<long long> a, subtree;
long long total = 0;

void dfs(int v, int prev) {
    subtree[v] = a[v];
    for (int to : g[v]) {
        if (to == prev) {
			continue;
		}
        dfs(to, v);
        subtree[v] += subtree[to];
    }
}

int find_center(int n) {
    dfs(1, -1);

    long long best_val = INT64_MAX;
    int best_v = 1;

    for (int v = 1; v <= n; v++) {
        long long mx = a[v];
        for (int to : g[v]) {
            long long q;
			q = subtree[to] < subtree[v] ? subtree[to] : total - subtree[v];
            mx = std::max(mx, q);
        }
        if (mx < best_val) {
            best_val = mx;
            best_v = v;
        }
    }

    return best_v;
}

void test1() {
    int n = 5;
    a = {0, 3, 3, 2, 5, 1};
	g = std::vector<std::vector<int>>(n + 1);
	subtree = std::vector<long long>(n + 1);
    total = 14;

	g = {
		{},
		{2},
		{1, 3, 4},
		{2},
		{2, 5},
		{4},
	};

    int res = find_center(n);
    int ans = 2;
    assert(res == ans);
    std::cout << "OK!\n";
}

void test2() {
    int n = 3;
    a = {0, 1, 2, 1};
    g = std::vector<std::vector<int>>(n + 1);
	subtree = std::vector<long long>(n + 1);
    total = 4;

	g = {
		{},
		{2},
		{1, 3},
		{2}
	};

    int res = find_center(n);
    int ans = 2;
    assert(res == ans);
    std::cout << "OK!\n";
}

void test3() {
	int n = 1;
    a = {0, 1000000000};
    g = std::vector<std::vector<int>>(n + 1);
	subtree = std::vector<long long>(n + 1);
    total = 1000000000;

    int res = find_center(n);
    int ans = 1;
    assert(res == ans);
    std::cout << "OK!\n";
}

void test4() {
	int n = 100000;
    a = std::vector<long long>(100001, 1000000000);
	a[0] = 0;
    g = std::vector<std::vector<int>>(n + 1);
	for(int i = 2; i < n; i++) {
		g[i].push_back(i + 1);
		g[i].push_back(i - 1);
	}
	g[1].push_back(2);
	g[n].push_back(n-1);
	subtree = std::vector<long long>(n + 1);
    total = 1000000000L * 100000L;

    int res = find_center(n);
    int ans = floor((n + 1) >> 1);
	std::cout << res << "/" << ans << '\n';
    assert(res == ans);
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
    int n;
    std::cin >> n;
	a = std::vector<long long>(n + 1, 0);
	subtree = std::vector<long long>(n + 1, 0);
	g = std::vector<std::vector<int>>(n + 1);
    total = 0;

    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        total += a[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::cout << find_center(n);
    return 0;
}
