#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>

struct model {
    int x, y;
    int vx, vy;
    int id;
};

struct event {
    double time;
    int model_id1, model_id2;
    enum event_type { FINISH, COLLISION, WALL_COLLISION } type;

    bool operator<(const event& other) const {
		if(time == other.time) return type > other.type;
        return time < other.time;
    }
};

bool check_collision_wall(int y, int vy, int W, double &time_to_wall) {
    if (vy == 0) return false;
    double t1 = (double)(0.0 - y) / (double)vy;
    double t2 = (double)(W - y) / (double)vy;
    if (t1 > 0) {
        time_to_wall = t1;
        return true;
    }
    if (t2 > 0) {
        time_to_wall = t2;
        return true;
    }
    return false;
}

bool check_collision_between_models(const model &m1, const model &m2, double &collision_time) {
    double dx = m1.x - m2.x;
    double dy = m1.y - m2.y;
    double dvx = m1.vx - m2.vx;
    double dvy = m1.vy - m2.vy;

    if (dvx == 0 && dvy == 0) {
        return dx == 0 && dy == 0;
    }
    if (dvx != 0) {
        double t = -dx / dvx;
        if (t >= 0 && dvy * t == -dy) {
            collision_time = t;
            return true;
        }
    }
    else if (dvy != 0) {
        double t = -dy / dvy;
        if (t >= 0 && dvx * t == -dx) {
            collision_time = t;
            return true;
        }
    }
    return false;
}

std::vector<int> find_winners(int N, int L, int W, std::vector<model> &models) {
    std::vector<event> events;
    std::unordered_map<int, bool> active_models;

    for (int i = 0; i < N; i++) {
		active_models[models[i].id] = true;
        if (models[i].vx > 0) {
            double finish_time = (double)(L - models[i].x) / (double)models[i].vx;
            events.push_back({finish_time, models[i].id, -1, event::FINISH});
        }
        double time_to_wall = 1e9;
        if (check_collision_wall(models[i].y, models[i].vy, W, time_to_wall)) {
            events.push_back({time_to_wall, models[i].id, -1, event::WALL_COLLISION});
        }
        for (int j = i + 1; j < N; j++) {
            double collision_time = 1e9;
            if (check_collision_between_models(models[i], models[j], collision_time)) {
                events.push_back({collision_time, models[i].id, models[j].id, event::COLLISION});
            }
        }
    }

    std::sort(events.begin(), events.end());

    std::vector<int> res;
	double min_time = 10e9;
    for (int k = 0; k < events.size(); k++) {
        if (events[k].type == event::COLLISION) {
			std::set<int> about_to_crash;
			for (int i = k; i < events.size(); i++) {
				if(events[i].time == events[k].time) {
					if(active_models[events[i].model_id1] && active_models[events[i].model_id2]) {
						about_to_crash.insert(events[i].model_id1);
                        about_to_crash.insert(events[i].model_id2);
                    }
				}
                else {
                    break;
                }
			}
            if(about_to_crash.size() > 1) {
                for(int id : about_to_crash) {
                    active_models[id] = false;
                }
            }
        } 
		else if (events[k].type == event::WALL_COLLISION) {
            if (active_models[events[k].model_id1]) {
                active_models[events[k].model_id1] = false;
            }
        } 
		else if (events[k].type == event::FINISH) {
            if (active_models[events[k].model_id1]) {
			    if(events[k].time < min_time) {
					min_time = events[k].time;
					res = {events[k].model_id1};
				}
				else if (events[k].time == min_time) {
					res.push_back(events[k].model_id1); 
				}
            }
        }
    }
    return res;
}

void test1() {
    int N = 1;
    int L = 1;
    int W = 2;
    std::vector<model> models {
        {0, 1, 1, 0, 1}
    };
    std::vector<int> res = find_winners(N, L, W, models);
    std::vector<int> answ = {1};
    assert(res.size() == answ.size());
    for(int i = 0; i < res.size(); i++) {
        assert(res[i] == answ[i]);
    }
    std::cout << "OK!\n";
}

void test2() {
    int N = 2;
    int L = 10;
    int W = 3;
    std::vector<model> models {
        {0, 1, 2, 0, 1},
        {5, 2, 1, 0, 2}
    };
    std::vector<int> res = find_winners(N, L, W, models);
    std::vector<int> answ = {1, 2};
    assert(res.size() == answ.size());
    for(int i = 0; i < res.size(); i++) {
        assert(res[i] == answ[i]);
    }
    std::cout << "OK!\n";
}

