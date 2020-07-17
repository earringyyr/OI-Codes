#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
int n, sum, vis[200005], d[200005], head[200005];
struct node
{
    int v;
    int w;
    int next;
} a[800005];
struct bili
{
    int id;
    int x;
    int y;
} b[200005];
struct point
{
    int id;
    int d;
    point(int aa, int bb)
    {
        id = aa;
        d = bb;
    }
    bool operator<(point bb) const
    {
        return d > bb.d;
    }
};
priority_queue<point> q;
inline int read()
{
    int x = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
    {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    return x;
}
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
bool cmp1(bili aa, bili bb)
{
    return aa.x < bb.x;
}
bool cmp2(bili aa, bili bb)
{
    return aa.y < bb.y;
}
void dijkstra()
{
    memset(d, 0x7f, sizeof(d));
    d[1] = 0;
    q.push(point(1, 0));
    while (!q.empty())
    {
        point k = q.top();
        q.pop();
        if (vis[k.id])
            continue;
        vis[k.id] = 1;
        if (k.id == n)
            break;
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
int main()
{
    n = read();
    for (int i = 1; i <= n; ++i)
    {
        b[i].id = i;
        b[i].x = read();
        b[i].y = read();
    }
    sort(b + 1, b + n + 1, cmp1);
    for (int i = 1; i < n; ++i)
    {
        ins(b[i].id, b[i + 1].id, b[i + 1].x - b[i].x);
        ins(b[i + 1].id, b[i].id, b[i + 1].x - b[i].x);
    }
    sort(b + 1, b + n + 1, cmp2);
    for (int i = 1; i < n; ++i)
    {
        ins(b[i].id, b[i + 1].id, b[i + 1].y - b[i].y);
        ins(b[i + 1].id, b[i].id, b[i + 1].y - b[i].y);
    }
    dijkstra();
    printf("%d", d[n]);
    return 0;
}