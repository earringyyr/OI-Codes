#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, num[100005];
long long sum[100005];
struct node
{
    int v;
    int x;
} a[100005];
bool cmp(node aa, node bb)
{
    return aa.v < bb.v;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &a[i].v, &a[i].x);
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
    {
        num[i] = num[i - 1] + a[i].x;
        sum[i] = sum[i - 1] + (long long)a[i].v * a[i].x;
    }
    for (int i = 1; i <= m; ++i)
    {
        int ans = 0;
        long long w;
        scanf("%lld", &w);
        int top = n;
        while (top > 0 && a[1].v <= w)
        {
            int l, r;
            l = 1;
            r = top;
            while (l < r)
            {
                int mid = (l + r + 1) >> 1;
                if (w >= a[mid].v)
                    l = mid;
                else
                    r = mid - 1;
            }
            int pos = l;
            if (w >= sum[pos])
            {
                ans += num[pos];
                w -= sum[pos];
                break;
            }
            l = 1;
            r = pos;
            while (l < r)
            {
                int mid = (l + r) >> 1;
                if (w < sum[pos] - sum[mid])
                    l = mid + 1;
                else
                    r = mid;
            }
            w -= sum[pos] - sum[l];
            ans += num[pos] - num[l];
            ans += w / a[l].v;
            w %= a[l].v;
            top = l - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}