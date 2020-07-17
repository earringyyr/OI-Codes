#include <iostream>
#include <cstdio>
using namespace std;
int t, n, m, a[1005][1005], f[1005][1005];
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                scanf("%d", &a[i][j]);
        for (int i = n; i >= 1; --i)
            for (int j = 1; j <= m; ++j)
                f[i][j] = max(f[i + 1][j - 1] + a[i][j], max(f[i + 1][j], f[i][j - 1]));
        printf("%d\n", f[1][n]);
    }
    return 0;
}