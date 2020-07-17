#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
int n, m, sum, head[1000005], d[1000005], vis[1000005], ans[1000005];
struct node
{
    int v;
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
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
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
            if (!vis[a[dd].v] && d[a[dd].v] > d[k.id] + 1)
            {
                d[a[dd].v] = d[k.id] + 1;
                q.push(point(a[dd].v, d[a[dd].v]));
                ans[a[dd].v] = ans[k.id];
            }
            else if (d[a[dd].v] == d[k.id] + 1)
                ans[a[dd].v] = (ans[a[dd].v] + ans[k.id]) % 100003;
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
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    dijkstra();
    for (int i = 1; i <= n; ++i)
        printf("%d\n", ans[i]);
    return 0;
}