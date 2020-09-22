#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, l, k, p[205], a[205];
double ans, f[205][405][205];
int main()
{
    scanf("%d%d%d", &n, &l, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &p[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    f[1][200][0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 200 - i + 1; j <= n + 200; ++j)
            for (int k = 0; k <= i; ++k)
            {
                f[i + 1][min(j + a[i], n + 200)][k + 1] += f[i][j][k] * p[i] / 100;
                f[i + 1][j][k] += f[i][j][k] * (100 - p[i]) / 100;
            }
    for (int i = 0; i <= n + 200; ++i)
        if (i - 200 + k >= 0)
            for (int j = l; j <= n; ++j)
                ans += f[n + 1][i][j];
    printf("%.6f", ans);
    return 0;
}