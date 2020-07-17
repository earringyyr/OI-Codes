#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
long long n, k, num, cnt;
double p, tot, ans[3];
int main()
{
    scanf("%lld%lf", &n, &p);
    k = n - 1;
    while (k)
    {
        k >>= 1;
        ++num;
    }
    for (int i = 0; i < num; ++i)
    {
        double c = (double)(((n >> (i + 1)) << i) + max(n % (1LL << (i + 1)) - (1LL << i), 0LL)) / n;
        ans[1] += 2 * (1 - c) * c * (1LL << i);
    }
    if (n > 1)
    {
        --n;
        k = 1;
        while (k <= n)
            k <<= 1;
        num = k - 1;
        k >>= 1;
        cnt = k;
        tot = (double)num * (n - k + 1) + (double)k * k;
        num >>= 1;
        while (k != 1)
        {
            k >>= 1;
            num >>= 1;
            if (n & k)
            {
                tot += (double)cnt * k + (double)(cnt >> 1) * num;
                cnt >>= 1;
            }
            else
                tot += (double)(cnt >> 1) * k;
        }
        ans[2] = tot / (n + 1);
    }
    printf("%.6f", (1 - p) * ans[1] + p * ans[2]);
    return 0;
}