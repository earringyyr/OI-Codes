#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
const ll inf = 0x7f7f7f7f7f7f7f7f;
int n, m, k, sum;
int head[3005], w[3005], vis[3005];
ll ans;
ll dis[3005];
struct edge
{
    int v;
    int w;
    int val;
    int nxt;
} a[6005];
struct node
{
    int id;
    ll dis;
    node(int aa = 0, ll bb = 0)
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
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].val = w;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dijkstra()
{
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    q.push(node(1, 0));
    dis[1] = 0;
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
            if (dis[k] + a[d].w < dis[a[d].v])
            {
                dis[a[d].v] = dis[k] + a[d].w;
                q.push(node(a[d].v, dis[a[d].v]));
            }
            d = a[d].nxt;
        }
    }
    return;
}
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d%d", &u, &v, &w[i]);
        ins(u, v, w[i]);
        ins(v, u, w[i]);
    }
    dijkstra();
    ans = dis[n];
    sort(w + 1, w + m + 1);
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= sum; ++j)
            a[j].w = max(0, a[j].val - w[i]);
        dijkstra();
        ans = min(ans, dis[n] + (ll)w[i] * k);
    }
    printf("%lld", ans);
    return 0;
}