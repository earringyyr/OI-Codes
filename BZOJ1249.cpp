#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
#define int long long
using namespace std;
const double eps = 1e-8;
int q, ans, X[4], Y[4];
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
    int operator*(const node &bb) const
    {
        return x * bb.x + y * bb.y;
    }
    int operator^(const node &bb) const
    {
        return x * bb.y - y * bb.x;
    }
} base;
set<node> s;
int dis(node p)
{
    return (base.x - p.x) * (base.x - p.x) + (base.y - p.y) * (base.y - p.y);
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
    ans -= (*pre(it) ^ *nxt(it));
    ans += (*pre(it) ^ *it) + (*it ^ *nxt(it));
    it = nxt(s.find(p));
    while (s.size() > 3 && ((p - *nxt(it)) ^ (*it - *nxt(it))) < eps)
    {
        ans -= (*pre(it) ^ *it) + (*it ^ *nxt(it));
        ans += (*pre(it) ^ *nxt(it));
        it = nxt(it);
        s.erase(pre(it));
    }
    it = pre(s.find(p));
    while (s.size() > 3 && ((*it - *pre(it)) ^ (p - *pre(it))) < eps)
    {
        ans -= (*pre(it) ^ *it) + (*it ^ *nxt(it));
        ans += (*pre(it) ^ *nxt(it));
        it = pre(it);
        s.erase(nxt(it));
    }
    return;
}
signed main()
{
    for (int i = 1; i <= 3; ++i)
    {
        int x, y;
        scanf("%lld%lld", &x, &y);
        base.x += x;
        base.y += y;
        X[i] = x;
        Y[i] = y;
    }
    for (int i = 1; i <= 3; ++i)
        s.insert(node(3 * X[i], 3 * Y[i]));
    ans += (*s.begin() ^ *(nxt(s.begin())));
    ans += (*(nxt(s.begin())) ^ *(nxt(nxt(s.begin()))));
    ans += (*nxt(nxt(s.begin())) ^ *nxt(nxt(nxt(s.begin()))));
    scanf("%lld", &q);
    for (int i = 1; i <= q; ++i)
    {
        int x, y;
        scanf("%lld%lld", &x, &y);
        insert(node(3 * x, 3 * y));
        printf("%lld\n", ans / 9);
    }
    return 0;
}