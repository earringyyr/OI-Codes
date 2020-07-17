#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
int n, m, sum, s, t, base;
int b[30005], p[30005], head[6000005], dis[6000005], vis[6000005];
struct node
{
    int v;
    int w;
    int nxt;
} a[20000005];
struct pi
{
    int id;
    int dis;
    pi(int x = 0, int y = 0)
    {
        id = x;
        dis = y;
    }
    bool operator<(const pi &y) const
    {
        return dis > y.dis;
    }
};
priority_queue<pi> q;
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dijkstra()
{
    memset(dis, 0x7f, sizeof(dis));
    dis[s] = 0;
    q.push(pi(s, dis[s]));
    while (!q.empty())
    {
        int k = q.top().id;
        q.pop();
        if (vis[k])
            continue;
        vis[k] = 1;
        if (k == t)
            break;
        int d = head[k];
        while (d)
        {
            if (!vis[a[d].v] && dis[k] + a[d].w < dis[a[d].v])
            {
                dis[a[d].v] = dis[k] + a[d].w;
                q.push(pi(a[d].v, dis[a[d].v]));
            }
            d = a[d].nxt;
        }
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    base = sqrt(n / 3);
    for (int i = 1; i <= base; ++i)
        for (int j = 0; j < n; ++j)
        {
            ins(n * i + j, j, 0);
            if (j - i >= 0)
            {
                ins(n * i + j, n * i + j - i, 1);
                ins(n * i + j - i, n * i + j, 1);
            }
            if (j + i < n)
            {
                ins(n * i + j, n * i + j + i, 1);
                ins(n * i + j + i, n * i + j, 1);
            }
        }
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d", &b[i], &p[i]);
        if (p[i] > base)
        {
            int w = b[i], num = 0;
            while (w - p[i] >= 0)
            {
                ins(b[i], w - p[i], ++num);
                w -= p[i];
            }
            w = b[i];
            num = 0;
            while (w + p[i] < n)
            {
                ins(b[i], w + p[i], ++num);
                w += p[i];
            }
        }
        else
            ins(b[i], n * p[i] + b[i], 0);
    }
    s = b[0];
    t = b[1];
    dijkstra();
    if (dis[t] == 0x7f7f7f7f)
        printf("-1");
    else
        printf("%d", dis[t]);
    return 0;
}