#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
#define dlt 0.00000001
int ax, ay, bx, by;
int cx, cy, dx, dy;
int p, q, r;
double test(double x, double y, double xx, double yy)
{
    return sqrt((ax - x) * (ax - x) + (ay - y) * (ay - y)) / p + sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy)) / r + sqrt((dx - xx) * (dx - xx) + (dy - yy) * (dy - yy)) / q;
}
double doit(double x, double y)
{
    double l = cx, r = dx, ll = cy, rr = dy;
    while (abs(r - l) > dlt || abs(rr - ll) > dlt)
    {
        double m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
        double mm1 = ll + (rr - ll) / 3, mm2 = rr - (rr - ll) / 3;
        if (test(x, y, m1, mm1) < test(x, y, m2, mm2))
        {
            r = m2;
            rr = mm2;
        }
        else
        {
            l = m1;
            ll = mm1;
        }
    }
    return test(x, y, l, ll);
}
int main()
{
    scanf("%d%d%d%d%d%d%d%d%d%d%d", &ax, &ay, &bx, &by, &cx, &cy, &dx, &dy, &p, &q, &r);
    double l = ax, r = bx, ll = ay, rr = by;
    while (abs(r - l) > dlt || abs(rr - ll) > dlt)
    {
        double m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
        double mm1 = ll + (rr - ll) / 3, mm2 = rr - (rr - ll) / 3;
        if (doit(m1, mm1) < doit(m2, mm2))
        {
            r = m2;
            rr = mm2;
        }
        else
        {
            l = m1;
            ll = mm1;
        }
    }
    printf("%.2f", doit(l, ll));
    return 0;
}