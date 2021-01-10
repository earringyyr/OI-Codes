#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define lch k << 1
#define rch k << 1 | 1
int n, m, ans;
int a[2005][15], b[2005][15];
int vis[2005];
int f[2005][1005], g[2005][1005];
void dfs(int k, int dep)
{
    for (int i = 0; i <= (1 << dep); ++i)
        f[k][i] = 0;
    if (!dep)
    {
        for (int i = 1; i < n; ++i)
            if (vis[i])
                f[k][1] += a[k][i];
            else
                f[k][0] += b[k][i];
        return;
    }
    vis[dep] = 0;
    dfs(lch, dep - 1);
    dfs(rch, dep - 1);
    for (int i = 0; i <= (1 << (dep - 1)); ++i)
        for (int j = 0; j <= (1 << (dep - 1)); ++j)
            f[k][i + j] = max(f[k][i + j], f[lch][i] + f[rch][j]);
    vis[dep] = 1;
    dfs(lch, dep - 1);
    dfs(rch, dep - 1);
    for (int i = 0; i <= (1 << (dep - 1)); ++i)
        for (int j = 0; j <= (1 << (dep - 1)); ++j)
            f[k][i + j] = max(f[k][i + j], f[lch][i] + f[rch][j]);
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = (1 << (n - 1)); i < (1 << n); ++i)
        for (int j = 1; j < n; ++j)
            scanf("%d", &a[i][j]);
    for (int i = (1 << (n - 1)); i < (1 << n); ++i)
        for (int j = 1; j < n; ++j)
            scanf("%d", &b[i][j]);
    dfs(1, n - 1);
    for (int i = 0; i <= m; ++i)
        ans = max(ans, f[1][i]);
    printf("%d", ans);
    return 0;
}