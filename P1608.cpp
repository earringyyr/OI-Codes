#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
int n, m, sum, head[2005], d[2005], vis[2005], ans[2005], use[2005][2005];
struct node
{
    int v;
    int w;
    int next;
} a[4000005];
struct point
{
    int id;
    int d;
    point(int aa, int bb)
    {
        id = aa;
        d = bb;
    }
    bool operator<(const point bb) const
    {
        return d > bb.d;
    }
};
priority_queue<point> q;
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void dijkstra()
{
    memset(d, 0x7f, sizeof(d));
    d[1] = 0;
    q.push(point(1, 0));
    ans[1] = 1;
    while (!q.empty())
    {
        point k = q.top();
        q.pop();
        if (vis[k.id])
            continue;
        vis[k.id] = 1;
        int dd = head[k.id];
        while (dd)
        {
            if (!vis[a[dd].v] && d[a[dd].v] > d[k.id] + a[dd].w)
            {
                d[a[dd].v] = d[k.id] + a[dd].w;
                q.push(point(a[dd].v, d[a[dd].v]));
                ans[a[dd].v] = ans[k.id];
            }
            else if (d[a[dd].v] == d[k.id] + a[dd].w)
                ans[a[dd].v] = ans[a[dd].v] + ans[k.id];
            dd = a[dd].next;
        }
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        if (!use[u][v] || use[u][v] > w)
        {
            ins(u, v, w);
            use[u][v] = w;
        }
    }
    dijkstra();
    if (d[n] == 0x7f7f7f7f)
        printf("No answer");
    else
        printf("%d %d", d[n], ans[n]);
    return 0;
}