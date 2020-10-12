#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const double eps = 1e-6;
int n, m, sum;
int head[5005], cnt[5005], vis[5005];
double dis[5005];
queue<int> q;
struct node
{
    int v;
    double w;
    int W;
    int nxt;
} a[6005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].W = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
bool spfa(double mid)
{
    memset(dis, 0x7f, sizeof(dis));
    memset(cnt, 0, sizeof(cnt));
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= sum; ++i)
        a[i].w = mid - a[i].W;
    while (!q.empty())
        q.pop();
    dis[n + 1] = 0;
    vis[n + 1] = 1;
    q.push(n + 1);
    while (!q.empty())
    {
        int k = q.front();
        q.pop();
        vis[k] = 0;
        int d = head[k];
        while (d)
        {
            if (dis[a[d].v] >= dis[k] + a[d].w)
            {
                dis[a[d].v] = dis[k] + a[d].w;
                cnt[a[d].v] = cnt[k] + 1;
                if (cnt[a[d].v] >= n + 2)
                    return true;
                if (!vis[a[d].v])
                {
                    vis[a[d].v] = 1;
                    q.push(a[d].v);
                }
            }
            d = a[d].nxt;
        }
    }
    return false;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, a, b, c, d;
        scanf("%d%d%d%d%d%d", &u, &v, &a, &b, &c, &d);
        ins(u, v, -b - d);
        if (c)
            ins(v, u, d - a);
    }
    double lef = 0, rig = 1000;
    while (rig - lef > eps)
    {
        double mid = (lef + rig) / 2;
        if (spfa(mid))
            lef = mid;
        else
            rig = mid;
    }
    printf("%.2f", lef);
    return 0;
}