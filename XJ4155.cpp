#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
#define lch id << 1
#define rch id << 1 | 1
const int inf = 0x7fffffff;
int n, m, ans;
int *a[1000005], *b[1000005], *c[1000005], *d[1000005], *e[1000005];
int *dis[1000005];
int *fa[4000005], *cnt[4000005];
char buf[1 << 21], *p1 = buf, *p2 = buf;
struct tree
{
    int l;
    int r;
} tr[4000005];
struct node
{
    int x;
    int y;
    int dis;
    node(int xx = 0, int yy = 0, int dd = 0)
    {
        x = xx;
        y = yy;
        dis = dd;
    }
    bool operator<(const node &bb) const
    {
        return dis > bb.dis;
    }
};
priority_queue<node> q;
int read()
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
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    fa[id] = new int[n + 2];
    cnt[id] = new int[n + 1];
    for (int i = 1; i <= n + 1; ++i)
        fa[id][i] = i;
    for (int i = 1; i <= n; ++i)
        cnt[id][i] = r - l + 1;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    return;
}
int getfather(int x, int y)
{
    if (fa[x][y] == y)
        return y;
    fa[x][y] = getfather(x, fa[x][y]);
    return fa[x][y];
}
void solve(int id, int l, int r, int L, int R, int d)
{
    if (getfather(id, L) > R)
        return;
    if (tr[id].l == tr[id].r)
    {
        int i = getfather(id, L);
        while (i <= R)
        {
            int x = i, y = l;
            dis[y][x] = d + a[y][x] + 1;
            q.push(node(y, x, dis[y][x]));
            for (int j = id; j >= 1; j >>= 1)
            {
                --cnt[j][i];
                if (!cnt[j][i])
                    fa[j][i] = i + 1;
            }
            i = getfather(id, i);
        }
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        solve(lch, l, r, L, R, d);
    else if (l >= mid + 1)
        solve(rch, l, r, L, R, d);
    else
    {
        solve(lch, l, mid, L, R, d);
        solve(rch, mid + 1, r, L, R, d);
    }
    return;
}
int main()
{
    n = read();
    m = read();
    for (register int i = 1; i <= m; ++i)
    {
        a[i] = new int[n + 1];
        b[i] = new int[n + 1];
        c[i] = new int[n + 1];
        d[i] = new int[n + 1];
        e[i] = new int[n + 1];
        dis[i] = new int[n + 1];
    }
    for (register int i = 1; i <= n; ++i)
        for (register int j = 1; j <= m; ++j)
        {
            a[j][i] = read();
            b[j][i] = read();
            b[j][i] = max(b[j][i], 1);
            c[j][i] = read();
            c[j][i] = max(c[j][i], 1);
            d[j][i] = read();
            d[j][i] = min(d[j][i], n);
            e[j][i] = read();
            e[j][i] = min(e[j][i], m);
            dis[j][i] = inf;
        }
    build(1, 1, m);
    for (register int i = 1; i <= m; ++i)
    {
        dis[i][1] = a[i][1];
        q.push(node(i, 1, dis[i][1]));
    }
    while (!q.empty())
    {
        node k = q.top();
        q.pop();
        if (k.y == n)
        {
            printf("%d", k.dis);
            return 0;
        }
        if (b[k.x][k.y] <= d[k.x][k.y] && c[k.x][k.y] <= e[k.x][k.y])
            solve(1, c[k.x][k.y], e[k.x][k.y], b[k.x][k.y], d[k.x][k.y], k.dis);
    }
    return 0;
}