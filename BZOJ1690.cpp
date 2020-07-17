#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define eps 1e-6
using namespace std;
int n, m, sum, f[1005], head[1005], vis[1005], cnt[1005];
double dis[1005];
queue<int> q;
struct node
{
    int v;
    int t;
    double w;
    int nxt;
} a[5005];
void ins(int u, int v, int t)
{
    ++sum;
    a[sum].v = v;
    a[sum].t = t;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
bool spfa()
{
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
                if (cnt[a[d].v] >= n)
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
bool check(double k)
{
    for (int i = 1; i <= sum; ++i)
        a[i].w = a[i].t * k - f[a[i].v];
    for (int i = 1; i <= n; ++i)
    {
        memset(dis, 0x3f, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        memset(cnt, 0, sizeof(cnt));
        vis[i] = 1;
        q = queue<int>();
        q.push(i);
        if (spfa())
            return true;
    }
    return false;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &f[i]);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, t;
        scanf("%d%d%d", &u, &v, &t);
        ins(u, v, t);
    }
    double lef = 0, rig = 1000;
    while (rig - lef > eps)
    {
        double mid = (lef + rig) / 2;
        if (check(mid))
            lef = mid;
        else
            rig = mid;
    }
    printf("%.2f", lef);
    return 0;
}