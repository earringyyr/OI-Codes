#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;
const double eps = 1e-8, pi = acos(-1.0);
int n, a, q;
double r;
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
    node operator/(const int &bb) const
    {
        return node(x / bb, y / bb);
    }
    double operator*(const node &bb) const
    {
        return x * bb.x + y * bb.y;
    }
    double operator^(const node &bb) const
    {
        return x * bb.y - y * bb.x;
    }
    double dis(const node bb)
    {
        return sqrt((x - bb.x) * (x - bb.x) + (y - bb.y) * (y - bb.y));
    }
} o, p[50005];
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
    line rotate(node aa)
    {
        a = aa;
        swap(b.x, b.y);
        b.x *= -1;
        return line(a, a + b);
    }
};
node intersect(line aa, line bb)
{
    node cc = aa.a - bb.a;
    double k = (bb.b ^ cc) / (aa.b ^ bb.b);
    cc = node(aa.b.x * k, aa.b.y * k);
    return aa.a + cc;
}
int main()
{
    srand(time(0));
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lf%lf", &p[i].x, &p[i].y);
    scanf("%d%d", &a, &q);
    for (int i = 1; i <= n; ++i)
    {
        node pp = p[i];
        p[i].x = pp.x * cos(pi * a / 180) + pp.y * sin(pi * a / 180);
        p[i].y = pp.y * cos(pi * a / 180) - pp.x * sin(pi * a / 180);
        p[i].x /= q;
    }
    random_shuffle(p + 1, p + n + 1);
    for (int i = 1; i <= n; ++i)
        if (r - p[i].dis(o) < eps)
        {
            o = p[i];
            r = 0;
            for (int j = 1; j < i; ++j)
                if (r - p[j].dis(o) < eps)
                {
                    o = (p[i] + p[j]) / 2;
                    r = p[i].dis(p[j]) / 2;
                    for (int k = 1; k < j; ++k)
                        if (r - p[k].dis(o) < eps)
                        {
                            o = intersect(line(p[i], p[j]).rotate((p[i] + p[j]) / 2), line(p[j], p[k]).rotate((p[j] + p[k]) / 2));
                            r = p[k].dis(o);
                        }
                }
        }
    printf("%.3f", r);
    return 0;
}