#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const double eps = 1e-8, pi = acos(-1);
int T, num;
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
    node operator*(const double &bb) const
    {
        return node(x * bb, y * bb);
    }
    double operator*(const node &bb) const
    {
        return x * bb.x + y * bb.y;
    }
    double operator^(const node &bb) const
    {
        return x * bb.y - y * bb.x;
    }
    node rotate(const double &deg) const
    {
        node bb;
        bb.x = x * cos(deg) - y * sin(deg);
        bb.y = x * sin(deg) + y * cos(deg);
        return bb;
    }
} o;
struct line
{
    node a;
    node b;
    line() {}
    line(node aa, node bb)
    {
        a = aa;
        b = bb - aa;
    }
};
struct circle
{
    node o;
    double r;
} A, B, a, b, ans[5];
double dist(node aa, node bb)
{
    return sqrt((aa.x - bb.x) * (aa.x - bb.x) + (aa.y - bb.y) * (aa.y - bb.y));
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
    scanf("%d", &T);
    while (T--)
    {
        num = 0;
        scanf("%lf%lf%lf", &A.o.x, &A.o.y, &A.r);
        scanf("%lf%lf%lf", &B.o.x, &B.o.y, &B.r);
        scanf("%lf%lf", &o.x, &o.y);
        double oA = dist(o, A.o), oB = dist(o, B.o);
        a.r = (1 / (oA - A.r) - 1 / (oA + A.r)) * 50;
        b.r = (1 / (oB - B.r) - 1 / (oB + B.r)) * 50;
        double oa = 100 / (oA - A.r) - a.r;
        double ob = 100 / (oB - B.r) - b.r;
        a.o = o + (A.o - o) * (oa / oA);
        b.o = o + (B.o - o) * (ob / oB);
        if (a.r > b.r)
            swap(a, b);
        double dis = dist(a.o, b.o), deg;
        node p0, p1, p2;
        if (fabs(a.r - b.r) < eps)
            deg = pi / 2;
        else
            deg = atan2(sqrt(dis * dis - (b.r - a.r) * (b.r - a.r)), b.r - a.r);
        p0 = (a.o - b.o).rotate(deg);
        p1 = a.o + p0 * (a.r / dis);
        p2 = b.o + p0 * (b.r / dis);
        p0 = intersect(line(p1, p2), line(o, o + (p1 - p2).rotate(pi / 2)));
        ++num;
        ans[num].r = 100 / dist(o, p0);
        ans[num].r /= 2;
        ans[num].o = o + (p0 - o) * (ans[num].r / dist(o, p0));
        if (dist(ans[num].o, A.o) < ans[num].r || dist(ans[num].o, B.o) < ans[num].r)
            --num;
        p0 = (a.o - b.o).rotate(2 * pi - deg);
        p1 = a.o + p0 * (a.r / dis);
        p2 = b.o + p0 * (b.r / dis);
        p0 = intersect(line(p1, p2), line(o, o + (p1 - p2).rotate(pi / 2)));
        ++num;
        ans[num].r = 100 / dist(o, p0);
        ans[num].r /= 2;
        ans[num].o = o + (p0 - o) * (ans[num].r / dist(o, p0));
        if (dist(ans[num].o, A.o) < ans[num].r || dist(ans[num].o, B.o) < ans[num].r)
            --num;
        printf("%d\n", num);
        for (int i = 1; i <= num; ++i)
            printf("%.8f %.8f %.8f\n", ans[i].o.x, ans[i].o.y, ans[i].r);
    }
    return 0;
}