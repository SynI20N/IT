#include <iostream>
#include <vector>
#include <cassert>

int happy(const std::vector<int>& a)
{
    int R0 = 0;
    // i1 = min even
    // j1 = max odd
    int i1 = 0, j1 = 1;
    for(int i = 0; i < a.size(); i+= 2)
    {
        if(a[i] < a[i1])
        {
            i1 = i;
        }
        R0 += a[i];
    }
    for(int j = 1; j < a.size(); j+= 2)
    {
        if(a[j] > a[j1])
        {
            j1 = j;
        }
        R0 -= a[j];
    }
    int R = a[j1] > a[i1] ? R0 + 2*(a[j1] - a[i1]) : R0;
    return R;
}

/// @brief tests
void test1()
{
    std::vector<int> a = {2, 2, 2};
    int h = happy(a);
    assert(h == 2);
}

void test2()
{
    std::vector<int> a = {4, 10, 7, 5, 4, 5, 3, 8, 3, 2, 5};
    int h = happy(a);
    assert(h == 10);
}

void test3()
{
    std::vector<int> a = {1, 2};
    int h = happy(a);
    assert(h == 1);
}

void test4()
{
    std::vector<int> a = {5, 1, 6, 1, 8, 1, 6};
    int h = happy(a);
    assert(h == 22);
}

void test5()
{
    std::vector<int> a(1001, 10);
    a[100] = 500;
    int h = happy(a);
    assert(h == 500);
}
///

int main()
{
#ifdef TEST_LEO
    test1();
    test2();
    test3();
    test4();
    test5();
    std::cout << "all tests passed!\n";
    return 0;
#endif
    int n = 0;
    std::cin >> n;
    if(n < 2)
    {
        return -1;
    }
    std::vector<int> a(n, 0);
    for(int i = 0; i < a.size(); i++)
    {
        std::cin >> a[i];
    }
    int h = happy(a);
    std::cout << h << '\n';
    return 0;
}