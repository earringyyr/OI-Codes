#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, k, a, ans;
int inv[10000005];
int ksm(int aa, int k)
{
    int bb = 1;
    while (k)
    {
        if (k & 1)
            bb = (ll)aa * bb % mod;
        aa = (ll)aa * aa % mod;
        k >>= 1;
    }
    return bb;
}
int main()
{
    inv[1] = 1;
    for (int i = 2; i <= 10000000; ++i)
        inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &n, &k, &a);
        if (a == 1)
            puts("1");
        else
        {
            ans = 0;
            int pw = 1, c = 1;
            for (int i = 0; i <= k - 1; ++i)
            {
                ans = (ans + (ll)pw * c % mod) % mod;
                pw = (ll)pw * (a - 1) % mod;
                c = (ll)c * (n - i) % mod * inv[i + 1] % mod;
            }
            ans = (ksm(a, n) - ans + mod) % mod;
            ans = (ll)a * ksm(ksm(a - 1, k), mod - 2) % mod * ans % mod;
            ans = (ll)ans * ksm(c, mod - 2) % mod;
            printf("%d\n", ans);
        }
    }
    return 0;
}