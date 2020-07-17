#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, sum, num, st, ans = 0x7fffffff, vis[15], dis[15], a[15][15];
void dfs(int k)
{
    if (num > ans)
        return;
    if (k == st)
    {
        ans = num;
        return;
    }
    int kk = 0, use[15], cnt[15];
    for (int i = 0; i < n; ++i)
    {
        use[i] = vis[i];
        cnt[i] = dis[i];
    }
    for (int i = 0; i < n; ++i)
        if (k & (1 << i))
            for (int j = 0; j < n; ++j)
                if (a[i][j] != -1 && !(k & (1 << j)) && (vis[j] == -1 || vis[j] > (dis[i] + 1) * a[i][j]))
                {
                    dis[j] = dis[i] + 1;
                    vis[j] = dis[j] * a[i][j];
                    kk |= (1 << j);
                }
    for (int i = kk; i; i = (i - 1) & kk)
    {
        for (int j = 0; j < n; ++j)
            if (i & (1 << j))
                num += vis[j];
        dfs(k | i);
        for (int j = 0; j < n; ++j)
            if (i & (1 << j))
                num -= vis[j];
    }
    for (int i = 0; i < n; ++i)
    {
        vis[i] = use[i];
        dis[i] = cnt[i];
    }
    return;
}
int main()
{
    memset(a, -1, sizeof(a));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        if (a[u - 1][v - 1] == -1 || a[u - 1][v - 1] > w)
        {
            a[u - 1][v - 1] = w;
            a[v - 1][u - 1] = w;
        }
    }
    st = (1 << n) - 1;
    for (int i = 0; i < n; ++i)
    {
        memset(vis, -1, sizeof(vis));
        vis[i] = 0;
        dis[i] = 0;
        dfs(1 << i);
    }
    printf("%d", ans);
    return 0;
}