void test3() {
    int N = 2;
    int L = 12;
    int W = 3;
    std::vector<model> models {
        {0, 1, 11, 0, 1},
        {0, 2, 11, -1, 2}
    };
    std::vector<int> res = find_winners(N, L, W, models);
    std::vector<int> answ = {};
    assert(res.size() == answ.size());
    for(int i = 0; i < res.size(); i++) {
        assert(res[i] == answ[i]);
    }
    std::cout << "OK!\n";
}

void test4() {
    int N = 2;
    int L = 11;
    int W = 3;
    std::vector<model> models {
        {0, 1, 11, 0, 1},
        {0, 2, 11, -1, 2}
    };
    std::vector<int> res = find_winners(N, L, W, models);
    std::vector<int> answ = {};
    assert(res.size() == answ.size());
    for(int i = 0; i < res.size(); i++) {
        assert(res[i] == answ[i]);
    }
    std::cout << "OK!\n";
}

void test5() {
    int N = 3;
    int L = 10;
    int W = 4;
    std::vector<model> models {
        {0, 1, 4, 1, 1},
        {0, 2, 4, 0, 2},
		{0, 3, 4, 0, 3},
    };
    std::vector<int> res = find_winners(N, L, W, models);
    std::vector<int> answ = {3};
    assert(res.size() == answ.size());
    for(int i = 0; i < res.size(); i++) {
        assert(res[i] == answ[i]);
    }
    std::cout << "OK!\n";
}

void test6() {
    int N = 3;
    int L = 10000;
    int W = 8;
    std::vector<model> models {
        {4999, 6, 0, -2, 1},
        {4998, 7, 1, -3, 2},
		{0, 1, 2500, 0, 3},
    };
    std::vector<int> res = find_winners(N, L, W, models);
    std::vector<int> answ = {3};
    assert(res.size() == answ.size());
    for(int i = 0; i < res.size(); i++) {
        assert(res[i] == answ[i]);
    }
    std::cout << "OK!\n";
}

void test7() {
    int N = 2;
    int L = 10;
    int W = 3;
    std::vector<model> models {
        {0, 1, 9, 0, 1},
        {0, 2, 8, 0, 2}
    };
    std::vector<int> res = find_winners(N, L, W, models);
    std::vector<int> answ = {1};
    assert(res.size() == answ.size());
    for(int i = 0; i < res.size(); i++) {
        assert(res[i] == answ[i]);
    }
    std::cout << "OK!\n";
}

void test8() {
    int N = 3;
    int L = 10;
    int W = 10000;
    std::vector<model> models {
        {0, 4999, 1, 1, 1},
        {0, 5000, 1, 0, 2},
        {0, 5001, 1, -1, 3}
    };
    std::vector<int> res = find_winners(N, L, W, models);
    std::vector<int> answ = {};
    assert(res.size() == answ.size());
    for(int i = 0; i < res.size(); i++) {
        assert(res[i] == answ[i]);
    }
    std::cout << "OK!\n";
}

void test9() {
    int N = 1000;
    int L = 1;
    int W = 10000;
    std::vector<model> models;
    int number = 1;
    for(int y = 4999; y >= 4500; y--) {
        models.push_back({0, y, 1, 1, number});
        number++;
    }
    for(int y = 5000; y <= 5499; y++) {
        models.push_back({0, y, 1, -1, number});
        number++;
    }
    std::vector<int> res = find_winners(N, L, W, models);
    std::sort(res.begin(), res.end());
    std::vector<int> answ;
    for(int i = 1; i <= 1000; i++) {
        if(i != 1 && i != 501) answ.push_back(i);
    }
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
	test4();
	test5();
	test6();
	test7();
    test8();
    test9();
    std::cout << "all tests passed!\n";    
    return 0;
#endif
    int N, L, W;
    std::cin >> N >> L >> W;
    
    std::vector<model> models(N);
    for (int i = 0; i < N; i++) {
        std::cin >> models[i].x >> models[i].y >> models[i].vx >> models[i].vy;
        models[i].id = i + 1;
    }
    
    std::vector<int> res = find_winners(N, L, W, models);
    std::sort(res.begin(), res.end());
    std::cout << res.size() << '\n';
    for(int i : res) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    
    return 0;
}
