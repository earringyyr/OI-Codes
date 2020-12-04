#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int mod;
int fac[100005], inv[100005];
int ksm(int aa, int k)
{
    int bb = 1;
    while (k)
    {
        if (k & 1)
            bb = (ll)bb * aa % mod;
        aa = (ll)aa * aa % mod;
        k >>= 1;
    }
    return bb;
}
int C(int n, int m)
{
    if (m > n)
        return 0;
    return (ll)fac[n] * inv[m] % mod * inv[n - m] % mod;
}
int Lucas(int n, int m)
{
    if (m == 0)
        return 1;
    return Lucas(n / mod, m / mod) * C(n % mod, m % mod) % mod;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m;
        scanf("%d%d%d", &n, &m, &mod);
        fac[0] = 1;
        for (int i = 1; i < mod; ++i)
            fac[i] = (ll)fac[i - 1] * i % mod;
        inv[mod - 1] = ksm(fac[mod - 1], mod - 2);
        for (int i = mod - 2; i >= 0; --i)
            inv[i] = (ll)inv[i + 1] * (i + 1) % mod;
        printf("%d\n", Lucas(n + m, n));
    }
    return 0;
}