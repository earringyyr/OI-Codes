#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
const ll inf = 100000000000000;
int a, b, c, d, e, m, s, sum, len;
int head[500005], vis[500005];
ll dis[500005], ans, ans1, ans2, ans3;
struct edge
{
    int v;
    int w;
    int nxt;
} aa[200005];
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
    aa[sum].v = v;
    aa[sum].w = w;
    aa[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dijkstra()
{
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= len + 1; ++i)
        dis[i] = inf;
    dis[s] = 0;
    q.push(node(s, dis[s]));
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
            if (!vis[aa[d].v] && dis[k] + aa[d].w < dis[aa[d].v])
            {
                dis[aa[d].v] = dis[k] + aa[d].w;
                q.push(node(aa[d].v, dis[aa[d].v]));
            }
            d = aa[d].nxt;
        }
    }
    return;
}
int main()
{
    scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
    len = a + b + c + d + e;
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        ins(l, r + 1, r - l + 1);
        ins(r + 1, l, r - l + 1);
    }
    s = a + 1;
    dijkstra();
    ans1 += dis[a + b + 1];
    ans2 += dis[a + b + c + d + 1];
    ans3 += dis[a + b + c + 1];
    s = a + b + c + 1;
    dijkstra();
    ans1 += dis[a + b + c + d + 1];
    s = a + b + 1;
    dijkstra();
    ans2 += dis[a + b + c + 1];
    ans3 += dis[a + b + c + d + 1];
    ans = min(ans1, min(ans2, ans3));
    if (ans >= inf)
        printf("-1");
    else
        printf("%lld", ans);
    return 0;
}