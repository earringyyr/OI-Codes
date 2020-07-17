#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
long long n, k;
int num;
double pp, ans[2], an;
int main()
{
    scanf("%lld%lf", &n, &pp);
    k = n - 1;
    while (k)
    {
        k >>= 1;
        ++num;
    }
    for (int i = num; i >= 1; --i)
    {
        double p = (double)(n - ((n >> i) * (1LL << (i - 1)) + min(n - (n >> i) * (1LL << i), 1LL << (i - 1)))) / (double)n;
        ans[0] += 2.0 * (1.0 - p) * p * (1LL << (i - 1));
    }
    if (n != 1)
    {
        long long sum, cnt;
        double tot = 0.0;
        --n;
        k = 1;
        while (k <= n)
            k <<= 1;
        sum = k - 1;
        k >>= 1;
        tot += (double)sum * (n - k + 1);
        tot += (double)k * k;
        cnt = k;
        sum >>= 1;
        while (k != 1)
        {
            k >>= 1;
            sum >>= 1;
            if (n & k)
            {
                tot += (double)cnt * k;
                tot += (double)(cnt >> 1) * sum;
                cnt >>= 1;
            }
            else
                tot += (double)(cnt >> 1) * k;
        }
        ans[1] = tot / (double)(n + 1);
    }
    an = (1.0 - pp) * ans[0] + pp * ans[1];
    num = 0;
    while (an >= 10.0)
    {
        an /= 10.0;
        ++num;
    }
    while (an > 0.0 && an < 1.0)
    {
        an *= 10.0;
        --num;
    }
    printf("%.5f %d", an, num);
    return 0;
}