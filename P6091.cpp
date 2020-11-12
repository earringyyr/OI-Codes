#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
int n, d, sum, mod, g, cnt;
int p[1005];
int vis[1000005], pri[1000005], phi[1000005];
int use[1000005], ans[1000005];
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
int gcd(int x, int y)
{
    if (!y)
        return x;
    return gcd(y, x % y);
}
bool check(int k)
{
    for (int i = 1; i <= cnt; ++i)
        if (ksm(k, phi[n] / p[i]) == 1)
            return false;
    return true;
}
int main()
{
    phi[1] = 1;
    for (int i = 2; i <= 1000000; ++i)
    {
        if (!vis[i])
        {
            vis[i] = i;
            pri[++sum] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= sum && vis[i] >= pri[j] && i * pri[j] <= 1000000; ++j)
        {
            vis[i * pri[j]] = pri[j];
            if (vis[i] == pri[j])
                phi[i * pri[j]] = phi[i] * pri[j];
            else
                phi[i * pri[j]] = phi[i] * phi[pri[j]];
        }
    }
    use[1] = 1;
    use[2] = 1;
    use[4] = 1;
    for (int i = 2; i <= sum; ++i)
    {
        for (ll j = 1; (ll)j * pri[i] <= 1000000; j *= pri[i])
            use[j * pri[i]] = 1;
        for (ll j = 2; (ll)j * pri[i] <= 1000000; j *= pri[i])
            use[j * pri[i]] = 1;
    }
    int T;
    scanf("%d", &T);
    while (T--)
    {
        cnt = 0;
        scanf("%d%d", &n, &d);
        if (use[n])
        {
            mod = n;
            int ph = phi[n];
            for (int i = 1; pri[i] * pri[i] <= phi[n]; ++i)
                if (ph % pri[i] == 0)
                {
                    while (ph % pri[i] == 0)
                        ph /= pri[i];
                    p[++cnt] = pri[i];
                }
            if (ph > 1)
                p[++cnt] = ph;
            for (int i = 1; i <= n; ++i)
                if (gcd(i, n) == 1 && check(i))
                {
                    g = i;
                    break;
                }
            int base = 1;
            ans[0] = 0;
            for (int i = 1; i <= phi[n]; ++i)
            {
                base = (ll)base * g % mod;
                if (gcd(i, phi[n]) == 1)
                    ans[++ans[0]] = base;
            }
            sort(ans + 1, ans + ans[0] + 1);
            printf("%d\n", ans[0]);
            for (int i = 1; i <= ans[0] / d; ++i)
                printf("%d ", ans[i * d]);
            putchar('\n');
        }
        else
            printf("0\n\n");
    }
    return 0;
}