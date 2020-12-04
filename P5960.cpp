#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, sum, hh, tt;
int head[5005], dis[5005], cnt[5005], vis[5005];
int l[50000005];
struct node
{
    int v;
    int w;
    int nxt;
} a[10005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
bool spfa()
{
    memset(dis, 0x7f, sizeof(dis));
    dis[0] = 0;
    l[++tt] = 0;
    while (hh < tt)
    {
        int k = l[++hh];
        vis[k] = 0;
        int d = head[k];
        while (d)
        {
            if (dis[a[d].v] > dis[k] + a[d].w)
            {
                dis[a[d].v] = dis[k] + a[d].w;
                cnt[a[d].v] = cnt[k] + 1;
                if (cnt[a[d].v] >= n + 1)
                    return false;
                if (!vis[a[d].v])
                {
                    vis[a[d].v] = 1;
                    l[++tt] = a[d].v;
                }
            }
            d = a[d].nxt;
        }
    }
    return true;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        ins(v, u, w);
    }
    for (int i = 1; i <= n; ++i)
        ins(0, i, 0);
    if (!spfa())
    {
        printf("NO");
        return 0;
    }
    for (int i = 1; i <= n; ++i)
        printf("%d ", dis[i]);
    return 0;
}