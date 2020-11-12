#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
int read()
{
    int x = 0, f = 1;
    char c = gc();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = gc();
    }
    while (isdigit(c))
    {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = gc();
    }
    return x * f;
}
int n, m, sum;
int head[55], l[55], dis[55], use[55];
int vis[55][55][35];
struct node
{
    int v;
    int nxt;
} a[75005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
int main()
{
    n = read();
    m = read();
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        u = read();
        v = read();
        vis[u][v][0] = 1;
    }
    for (int i = 1; i <= 30; ++i)
        for (int u = 1; u <= n; ++u)
            for (int v = 1; v <= n; ++v)
                for (int w = 1; w <= n; ++w)
                    if (vis[u][w][i - 1] && vis[w][v][i - 1])
                        vis[u][v][i] = 1;
    for (int i = 0; i <= 30; ++i)
        for (int u = 1; u <= n; ++u)
            for (int v = 1; v <= n; ++v)
                if (vis[u][v][i])
                    ins(u, v);
    int hh = 0, tt = 1, flg = 1;
    l[1] = 1;
    use[1] = 1;
    dis[1] = 0;
    while (hh < tt)
    {
        int k = l[++hh];
        int d = head[k];
        while (d)
        {
            if (!use[a[d].v])
            {
                use[a[d].v] = 1;
                dis[a[d].v] = dis[k] + 1;
                if (a[d].v == n)
                {
                    flg = 0;
                    break;
                }
                l[++tt] = a[d].v;
            }
            d = a[d].nxt;
        }
        if (!flg)
            break;
    }
    printf("%d\n", dis[n]);
    return 0;
}