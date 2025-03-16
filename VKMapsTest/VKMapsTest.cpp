#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>

typedef unsigned int uint;

struct Edge {
    uint U;
    uint V;
    int Weight;

    Edge(uint v1, uint v2, int weight)
        : U(v1), V(v2), Weight(weight) {}
};

class Graph {
private:
    uint v_;
    uint e_;
    std::vector<Edge> edges_;

public:

    Graph(uint v, std::vector<Edge> edges) : v_(v), e_(edges.size()) {
        if (e_ == 0 || v_ == 0) {
            throw std::length_error("Graph is empty!");
        }
        for (Edge& e : edges) {
            if (e.U >= v_ || e.V >= v_) {
                throw std::length_error("Edge is not allowed!");
            }
            edges_.push_back(e);
            Edge inv(e.V, e.U, e.Weight);
            edges_.push_back(inv);
        }
    }

    void bellmanFord(uint V, std::ostream& out) {
        if (V >= v_) {
            throw std::runtime_error("This vertex does not exist!");
        }
        std::vector<std::vector<int>> A(v_, std::vector<int>(v_, UINT16_MAX));
        int k = 0;
        while (k < v_) {
            A[V][k] = 0;
            k++;
        }
        for (uint i = 1; i < v_; i++) {
            for (Edge& e : edges_) {
                if (A[e.V][i] > A[e.U][i] + e.Weight) {
                    k = i;
                    while (k < v_) {
                        A[e.V][k] = A[e.U][i] + e.Weight;
                        k++;
                    }
                }
            }
        }

        for (uint j = 0; j < v_; j++) {
            out << A[j][v_-1] << '\n';
        }
    }
};

struct TestData {
    Graph G;
    uint S;

    TestData(Graph g, uint s) : G(g), S(s) {}
};

class GraphTests {
private:
    TestData read(std::istream& in) {
        uint v = 0, e = 0;
        in >> v >> e;
        std::vector<Edge> edges;
        for (int i = 0; i < e; i++) {
            uint v1 = 0, v2 = 0;
            in >> v1 >> v2;
            Edge e(v1, v2, 1);
            edges.push_back(e);
        }
        Graph g(v, edges);
        uint s;
        in >> s;
        TestData data(g, s);
        return data;
    }
public:
    void test1() {
        std::ifstream file("graph1.txt");
        TestData data = read(file);
        std::stringstream out;
        data.G.bellmanFord(data.S, out);
        assert(out.str() == "1\n2\n3\n3\n0\n");
        std::cout << "test1 passed\n";
    }

    void test2() {
        std::ifstream file("graph2.txt");
        TestData data = read(file);
        std::stringstream out;
        data.G.bellmanFord(data.S, out);
        assert(out.str() == "2\n1\n2\n3\n0\n1\n");
        std::cout << "test2 passed\n";
    }

    void test3() {
        try {
            std::ifstream file("graph3.txt");
            TestData data = read(file);
            std::stringstream out;
            data.G.bellmanFord(data.S, out);
            assert(out.str() == "1\n2\n3\n3\n0\n");
        }
        catch (std::exception& e) {
            std::cout << e.what() << '\n';
        }
        std::cout << "test3 passed\n";
    }
};

int main()
{
    GraphTests tests;
    tests.test1();
    tests.test2();
    tests.test3();
    return 0;
}