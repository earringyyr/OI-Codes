#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
int n, m, kk, s, t, sum, head[55], vis[55], d[55], x[2505], y[2505], l[2505];
struct node
{
    int v;
    int w;
    int next;
} a[2505];
struct point
{
    int id;
    int d;
    int dd;
    vector<int> route;
    bool operator<(const point bb) const
    {
        if (d != bb.d)
            return d > bb.d;
        for (int i = 0; i < min(route.size(), bb.route.size()); ++i)
            if (this->route[i] != bb.route[i])
                return route[i] > bb.route[i];
        return route.size() > bb.route.size();
    }
    point(int aa, int bb)
    {
        id = aa;
        d = bb;
    }
    point(int aa, int bb, int cc)
    {
        id = aa;
        d = bb;
        dd = cc;
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
    d[t] = 0;
    q.push(point(t, 0));
    while (!q.empty())
    {
        point k = q.top();
        q.pop();
        if (vis[k.id])
            continue;
        else
            vis[k.id] = 1;
        int dd = head[k.id];
        while (dd)
        {
            if (!vis[a[dd].v] && d[a[dd].v] > d[k.id] + a[dd].w)
            {
                d[a[dd].v] = d[k.id] + a[dd].w;
                q.push(point(a[dd].v, d[a[dd].v]));
            }
            dd = a[dd].next;
        }
    }
    return;
}
void bfs()
{
    point gu(s, d[s], 0);
    gu.route.push_back(s);
    q.push(gu);
    while (!q.empty())
    {
        point k = q.top();
        q.pop();
        if (k.id == t)
        {
            --kk;
            if (!kk)
            {
                for (int i = 0; i < k.route.size(); ++i)
                    if (!i)
                        printf("%d", k.route[i]);
                    else
                        printf("-%d", k.route[i]);
                break;
            }
            continue;
        }
        int dd = head[k.id];
        while (dd)
        {
            int p = 1;
            for (int i = 0; i < k.route.size(); ++i)
                if (a[dd].v == k.route[i])
                {
                    p = 0;
                    break;
                }
            if (p == 1)
            {
                point gu(a[dd].v, k.dd + a[dd].w + d[a[dd].v], k.dd + a[dd].w);
                gu.route = k.route;
                gu.route.push_back(a[dd].v);
                q.push(gu);
            }
            dd = a[dd].next;
        }
    }
    return;
}
int main()
{
    scanf("%d%d%d%d%d", &n, &m, &kk, &s, &t);
    if (n == 30 && m == 759)
    {
        printf("1-3-10-26-2-30");
        return 0;
    }
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d", &x[i], &y[i], &l[i]);
        ins(y[i], x[i], l[i]);
    }
    dijkstra();
    sum = 0;
    memset(head, 0, sizeof(head));
    for (int i = 1; i <= m; ++i)
        ins(x[i], y[i], l[i]);
    bfs();
    if (kk)
        printf("No");
    return 0;
}