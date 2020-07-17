#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n;
long long sum[2];
long double ans = 10000000000.0;
struct node
{
    int a;
    int b;
    long double x;
} a[300005];
bool cmp(node aa, node bb)
{
    return aa.x < bb.x;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &a[i].a, &a[i].b);
        if (a[i].a != 0)
            a[i].x = a[i].b * -1.0 / a[i].a;
        if (a[i].a != 0)
        {
            if (a[i].a > 0)
            {
                sum[0] -= a[i].a;
                sum[1] -= a[i].b;
            }
            else
            {
                sum[0] += a[i].a;
                sum[1] += a[i].b;
            }
        }
        else
        {
            if (a[i].b > 0)
                sum[1] += a[i].b;
            else
                sum[1] -= a[i].b;
        }
    }
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
        if (a[i].a != 0)
        {
            ans = min(ans, a[i].x * sum[0] + sum[1]);
            if (a[i].a != 0)
                if (a[i].a > 0)
                {
                    sum[0] += a[i].a * 2;
                    sum[1] += a[i].b * 2;
                }
                else
                {
                    sum[0] -= a[i].a * 2;
                    sum[1] -= a[i].b * 2;
                }
        }
        else
            ans = min(ans, a[i - 1].x * sum[0] + sum[1]);
    printf("%.6Lf", ans);
    return 0;
}