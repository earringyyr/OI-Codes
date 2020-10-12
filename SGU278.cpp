#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const double eps = 1e-8;
int n, id, top, A, B;
int a[75005], b[75005], c[75005];
double ans;
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
} minx, p[75005], st[75005];
struct line
{
    point a;
    point b;
    line() {}
    line(point aa, point bb)
    {
        a = aa;
        b = bb - aa;
    }
};
point intersect(line aa, line bb)
{
    point cc = aa.a - bb.a;
    double k = (bb.b ^ cc) / (aa.b ^ bb.b);
    cc = point(aa.b.x * k, aa.b.y * k);
    return aa.a + cc;
}
bool cmp(point aa, point bb)
{
    if (abs((aa - p[1]) ^ (bb - p[1])) <= eps)
        return aa.dis(p[1]) < bb.dis(p[1]);
    return ((aa - p[1]) ^ (bb - p[1])) > 0;
}
int main()
{
    scanf("%d%d%d", &n, &A, &B);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d%d", &a[i], &b[i], &c[i]);
        p[i].x = (double)a[i] / c[i];
        p[i].y = (double)b[i] / c[i];
    }
    id = 1;
    minx = p[1];
    for (int i = 2; i <= n; ++i)
        if (minx.y - p[i].y > eps || (fabs(p[i].y - minx.y) <= eps && minx.x - p[i].x > eps))
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
    for (int i = 1; i <= top; ++i)
        ans = max(ans, min(A / st[i].x, B / st[i].y));
    st[top + 1] = st[1];
    for (int i = 1; i <= top; ++i)
    {
        point vec = intersect(line(st[i], st[i + 1]), line(point(0, 0), point(A, B)));
        if (vec.x - min(st[i].x, st[i + 1].x) > -eps && vec.x - max(st[i].x, st[i + 1].x) < eps)
            if (vec.y - min(st[i].y, st[i + 1].y) > -eps && vec.y - max(st[i].y, st[i + 1].y) < eps)
                ans = max(ans, A / vec.x);
    }
    printf("%.6f", ans);
    return 0;
}