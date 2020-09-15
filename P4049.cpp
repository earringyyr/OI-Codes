#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
const double eps = 1e-8;
int n, m, ans, f[505][505];
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
} minx, a[505], p[505];
int main()
{
    memset(f, 0x3f, sizeof(f));
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= m; ++i)
    {
        double tmp;
        scanf("%lf%lf%lf", &p[i].x, &p[i].y, &tmp);
    }
    for (int i = 1; i <= n; ++i)
    {
        double tmp;
        scanf("%lf%lf%lf", &a[i].x, &a[i].y, &tmp);
    }
    for (int i = 1; i <= m; ++i)
    {
        int ppp = 1;
        for (int j = 1; j <= n; ++j)
            if (fabs(p[i].x - a[j].x) > eps && fabs(p[i].y - a[j].y) > eps)
            {
                ppp = 0;
                break;
            }
        if (ppp)
            f[i][i] = 1;
        for (int j = (i + 1) % m ? (i + 1) % m : m; j != i; j = (j + 1) % m ? (j + 1) % m : m)
        {
            int pp = 1;
            for (int k = 1; k <= n; ++k)
                if (((p[j] - p[i]) ^ (a[k] - p[i])) < -eps)
                {
                    pp = 0;
                    break;
                }
                else if (fabs((p[j] - p[i]) ^ (a[k] - p[i])) < eps)
                    if ((fabs((p[j] - p[i]).x) > eps && fabs((a[k] - p[i]).x) > eps && ((p[j] - p[i]).x > eps) != ((a[k] - p[i]).x > eps)) || fabs((p[j] - p[i]).x) - fabs((a[k] - p[i]).x) < -eps)
                        pp = 0;
            if (pp)
                f[i][j] = 1;
        }
    }
    for (int k = 1; k <= m; ++k)
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= m; ++j)
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    ans = 0x3f3f3f3f;
    for (int i = 1; i <= m; ++i)
        ans = min(ans, f[i][i]);
    if (ans == 0x3f3f3f3f)
        printf("-1");
    else
        printf("%d", ans);
    return 0;
}