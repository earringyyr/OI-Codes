#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
int n, m, k, sum, ans;
int head[1000050], u[1000050], v[1000050], w[1000050];
int dis[2][1000050][3], pre[2][1000050][3];
struct edge
{
    int v;
    int w;
    int nxt;
} a[2000050];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k, int val, int type)
{
    int d = head[k];
    while (d)
    {
        if (a[d].v != 1 && a[d].v != n)
        {
            if (val + a[d].w < dis[type][a[d].v][0])
            {
                dis[type][a[d].v][2] = dis[type][a[d].v][1];
                dis[type][a[d].v][1] = dis[type][a[d].v][0];
                dis[type][a[d].v][0] = val + a[d].w;
                pre[type][a[d].v][2] = pre[type][a[d].v][1];
                pre[type][a[d].v][1] = pre[type][a[d].v][0];
                pre[type][a[d].v][0] = k;
            }
            else if (val + a[d].w < dis[type][a[d].v][1])
            {
                dis[type][a[d].v][2] = dis[type][a[d].v][1];
                dis[type][a[d].v][1] = val + a[d].w;
                pre[type][a[d].v][2] = pre[type][a[d].v][1];
                pre[type][a[d].v][1] = k;
            }
            else if (val + a[d].w < dis[type][a[d].v][2])
            {
                dis[type][a[d].v][2] = val + a[d].w;
                pre[type][a[d].v][2] = k;
            }
        }
        d = a[d].nxt;
    }
}
int main()
{
    ans = inf;
    memset(dis, 0x3f, sizeof(dis));
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d", &u[i], &v[i], &w[i]);
        ins(u[i], v[i], w[i]);
        ins(v[i], u[i], w[i]);
    }
    if (k > m || k > n)
    {
        printf("-1");
        return 0;
    }
    if (k < 5)
    {
        for (int i = k + 1; i <= 5; ++i)
        {
            ++m;
            u[m] = n + i - k - 1;
            v[m] = n + i - k;
            w[m] = 0;
            ins(u[m], v[m], w[m]);
            ins(v[m], u[m], w[m]);
        }
        n = n + 5 - k;
    }
    int d = head[1];
    while (d)
    {
        if (a[d].v != n)
            dfs(a[d].v, a[d].w, 0);
        d = a[d].nxt;
    }
    d = head[n];
    while (d)
    {
        if (a[d].v != 1)
            dfs(a[d].v, a[d].w, 1);
        d = a[d].nxt;
    }
    for (int i = 1; i <= m; ++i)
        if (u[i] != 1 && u[i] != n && v[i] != 1 && v[i] != n)
        {
            for (int k = 0; k < 3; ++k)
                if (pre[1][v[i]][k] != u[i])
                    for (int j = 0; j < 3; ++j)
                        if (pre[0][u[i]][j] != v[i] && pre[0][u[i]][j] != pre[1][v[i]][k])
                        {
                            ans = min(ans, dis[0][u[i]][j] + w[i] + dis[1][v[i]][k]);
                            break;
                        }
            swap(u[i], v[i]);
            for (int k = 0; k < 3; ++k)
                if (pre[1][v[i]][k] != u[i])
                    for (int j = 0; j < 3; ++j)
                        if (pre[0][u[i]][j] != v[i] && pre[0][u[i]][j] != pre[1][v[i]][k])
                        {
                            ans = min(ans, dis[0][u[i]][j] + w[i] + dis[1][v[i]][k]);
                            break;
                        }
        }
    if (ans == inf)
        printf("-1");
    else
        printf("%d", ans);
    return 0;
}