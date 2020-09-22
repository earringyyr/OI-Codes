#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
namespace io_in
{
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
} // namespace io_in
namespace io_out
{
    char buf[1 << 21];
    int p1 = -1;
    const int p2 = (1 << 21) - 1;
    void flush()
    {
        fwrite(buf, 1, p1 + 1, stdout);
        p1 = -1;
        return;
    }
    void pc(char x)
    {
        if (p1 == p2)
            flush();
        buf[++p1] = x;
        return;
    }
    void write(int x)
    {
        char buffer[10];
        int len = -1;
        if (x >= 0)
        {
            do
            {
                buffer[++len] = (x % 10) | 48;
                x /= 10;
            } while (x);
        }
        else
        {
            pc('-');
            do
            {
                buffer[++len] = -(x % 10) | 48;
                x /= 10;
            } while (x);
        }
        while (len >= 0)
            pc(buffer[len--]);
        return;
    }
} // namespace io_out
using namespace std;
int n, Q, rt, sum, cnt, num, tp, pos;
int head[200005], fa[200005], son[200005];
int siz[200005], dep[200005], top[200005];
int dfn[200005], c[200005], vis[200005];
int ans[2][200005];
struct edge
{
    int v;
    int nxt;
} a[200005];
struct node1
{
    int x;
    int y;
    int id;
    int tim;
} q[200005];
struct node2
{
    int id;
    int tim;
} st[200005];
inline bool cmp(node1 aa, node1 bb)
{
    return aa.tim < bb.tim;
}
inline void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
inline void dfs1(int k)
{
    son[k] = -1;
    siz[k] = 1;
    int d = head[k];
    while (d)
    {
        dep[a[d].v] = dep[k] + 1;
        dfs1(a[d].v);
        siz[k] += siz[a[d].v];
        if (son[k] == -1 || siz[a[d].v] > siz[son[k]])
            son[k] = a[d].v;
        d = a[d].nxt;
    }
    return;
}
inline void dfs2(int k, int topf)
{
    dfn[k] = ++cnt;
    top[k] = topf;
    if (son[k] != -1)
        dfs2(son[k], topf);
    int d = head[k];
    while (d)
    {
        if (a[d].v != son[k])
            dfs2(a[d].v, a[d].v);
        d = a[d].nxt;
    }
    return;
}
inline int lowbit(int x)
{
    return x & -x;
}
inline void add(int x)
{
    while (x <= n)
    {
        ++c[x];
        x += lowbit(x);
    }
    return;
}
inline int ask(int x)
{
    if (!x)
        return 0;
    int tot = 0;
    while (x >= 1)
    {
        tot += c[x];
        x -= lowbit(x);
    }
    return tot;
}
inline int query(int u, int v, int type)
{
    int tot = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        if (!type)
            tot += dfn[u] - dfn[top[u]] + 1;
        else
            tot += ask(dfn[u]) - ask(dfn[top[u]] - 1);
        u = fa[top[u]];
    }
    if (dfn[u] > dfn[v])
        swap(u, v);
    if (!type)
        tot += dfn[v] - dfn[u] + 1;
    else
        tot += ask(dfn[v]) - ask(dfn[u] - 1);
    return tot;
}
int main()
{
    n = io_in::read();
    for (register int i = 1; i <= n; ++i)
    {
        fa[i] = io_in::read();
        if (fa[i])
            ins(fa[i], i);
        else
            rt = i;
    }
    dfs1(rt);
    dfs2(rt, rt);
    Q = io_in::read();
    for (register int i = 1; i <= Q; ++i)
    {
        int k;
        k = io_in::read();
        if (k == 1)
        {
            int C;
            vis[i] = 1;
            ++num;
            q[num].id = i;
            q[num].x = io_in::read();
            q[num].y = io_in::read();
            C = io_in::read();
            q[num].tim = i - C - 1;
            ans[0][i] = query(q[num].x, q[num].y, 0);
        }
        else
        {
            ++tp;
            st[tp].id = io_in::read();
            st[tp].tim = i;
        }
    }
    sort(q + 1, q + num + 1, cmp);
    for (register int i = 1; i <= num; ++i)
    {
        while (pos < tp && st[pos + 1].tim <= q[i].tim)
        {
            ++pos;
            if (ask(dfn[st[pos].id]) - ask(dfn[st[pos].id] - 1) == 0)
                add(dfn[st[pos].id]);
        }
        ans[1][q[i].id] = query(q[i].x, q[i].y, 1);
    }
    for (register int i = 1; i <= Q; ++i)
        if (vis[i])
        {
            io_out::write(ans[0][i]);
            io_out::pc(' ');
            io_out::write(ans[1][i]);
            io_out::pc('\n');
        }
    io_out::flush();
    return 0;
}