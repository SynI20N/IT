#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <stack>
#include <chrono>
#include <numeric>
#include <map>

namespace lab5
{
    // Структура для хранения параметров графа
    struct GraphParams {
        int V;
        int minDegree;

        GraphParams(int V, int minDegree)
            : V(V), minDegree(minDegree) {
        }
    };

    // Класс для представления графа
    class WeightedGraph {
    public:
        int V;  // Количество вершин
        int E;  // Количество рёбер
        std::vector<std::vector<int>> adjMatrix;  // Матрица смежности
        std::vector<std::vector<int>> adjList;  // Список смежности
        std::vector<std::tuple<int, int, int>> edges; // Список ребер

        WeightedGraph(int V, int E)
            : V(V), E(E) {
            adjMatrix.resize(V, std::vector<int>(V, 0));
            adjList.resize(V);
        }

        // Структура для представления рёбер
        struct Edge {
            int weight, u, v;

            bool operator<(const Edge& other) const {
                return weight < other.weight;
            }
        };

        // Вывод матрицы смежности
        void printAdjMatrix() {
            for (auto& row : adjMatrix) {
                for (auto& cell : row) {
                    printf("%3d", cell);
                }
                std::cout << std::endl;
            }
        }

        // Вывод списка смежности
        void printAdjList() {
            for (int i = 0; i < V; ++i) {
                std::cout << i << ": ";
                for (auto& neighbor : adjList[i]) {
                    std::cout << neighbor << " ";
                }
                std::cout << std::endl;
            }
        }

        // Поиск в ширину
        bool bfs(int start, int goal) {
            std::vector<bool> visited(V, false);
            std::queue<int> q;
            std::vector<int> parent(V, -1);

            visited[start] = true;
            q.push(start);

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                if (node == goal) {
                    return true;
                }

                for (int neighbor : adjList[node]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        parent[neighbor] = node;
                        q.push(neighbor);
                    }
                }
            }
            return false;
        }

        // Поиск в глубину
        bool dfs(int start, int goal) {
            std::vector<bool> visited(V, false);
            std::stack<int> s;
            std::vector<int> parent(V, -1);

            visited[start] = true;
            s.push(start);

            while (!s.empty()) {
                int node = s.top();
                s.pop();

                if (node == goal) {
                    return true;
                }

                for (int neighbor : adjList[node]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        parent[neighbor] = node;
                        s.push(neighbor);
                    }
                }
            }
            return false;
        }

        // Функция для поиска сжатия пути
        int find(int parent[], int i) {
            if (parent[i] == -1) {
                return i;
            }
            return parent[i] = find(parent, parent[i]);
        }

        // Функция для объединения двух подмножеств
        void Union(int parent[], int rank[], int x, int y) {
            int xroot = find(parent, x);
            int yroot = find(parent, y);

            if (rank[xroot] < rank[yroot]) {
                parent[xroot] = yroot;
            }
            else if (rank[xroot] > rank[yroot]) {
                parent[yroot] = xroot;
            }
            else {
                parent[yroot] = xroot;
                rank[xroot]++;
            }
        }

        void kruskal() {
            std::vector<Edge> edgeList;

            // Добавление рёбер в список
            for (int i = 0; i < V; ++i) {
                for (int j = i + 1; j < V; ++j) {
                    if (adjMatrix[i][j] > 0) {
                        edgeList.push_back({ adjMatrix[i][j], i, j });
                    }
                }
            }

            // Сортируем рёбра по весу
            std::sort(edgeList.begin(), edgeList.end());

            int* parent = (int*)malloc(sizeof(int) * V);
            int* rank = (int*)malloc(sizeof(int) * V);
            std::fill(parent, parent + V, -1);
            std::fill(rank, rank + V, 0);

            std::vector<Edge> mst;
            for (auto& edge : edgeList) {
                int u = edge.u;
                int v = edge.v;

                // Если ребра не образуют цикл, добавляем в MST
                if (find(parent, u) != find(parent, v)) {
                    mst.push_back(edge);
                    Union(parent, rank, u, v);
                }
            }

            free(parent);
            free(rank);

            std::vector<std::vector<int>> adjMatrixMST;
            adjMatrixMST.resize(V, std::vector<int>(V, 0));
            for (auto& edge : mst) {
                adjMatrixMST[edge.u][edge.v] = 1;
                adjMatrixMST[edge.v][edge.u] = 1;
            }

            std::cout << "MST adjacency matrix:" << std::endl;
            for (auto& row : adjMatrixMST) {
                for (auto& cell : row) {
                    printf("%3d", cell);
                }
                std::cout << std::endl;
            }
        }
    };

    // Класс для генерации случайных графов
    class GraphGenerator {
    public:
        static WeightedGraph* generateRandomGraph(const GraphParams& params) {
            srand(time(0));

            int V = params.V;
            int E = 0;

            WeightedGraph* g = new WeightedGraph(V, E);

            for (int i = 0; i < V - 1; ++i) {
                int weight = rand() % 20 + 1;
                g->adjMatrix[i][i + 1] = weight;
                g->adjList[i].push_back(i+1);
                g->E++;
            }

            for (int i = 0; i < V; ++i) {
                while (g->adjList[i].size() < params.minDegree) {
                    int u = i;
                    int v = rand() % V;
                    if (u != v) {
                        if (!(g->adjMatrix[v][u] > 0)) {
                            int weight = rand() % 20 + 1;
                            g->adjMatrix[u][v] = weight;
                            g->adjList[u].push_back(v);
                            g->E++;
                        }
                    }
                }
            }

            return g;
        }
    };

    // Замер времени
    void testKruskal(const GraphParams& params, std::ofstream& outFile) {
        std::vector<double> times;

        WeightedGraph* graph = GraphGenerator::generateRandomGraph(params);

        graph->printAdjMatrix();

        int trials = rand() % 6 + 5;
        for (int i = 0; i < trials; ++i)
        {
            // Замер времени
            auto startTime = std::chrono::high_resolution_clock::now();
            graph->kruskal();
            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsedDFS = endTime - startTime;
            times.push_back(elapsedDFS.count());
        }

        free(graph);

        double mean = std::accumulate(times.begin(), times.end(), 0.0) / times.size();

        if (outFile.is_open()) {
            outFile << "Mean time: " << mean << " seconds " 
                << " for " << params.V << " minDegree " << params.minDegree << '\n';
        }
        else {
            std::cerr << "Unable to open the file for writing." << std::endl;
        }
    }
}

//int main() {
//    std::ofstream file("graph2.txt", std::ios::app);
//    lab5::GraphParams params(10, 3);
//    testKruskal(params, file);
//    lab5::GraphParams params2(20, 4);
//    testKruskal(params2, file);
//    lab5::GraphParams params3(50, 10);
//    testKruskal(params3, file);
//    lab5::GraphParams params4(100, 20);
//    testKruskal(params4, file);
//    lab5::GraphParams params5(200, 35);
//    testKruskal(params5, file);
//
//    file.close();
//    return 0;
//}
