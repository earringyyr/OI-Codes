#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n, m, ans;
int fac[3000005], inv[3000005];
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
void flip(int &x, int &y, int id)
{
    if (id == 0)
    {
        swap(x, y);
        --x;
        ++y;
    }
    else
    {
        swap(x, y);
        x += m + 2;
        y -= m + 2;
    }
    return;
}
int C(int n, int m)
{
    return (ll)fac[n] * inv[m] % mod * inv[n - m] % mod;
}
int main()
{
    scanf("%d%d", &n, &m);
    fac[0] = 1;
    for (int i = 1; i <= 2 * n + m + 1; ++i)
        fac[i] = (ll)fac[i - 1] * i % mod;
    inv[2 * n + m + 1] = ksm(fac[2 * n + m + 1], mod - 2);
    for (int i = 2 * n + m; i >= 0; --i)
        inv[i] = (ll)inv[i + 1] * (i + 1) % mod;
    int x = n + m + 1, y = n;
    ans = C(x + y, y);
    while (x >= 0 && y >= 0)
    {
        flip(x, y, 0);
        if (x >= 0 && y >= 0)
            ans = (ans - C(x + y, y) + mod) % mod;
        flip(x, y, 1);
        if (x >= 0 && y >= 0)
            ans = (ans + C(x + y, y)) % mod;
    }
    x = n + m + 1;
    y = n;
    while (x >= 0 && y >= 0)
    {
        flip(x, y, 1);
        if (x >= 0 && y >= 0)
            ans = (ans - C(x + y, y) + mod) % mod;
        flip(x, y, 0);
        if (x >= 0 && y >= 0)
            ans = (ans + C(x + y, y)) % mod;
    }
    printf("%d", ans);
    return 0;
}