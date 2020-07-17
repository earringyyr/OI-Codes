#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
int n, M = 1, x, y, ans, a[1005], b[1005];
int ksm(int a, int k, int mod)
{
    int b = 1;
    while (k)
    {
        if (k & 1)
            b = a * b % mod;
        a = a * a % mod;
        k >>= 1;
    }
    return b;
}
void exgcd(int a, int b)
{
    if (!b)
    {
        x = 1;
        y = 0;
        return;
    }
    exgcd(b, a % b);
    int tmp = x;
    x = y;
    y = tmp - a / b * y;
    return;
}
signed main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld%lld", &a[i], &b[i]);
        M *= a[i];
    }
    for (int i = 1; i <= n; ++i)
    {
        int m = M / a[i];
        exgcd(m, a[i]);
        x = (x % a[i] + a[i]) % a[i];
        ans += b[i] * m * x;
    }
    ans = (ans % M + M) % M;
    printf("%lld", ans);
    return 0;
}