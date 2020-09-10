#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
#define int long long
using namespace std;
const double eps = 1e-8;
int n, m, q, type[100005], pos[100005], vis[100005];
double ans[100005];
struct node
{
    int x;
    int y;
    node(int aa = 0, int bb = 0)
    {
        x = aa;
        y = bb;
    }
    node operator+(const node &bb) const
    {
        return node(x + bb.x, y + bb.y);
    }
    node operator-(const node &bb) const
    {
        return node(x - bb.x, y - bb.y);
    }
    node operator*(const int &bb) const
    {
        return node(x * bb, y * bb);
    }
    int operator^(const node &bb) const
    {
        return x * bb.y - y * bb.x;
    }
} base, c[100005];
set<node> s;
int dis(node p)
{
    return (base.x - p.x) * (base.x - p.x) + (base.y - p.y) * (base.y - p.y);
}
double dist(node aa, node bb)
{
    return sqrt((aa.x - bb.x) * (aa.x - bb.x) + (aa.y - bb.y) * (aa.y - bb.y));
}
bool operator<(const node &aa, const node &bb)
{
    double aaa = atan2(aa.y - base.y, aa.x - base.x);
    double bbb = atan2(bb.y - base.y, bb.x - base.x);
    if (fabs(aaa - bbb) < eps)
        return dis(aa) < dis(bb);
    return aaa < bbb;
}
typedef set<node>::iterator ite;
ite pre(ite it)
{
    if (it == s.begin())
        return --s.end();
    --it;
    return it;
}
ite nxt(ite it)
{
    ++it;
    if (it == s.end())
        return s.begin();
    return it;
}
bool query(node p)
{
    ite it = s.lower_bound(p);
    if (it == s.end())
        it = s.begin();
    return ((p - *pre(it)) ^ (*it - *pre(it))) < eps;
}
void insert(node p)
{
    if (query(p))
        return;
    s.insert(p);
    ite it = s.find(p);
    ans[0] -= dist(*pre(it), *nxt(it));
    ans[0] += dist(*pre(it), *it) + dist(*it, *nxt(it));
    it = nxt(s.find(p));
    while (s.size() > 3 && ((p - *nxt(it)) ^ (*it - *nxt(it))) < eps)
    {
        ans[0] -= dist(*pre(it), *it) + dist(*it, *nxt(it));
        ans[0] += dist(*pre(it), *nxt(it));
        it = nxt(it);
        s.erase(pre(it));
    }
    it = pre(s.find(p));
    while (s.size() > 3 && ((*it - *pre(it)) ^ (p - *pre(it))) < eps)
    {
        ans[0] -= dist(*pre(it), *it) + dist(*it, *nxt(it));
        ans[0] += dist(*pre(it), *nxt(it));
        it = pre(it);
        s.erase(nxt(it));
    }
    return;
}
signed main()
{
    int X, Y;
    scanf("%lld%lld%lld", &n, &X, &Y);
    base.x = n + X;
    base.y = Y;
    s.insert(node(0, 0));
    s.insert(node(3 * n, 0));
    s.insert(node(3 * X, 3 * Y));
    ans[0] += dist(node(3 * n, 0), node(3 * X, 3 * Y));
    ans[0] += dist(node(3 * X, 3 * Y), node(0, 0));
    scanf("%lld", &m);
    for (int i = 1; i <= m; ++i)
        scanf("%lld%lld", &c[i].x, &c[i].y);
    scanf("%lld", &q);
    for (int i = 1; i <= q; ++i)
    {
        scanf("%lld", &type[i]);
        if (type[i] == 1)
        {
            scanf("%lld", &pos[i]);
            vis[pos[i]] = 1;
        }
    }
    for (int i = 1; i <= m; ++i)
        if (!vis[i])
            insert(c[i] * 3);
    for (int i = q; i >= 1; --i)
        if (type[i] == 1)
            insert(c[pos[i]] * 3);
        else
            ans[i] = ans[0];
    for (int i = 1; i <= q; ++i)
        if (type[i] == 2)
            printf("%.2f\n", ans[i] / 3);
    return 0;
}