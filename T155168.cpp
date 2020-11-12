#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, R, num, ans, r[10], vis[10];
int dis[205][205];
void dfs(int k, int now)
{
    if (k == R + 1)
    {
        ans = min(ans, num);
        return;
    }
    for (int i = 1; i <= R; ++i)
        if (!vis[i])
        {
            vis[i] = 1;
            if (now)
                num += dis[now][r[i]];
            dfs(k + 1, r[i]);
            vis[i] = 0;
            if (now)
                num -= dis[now][r[i]];
        }
    return;
}
int main()
{
    memset(dis, 0x3f, sizeof(dis));
    ans = 0x7f7f7f7f;
    scanf("%d%d%d", &n, &m, &R);
    for (int i = 1; i <= R; ++i)
        scanf("%d", &r[i]);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        dis[u][v] = w;
        dis[v][u] = w;
    }
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    dfs(1, 0);
    printf("%d", ans);
    return 0;
}