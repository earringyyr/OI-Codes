#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
const int inf = 0x7f7f7f7f;
int n, m, sum;
int head[300005], vis[300005], dis[300005];
struct edge
{
    int v;
    int w;
    int nxt;
} a[300005];
struct node
{
    int id;
    int dis;
    node(int aa = 0, int bb = 0)
    {
        id = aa;
        dis = bb;
    }
    bool operator<(const node &bb) const
    {
        return dis > bb.dis;
    }
};
priority_queue<node> q;
int read()
{
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
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
bool dijkstra(ll mid)
{
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x7f, sizeof(dis));
    dis[1] = 1;
    q.push(node(1, dis[1]));
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
            if (dis[a[d].v] > dis[k] + 1 && (ll)dis[k] * a[d].w <= mid)
            {
                dis[a[d].v] = dis[k] + 1;
                q.push(node(a[d].v, dis[a[d].v]));
            }
            d = a[d].nxt;
        }
    }
    return dis[n] != inf;
}
int main()
{
    n = read();
    m = read();
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        u = read();
        v = read();
        w = read();
        ins(u, v, w);
    }
    ll l = 0, r = 3e14;
    while (l < r)
    {
        ll mid = (l + r) >> 1;
        if (dijkstra(mid))
            r = mid;
        else
            l = mid + 1;
    }
    printf("%lld", l);
    return 0;
}