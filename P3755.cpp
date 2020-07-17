#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, sum;
long long ans[100005];
struct node
{
    int x;
    int y;
    int p;
    int type;
    int id;
    int k;
    long long ans;
} a[500005], b[500005];
bool cmp(node aa, node bb)
{
    if (aa.x != bb.x)
        return aa.x < bb.x;
    if (aa.y != bb.y)
        return aa.y < bb.y;
    return aa.type < bb.type;
}
void solve(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    solve(l, mid);
    solve(mid + 1, r);
    int i = l, j = mid + 1, cnt = l - 1;
    long long num = 0;
    while (j <= r)
    {
        while (a[i].y <= a[j].y && i <= mid)
        {
            if (a[i].type == 1)
                num += a[i].p;
            b[++cnt] = a[i];
            ++i;
        }
        if (a[j].type == 2)
            a[j].ans += num;
        b[++cnt] = a[j];
        ++j;
    }
    while (i <= mid)
    {
        b[++cnt] = a[i];
        ++i;
    }
    for (int i = l; i <= r; ++i)
        a[i] = b[i];
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        ++sum;
        scanf("%d%d%d", &a[sum].x, &a[sum].y, &a[sum].p);
        a[sum].type = 1;
    }
    for (int i = 1; i <= m; ++i)
    {
        int x, y, xx, yy;
        scanf("%d%d%d%d", &x, &y, &xx, &yy);
        ++sum;
        a[sum].x = xx;
        a[sum].y = yy;
        a[sum].type = 2;
        a[sum].id = i;
        a[sum].k = 1;
        ++sum;
        a[sum].x = x - 1;
        a[sum].y = y - 1;
        a[sum].type = 2;
        a[sum].id = i;
        a[sum].k = 1;
        ++sum;
        a[sum].x = x - 1;
        a[sum].y = yy;
        a[sum].type = 2;
        a[sum].id = i;
        a[sum].k = -1;
        ++sum;
        a[sum].x = xx;
        a[sum].y = y - 1;
        a[sum].type = 2;
        a[sum].id = i;
        a[sum].k = -1;
    }
    sort(a + 1, a + sum + 1, cmp);
    solve(1, sum);
    for (int i = 1; i <= sum; ++i)
        if (a[i].type == 2)
            ans[a[i].id] += a[i].k * a[i].ans;
    for (int i = 1; i <= m; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}