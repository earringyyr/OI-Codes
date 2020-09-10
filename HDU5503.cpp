#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
int n, a[50005];
signed main()
{
    int T;
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%lld", &a[i]);
        sort(a + 1, a + n + 1);
        bool p = true;
        for (int i = 2; i <= n; ++i)
        {
            a[i] += a[i - 1];
            if (a[i] < i * (i - 1) / 2)
                p = false;
        }
        if (a[n] != n * (n - 1) / 2)
            p = false;
        if (p)
            puts("It seems to have no problem.");
        else
            puts("The data have been tampered with!");
    }
    return 0;
}