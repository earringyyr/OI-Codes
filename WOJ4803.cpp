#include <iostream>
#include <cstdio>
#define mod 1000000007
using namespace std;
int n, aa, bb, a, b, c, x, y, inv, f[20000005];
void exgcd(int p, int q)
{
    if (!q)
    {
        x = 1;
        y = 0;
        return;
    }
    exgcd(q, p % q);
    int tmp = x;
    x = y;
    y = tmp - p / q * y;
    return;
}
int main()
{
    scanf("%d%d%d", &n, &aa, &bb);
    a = (long long)(mod + 1 - aa) * bb % mod;
    b = ((long long)aa * bb % mod + (long long)(mod + 1 - aa) * (mod + 1 - bb) % mod) % mod;
    c = (long long)aa * (mod + 1 - bb) % mod;
    exgcd(c, mod);
    inv = (x % mod + mod) % mod;
    f[0] = 0;
    f[1] = 1;
    for (int i = 2; i <= 2 * n; ++i)
        f[i] = ((long long)(mod + 1 - b) * f[i - 1] + (long long)(mod - a) * f[i - 2]) % mod * inv % mod;
    exgcd(f[2 * n], mod);
    inv = (x % mod + mod) % mod;
    printf("%d", (long long)f[n] * inv % mod);
    return 0;
}