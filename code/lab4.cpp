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

namespace lab4
{
    // Структура для хранения параметров графа
    struct GraphParams {
        int minV;
        int maxV;
        int minE;
        int maxE;
        int maxVE;
        bool directed;
        int maxVE_in;
        int maxVE_out;

        GraphParams(int minV, int maxV, int minE,
            int maxE, int maxVE, bool isDirected, int maxVE_in, int maxVE_out)
            : minV(minV), maxV(maxV), directed(isDirected), maxVE(maxVE),
            minE(minE), maxE(maxE), maxVE_in(maxVE_in), maxVE_out(maxVE_out){
        }
    };

    // Класс для представления графа
    class Graph {
    public:
        int V;  // Количество вершин
        int E;  // Количество рёбер
        bool directed;  // Направленность графа
        std::vector<std::vector<short>> adjMatrix;  // Матрица смежности
        std::vector<std::vector<short>> incidenceMatrix;  // Матрица инцидентности
        std::vector<std::vector<short>> adjList;  // Список смежности
        std::vector<std::pair<short, short>> edges_;  // Список рёбер (для неориентированных графов)

        Graph(int V, int E, bool directed)
            : V(V), E(E), directed(directed) {
            adjMatrix.resize(V, std::vector<short>(V, 0));
            incidenceMatrix.resize(V, std::vector<short>(E, 0));
            adjList.resize(V);
        }

        // Вывод матрицы смежности
        void printAdjMatrix() {
            for (auto& row : adjMatrix) {
                for (auto& cell : row) {
                    std::cout << cell << " ";
                }
                std::cout << std::endl;
            }
        }

        // Вывод матрицы инцидентности
        void printIncidenceMatrix() {
            for (auto& row : incidenceMatrix) {
                for (auto& cell : row) {
                    std::cout << cell << " ";
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

        // Вывод списка рёбер
        void printEdges() {
            for (auto& edge : edges_) {
                std::cout << edge.first << " -> " << edge.second << std::endl;
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
    };

    // Класс для генерации случайных графов
    class GraphGenerator {
    public:
        static Graph* generateRandomGraph(const GraphParams& params) {
            srand(time(0));

            // Generate a random number of vertices and edges
            int V = rand() % (params.maxV - params.minV + 1) + params.minV;
            int E = rand() % (params.maxE - params.minE + 1) + params.minE;

            Graph* g = new Graph(V, E, params.directed);

            std::vector<short> degree(V, 0);  // For undirected graph degree (not used if directed)
            std::vector<short> outDegree(V, 0);  // Outgoing edges for directed graph
            std::vector<short> inDegree(V, 0);   // Incoming edges for directed graph

            // List to track available vertices (those that haven't reached max degree yet)
            std::vector<int> availableVertices;
            for (int i = 0; i < V; ++i) {
                availableVertices.push_back(i);
            }

            // Generate random edges
            int edgeCount = 0;
            while (edgeCount < E && !availableVertices.empty()) {
                // Randomly select two vertices from the available list
                int idx1 = rand() % availableVertices.size();
                int idx2 = rand() % availableVertices.size();

                int u = availableVertices[idx1];
                int v = availableVertices[idx2];

                if (u == v || g->adjMatrix[u][v] != 0)
                    continue;

                if (params.directed) {
                    outDegree[u]++;
                    inDegree[v]++;
                }
                else {
                    degree[u]++;
                    degree[v]++;
                }

                g->adjMatrix[u][v] = 1;
                if (!params.directed) {
                    g->adjMatrix[v][u] = 1;
                }

                g->adjList[u].push_back(v);
                if (!params.directed) {
                    g->adjList[v].push_back(u);
                }

                g->edges_.push_back({ u, v });
                edgeCount++;
                std::vector<int>& a = availableVertices;
                if (params.directed) {
                    if (outDegree[u] >= params.maxVE_out) {
                        a.erase(std::remove(a.begin(), a.end(), u), a.end());
                    }
                    if (inDegree[v] >= params.maxVE_in) {
                        a.erase(std::remove(a.begin(), a.end(), v), a.end());
                    }
                }
                else {
                    if (degree[u] >= params.maxVE) {
                        a.erase(std::remove(a.begin(), a.end(), u), a.end());
                    }
                    if (degree[v] >= params.maxVE) {
                        a.erase(std::remove(a.begin(), a.end(), v), a.end());
                    }
                }
            }

            // Генерация матрицы инцидентности
            /*for (int i = 0; i < V; ++i) {
                for (int j = 0; j < E; ++j) {
                    if (g->adjMatrix[i][g->edges_[j].first]) {
                        g->incidenceMatrix[i][j] = 1;
                    }
                    if (g->adjMatrix[i][g->edges_[j].second]) {
                        g->incidenceMatrix[i][j] = 1;
                    }
                }
            }*/

            // Создание и возвращение графа
            return g;
        }
    };

    // Замер времени
    void testGraphSearch(const GraphParams& params, std::ofstream& outFile) {
        std::vector<double> bfsTimes;
        std::vector<double> dfsTimes;


        // Генерация графа
        Graph* graph = GraphGenerator::generateRandomGraph(params);

        for (int i = 0; i < 500; ++i)
        {
            // Выбор случайных вершин для поиска
            int start = rand() % graph->V;
            int goal = rand() % graph->V;

            // Замер времени поиска в ширину
            auto startTime = std::chrono::high_resolution_clock::now();
            graph->bfs(start, goal);
            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsedBFS = endTime - startTime;
            bfsTimes.push_back(elapsedBFS.count());

            // Замер времени поиска в глубину
            startTime = std::chrono::high_resolution_clock::now();
            graph->dfs(start, goal);
            endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsedDFS = endTime - startTime;
            dfsTimes.push_back(elapsedDFS.count());
        }

        free(graph);

        // Calculate mean times for BFS and DFS
        double meanBFS = std::accumulate(bfsTimes.begin(), bfsTimes.end(), 0.0) / bfsTimes.size();
        double meanDFS = std::accumulate(dfsTimes.begin(), dfsTimes.end(), 0.0) / dfsTimes.size();

        // Write results to graph1.txt
        if (outFile.is_open()) {
            outFile << "Mean BFS time: " << meanBFS << " seconds\n";
            outFile << "Mean DFS time: " << meanDFS << " seconds\n";
        }
        else {
            std::cerr << "Unable to open the file for writing." << std::endl;
        }
    }
}

//int main() {
//    std::ofstream outFile("graph1.txt", std::ios::app);
//    if (!outFile.is_open()) {
//        std::cerr << "Unable to open the file for writing." << std::endl;
//        return 1;
//    }
//
//    for (int i = pow(2, 6); i < pow(2, 16); i *= 2) {
//        lab4::GraphParams params(i / 2, i / 2 + 50, i, 2 * i, 4, true, 8, 8);
//        lab4::testGraphSearch(params, outFile);
//    }
//    outFile.close();
//    return 0;
//}
