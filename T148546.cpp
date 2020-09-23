#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n, tot, gcd, A, B, ans;
int vis[10000005], pri[10000005], mu[10000005];
int num[10000005], sum[10000005];
int GCD(int a, int b)
{
    if (!b)
        return a;
    return GCD(b, a % b);
}
int ksm(int a, int k)
{
    int b = 1;
    while (k)
    {
        if (k & 1)
            b = (ll)b * a % mod;
        a = (ll)a * a % mod;
        k >>= 1;
    }
    return b;
}
int main()
{
    mu[1] = 1;
    for (int i = 2; i <= 10000000; ++i)
    {
        if (!vis[i])
        {
            vis[i] = i;
            pri[++tot] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= tot && pri[j] <= vis[i] && i * pri[j] <= 10000000; ++j)
        {
            vis[i * pri[j]] = pri[j];
            if (pri[j] == vis[i])
                mu[i * pri[j]] = 0;
            else
                mu[i * pri[j]] = mu[i] * mu[pri[j]];
        }
    }
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        scanf("%d", &x);
        ++num[x];
        if (i == 1)
            gcd = x;
        else
            gcd = GCD(gcd, x);
    }
    if (gcd != 1)
    {
        printf("0");
        return 0;
    }
    for (int i = 2; i <= 10000000; ++i)
        for (int j = i; j <= 10000000; j += i)
            sum[i] += num[j];
    for (int i = 2; i <= 10000000; ++i)
        if (sum[i] && mu[i])
            if (mu[i] == -1)
            {
                A = (A + (ksm(2, sum[i]) - 1 + mod) % mod) % mod;
                B = (B + (ll)(ksm(2, sum[i]) - 1 + mod) * sum[i] % mod) % mod;
            }
            else
            {
                A = (A - (ksm(2, sum[i]) - 1 + mod) % mod + mod) % mod;
                B = (B - (ll)(ksm(2, sum[i]) - 1 + mod) * sum[i] % mod + mod) % mod;
            }
    ans = ((ll)A * n - B + mod) % mod;
    printf("%d", ans);
    return 0;
}