#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
typedef long long ll;
using namespace std;
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
namespace io
{
    char buf[1 << 21], *p1 = buf, *p2 = buf;
    int read()
    {
        int x = 0;
        char ch = gc();
        while (!isdigit(ch))
            ch = gc();
        while (isdigit(ch))
        {
            x = (x << 3) + (x << 1) + (ch ^ 48);
            ch = gc();
        }
        return x;
    }
    ll read_ll()
    {
        ll x = 0;
        char ch = gc();
        while (!isdigit(ch))
            ch = gc();
        while (isdigit(ch))
        {
            x = (x << 3) + (x << 1) + (ch ^ 48);
            ch = gc();
        }
        return x;
    }
} // namespace io
using namespace io;
const int mod = 10000019;
int n, a, b, sum, pw, aw, bw, rev, ans;
ll bb;
int p[5000005], inv[5000005];
int ca[5000005], cb[5000005];
int f[5000005], g[5000005];
int ff[5000005], gg[5000005];
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
int main()
{
    n = read();
    a = read();
    bb = read_ll();
    b = bb % mod;
    for (int i = 1; i <= n; ++i)
    {
        p[i] = read();
        sum = (sum + p[i]) % mod;
    }
    sum = (ll)sum * ksm(n, mod - 2) % mod;
    if (sum == 1)
    {
        printf("%d", a < bb);
        return 0;
    }
    inv[1] = 1;
    for (int i = 2; i <= a; ++i)
        inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;
    pw = 1;
    aw = ksm(1 - sum + mod, a);
    bw = ksm(1 - sum + mod, bb % (mod - 1));
    rev = ksm(1 - sum + mod, mod - 2);
    for (int i = 0; i <= a; ++i)
    {
        if (i == 0)
        {
            ca[0] = 1;
            cb[0] = 1;
        }
        else
        {
            ca[i] = (ll)ca[i - 1] * (a - i + 1 + mod) % mod * inv[i] % mod;
            cb[i] = (ll)cb[i - 1] * (b - i + 1 + mod) % mod * inv[i] % mod;
        }
        f[i] = (ll)ca[i] * pw % mod * aw % mod;
        g[i] = (ll)cb[i] * pw % mod * bw % mod;
        pw = (ll)pw * sum % mod;
        aw = (ll)aw * rev % mod;
        bw = (ll)bw * rev % mod;
    }
    ff[0] = f[0];
    gg[0] = g[0];
    for (int i = 1; i <= a; ++i)
    {
        ff[i] = (f[i] + ff[i - 1]) % mod;
        gg[i] = (g[i] + gg[i - 1]) % mod;
    }
    for (int i = 0; i <= a; ++i)
        ans = (ans + (ll)f[i] * gg[i]) % mod;
    ans = (1 - ans + mod) % mod;
    printf("%d", ans);
    return 0;
}