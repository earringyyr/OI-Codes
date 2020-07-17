#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define eps 1e-6
using namespace std;
int n, top, st[2005];
double ans;
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
    double dis(const node &bb) const
    {
        return sqrt((x - bb.x) * (x - bb.x) + (y - bb.y) * (y - bb.y));
    }
} p[2005];
bool cmp1(node aa, node bb)
{
    if (fabs(aa.y - bb.y) < eps)
        return aa.x < bb.x;
    return aa.y < bb.y;
}
bool cmp2(node aa, node bb)
{
    if (fabs((aa - p[1]) ^ (bb - p[1])) < eps)
        return aa.dis(p[1]) < bb.dis(p[1]);
    return ((aa - p[1]) ^ (bb - p[1])) < 0;
}
bool check(node aa, node bb, node cc, node dd)
{
    double sa, sb;
    sa = fabs((bb - aa) ^ (cc - aa));
    sb = fabs((bb - aa) ^ (dd - aa));
    return sa < sb;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lf%lf", &p[i].x, &p[i].y);
    sort(p + 1, p + n + 1, cmp1);
    sort(p + 2, p + n + 1, cmp2);
    for (int i = 1; i <= n; ++i)
    {
        while (top > 1 && ((p[st[top]] - p[i]) ^ (p[st[top - 1]] - p[i])) <= 0)
            --top;
        st[++top] = i;
    }
    if (top <= 2)
    {
        printf("0.000");
        return 0;
    }
    if (top == 3)
    {
        ans = -1;
        for (int i = 1; i <= n; ++i)
        {
            bool pl = false;
            for (int j = 1; j <= top; ++j)
                if (st[j] == i)
                {
                    pl = true;
                    break;
                }
            if (pl)
                continue;
            if (ans == -1)
                ans = fabs((p[st[0]] - p[i]) ^ (p[st[1]] - p[i])) / 2;
            ans = min(ans, fabs((p[st[0]] - p[i]) ^ (p[st[1]] - p[i])) / 2);
            ans = min(ans, fabs((p[st[1]] - p[i]) ^ (p[st[2]] - p[i])) / 2);
            ans = min(ans, fabs((p[st[2]] - p[i]) ^ (p[st[0]] - p[i])) / 2);
        }
        ans = fabs((st[1] - st[0]) ^ (st[2] - st[0])) / 2 - ans;
        printf("%.3f", ans);
        return 0;
    }
    for (int i = 1; i <= top; ++i)
    {
        st[top + 1] = st[1];
        int lef = i, rig = (i + 1) % top;
        if (rig == 0)
            rig = top;
        for (int j = (i + 1) % top; j != i; ++j, j %= top)
        {
            if (j == 0)
                j = top;
            if (j == i)
                break;
            while (lef != j && check(p[st[i]], p[st[j]], p[st[lef]], p[st[lef + 1]]))
            {
                lef = (lef + 1) % top;
                if (lef == 0)
                    lef = top;
            }
            while (rig != i && check(p[st[i]], p[st[j]], p[st[rig]], p[st[rig + 1]]))
            {
                rig = (rig + 1) % top;
                if (rig == 0)
                    rig = top;
            }
            ans = max(ans, (fabs((p[st[lef]] - p[st[i]]) ^ (p[st[j]] - p[st[i]])) + fabs((p[st[rig]] - p[st[i]]) ^ (p[st[j]] - p[st[i]]))) / 2);
        }
    }
    printf("%.3f", ans);
    return 0;
}