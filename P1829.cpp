#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long ll;
const int mod = 20101009;
int n, m, sum, ans, vis[10000005], pri[10000005], f[10000005], s[10000005];
int main()
{
    scanf("%d%d", &n, &m);
    if (m < n)
        swap(m, n);
    f[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        if (!vis[i])
        {
            vis[i] = i;
            pri[++sum] = i;
            f[i] = 1 - i + mod;
        }
        for (int j = 1; j <= sum && pri[j] <= vis[i] && (ll)i * pri[j] <= n; ++j)
        {
            vis[i * pri[j]] = pri[j];
            if (i % pri[j] == 0)
                f[i * pri[j]] = f[i];
            else
                f[i * pri[j]] = (ll)f[i] * f[pri[j]] % mod;
        }
    }
    for (int i = 1; i <= n; ++i)
        f[i] = ((ll)f[i] * i % mod + f[i - 1]) % mod;
    for (int i = 1; i <= m; ++i)
        s[i] = ((ll)s[i - 1] + i) % mod;
    for (int l = 1, r; l <= n; l = r + 1)
    {
        r = min(n / (n / l), m / (m / l));
        ans = ((ll)ans + (ll)s[n / l] * s[m / l] % mod * ((f[r] - f[l - 1]) % mod + mod) % mod) % mod;
    }
    printf("%d", ans);
    return 0;
}