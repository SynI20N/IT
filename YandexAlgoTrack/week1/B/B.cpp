#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>

float time(float a, float b, float c, float v0, float v1, float v2) {
    float time1 = a / v0 + a / v1 + b / v0 + (a+c) / v1;
    float time2 = a / v0 + a / v1 + b / v0 + b / v1;
    float time3 = a / v0 + c / v1 + (a+c) / v2;
    float time4 = a / v0 + c / v1 + b / v2;

    float time5 = b / v0 + b / v1 + a / v0 + (b+c) / v1;
    float time6 = b / v0 + b / v1 + a / v0 + a / v1;
    float time7 = b / v0 + c / v1 + (b+c) / v2;
    float time8 = b / v0 + c / v1 + a / v2;

    std::vector<float> times {time1, time2, time3, time4, time5, time6, time7, time8};
    std::sort(times.begin(), times.end());

    return times[0];
}

bool check_bounds(int x) {
    if(x > 100 || x < 1) {
        return false;
    }
    return true;
}

void test(int a, int b, int c, int v0, int v1, int v2, float answ) {
    float t = time(a,b,c,v0,v1,v2);
    std::cout << t << ' ' << answ << '\n';
    assert(fabs(answ - t) < 0.0001);
}

int main() {
#ifdef TEST
    test(1, 2, 2, 10, 10, 10, 0.5000);
    test(4, 1, 2, 5, 5, 5, 1.2000);
    test(2, 3, 4, 7, 6, 5, 1.4952);
    test(2, 3, 4, 10, 9, 2, 1.0556);
    test(1, 6, 3, 7, 6, 5, 1.2714);
    return 0;
#endif
    int a,b,c,v0,v1,v2;
    std::cin >> a >> b >> c >> v0 >> v1 >> v2;
    if(!check_bounds(a) 
        || !check_bounds(b)
        || !check_bounds(c)
        || !check_bounds(v0)
        || !check_bounds(v1)
        || !check_bounds(v2)
    ) {
        return -1;
    }
    int res = time(a,b,c,v0,v1,v2);
    std::cout << res;
    return 0;
}