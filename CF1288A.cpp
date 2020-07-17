#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int t, n, d;
int main()
{
    scanf("%d", &t);
    for (int i = 1; i <= t; ++i)
    {
        scanf("%d%d", &n, &d);
        if (floor(sqrt(d) - 1) + ceil((double)d / floor(sqrt(d))) <= n || ceil(sqrt(d) - 1) + ceil((double)d / ceil(sqrt(d))) <= n)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}