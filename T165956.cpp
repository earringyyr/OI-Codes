#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long ll;
using namespace std;
namespace pr
{
    int n, sum, mod, cnt;
    int p[1005];
    int vis[30005], pri[30005], phi[30005];
    int ans[30005];
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
    int getpr(int num)
    {
        n = num;
        phi[1] = 1;
        for (int i = 2; i <= 30000; ++i)
        {
            if (!vis[i])
            {
                vis[i] = i;
                pri[++sum] = i;
                phi[i] = i - 1;
            }
            for (int j = 1; j <= sum && vis[i] >= pri[j] && i * pri[j] <= 30000; ++j)
            {
                vis[i * pri[j]] = pri[j];
                if (vis[i] == pri[j])
                    phi[i * pri[j]] = phi[i] * pri[j];
                else
                    phi[i * pri[j]] = phi[i] * phi[pri[j]];
            }
        }
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
                return i;
        return 0;
    }
} // namespace pr
const int mod = 998244353;
int p, G, num = 1;
int fac[30005], inv[30005], ind[30005], ans[30005];
int rev[120005], f[120005], g[120005];
int tmp1[120005], tmp2[120005], tmp3[120005];
__int128 n, l, r;
__int128 read()
{
    __int128 x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}
int ksmp(int aa, int k)
{
    int bb = 1;
    while (k)
    {
        if (k & 1)
            bb = (ll)bb * aa % p;
        aa = (ll)aa * aa % p;
        k >>= 1;
    }
    return bb;
}
int C(int n, int m)
{
    return (ll)fac[n] * inv[m] % p * inv[n - m] % p;
}
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
void ntt(int *c, int type)
{
    for (int i = 0; i < num; ++i)
        if (i < rev[i])
            swap(c[i], c[rev[i]]);
    for (int mid = 1; mid < num; mid <<= 1)
    {
        int ww = ksm(3, (mod - 1) / (mid << 1));
        if (type == -1)
            ww = ksm(ww, mod - 2);
        for (int j = 0; j < num; j += (mid << 1))
        {
            int w = 1;
            for (int k = 0; k < mid; ++k)
            {
                int x = c[j + k], y = (ll)w * c[j + mid + k] % mod;
                c[j + k] = (x + y) % mod;
                c[j + mid + k] = (x - y + mod) % mod;
                w = (ll)w * ww % mod;
            }
        }
    }
    if (type == -1)
    {
        int inv = ksm(num, mod - 2);
        for (int i = 0; i < num; ++i)
            c[i] = (ll)c[i] * inv % mod;
    }
    return;
}
void solve(__int128 x, __int128 y, int type)
{
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    f[0] = 1;
    g[0] = 1;
    while (x || y)
    {
        memset(tmp1, 0, sizeof(tmp1));
        memset(tmp2, 0, sizeof(tmp2));
        memset(tmp3, 0, sizeof(tmp3));
        ntt(f, 1);
        ntt(g, 1);
        for (int i = y % p; i < p; ++i)
        {
            ++tmp1[ind[C(i, y % p)]];
            if (i < x % p)
                ++tmp2[ind[C(i, y % p)]];
            if (i == x % p)
                ++tmp3[ind[C(i, y % p)]];
        }
        ntt(tmp1, 1);
        ntt(tmp2, 1);
        ntt(tmp3, 1);
        for (int i = 0; i < num; ++i)
        {
            f[i] = ((ll)g[i] * tmp2[i] + (ll)f[i] * tmp3[i]) % mod;
            g[i] = (ll)g[i] * tmp1[i] % mod;
        }
        ntt(f, -1);
        ntt(g, -1);
        for (int i = p - 1; i < num; ++i)
        {
            f[i % (p - 1)] = (f[i % (p - 1)] + f[i]) % mod;
            f[i] = 0;
            g[i % (p - 1)] = (g[i % (p - 1)] + g[i]) % mod;
            g[i] = 0;
        }
        x /= p;
        y /= p;
    }
    int now = 1;
    for (int i = 0; i < p; ++i)
    {
        ans[now] = ((ans[now] + f[i] * type) % mod + mod) % mod;
        now = (ll)now * G % p;
    }
    return;
}
int main()
{
    scanf("%d", &p);
    fac[0] = 1;
    for (int i = 1; i < p; ++i)
        fac[i] = (ll)fac[i - 1] * i % p;
    inv[p - 1] = ksmp(fac[p - 1], p - 2);
    for (int i = p - 2; i >= 0; --i)
        inv[i] = (ll)inv[i + 1] * (i + 1) % p;
    G = pr::getpr(p);
    int now = 1;
    for (int i = 0; i < p - 1; ++i)
    {
        ind[now] = i;
        now = (ll)now * G % p;
    }
    while (num < 2 * p)
        num <<= 1;
    for (int i = 0; i < num; ++i)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (num >> 1) : 0);
    n = read();
    l = read();
    r = read();
    if (l >= 1)
        solve(l - 1, n, -1);
    solve(r, n, 1);
    for (int i = 1; i < p; ++i)
        ans[0] = (ans[0] + ans[i]) % mod;
    ans[0] = ((r - l + 1) % mod - ans[0] + mod) % mod;
    for (int i = 0; i < p; ++i)
        printf("%d\n", ans[i]);
    return 0;
}