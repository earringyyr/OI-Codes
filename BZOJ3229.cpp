#include <iostream>
#include <cstdio>
using namespace std;
#define inf 2000000000
int n, m, ans, a[40005];
int main()
{
    scanf("%d", &n);
    m = n;
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    a[0] = a[n + 1] = inf;
    for (int t = 1; t < n; ++t)
    {
        int k;
        for (register int i = 1; i <= m; ++i)
            if (a[i - 1] <= a[i + 1])
            {
                k = i - 1;
                break;
            }
        a[k] += a[k + 1];
        ans += a[k];
        --m;
        for (register int i = k + 1; i <= m + 1; ++i)
            a[i] = a[i + 1];
        for (register int i = k - 1; i >= 0; --i)
            if (a[i] > a[i + 1])
                break;
            else
                swap(a[i], a[i + 1]);
    }
    printf("%d", ans);
    return 0;
}