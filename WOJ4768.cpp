#include <iostream>
#include <cstdio>
#include <set>
#include <cmath>
#include <algorithm>
#define inf 0x3f3f3f3f
using namespace std;
int n, tx;
struct point
{
    int l;
    int r;
    int d;
    int u;
} a[500005];
struct node
{
    int x;
    int y;
    int d;
    node(int aa, int bb, int cc)
    {
        x = aa;
        y = bb;
        d = cc;
    }
    inline bool operator<(const node &bb) const
    {
        return y < bb.y;
    }
};
set<node> s;
inline bool cmp(point aa, point bb)
{
    return aa.l < bb.l;
}
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (isdigit(c))
    {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline int dis(int x, int y, int xx, int yy)
{
    return abs(x - xx) + abs(y - yy);
}
int main()
{
    n = read();
    tx = read();
    for (int i = 1; i <= n; ++i)
    {
        a[i].l = read();
        a[i].d = read();
        a[i].r = read();
        a[i].u = read();
        if (a[i].l > a[i].r)
            swap(a[i].l, a[i].r);
        if (a[i].d > a[i].u)
            swap(a[i].d, a[i].u);
    }
    sort(a + 1, a + n + 1, cmp);
    s.insert(node(0, 0, 0));
    for (int i = 1; i <= n; ++i)
    {
        set<node>::iterator h, t, gu;
        int p = inf, q = inf;
        h = s.lower_bound(node(a[i].l, a[i].d, 0));
        t = s.upper_bound(node(a[i].l, a[i].u, 0));
        while (h != t)
        {
            p = min(p, dis(h->x, h->y, a[i].l, a[i].d) + h->d);
            q = min(q, dis(h->x, h->y, a[i].l, a[i].u) + h->d);
            gu = h;
            ++h;
            s.erase(gu);
        }
        s.insert(node(a[i].l, a[i].d, p));
        s.insert(node(a[i].l, a[i].u, q));
    }
    int ans = inf;
    for (set<node>::iterator it = s.begin(); it != s.end(); ++it)
        ans = min(ans, dis(it->x, it->y, tx, 0) + it->d);
    printf("%d", ans);
    return 0;
}