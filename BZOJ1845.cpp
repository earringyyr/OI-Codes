#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define eps 1e-12
using namespace std;
int n, sum;
long double ans;
struct node
{
    long double x;
    long double y;
    node(long double xx = 0, long double yy = 0)
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
    long double operator*(const node &bb) const
    {
        return x * bb.x + y * bb.y;
    }
    long double operator^(const node &bb) const
    {
        return x * bb.y - y * bb.x;
    }
} p[100005], w;
struct line
{
    node a;
    node b;
    line()
    {
    }
    line(node aa, node bb)
    {
        a = aa;
        b = bb - aa;
    }
} l[105][4];
bool cmp(node aa, node bb)
{
    if (fabs(aa.x - bb.x) < eps)
        return aa.y < bb.y;
    else
        return aa.x < bb.x;
}
bool cross(line aa, line bb)
{
    bool p1 = ((bb.a - aa.a) ^ aa.b) * ((bb.a + bb.b - aa.a) ^ aa.b) < -eps;
    bool p2 = ((aa.a - bb.a) ^ bb.b) * ((aa.a + aa.b - bb.a) ^ bb.b) < -eps;
    return p1 && p2;
}
node intersect(line aa, line bb)
{
    node cc = aa.a - bb.a;
    long double k = (bb.b ^ cc) / (aa.b ^ bb.b);
    return aa.a + node(aa.b.x * k, aa.b.y * k);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        long double x1, y1, x2, y2, x3, y3;
        node pp[4];
        scanf("%Lf%Lf%Lf%Lf%Lf%Lf", &x1, &y1, &x2, &y2, &x3, &y3);
        p[++sum] = node(x1, y1);
        pp[1] = p[sum];
        p[++sum] = node(x2, y2);
        pp[2] = p[sum];
        p[++sum] = node(x3, y3);
        pp[3] = p[sum];
        sort(pp + 1, pp + 4, cmp);
        l[i][1] = line(pp[1], pp[3]);
        l[i][2] = line(pp[1], pp[2]);
        l[i][3] = line(pp[2], pp[3]);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            for (int x = 1; x <= 3; ++x)
                for (int y = 1; y <= 3; ++y)
                    if (cross(l[i][x], l[j][y]))
                        p[++sum] = intersect(l[i][x], l[j][y]);
    sort(p + 1, p + sum + 1, cmp);
    line w = line(node(0, -1e7), node(0, 1e7));
    for (int i = 2; i <= sum; ++i)
    {
        node pp[105];
        int num = 0;
        w.a.x = (p[i - 1].x + p[i].x) / 2;
        for (int j = 1; j <= n; ++j)
            if (cross(l[j][1], w))
            {
                long double aa = intersect(l[j][1], w).y, bb;
                if (cross(l[j][2], w))
                    bb = intersect(l[j][2], w).y;
                else
                    bb = intersect(l[j][3], w).y;
                if (aa > bb)
                    swap(aa, bb);
                pp[++num] = node(aa, bb);
            }
        sort(pp + 1, pp + num + 1, cmp);
        long double sum = 0, lst = -1e7;
        for (int j = 1; j <= num; ++j)
            if (pp[j].x > lst)
            {
                sum += pp[j].y - pp[j].x;
                lst = pp[j].y;
            }
            else if (pp[j].y > lst)
            {
                sum += pp[j].y - lst;
                lst = pp[j].y;
            }
        ans += sum * (p[i].x - p[i - 1].x);
    }
    printf("%.2Lf", ans - 0.0005);
    return 0;
}