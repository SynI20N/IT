#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <map>
#include <tuple>
#include <sstream>
#include <string>

namespace solutions {
	void A() {
        int n, m, x, y;
        std::cin >> n >> m >> x >> y;
        std::vector<std::vector<int>> original(n * x, std::vector<int>(m * y));
        std::vector<std::vector<int>> result(n, std::vector<int>(m, 0));
        for (int i = 0; i < n * x; ++i) {
            for (int j = 0; j < m * y; ++j) {
                char ch;
                std::cin >> ch;
                if (ch == 'X') {
                    original[i][j] = 1;
                }
                else {
                    original[i][j] = 0;
                }
            }
        }
        for (int i = 0; i < n * x; ++i) {
            for (int j = 0; j < m * y; ++j) {
                int row_index = i / x;
                int col_index = j / y;

                if (original[i][j] == 1) {
                    result[row_index][col_index] += 1;
                }
            }
        }

        int k = 0;
        int threshold = std::ceil(static_cast<double>(x * y) / 2.0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (result[i][j] >= threshold) {
                    k++;
                }
            }
        }
        std::cout << k << std::endl;
	}
	void B() {
        int N, A, B;
        std::cin >> N;
        std::vector<int> Q(N);
        for (int i = 0; i < N; ++i) {
            std::cin >> Q[i];
        }
        std::vector<int> C(N);
        for (int i = 0; i < N; ++i) {
            std::cin >> C[i];
        }
        std::cin >> A >> B;
        std::vector<long> D(N);
        for (int i = 0; i < N; ++i) {
            D[i] = std::ceil(C[i] * (static_cast<double>(B - A)) / 255 + A);
        }
        long result = 0;
        for (int i = 0; i < N; ++i) {
            result += Q[i] * D[i];
        }
        std::cout << result << std::endl;
	}
	void C() {
        std::ifstream file("input.txt");
        if (!file.is_open()) {
            std::cerr << "Not opened!" << std::endl;
            return;
        }

        int N, L, S;
        file >> N >> L >> S;
        std::map<short, std::tuple<int, int>> taxi_map;
        int timestamp, order_id, order_position, order_time;
        std::string line;
        std::getline(file, line);

        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string command;

            ss >> command;

            if (command == "TAXI") {
                int timestamp, taxi_id, taxi_position;
                ss >> timestamp >> taxi_id >> taxi_position;
                taxi_map[taxi_id] = std::make_tuple(timestamp, taxi_position);
            }
            else if (command == "ORDER") {
                ss >> timestamp >> order_id >> order_position >> order_time;
                short taxis = 0;
                for (const auto& pair : taxi_map) {
                    short taxi_id = pair.first;
                    int taxi_timestamp = std::get<0>(pair.second);
                    int taxi_position = std::get<1>(pair.second);
                    int dist = S * (timestamp - taxi_timestamp);
                    int taxi_prime = (taxi_position + dist) % L;

                    int dist1 = (L - taxi_prime + order_position) % L;
                    int dist0 = (L - taxi_position + order_position) % L;

                    int dist_max = std::max(dist0, dist1);

                    if (dist_max <= S * order_time && taxis < 5) {
                        if (taxis < 1) {
                            std::cout << taxi_id;
                        }
                        else {
                            std::cout << ' ' << taxi_id;
                        }
                        taxis++;
                    }
                }
                if (taxis == 0) {
                    std::cout << -1;
                }
                std::cout << '\n';
            }
        }
        file.close();
	}
	void D() {
        int n, m, d;
        std::cin >> n >> m >> d;
        std::vector<std::vector<char>> map(n, std::vector<char>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                std::cin >> map[i][j];
            }
        }
        std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));
        int max_square_size = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (map[i][j] == 'o') {
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1;
                    }
                    else {
                        dp[i][j] = std::min(std::min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
                    }
                    max_square_size = std::max(max_square_size, dp[i][j]);
                }
            }
        }
        if (max_square_size > 2 * d) {
            std::cout << max_square_size << std::endl;
        }
        else {
            std::cout << 0 << std::endl;
        }
	}
	void E() {
		std::cout << 40;
	}
}

int main()
{
	solutions::D();
	return 0;
}