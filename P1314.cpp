#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n, m, w[200005], v[200005], l[200005], r[200005];
long long s, sum[2][200005];
long long check(int k)
{
    for (int i = 1; i <= n; ++i)
    {
        sum[0][i] = sum[0][i - 1];
        sum[1][i] = sum[1][i - 1];
        if (w[i] >= k)
        {
            ++sum[0][i];
            sum[1][i] += v[i];
        }
    }
    long long num = 0;
    for (int i = 1; i <= m; ++i)
        num += (sum[0][r[i]] - sum[0][l[i] - 1]) * (sum[1][r[i]] - sum[1][l[i] - 1]);
    return num;
}
long long my_abs(long long k)
{
    if (k < 0)
        return -k;
    return k;
}
int main()
{
    scanf("%d%d%lld", &n, &m, &s);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &w[i], &v[i]);
    for (int i = 1; i <= m; ++i)
        scanf("%d%d", &l[i], &r[i]);
    int lef = 0, rig = 1000000;
    while (lef < rig)
    {
        int mid = (lef + rig + 1) >> 1;
        if (check(mid) <= s)
            rig = mid - 1;
        else
            lef = mid;
    }
    if (my_abs(check(lef + 1) - s) < my_abs(check(lef) - s))
        ++lef;
    printf("%lld", my_abs(check(lef) - s));
    return 0;
}