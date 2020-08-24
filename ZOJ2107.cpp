#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x7fffffff;
int n, top, st[100005];
struct node
{
    double x;
    double y;
} a[100005];
bool cmp1(node aa, node bb)
{
    return aa.x < bb.x;
}
bool cmp2(int aa, int bb)
{
    return a[aa].y < a[bb].y;
}
double dis(int i, int j)
{
    return sqrt((a[i].x - a[j].x) * (a[i].x - a[j].x) + (a[i].y - a[j].y) * (a[i].y - a[j].y));
}
double solve(int l, int r)
{
    if (l == r)
        return inf;
    if (l + 1 == r)
        return dis(l, r);
    int mid = (l + r) >> 1;
    double ans1 = solve(l, mid - 1);
    double ans2 = solve(mid + 1, r);
    double ans = min(ans1, ans2);
    top = 0;
    for (int i = l; i <= r; ++i)
        if (fabs(a[i].x - a[mid].x) < ans)
            st[++top] = i;
    sort(st + 1, st + top + 1, cmp2);
    for (int i = 1; i <= top; ++i)
        for (int j = i + 1; j <= top && a[st[j]].y - a[st[i]].y < ans; ++j)
            ans = min(ans, dis(st[i], st[j]));
    return ans;
}
int main()
{
    while (scanf("%d", &n))
    {
        if (n == 0)
            break;
        for (int i = 1; i <= n; ++i)
            scanf("%lf%lf", &a[i].x, &a[i].y);
        sort(a + 1, a + n + 1, cmp1);
        printf("%.2f\n", solve(1, n) / 2);
    }
    return 0;
}