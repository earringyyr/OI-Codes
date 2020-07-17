#include <iostream>
#include <cstdio>
#define mod 998244353
using namespace std;
int n, k, ans, num[500005], a[500005], c[500005], cnt[500005], sum[500005], inv[500005];
char s[500005];
int ksm(int aa, int kk)
{
    int bb = 1;
    while (kk)
    {
        if (kk & 1)
            bb = (long long)bb * aa % mod;
        aa = (long long)aa * aa % mod;
        kk >>= 1;
    }
    return bb;
}
int C(int aa, int bb)
{
    if (bb < aa || aa < 0)
        return 0;
    return (long long)num[bb] * inv[aa] % mod * inv[bb - aa] % mod;
}
int main()
{
    scanf("%d%d%s", &n, &k, s);
    for (int i = 0; i < n; ++i)
        a[i + 1] = s[i] ^ 48;
    cnt[0] = 1;
    for (int i = 1; i <= n; ++i)
        cnt[i] = (long long)cnt[i - 1] * 10 % mod;
    num[0] = 1;
    inv[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        num[i] = (long long)num[i - 1] * i % mod;
        inv[i] = ksm(num[i], mod - 2);
    }
    for (int i = n - 1; i >= 1; --i)
        c[i] = (c[i + 1] + (long long)cnt[n - i - 1] * C(k - 1, i - 1) % mod) % mod;
    for (int i = 1; i <= n; ++i)
        c[i] = (c[i] + (long long)cnt[n - i] * C(k, i - 1) % mod) % mod;
    for (int i = 1; i <= n; ++i)
        ans = (ans + (long long)c[i] * a[i] % mod) % mod;
    printf("%d", ans);
    return 0;
}