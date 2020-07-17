#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int w, n, m, sum, vis[1005], s[1005], head[1005];
struct node
{
    int v;
    int w;
    int next;
} a[3005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
bool spfa(int k)
{
    vis[k] = 1;
    int d = head[k];
    while (d)
    {
        if (s[a[d].v] > s[k] + a[d].w)
        {
            s[a[d].v] = s[k] + a[d].w;
            if (vis[a[d].v])
                return false;
            if (!spfa(a[d].v))
                return false;
        }
        d = a[d].next;
    }
    vis[k] = 0;
    return true;
}
int main()
{
    scanf("%d", &w);
    for (int tt = 1; tt <= w; ++tt)
    {
        sum = 0;
        memset(head, 0, sizeof(head));
        memset(vis, 0, sizeof(vis));
        memset(s, 0x3f, sizeof(s));
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; ++i)
        {
            int s, t, v;
            scanf("%d%d%d", &s, &t, &v);
            ins(s - 1, t, v);
            ins(t, s - 1, -v);
        }
        for (int i = 1; i <= n; ++i)
            ins(n + 1, i, 0);
        s[n + 1] = 0;
        if (spfa(n + 1))
            puts("true");
        else
            puts("false");
    }
    return 0;
}