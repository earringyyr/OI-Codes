#include <iostream>
#include <cstdio>
using namespace std;
int t, n, a;
int main()
{
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        scanf("%d", &n);
        int sum = 0;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &a);
            sum ^= a;
        }
        if (sum)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}