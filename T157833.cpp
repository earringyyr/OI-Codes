#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, k, hh, tt;
int a[1000005], p[1000005], q[1000005], sum[1000005];
bool check1()
{
    int num = 0;
    for (int i = 1; i < k; ++i)
    {
        num += k - 2;
        while (num < sum[p[i + 1]])
            num += k;
        if (num > sum[q[i]])
            return false;
    }
    return true;
}
bool check2()
{
    int num = 0;
    for (int i = 2; i <= k; ++i)
    {
        num = max(num, sum[p[i]]);
        num += k - 2;
        if (num > sum[q[i - 1]])
            return false;
    }
    return true;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        hh = 0;
        tt = 0;
        if (n < k * k)
        {
            puts("0");
            continue;
        }
        if (n % k != 0)
        {
            puts("0");
            continue;
        }
        if (a[1] != 0 || a[n] != 0)
        {
            puts("0");
            continue;
        }
        for (int i = 1; i <= n; ++i)
            if (!a[i])
                p[++hh] = i;
        for (int i = n; i >= 1; --i)
            if (!a[i])
                q[++tt] = i;
        if (hh < k || p[k] >= q[k])
        {
            puts("0");
            continue;
        }
        hh = k;
        tt = k;
        reverse(q + 1, q + k + 1);
        for (int i = p[k] + 1; i < q[1]; ++i)
            a[i] = 1;
        for (int i = 1; i <= n; ++i)
            sum[i] = sum[i - 1] + a[i];
        if (!check1() && !check2())
            puts("0");
        else
            puts("1");
    }
    return 0;
}