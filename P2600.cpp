#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
int n, sum, tail;
double ans;
const double eps = 1e-8;
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
} p[305], vec[305];
struct line
{
    node a;
    node b;
    double k;
    line()
    {
    }
    line(node aa, node bb)
    {
        a = aa;
        b = bb - aa;
        k = atan2(b.y, b.x);
    }
} s[305], st[305];
bool cmp(line aa, line bb)
{
    return aa.k < bb.k;
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
        scanf("%lf", &p[i].x);
    for (int i = 1; i <= n; ++i)
        scanf("%lf", &p[i].y);
    for (int i = 1; i < n; ++i)
        s[++sum] = line(p[i], p[i + 1]);
    s[++sum] = line(node(p[1].x, 0), node(p[1].x, -1));
    s[++sum] = line(node(p[n].x, 0), node(p[n].x, 1));
    sort(s + 1, s + sum + 1, cmp);
    st[++tail] = s[1];
    for (int i = 2; i <= sum; ++i)
    {
        while (tail > 1 && (s[i].b ^ (vec[tail - 1] - s[i].a)) < eps)
            --tail;
        st[++tail] = s[i];
        if (fabs(st[tail].b ^ st[tail - 1].b) < eps)
        {
            --tail;
            if (((s[i].a - st[tail].a) ^ st[tail].b) < eps)
                st[tail] = s[i];
        }
        if (tail > 1)
            vec[tail - 1] = intersect(st[tail - 1], st[tail]);
    }
    int j = 1;
    ans = min(vec[1].y - p[1].y, vec[tail - 1].y - p[n].y);
    for (int i = 2; i < n; ++i)
    {
        while (j < n && vec[j].x < p[i].x)
            ++j;
        ans = min(ans, vec[j - 1].y + (vec[j].y - vec[j - 1].y) * (p[i].x - vec[j - 1].x) / (vec[j].x - vec[j - 1].x) - p[i].y);
        if (vec[j].x <= p[i + 1].x)
            ans = min(ans, vec[j].y - p[i].y - (p[i + 1].y - p[i].y) * (vec[j].x - p[i].x) / (p[i + 1].x - p[i].x));
    }
    printf("%.3f", ans);
    return 0;
}