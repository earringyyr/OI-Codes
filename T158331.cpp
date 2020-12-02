#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
const int inf = 0x7fffffff;
int n, m, s, t, sum = 1;
int h[2][105];
int w[105][105];
int head[20005], cur[20005], use[20005];
ll ans, dis[20005];
queue<int> q;
struct edge
{
    int v;
    int w;
    int f;
    int nxt;
} a[100005];
void ins(int u, int v, int w, int f)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].f = f;
    a[sum].nxt = head[u];
    head[u] = sum;
    ++sum;
    a[sum].v = u;
    a[sum].w = 0;
    a[sum].f = -f;
    a[sum].nxt = head[v];
    head[v] = sum;
    return;
}
bool spfa()
{
    memset(use, 0, sizeof(use));
    memset(dis, -1, sizeof(dis));
    for (int i = s; i <= t; ++i)
        cur[i] = head[i];
    int vis[20005] = {0};
    q.push(s);
    vis[s] = 1;
    dis[s] = 0;
    while (!q.empty())
    {
        int k = q.front();
        q.pop();
        vis[k] = 0;
        int d = head[k];
        while (d)
        {
            if (a[d].w > 0 && dis[a[d].v] < dis[k] + a[d].f)
            {
                dis[a[d].v] = dis[k] + a[d].f;
                if (!vis[a[d].v])
                {
                    q.push(a[d].v);
                    vis[a[d].v] = 1;
                }
            }
            d = a[d].nxt;
        }
    }
    if (dis[t] != -1)
        return true;
    else
        return false;
}
int dinic(int k, int flow)
{
    if (k == t)
    {
        ans += dis[t] * flow;
        return flow;
    }
    use[k] = 1;
    int d = cur[k], res = 0, delta;
    while (d)
    {
        if (!use[a[d].v] && a[d].w > 0 && dis[k] + a[d].f == dis[a[d].v])
        {
            delta = dinic(a[d].v, min(a[d].w, flow - res));
            if (delta)
            {
                a[d].w -= delta;
                a[d ^ 1].w += delta;
                res += delta;
                if (res == flow)
                    break;
            }
        }
        d = a[d].nxt;
        cur[k] = d;
    }
    use[k] = 0;
    if (res != flow)
        use[k] = 1;
    return res;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ans = 0;
        sum = 1;
        memset(h, 0, sizeof(h));
        memset(head, 0, sizeof(head));
        scanf("%d%d", &n, &m);
        s = 0;
        t = n + m + n * m + 1;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
            {
                scanf("%d", &w[i][j]);
                ans += w[i][j];
                if (w[i][j])
                    --ans;
                h[0][i] = max(h[0][i], w[i][j]);
                h[1][j] = max(h[1][j], w[i][j]);
            }
        for (int i = 1; i <= n; ++i)
            if (h[0][i])
            {
                ans -= h[0][i] - 1;
                ins(s, i, 1, 0);
            }
        for (int i = 1; i <= m; ++i)
            if (h[1][i])
            {
                ans -= h[1][i] - 1;
                ins(n + i, t, 1, 0);
            }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (w[i][j] && h[0][i] == h[1][j])
                {
                    ins(i, n + m + (i - 1) * m + j, 1, h[0][i] - 1);
                    ins(n + m + (i - 1) * m + j, j + n, 1, 0);
                }
        while (spfa())
            dinic(s, inf);
        printf("%lld\n", ans);
    }
    return 0;
}