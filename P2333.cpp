#include <iostream>
#include <cstdio>
#include <cmath>
#define eps 1e-6
int n;
double S;
using namespace std;
struct node
{
    double x;
    double y;
    node(double xx = 0, double yy = 0)
    {
        x = xx;
        y = yy;
    }
} p[55];
double dis(node aa, node bb)
{
    return sqrt((aa.x - bb.x) * (aa.x - bb.x) + (aa.y - bb.y) * (aa.y - bb.y));
}
node vert(node aa, node bb)
{
    if (fabs(aa.x - bb.x) < eps)
        return node(aa.x, 0);
    if (fabs(aa.y - bb.y) < eps)
        return node(0, aa.y);
    double k = (aa.y - bb.y) / (aa.x - bb.x);
    double b = aa.y - k * aa.x;
    node res;
    res.x = -b / (k + 1 / k);
    res.y = -res.x / k;
    if (aa.x > bb.x)
        swap(aa, bb);
    if (res.x < aa.x || res.x > bb.x)
        if (dis(res, aa) < dis(res, bb))
            res = aa;
        else
            res = bb;
    if (aa.y > bb.y)
        swap(aa, bb);
    if (res.y < aa.y || res.y > bb.y)
        if (dis(res, aa) < dis(res, bb))
            res = aa;
        else
            res = bb;
    return res;
}
node intersect(node aa, node bb, double l)
{
    node res;
    if (fabs(aa.x - bb.x) < eps)
    {
        res.x = aa.x;
        res.y = sqrt(l * l - res.x * res.x);
        if (max(aa.y, bb.y) < res.y)
            res.y = -res.y;
        return res;
    }
    if (aa.x > bb.x)
        swap(aa, bb);
    double k = (aa.y - bb.y) / (aa.x - bb.x);
    double b = aa.y - k * aa.x;
    double delta = sqrt(4 * k * k * b * b - 4 * (k * k + 1) * (b * b - l * l));
    double x1 = (-2 * k * b + delta) / (2 * k * k + 2);
    double x2 = (-2 * k * b - delta) / (2 * k * k + 2);
    if (x1 >= aa.x && x1 <= bb.x)
        res.x = x1;
    else
        res.x = x2;
    res.y = res.x * k + b;
    return res;
}
double case1(node aa, node bb)
{
    return fabs(aa.x * bb.y - aa.y * bb.x) / 2;
}
double case2(node aa, node bb, double l)
{
    double la = dis(p[0], aa), lb = dis(p[0], bb), lc = dis(aa, bb);
    double theta = acos((la * la + lb * lb - lc * lc) / (2 * la * lb));
    return theta * l * l / 2;
}
double calc(node aa, node bb, double l)
{
    double la = dis(p[0], aa), lb = dis(p[0], bb);
    if (la > lb)
    {
        swap(aa, bb);
        swap(la, lb);
    }
    if (la <= l && lb <= l)
        return case1(aa, bb);
    node h = vert(aa, bb);
    if (dis(p[0], h) >= l)
        return case2(aa, bb, l);
    if (la >= l)
        return calc(aa, h, l) + calc(h, bb, l);
    node q = intersect(aa, bb, l);
    return case1(aa, q) + case2(q, bb, l);
}
double check(double l)
{
    double ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += calc(p[i], p[i + 1], l);
    return ans;
}
int main()
{
    scanf("%d%lf", &n, &S);
    double lef = 0, rig = 0;
    for (int i = 1; i <= n; ++i)
    {
        double x, y;
        scanf("%lf%lf", &x, &y);
        p[i] = node(x, y);
        rig = max(rig, dis(p[0], p[i]));
    }
    p[n + 1] = p[1];
    while (rig - lef > eps)
    {
        double mid = (lef + rig) / 2;
        if (check(mid) > S)
            rig = mid;
        else
            lef = mid;
    }
    printf("%.2f", lef);
    return 0;
}