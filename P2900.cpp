#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define int long long
using namespace std;
const double eps = 1e-8;
int n, top, pos, st[50005];
struct node
{
    int w;
    int l;
} a[50005], b[50005];
struct point
{
    double x;
    double y;
    point(double aa = 0, double bb = 0)
    {
        x = aa;
        y = bb;
    }
    point operator+(const point &bb) const
    {
        return point(x + bb.x, y + bb.y);
    }
    point operator-(const point &bb) const
    {
        return point(x - bb.x, y - bb.y);
    }
    double operator*(const point &bb) const
    {
        return x * bb.x + y * bb.y;
    }
    double operator^(const point &bb) const
    {
        return x * bb.y - y * bb.x;
    }
} vec[50005];
struct line
{
    int k;
    int b;
    line(int aa = 0, int bb = 0)
    {
        k = aa;
        b = bb;
    }
} l[50005];
bool cmp(node aa, node bb)
{
    if (aa.w == bb.w)
        return aa.l < bb.l;
    return aa.w < bb.w;
}
point intersect(line aa, line bb)
{
    point cc = point(0, aa.b) - point(0, bb.b);
    double k = (point(1, bb.k) ^ cc) / (point(1, aa.k) ^ point(1, bb.k));
    cc = point(k, aa.k * k);
    return point(0, aa.b) + cc;
}
signed main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld%lld", &a[i].w, &a[i].l);
    sort(a + 1, a + n + 1, cmp);
    memcpy(b, a, sizeof(a));
    for (int i = 1; i <= n; ++i)
    {
        while (top && a[st[top]].l <= a[i].l)
            --top;
        st[++top] = i;
    }
    n = top;
    for (int i = 1; i <= n; ++i)
        a[i] = b[st[i]];
    top = 0;
    l[++top] = line(a[1].l, 0);
    for (int i = 1; i <= n; ++i)
    {
        while (pos < top - 1 && vec[pos + 1].x <= a[i].w)
            ++pos;
        int f = l[pos + 1].k * a[i].w + l[pos + 1].b;
        while (top > 1 && ((vec[top - 1] - point(0, f)) ^ point(1, a[i + 1].l)) < eps)
        {
            --top;
            if (pos > top)
                --pos;
        }
        l[++top] = line(a[i + 1].l, f);
        if (top > 1)
            vec[top - 1] = intersect(l[top - 1], l[top]);
    }
    printf("%lld", l[top].b);
    return 0;
}