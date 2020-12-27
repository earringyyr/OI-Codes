#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, N, m, x;
int main()
{
    scanf("%d%d", &n, &m);
    N = n;
    while (n > 1)
    {
        ++x;
        for (int i = 1; i <= m; ++i)
        {
            printf("%d %d\n", x, i);
            printf("%d %d\n", N - x + 1, m - i + 1);
        }
        n -= 2;
    }
    ++x;
    if (n == 1)
    {
        for (int i = 1; i <= m; ++i)
            if (i % 2 == 1)
                printf("%d %d\n", x, (i + 1) / 2);
            else
                printf("%d %d\n", x, m - i / 2 + 1);
    }
    return 0;
}