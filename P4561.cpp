#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
using namespace std;
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
namespace io_in
{
    char buf[1 << 21], *p1 = buf, *p2 = buf;
    int read()
    {
        int x = 0, f = 1;
        char c = gc();
        while (!isdigit(c))
        {
            if (c == '-')
                f = -1;
            c = gc();
        }
        while (isdigit(c))
        {
            x = (x << 3) + (x << 1) + (c ^ 48);
            c = gc();
        }
        return x * f;
    }
} // namespace io_in
using namespace io_in;
namespace io_out
{
    char buf[1 << 21];
    int p1 = -1;
    const int p2 = (1 << 21) - 1;
    void flush()
    {
        fwrite(buf, 1, p1 + 1, stdout);
        p1 = -1;
        return;
    }
    void pc(char x)
    {
        if (p1 == p2)
            flush();
        buf[++p1] = x;
        return;
    }
    void write(int x)
    {
        char buffer[10];
        int len = -1;
        if (x < 0)
        {
            pc('-');
            x = -x;
        }
        do
        {
            buffer[++len] = (x % 10) | 48;
            x /= 10;
        } while (x);
        while (len >= 0)
            pc(buffer[len--]);
        return;
    }
} // namespace io_out
using namespace io_out;
typedef long long ll;
const int mod = 998244353;
int n, m, nn, mm, l, r, cnt, ans;
int a[200005], b[200005], num[200005];
int fac[10200005], inv[10200005];
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
    fac[0] = 1;
    for (int i = 1; i <= 10200000; ++i)
        fac[i] = (ll)fac[i - 1] * i % mod;
    inv[10200000] = ksm(fac[10200000], mod - 2);
    for (int i = 10199999; i >= 0; --i)
        inv[i] = (ll)inv[i + 1] * (i + 1) % mod;
    int T;
    T = read();
    while (T--)
    {
        cnt = 0;
        ans = 1;
        n = read();
        m = read();
        l = read();
        r = read();
        nn = 0;
        mm = m;
        for (int i = 1; i <= n; ++i)
        {
            a[i] = read();
            if (a[i] >= l && a[i] <= r)
                b[++nn] = a[i];
        }
        sort(a + 1, a + n + 1);
        int tmp = 0;
        for (int i = 1; i <= n; ++i)
            if (i == 1 || a[i] == a[i - 1])
                ++tmp;
            else
            {
                ans = (ll)ans * fac[tmp] % mod;
                tmp = 1;
            }
        ans = (ll)ans * fac[tmp] % mod;
        sort(b + 1, b + nn + 1);
        tmp = 0;
        for (int i = 1; i <= nn; ++i)
            if (i == 1 || b[i] == b[i - 1])
                ++tmp;
            else
            {
                num[++cnt] = tmp;
                tmp = 1;
            }
        num[++cnt] = tmp;
        sort(num + 1, num + cnt + 1);
        int len = r - l + 1, pos = 0;
        for (int i = 1; i <= cnt; ++i)
            if (mm >= (ll)(len - (cnt - i + 1)) * (num[i] - pos))
            {
                if (num[i] != pos)
                {
                    ans = (ll)ans * ksm((ll)fac[num[i]] * inv[pos] % mod, len - (cnt - i + 1)) % mod;
                    mm -= (len - (cnt - i + 1)) * (num[i] - pos);
                    pos = num[i];
                }
            }
            else
            {
                int h = mm / (len - (cnt - i + 1));
                ans = (ll)ans * ksm((ll)fac[pos + h] * inv[pos] % mod, len - (cnt - i + 1)) % mod;
                pos += h;
                mm -= (len - (cnt - i + 1)) * h;
                ans = (ll)ans * ksm((ll)fac[pos + 1] * inv[pos] % mod, mm) % mod;
                mm = 0;
                break;
            }
        if (m)
        {
            int h = mm / len;
            ans = (ll)ans * ksm((ll)fac[pos + h] * inv[pos] % mod, len) % mod;
            pos += h;
            mm -= len * h;
            ans = (ll)ans * ksm((ll)fac[pos + 1] * inv[pos] % mod, mm) % mod;
            mm = 0;
        }
        ans = (ll)fac[n + m] * ksm(ans, mod - 2) % mod;
        write(ans);
        pc('\n');
    }
    flush();
    return 0;
}