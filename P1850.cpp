#include <iostream>
#include <cstdio>
#include <cstring>
#define inf 1000000000000.0
using namespace std;
int n, m, v, e, c[2005], d[2005], s[305][305];
double ans, k[2005], f[2005][2005][2];
int main()
{
    scanf("%d%d%d%d", &n, &m, &v, &e);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &c[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &d[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%lf", &k[i]);
    memset(s, 0x3f, sizeof(s));
    for (int i = 1; i <= e; ++i)
    {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        s[x][y] = min(s[x][y], w);
        s[y][x] = min(s[y][x], w);
    }
    for (int i = 1; i <= v; ++i)
        s[i][i] = 0;
    for (int k = 1; k <= v; ++k)
        for (int i = 1; i <= v; ++i)
            for (int j = 1; j <= v; ++j)
                s[i][j] = min(s[i][j], s[i][k] + s[k][j]);
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
        {
            f[i][j][0] = inf;
            f[i][j][1] = inf;
        }
    f[1][0][0] = 0;
    f[1][1][1] = 0;
    for (int i = 2; i <= n; ++i)
    {
        f[i][0][0] = f[i - 1][0][0] + s[c[i - 1]][c[i]];
        for (int j = 1; j <= min(i, m); ++j)
        {
            f[i][j][0] = min(f[i][j][0], min(f[i - 1][j][0] + s[c[i - 1]][c[i]], f[i - 1][j][1] + s[c[i - 1]][c[i]] * (1 - k[i - 1]) + s[d[i - 1]][c[i]] * k[i - 1]));
            f[i][j][1] = min(f[i][j][1], min(f[i - 1][j - 1][0] + s[c[i - 1]][c[i]] * (1 - k[i]) + s[c[i - 1]][d[i]] * k[i], f[i - 1][j - 1][1] + s[d[i - 1]][d[i]] * k[i] * k[i - 1] + s[d[i - 1]][c[i]] * k[i - 1] * (1 - k[i]) + s[c[i - 1]][d[i]] * (1 - k[i - 1]) * k[i] + s[c[i - 1]][c[i]] * (1 - k[i - 1]) * (1 - k[i])));
        }
    }
    ans = inf;
    for (int i = 0; i <= m; ++i)
        ans = min(ans, min(f[n][i][0], f[n][i][1]));
    printf("%.2f", ans);
    return 0;
}