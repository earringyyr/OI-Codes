#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const double pi = acos(-1), eps = 1e-8;
int n, id, top;
double area;
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
    double dis(point bb)
    {
        return sqrt((x - bb.x) * (x - bb.x) + (y - bb.y) * (y - bb.y));
    }
    point rotate(double r)
    {
        double xx = x, yy = y;
        xx = x * cos(r) - y * sin(r);
        yy = x * sin(r) + y * cos(r);
        return point(xx, yy);
    }
} minx, p[40005], st[40005];
bool cmp(point aa, point bb)
{
    if (abs((aa - p[1]) ^ (bb - p[1])) <= eps)
        return aa.dis(p[1]) < bb.dis(p[1]);
    return ((aa - p[1]) ^ (bb - p[1])) > 0;
}
int main()
{
    for (int i = 2; i <= n; ++i)
        if (minx.y - p[i].y > eps || (abs(p[i].y - minx.y) <= eps && minx.x - p[i].x > eps))
        {
            id = i;
            minx = p[i];
        }
    swap(p[1], p[id]);
    sort(p + 2, p + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
    {
        while (top >= 2 && ((p[i] - st[top - 1]) ^ (st[top] - st[top - 1])) > -eps)
            --top;
        st[++top] = p[i];
    }
    st[top + 1] = st[1];
    for (int i = 1; i <= top; ++i)
        area += st[i].dis(st[i + 1]);

    return 0;
}