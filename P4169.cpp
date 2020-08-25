#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
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
typedef long long ll;
const int inf = 1e8;
int n, m, rt, cnt, ans, np, top, opt;
int minx[600005][2], maxn[600005][2];
int siz[600005], st[600005];
int *nq;
const double alpha = 0.75;
struct node
{
    int x[2];
    node(int aa = 0, int bb = 0)
    {
        x[0] = aa;
        x[1] = bb;
    }
} a[600005], p[600005];
struct tree
{
    int l;
    int r;
} tr[600005];
inline bool cmp(node aa, node bb)
{
    return aa.x[opt] < bb.x[opt];
}
inline void build(int &id, int l, int r, int type)
{
    if (l > r)
        return;
    id = ++cnt;
    int mid = (l + r) >> 1;
    siz[id] = 1;
    opt = type;
    nth_element(a + l, a + mid, a + r + 1, cmp);
    build(tr[id].l, l, mid - 1, type ^ 1);
    build(tr[id].r, mid + 1, r, type ^ 1);
    p[id] = a[mid];
    minx[id][0] = a[mid].x[0];
    minx[id][1] = a[mid].x[1];
    maxn[id][0] = a[mid].x[0];
    maxn[id][1] = a[mid].x[1];
    if (tr[id].l)
    {
        siz[id] += siz[tr[id].l];
        minx[id][0] = min(minx[id][0], minx[tr[id].l][0]);
        maxn[id][0] = max(maxn[id][0], maxn[tr[id].l][0]);
        minx[id][1] = min(minx[id][1], minx[tr[id].l][1]);
        maxn[id][1] = max(maxn[id][1], maxn[tr[id].l][1]);
    }
    if (tr[id].r)
    {
        siz[id] += siz[tr[id].r];
        minx[id][0] = min(minx[id][0], minx[tr[id].r][0]);
        maxn[id][0] = max(maxn[id][0], maxn[tr[id].r][0]);
        minx[id][1] = min(minx[id][1], minx[tr[id].r][1]);
        maxn[id][1] = max(maxn[id][1], maxn[tr[id].r][1]);
    }
    return;
}
inline void insert(int &id, node now, int type)
{
    if (!id)
    {
        id = ++cnt;
        siz[id] = 1;
        p[id] = now;
        minx[id][0] = now.x[0];
        minx[id][1] = now.x[1];
        maxn[id][0] = now.x[0];
        maxn[id][1] = now.x[1];
        return;
    }
    if (now.x[type] <= p[id].x[type])
        insert(tr[id].l, now, type ^ 1);
    else
        insert(tr[id].r, now, type ^ 1);
    siz[id] = 1;
    if (tr[id].l)
    {
        siz[id] += siz[tr[id].l];
        minx[id][0] = min(minx[id][0], minx[tr[id].l][0]);
        maxn[id][0] = max(maxn[id][0], maxn[tr[id].l][0]);
        minx[id][1] = min(minx[id][1], minx[tr[id].l][1]);
        maxn[id][1] = max(maxn[id][1], maxn[tr[id].l][1]);
    }
    if (tr[id].r)
    {
        siz[id] += siz[tr[id].r];
        minx[id][0] = min(minx[id][0], minx[tr[id].r][0]);
        maxn[id][0] = max(maxn[id][0], maxn[tr[id].r][0]);
        minx[id][1] = min(minx[id][1], minx[tr[id].r][1]);
        maxn[id][1] = max(maxn[id][1], maxn[tr[id].r][1]);
    }
    if (max(siz[tr[id].l], siz[tr[id].r]) > siz[id] * alpha)
    {
        np = 1;
        nq = &id;
        opt = type;
    }
    return;
}
inline void dfs(int id)
{
    if (!id)
        return;
    ++top;
    st[top] = id;
    a[top] = p[id];
    dfs(tr[id].l);
    dfs(tr[id].r);
    tr[id].l = 0;
    tr[id].r = 0;
    return;
}
inline void doit(int &id, int l, int r, int type)
{
    if (l > r)
        return;
    int mid = (l + r) >> 1;
    id = st[mid];
    siz[id] = 1;
    opt = type;
    nth_element(a + l, a + mid, a + r + 1, cmp);
    doit(tr[id].l, l, mid - 1, type ^ 1);
    doit(tr[id].r, mid + 1, r, type ^ 1);
    p[id] = a[mid];
    minx[id][0] = a[mid].x[0];
    minx[id][1] = a[mid].x[1];
    maxn[id][0] = a[mid].x[0];
    maxn[id][1] = a[mid].x[1];
    if (tr[id].l)
    {
        siz[id] += siz[tr[id].l];
        minx[id][0] = min(minx[id][0], minx[tr[id].l][0]);
        maxn[id][0] = max(maxn[id][0], maxn[tr[id].l][0]);
        minx[id][1] = min(minx[id][1], minx[tr[id].l][1]);
        maxn[id][1] = max(maxn[id][1], maxn[tr[id].l][1]);
    }
    if (tr[id].r)
    {
        siz[id] += siz[tr[id].r];
        minx[id][0] = min(minx[id][0], minx[tr[id].r][0]);
        maxn[id][0] = max(maxn[id][0], maxn[tr[id].r][0]);
        minx[id][1] = min(minx[id][1], minx[tr[id].r][1]);
        maxn[id][1] = max(maxn[id][1], maxn[tr[id].r][1]);
    }
    return;
}
inline void rebuild(int &id)
{
    top = 0;
    dfs(id);
    doit(id, 1, top, opt);
    return;
}
inline int ask(int id, node now)
{
    int sum[2];
    sum[0] = max(0, max(minx[id][0] - now.x[0], now.x[0] - maxn[id][0]));
    sum[1] = max(0, max(minx[id][1] - now.x[1], now.x[1] - maxn[id][1]));
    return sum[0] + sum[1];
}
inline int dis(node aa, node bb)
{
    return abs(aa.x[0] - bb.x[0]) + abs(aa.x[1] - bb.x[1]);
}
inline void query(int id, node now)
{
    int sum[2] = {inf, inf};
    if (tr[id].l)
        sum[0] = ask(tr[id].l, now);
    if (tr[id].r)
        sum[1] = ask(tr[id].r, now);
    int tmp = dis(now, p[id]);
    if (tmp < ans)
        ans = tmp;
    if (sum[0] < sum[1])
    {
        if (sum[0] < ans)
            query(tr[id].l, now);
        if (sum[1] < ans)
            query(tr[id].r, now);
    }
    else
    {
        if (sum[1] < ans)
            query(tr[id].r, now);
        if (sum[0] < ans)
            query(tr[id].l, now);
    }
    return;
}
int main()
{
    n = io_in::read();
    m = io_in::read();
    for (int i = 1; i <= n; ++i)
    {
        a[i].x[0] = io_in::read();
        a[i].x[1] = io_in::read();
    }
    build(rt, 1, n, 0);
    for (int i = 1; i <= m; ++i)
    {
        int t;
        node b;
        t = io_in::read();
        b.x[0] = io_in::read();
        b.x[1] = io_in::read();
        if (t == 1)
        {
            np = 0;
            insert(rt, b, 0);
            if (np)
                rebuild(*nq);
        }
        else
        {
            ans = inf;
            query(rt, b);
            io_out::write(ans);
            io_out::pc('\n');
        }
    }
    io_out::flush();
    return 0;
}