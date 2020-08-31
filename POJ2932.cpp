#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <set>
using namespace std;
const double eps = 1e-8;
int n, ans, q[40005];
struct node
{
    int id;
    double x;
    double y;
    double r;
    double pos;
    int type;
} a[80005];
struct point
{
    double x;
    double y;
    double r;
    point() {}
    point(node aa)
    {
        x = aa.x;
        y = aa.y;
        r = aa.r;
    }
    bool operator<(const point &bb) const
    {
        return y < bb.y;
    }
};
set<point> s;
bool cmp(node aa, node bb)
{
    if (fabs(aa.pos - bb.pos) < eps)
        return aa.type < bb.type;
    return aa.pos < bb.pos;
}
double dis(point aa, point bb)
{
    return sqrt((aa.x - bb.x) * (aa.x - bb.x) + (aa.y - bb.y) * (aa.y - bb.y)) + bb.r;
}
int main()
{
    while (scanf("%d", &n) == 1)
    {
        ans = 0;
        s.clear();
        for (int i = 1; i <= n; ++i)
        {
            a[i].id = i;
            scanf("%lf%lf%lf", &a[i].r, &a[i].x, &a[i].y);
            a[i + n] = a[i];
            a[i].pos = a[i].x - a[i].r;
            a[i + n].pos = a[i + n].x + a[i + n].r;
            a[i + n].type = 1;
        }
        sort(a + 1, a + 2 * n + 1, cmp);
        for (int i = 1; i <= 2 * n; ++i)
        {
            if (a[i].type == 1)
            {
                s.erase(point(a[i]));
                continue;
            }
            if (!s.empty())
            {
                set<point>::iterator it = s.lower_bound(point(a[i]));
                if (it != s.end() && dis(*it, point(a[i])) - it->r < eps)
                    continue;
                if (it != s.begin())
                {
                    --it;
                    if (dis(*it, point(a[i])) - it->r < eps)
                        continue;
                }
            }
            ++ans;
            s.insert(point(a[i]));
            q[ans] = a[i].id;
        }
        printf("%d\n", ans);
        sort(q + 1, q + ans + 1);
        for (int i = 1; i <= ans; ++i)
            printf("%d ", q[i]);
        putchar('\n');
    }
    return 0;
}