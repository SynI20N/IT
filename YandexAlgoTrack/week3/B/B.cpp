#include <iostream>
#include <cassert>
#include <vector>
#include <queue>

int min_dist(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<int> visited(n, -1);
	std::vector<int> distance(n, -1);
    std::queue<int> q;

    for (int i = 0; i < n; ++i) {
        if (graph[i].size() == 1) {
            visited[i] = i;
			distance[i] = 0;
            q.push(i);
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int neighbor : graph[v]) {
            if (visited[neighbor] == -1) {
                visited[neighbor] = visited[v];
				distance[neighbor] = distance[v] + 1;
                q.push(neighbor);
            } else if (visited[neighbor] != visited[v]) {
                return distance[neighbor] + distance[v] + 1;
            }
        }
    }

    return -1;
}

void test1() {
	std::vector<std::vector<int>> graph{
		{1, 2},
		{0, 3, 4},
		{0},
		{1},
		{1}
	};
	int res = min_dist(graph);
	std::cout << res << '\n';
	int answ = 2;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test2() {
	std::vector<std::vector<int>> graph{
		{1, 2},
		{0},
		{0, 4},
		{4},
		{2, 3}
	};
	int res = min_dist(graph);
	int answ = 4;
	assert(res == answ);
	std::cout << "OK!\n";
}

void test3() {
	std::vector<std::vector<int>> graph{
		{1},
		{0}
	};
	int res = min_dist(graph);
	int answ = 1;
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
	std::vector<std::vector<int>> graph(n);
	int u, v;
	for(int i = 0; i < n - 1; i++) {
		std::cin >> u >> v;
		graph[u - 1].push_back(v - 1);
		graph[v - 1].push_back(u - 1);
	}
	std::cout << min_dist(graph);
	return 0;
}