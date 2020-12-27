#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
int n, m, ans = inf;
int dis[105][105], mp[105][105];
int main()
{
    memset(dis, 0x3f, sizeof(dis));
    memset(mp, 0x3f, sizeof(mp));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        dis[u][v] = min(dis[u][v], d);
        dis[v][u] = min(dis[v][u], d);
        mp[u][v] = min(mp[u][v], d);
        mp[v][u] = min(mp[v][u], d);
    }
    for (int k = 1; k <= n; ++k)
    {
        for (int i = 1; i < k; ++i)
            for (int j = i + 1; j < k; ++j)
                if (dis[i][j] != inf && mp[j][k] != inf && mp[k][j] != inf)
                    ans = min(ans, dis[i][j] + mp[i][k] + mp[k][j]);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    }
    if (ans == inf)
        printf("No solution.");
    else
        printf("%d", ans);
    return 0;
}