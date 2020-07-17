#include <iostream>
#include <cstdio>
#include <cstring>
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
using namespace std;
int n, m, len, mid, sum, cnt, maxn;
int x[300005], y[300005], lg[300005];
int dep[300005], siz[300005], val[300005];
int lca[300005], head[300005], fa[300005][30], num[300005][30];
struct node
{
    int v;
    int w;
    int nxt;
} a[600005];
inline int read()
{
    int x = 0;
    char ch = gc();
    while (!isdigit(ch))
        ch = gc();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = gc();
    }
    return x;
}
inline void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
inline void dfs1(int k)
{
    for (register int i = 1; i <= lg[dep[k]]; ++i)
    {
        fa[k][i] = fa[fa[k][i - 1]][i - 1];
        num[k][i] = num[k][i - 1] + num[fa[k][i - 1]][i - 1];
    }
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa[k][0])
        {
            dep[a[d].v] = dep[k] + 1;
            fa[a[d].v][0] = k;
            num[a[d].v][0] = a[d].w;
            dfs1(a[d].v);
        }
        d = a[d].nxt;
    }
    return;
}
inline void query(int id, int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (register int i = lg[dep[x] - dep[y]]; i >= 0; --i)
        if (dep[x] - (1 << i) >= dep[y])
        {
            val[id] += num[x][i];
            x = fa[x][i];
        }
    if (x == y)
    {
        lca[id] = x;
        return;
    }
    for (register int i = lg[dep[x]]; i >= 0; --i)
        if (fa[x][i] != fa[y][i])
        {
            val[id] += num[x][i] + num[y][i];
            x = fa[x][i];
            y = fa[y][i];
        }
    val[id] += num[x][0] + num[y][0];
    lca[id] = fa[x][0];
    return;
}
inline bool dfs2(int k)
{
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa[k][0])
        {
            if (dfs2(a[d].v))
                return true;
            siz[k] += siz[a[d].v];
        }
        d = a[d].nxt;
    }
    if (siz[k] == cnt && maxn - num[k][0] <= mid)
        return true;
    return false;
}
inline bool check()
{
    cnt = 0;
    maxn = 0;
    memset(siz, 0, sizeof(siz));
    for (register int i = 1; i <= m; ++i)
        if (val[i] > mid)
        {
            ++cnt;
            ++siz[x[i]];
            ++siz[y[i]];
            siz[lca[i]] -= 2;
            maxn = max(maxn, val[i]);
        }
    return dfs2(1);
}
int main()
{
    n = read();
    m = read();
    for (register int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        u = read();
        v = read();
        w = read();
        len += w;
        ins(u, v, w);
        ins(v, u, w);
    }
    dfs1(1);
    for (register int i = 1; i <= m; ++i)
    {
        x[i] = read();
        y[i] = read();
        query(i, x[i], y[i]);
    }
    int l = 0, r = len;
    while (l < r)
    {
        mid = (l + r) >> 1;
        if (check())
            r = mid;
        else
            l = mid + 1;
    }
    printf("%d", l);
    return 0;
}