#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, q, sum, hh, tt;
int fa[5005], head[10005];
int vis[10005], l[10005];
int dis[5005][10005];
struct node
{
    int v;
    int nxt;
} a[20005];
int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
int main()
{
    n = read();
    m = read();
    q = read();
    memset(dis, 0x7f, sizeof(dis));
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        u = read();
        v = read();
        ins(u, v + n);
        ins(u + n, v);
        ins(v, u + n);
        ins(v + n, u);
        u = getfather(u), v = getfather(v);
        if (u != v)
            fa[u] = v;
    }
    for (int i = 1; i <= n; ++i)
    {
        memset(vis, 0, sizeof(vis));
        hh = 0;
        tt = 0;
        dis[i][i] = 0;
        vis[i] = 1;
        l[++tt] = i;
        while (hh < tt)
        {
            int k = l[++hh];
            int d = head[k];
            while (d)
            {
                if (!vis[a[d].v])
                {
                    dis[i][a[d].v] = dis[i][k] + 1;
                    vis[a[d].v] = 1;
                    l[++tt] = a[d].v;
                }
                d = a[d].nxt;
            }
        }
    }
    for (int i = 1; i <= q; ++i)
    {
        int s, t, d;
        s = read();
        t = read();
        d = read();
        if (s == t)
        {
            if (d == 0 || (head[s] && d % 2 == 0) || (d >= dis[s][s + n] && (d - dis[s][s + n]) % 2 == 0))
                puts("Yes");
            else
                puts("No");
            continue;
        }
        if (getfather(s) != getfather(t))
        {
            puts("No");
            continue;
        }
        if (d >= dis[s][t] && (d - dis[s][t]) % 2 == 0)
            puts("Yes");
        else if (d >= dis[s][t + n] && (d - dis[s][t + n]) % 2 == 0)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}