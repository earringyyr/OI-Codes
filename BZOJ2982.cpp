#include <iostream>
#include <cstdio>
#define int long long
#define mod 10007
using namespace std;
int t, n, m, num[10010];
int ksm(int a, int c)
{
    int b = 1;
    while (c)
    {
        if (c % 2 == 1)
            b = a * b % mod;
        a = a * a % mod;
        c >>= 1;
    }
    return b;
}
int c(int a, int b)
{
    if (a < b)
        return 0;
    return num[a] * ksm(num[b], mod - 2) % mod * ksm(num[a - b], mod - 2) % mod;
}
int lucas(int a, int b)
{
    if (b == 0)
        return 1;
    return lucas(a / mod, b / mod) * c(a % mod, b % mod) % mod;
}
signed main()
{
    scanf("%lld", &t);
    num[0] = 1;
    for (int i = 1; i <= mod; ++i)
        num[i] = num[i - 1] * i % mod;
    while (t--)
    {
        scanf("%lld%lld", &n, &m);
        printf("%lld\n", lucas(n, m));
    }
    return 0;
}