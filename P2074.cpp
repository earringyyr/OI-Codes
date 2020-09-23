#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const double eps = 1e-3;
int n, num, cnt;
double pos, ans;
struct point
{
    double x;
    int type;
    point(double aa = 0, int bb = 0)
    {
        x = aa;
        type = bb;
    }
} p[20005];
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
    double operator*(const node &bb) const
    {
        return x * bb.x + y * bb.y;
    }
    double operator^(const node &bb) const
    {
        return x * bb.y - y * bb.x;
    }
} h1, h2;
struct line
{
    node a;
    node b;
    line() {}
    line(node aa, node bb)
    {
        a = aa;
        b = bb;
    }
} l;
bool cmp(point aa, point bb)
{
    return aa.x < bb.x;
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
    double x, xx, y;
    while (scanf("%lf%lf%lf", &x, &xx, &y))
    {
        if (!x && !xx && !y)
            break;
        num = 0;
        cnt = 0;
        ans = 0;
        h1 = node(x, y);
        h2 = node(xx, y);
        scanf("%lf%lf%lf", &x, &xx, &y);
        l = line(node(x, y), node(xx - x, 0));
        pos = x;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%lf%lf%lf", &x, &xx, &y);
            if (y >= h1.y || y < l.a.y)
                continue;
            node o1 = node(x, y), o2 = node(xx, y);
            node a = intersect(l, line(h2, h2 - o1));
            node b = intersect(l, line(h1, h1 - o2));
            if (a.x < l.a.x + l.b.x && b.x > l.a.x)
            {
                p[++num] = point(max(a.x, l.a.x), 1);
                p[++num] = point(min(b.x, l.b.x), -1);
            }
        }
        sort(p + 1, p + num + 1, cmp);
        for (int i = 1; i <= num; ++i)
        {
            if (!cnt)
                ans = max(ans, p[i].x - pos);
            cnt += p[i].type;
            if (!cnt)
                pos = p[i].x;
        }
        ans = max(ans, l.a.x + l.b.x - pos);
        if (ans < eps)
            puts("No View");
        else
            printf("%.2f\n", ans);
    }
    return 0;
}