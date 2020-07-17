#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int t, n, m, sum, d[2005], vis[2005], head[2005], cnt[2005];
queue<int> q;
struct node
{
    int v;
    int w;
    int next;
} a[6005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
bool spfa()
{
    memset(cnt, 0, sizeof(cnt));
    memset(vis, 0, sizeof(vis));
    memset(d, 0x7f, sizeof(d));
    d[1] = 0;
    vis[1] = 1;
    q.push(1);
    while (!q.empty())
    {
        int k = q.front();
        q.pop();
        vis[k] = 0;
        int dd = head[k];
        while (dd)
        {
            if (d[a[dd].v] > d[k] + a[dd].w)
            {
                d[a[dd].v] = d[k] + a[dd].w;
                if (!vis[a[dd].v])
                {
                    vis[a[dd].v] = 1;
                    ++cnt[a[dd].v];
                    if (cnt[a[dd].v] > n)
                        return true;
                    q.push(a[dd].v);
                }
            }
            dd = a[dd].next;
        }
    }
    return false;
}
int main()
{
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        sum = 0;
        memset(head, 0, sizeof(head));
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; ++i)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            ins(u, v, w);
            if (w >= 0)
                ins(v, u, w);
        }
        if (spfa())
            puts("YE5");
        else
            puts("N0");
    }
    return 0;
}