#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const double eps = 1e-8;
int n, top, k[10005], v[10005], ans[10005];
struct node
{
    double x;
    double y;
    node(double xx = 0, double yy = 0)
    {
        x = xx;
        y = yy;
    }
    node operator+(const node &bb) const
    {
        return node(x + bb.x, y + bb.y);
    }
    node operator-(const node &bb) const
    {
        return node(x - bb.x, y - bb.y);
    }
    double operator^(const node &bb) const
    {
        return x * bb.y - y * bb.x;
    }
} vec[10005];
struct line
{
    int id;
    node a;
    node b;
    line() {}
    line(node aa, node bb)
    {
        a = aa;
        b = bb;
    }
    bool operator!=(const line &bb) const
    {
        if (fabs(a.x - bb.a.x) > eps)
            return true;
        if (fabs(a.y != bb.a.y) > eps)
            return true;
        if (fabs(b.x != bb.b.x) > eps)
            return true;
        if (fabs(b.y != bb.b.y) > eps)
            return true;
        return false;
    }
} l[10005], st[10005];
bool cmp(line aa, line bb)
{
    if (fabs(aa.b.y - bb.b.y) > eps)
        return aa.b.y < bb.b.y;
    else
        return aa.a.y < bb.a.y;
}
node intersect(line aa, line bb)
{
    node cc = aa.a - bb.a;
    double k = (bb.b ^ cc) / (aa.b ^ bb.b);
    cc = node(aa.b.x * k, aa.b.y * k);
    return aa.a + cc;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        l[i].id = i;
        scanf("%lf", &l[i].a.y);
        l[i].a.x = 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        l[i].b.x = 1;
        scanf("%lf", &l[i].b.y);
    }
    sort(l + 1, l + n + 1, cmp);
    st[++top] = line(node(0, 0), node(1, 0));
    for (int i = 1; i <= n; ++i)
    {
        while (top > 1 && (l[i].b ^ (vec[top - 1] - l[i].a)) < -eps)
            --top;
        st[++top] = l[i];
        vec[top - 1] = intersect(st[top - 1], st[top]);
    }
    int pos = 1, i = 2;
    while (i < top && vec[i].x < -eps)
        ++i;
    for (; i <= top; ++i)
    {
        while (pos < n && st[i] != l[pos])
            ++pos;
        ans[++ans[0]] = l[pos].id;
        ++pos;
    }
    sort(ans + 1, ans + ans[0] + 1);
    printf("%d\n", ans[0]);
    for (int i = 1; i <= ans[0]; ++i)
        printf("%d ", ans[i]);
    return 0;
}