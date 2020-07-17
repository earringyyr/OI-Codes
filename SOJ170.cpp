#include <iostream>
#include <cstdio>
#include <cstring>
#define inf 0x7f7f7f7f
using namespace std;
int n, k, tt, sum, h, t = 1, head[10005], d[10005], q[10000005], vis[10005];
struct node
{
    int v;
    int w;
    int next;
} a[200005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void spfa()
{
    memset(d, 0x7f, sizeof(d));
    d[tt] = 0;
    q[1] = tt;
    vis[tt] = 1;
    while (h < t)
    {
        int k = q[++h];
        vis[k] = 0;
        int dd = head[k];
        while (dd)
        {
            if (d[a[dd].v] > d[k] + a[dd].w)
            {
                d[a[dd].v] = d[k] + a[dd].w;
                if (!vis[a[dd].v])
                {
                    q[++t] = a[dd].v;
                    vis[a[dd].v] = 1;
                }
            }
            dd = a[dd].next;
        }
    }
    return;
}
int main()
{
    scanf("%d%d%d", &n, &k, &tt);
    for (int i = 1; i <= k; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        ins(u, v, w);
        ins(v, u, w);
    }
    spfa();
    printf("%d", d[n]);
    return 0;
}