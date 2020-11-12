#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, m, p, num = 1, ans;
int f[2000005];
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
void fwt(int *c, int type)
{
    for (int mid = 1; mid < num; mid <<= 1)
        for (int j = 0; j < num; j += (mid << 1))
            for (int k = 0; k < mid; ++k)
            {
                int x = c[j + k], y = c[j + mid + k];
                c[j + k] = x;
                if (type == 1)
                    c[j + mid + k] = (x + y) % mod;
                else
                    c[j + mid + k] = (y - x + mod) % mod;
            }
    return;
}
int main()
{
    scanf("%d%d%d", &n, &m, &p);
    while (num <= m)
        num <<= 1;
    for (int i = 0; i <= m; ++i)
        f[i] = 1;
    fwt(f, 1);
    for (int i = 0; i < num; ++i)
        f[i] = ksm(f[i], n);
    fwt(f, -1);
    for (int i = 0; i < num; ++i)
        ans = (ans + (ll)f[i] * ksm(p, i) % mod) % mod;
    printf("%d", ans);
    return 0;
}