#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, ans, a[55][55], f[55][55][2505];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)
        {
            scanf("%d", &a[i][j]);
            a[i][j] += a[i - 1][j];
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= i; ++j)
            for (int k = j * (j + 1) / 2; k <= m; ++k)
                for (int l = max(0, j - 1); l <= i - 1; ++l)
                    f[j][i][k] = max(f[j][i][k], f[l][i - 1][k - j] + a[j][i]);
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)
            ans = max(ans, f[i][j][m]);
    printf("%d", ans);
    return 0;
}