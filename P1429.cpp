#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define inf 0x7fffffff
using namespace std;
int n, st[200005], top;
struct node
{
    double x;
    double y;
} a[200005];
bool cmp(node aa, node bb)
{
    return aa.x < bb.x;
}
bool comp(int aa, int bb)
{
    return a[aa].y < a[bb].y;
}
double dis(int aa, int bb)
{
    return sqrt((a[aa].x - a[bb].x) * (a[aa].x - a[bb].x) + (a[aa].y - a[bb].y) * (a[aa].y - a[bb].y));
}
double merge(int l, int r)
{
    if (l == r)
        return inf;
    if (l + 1 == r)
        return dis(l, r);
    int mid = (l + r) >> 1;
    double ans1 = merge(l, mid - 1);
    double ans2 = merge(mid + 1, r);
    double ans = min(ans1, ans2);
    top = 0;
    for (int i = l; i <= r; ++i)
        if (fabs(a[i].x - a[mid].x) < ans)
            st[++top] = i;
    sort(st + 1, st + top + 1, comp);
    for (int i = 1; i <= top; ++i)
        for (int j = i + 1; j <= top && a[st[j]].y - a[st[i]].y < ans; ++j)
        {
            double tmp = dis(st[i], st[j]);
            if (tmp < ans)
                ans = tmp;
        }
    return ans;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lf%lf", &a[i].x, &a[i].y);
    sort(a + 1, a + n + 1, cmp);
    printf("%.4f", merge(1, n));
    return 0;
}