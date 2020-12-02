#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
int n, m, sum;
int head[1005], vis[1005], dis[1005];
double ans;
struct node
{
    int u;
    int v;
    int c;
    int f;
} e[1005];
struct edge
{
    int v;
    int w;
    int nxt;
} a[2005];
struct pi
{
    int id;
    int dis;
    pi(int aa = 0, int bb = 0)
    {
        id = aa;
        dis = bb;
    }
    bool operator<(const pi &bb) const
    {
        return dis > bb.dis;
    }
};
priority_queue<pi> q;
bool cmp(node aa, node bb)
{
    return aa.f > bb.f;
}
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
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x7f, sizeof(dis));
    dis[1] = 0;
    q.push(pi(1, 0));
    while (!q.empty())
    {
        int k = q.top().id;
        q.pop();
        if (vis[k])
            continue;
        vis[k] = 1;
        int d = head[k];
        while (d)
        {
            if (!vis[a[d].v] && dis[a[d].v] > dis[k] + a[d].w)
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
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].c, &e[i].f);
    sort(e + 1, e + m + 1, cmp);
    for (int i = 1; i <= m; ++i)
    {
        ins(e[i].u, e[i].v, e[i].c);
        ins(e[i].v, e[i].u, e[i].c);
        dijkstra();
        ans = max(ans, (double)e[i].f / dis[n]);
    }
    printf("%d", (int)floor(ans * 1000000));
    return 0;
}