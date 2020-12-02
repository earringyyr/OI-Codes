#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
int n, m, k, p;
int x[100005];
signed main()
{
    scanf("%lld%lld%lld%lld", &n, &m, &k, &p);
    for (int i = 1; i <= p; ++i)
        x[i] = k / p;
    k = k % p;
    if (k && p == n)
    {
        printf("NO");
        return 0;
    }
    if (p < n)
    {
        for (int i = p + 1; i <= n; ++i)
            x[i] = k / (n - p);
        k = k % (n - p);
        for (int i = p + 1; i <= p + k; ++i)
            ++x[i];
        if (x[p + 1] >= x[p])
        {
            printf("NO");
            return 0;
        }
    }
    if (x[p] > m)
    {
        int num = 0;
        for (int i = 1; i <= p; ++i)
        {
            num += x[i] - m;
            x[i] = m;
        }
        for (int i = p + 1; i <= n; ++i)
        {
            if (num > m - x[i] - 1)
            {
                num -= m - x[i] - 1;
                x[i] = m - 1;
            }
            else
            {
                x[i] += num;
                num = 0;
            }
        }
        if (num > 0)
            printf("NO");
        else
        {
            printf("YES\n");
            for (int i = 1; i <= n; ++i)
                printf("%lld %lld\n", x[i], m - x[i]);
        }
        return 0;
    }
    printf("YES\n");
    for (int i = 1; i <= n; ++i)
        printf("%lld %lld\n", x[i], m - x[i]);
    return 0;
}