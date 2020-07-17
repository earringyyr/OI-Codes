#include <iostream>
#include <cstdio>
#include <cmath>
#define int long long
using namespace std;
int sum, a[100], b[105], ans[105];
int exgcd(int aa, int bb, int &x, int &y)
{
    if (bb == 0)
    {
        x = 1;
        y = 0;
        return aa;
    }
    int gcd = exgcd(bb, aa % bb, x, y);
    int tmp = x;
    x = y;
    y = tmp - aa / bb * y;
    return gcd;
}
int query(int aa, int bb, int mod)
{
    int x, y;
    exgcd(aa, bb, x, y);
    x = (x % mod + mod) % mod;
    return x;
}
int ksm(int x, int y, int mod)
{
    int xx = 1;
    while (y)
    {
        if (y & 1)
            xx = xx * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return xx;
}
int f(int n, int p, int k)
{
    if (n == 0)
        return 1;
    int len = 1;
    for (int i = 1; i <= k; ++i)
        if (i % p)
            len = len * i % k;
    len = ksm(len, n / k, k);
    for (int i = n / k * k + 1; i <= n; ++i)
        if (i % p)
            len = len * (i % k) % k;
    return f(n / p, p, k) * len % k;
}
int g(int n, int p)
{
    if (n == 0)
        return 0;
    return g(n / p, p) + n / p;
}
int c(int n, int m, int p, int k)
{
    int f1 = f(n, p, k), f2 = f(m, p, k), f3 = f(n - m, p, k);
    f2 = query(f2, k, k);
    f3 = query(f3, k, k);
    int g1 = g(n, p), g2 = g(m, p), g3 = g(n - m, p);
    return f1 * f2 % k * f3 % k * ksm(p, g1 - g2 - g3, k) % k;
}
int crt(int n, int m, int mod)
{
    int x = 0;
    for (int i = 1; i <= sum; ++i)
    {
        int len = mod / b[i];
        int k = query(len, b[i], b[i]);
        x = (x + ans[i] * len % mod * k % mod) % mod;
    }
    return x;
}
int exlucas(int n, int m, int p)
{
    int mod = p;
    for (int i = 2; i <= sqrt(p); ++i)
        if (mod % i == 0)
        {
            a[++sum] = i;
            b[sum] = 1;
            while (mod % i == 0)
            {
                b[sum] *= i;
                mod /= i;
            }
        }
    if (mod > 1)
    {
        a[++sum] = mod;
        b[sum] = mod;
    }
    for (int i = 1; i <= sum; ++i)
        ans[i] = c(n, m, a[i], b[i]);
    return crt(n, m, p);
}
signed main()
{
    int n, m;
    int p;
    scanf("%lld%lld%lld", &n, &m, &p);
    printf("%lld", exlucas(n, m, p));
    return 0;
}