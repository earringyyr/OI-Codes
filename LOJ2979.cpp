#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int inf = 0x7f7f7f7f;
int n, m, s, t, cnt, sum = 1, num, ans;
int head[20005], cur[20005], dis[20005], use[20005];
int l[305][15], r[305][15];
int rt[25];
queue<int> q;
namespace io
{
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
} // namespace io
using namespace io;
struct edge
{
    int v;
    int w;
    int f;
    int nxt;
} a[1000005];
struct tree
{
    int l;
    int r;
} tr[100005];
void ins(int u, int v, int w, int f)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].f = f;
    a[sum].nxt = head[u];
    head[u] = sum;
    ++sum;
    a[sum].v = u;
    a[sum].w = 0;
    a[sum].f = -f;
    a[sum].nxt = head[v];
    head[v] = sum;
    return;
}
int build(int l, int r, int id)
{
    int x = ++cnt;
    if (l == r)
    {
        ins(x, ((id + 1) / 2 - 1) * n + l, inf, 0);
        return x;
    }
    int mid = (l + r) >> 1;
    tr[x].l = build(l, mid, id);
    tr[x].r = build(mid + 1, r, id);
    if (id % 2 == 1)
    {
        ins(x, tr[x].l, inf, (r - mid) * 2);
        ins(x, tr[x].r, inf, 0);
    }
    else
    {
        ins(x, tr[x].l, inf, 0);
        ins(x, tr[x].r, inf, (mid - l + 1) * 2);
    }
    return x;
}
void link(int x, int y, int l, int r)
{
    if (l == r)
    {
        ins(x, y, inf, 1);
        ins(y, x, inf, 1);
        return;
    }
    int mid = (l + r) >> 1;
    link(tr[x].l, tr[y].l, l, mid);
    link(tr[x].r, tr[y].r, mid + 1, r);
    return;
}
void insert(int x, int l, int r, int L, int R, int val, int id, int y)
{
    if (l == L && r == R)
    {
        ins(y, x, inf, val);
        return;
    }
    int mid = (l + r) >> 1;
    if (R <= mid)
    {
        insert(tr[x].l, l, mid, L, R, val, id, y);
        return;
    }
    if (L >= mid + 1)
    {
        insert(tr[x].r, mid + 1, r, L, R, val, id, y);
        return;
    }
    if (id % 2 == 1)
    {
        insert(tr[x].l, l, mid, L, mid, val + (R - mid) * 2, id, y);
        insert(tr[x].r, mid + 1, r, mid + 1, R, val, id, y);
    }
    else
    {
        insert(tr[x].l, l, mid, L, mid, val, id, y);
        insert(tr[x].r, mid + 1, r, mid + 1, R, val + (mid - L + 1) * 2, id, y);
    }
    return;
}
bool spfa()
{
    memset(use, 0, sizeof(use));
    memset(dis, 0x7f, sizeof(dis));
    for (int i = s; i <= t; ++i)
        cur[i] = head[i];
    int vis[20005] = {0};
    q.push(s);
    vis[s] = 1;
    dis[s] = 0;
    while (!q.empty())
    {
        int k = q.front();
        q.pop();
        vis[k] = 0;
        int d = head[k];
        while (d)
        {
            if (a[d].w > 0 && dis[a[d].v] > dis[k] + a[d].f)
            {
                dis[a[d].v] = dis[k] + a[d].f;
                if (!vis[a[d].v])
                {
                    q.push(a[d].v);
                    vis[a[d].v] = 1;
                }
            }
            d = a[d].nxt;
        }
    }
    if (dis[t] < inf)
        return true;
    else
        return false;
}
int dinic(int k, int flow)
{
    if (k == t)
    {
        ans += dis[t] * flow;
        return flow;
    }
    use[k] = 1;
    int d = cur[k], res = 0, delta;
    while (d)
    {
        if (!use[a[d].v] && a[d].w > 0 && dis[k] + a[d].f == dis[a[d].v])
        {
            delta = dinic(a[d].v, min(a[d].w, flow - res));
            if (delta)
            {
                a[d].w -= delta;
                a[d ^ 1].w += delta;
                res += delta;
                if (res == flow)
                    break;
            }
        }
        d = a[d].nxt;
        cur[k] = d;
    }
    use[k] = 0;
    if (res != flow)
        use[k] = 1;
    return res;
}
int main()
{
    n = io::read();
    m = io::read();
    cnt = 2 * n * m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            l[i][j] = io::read();
            ++l[i][j];
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            r[i][j] = io::read();
            ++r[i][j];
        }
    for (int i = 1; i <= 2 * m; ++i)
        rt[i] = build(1, n, i);
    s = 0;
    t = ++cnt;
    for (int i = 1; i <= n * m; ++i)
    {
        ins(s, n * m + i, 1, 0);
        ins(i, t, 1, 0);
    }
    for (int i = 1; i <= m; ++i)
        if (i != m)
        {
            link(rt[2 * i - 1], rt[2 * i + 1], 1, n);
            link(rt[2 * i], rt[2 * i + 2], 1, n);
        }
        else
        {
            link(rt[2 * i - 1], rt[1], 1, n);
            link(rt[2 * i], rt[2], 1, n);
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            if (l[i][j] <= i)
            {
                int R = min(i, r[i][j]);
                insert(rt[2 * j - 1], 1, n, l[i][j], R, (i - R) * 2, 2 * j - 1, n * m + (j - 1) * n + i);
            }
            if (r[i][j] > i)
            {
                int L = max(i + 1, l[i][j]);
                insert(rt[2 * j], 1, n, L, r[i][j], (L - i) * 2, 2 * j, n * m + (j - 1) * n + i);
            }
        }
    while (spfa())
        num += dinic(s, inf);
    if (num < n * m)
        printf("no solution");
    else
        printf("%d", ans);
    return 0;
}