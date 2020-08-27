#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const double eps = 1e-8;
int n;
struct node
{
    double x;
    double y;
    node(double aa = 0, double bb = 0)
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
    double operator*(const node &bb) const
    {
        return x * bb.x + y * bb.y;
    }
    double operator^(const node &bb) const
    {
        return x * bb.y - y * bb.x;
    }
} a[105], b[105];
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
} l[105];
bool intersect(line aa, line bb)
{
    if (fabs(aa.b ^ bb.b) < eps)
    {
        if (fabs(aa.b ^ (bb.a - aa.a)) < eps)
            return true;
        return false;
    }
    node cc = aa.a - bb.a;
    double k = (bb.b ^ cc) / (aa.b ^ bb.b);
    if (k > -eps && k - 1 < eps)
        return true;
    return false;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%lf%lf%lf%lf", &a[i].x, &a[i].y, &b[i].x, &b[i].y);
            l[i] = line(a[i], b[i]);
        }
        if (n == 1)
        {
            puts("Yes!");
            continue;
        }
        int p0 = 0;
        for (int i = 1; i <= n && !p0; ++i)
            for (int j = i + 1; j <= n && !p0; ++j)
            {
                int p1 = 1, p2 = 1, p3 = 1, p4 = 1;
                if (abs(a[i].x - a[j].x) < eps && abs(a[i].y - a[j].y) < eps)
                    p1 = 0;
                if (abs(a[i].x - b[j].x) < eps && abs(a[i].y - b[j].y) < eps)
                    p2 = 0;
                if (abs(b[i].x - a[j].x) < eps && abs(b[i].y - a[j].y) < eps)
                    p3 = 0;
                if (abs(b[i].x - b[j].x) < eps && abs(b[i].y - b[j].y) < eps)
                    p4 = 0;
                for (int k = 1; k <= n; ++k)
                {
                    if (p1 && !intersect(l[k], line(a[i], a[j])))
                        p1 = 0;
                    if (p2 && !intersect(l[k], line(a[i], b[j])))
                        p2 = 0;
                    if (p3 && !intersect(l[k], line(b[i], a[j])))
                        p3 = 0;
                    if (p4 && !intersect(l[k], line(b[i], b[j])))
                        p4 = 0;
                }
                if (p1 || p2 || p3 || p4)
                    p0 = 1;
            }
        if (p0)
            puts("Yes!");
        else
            puts("No!");
    }
    return 0;
}