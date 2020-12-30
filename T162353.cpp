#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 998244353, inv2 = 499122177;
int n, k, x, num = 1 << 12, ans;
int cnt[5005];
uint seed;
uint b[2000005];
vector<ull> a[2000005];
uint get01()
{
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed & 1;
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
void fwt(int *c, int type)
{
    for (int mid = 1; mid < num; mid <<= 1)
        for (int j = 0; j < num; j += (mid << 1))
            for (int k = 0; k < mid; ++k)
            {
                int x = c[j + k], y = c[j + mid + k];
                c[j + k] = (x + y) % mod;
                c[j + mid + k] = (x - y + mod) % mod;
                if (type == -1)
                {
                    c[j + k] = (ll)c[j + k] * inv2 % mod;
                    c[j + mid + k] = (ll)c[j + mid + k] * inv2 % mod;
                }
            }
    return;
}
void fwt_and(int *c)
{
    for (int mid = 1; mid < num; mid <<= 1)
        for (int j = 0; j < num; j += (mid << 1))
            for (int k = 0; k < mid; ++k)
                c[j + k] = (c[j + k] + c[j + mid + k]) % mod;
    return;
}
int main()
{
    scanf("%d%d%d%u", &n, &k, &x, &seed);
    if (k <= 100)
    {
        for (int i = 1; i <= n; ++i)
        {
            a[i].resize((k - 1) / 4 + 1);
            for (int j = 0; j < k; ++j)
                b[j] = get01();
            for (int j = k - 1; j >= 0; --j)
                a[i][j / 4] = (a[i][j / 4] << 1) | b[j];
        }
        int col = (k - 1) / 4;
        for (int x = 0; x <= col; ++x)
            for (int y = 0; y <= col; ++y)
                for (int z = 0; z <= col; ++z)
                {
                    memset(cnt, 0, sizeof(cnt));
                    for (int i = 1; i <= n; ++i)
                        ++cnt[(a[i][x] << 8) + (a[i][y] << 4) + a[i][z]];
                    fwt(cnt, 1);
                    for (int i = 0; i < num; ++i)
                        cnt[i] = (ll)cnt[i] * cnt[i] % mod;
                    fwt(cnt, -1);
                    fwt_and(cnt);
                    for (int l = 0; l < 4; ++l)
                        for (int m = 0; m < 4; ++m)
                            for (int r = 0; r < 4; ++r)
                                ans = (ans + (ll)cnt[(1 << (l + 8)) + (1 << (m + 4)) + (1 << r)] * ksm(2, 4 * x + l + 4 * y + m + 4 * z + r) % mod) % mod;
                }
        ans = (ll)ans * inv2 % mod;
    }
    else
    {
        for (int i = 1; i <= n; ++i)
        {
            a[i].resize((k - 1) / 63 + 1);
            for (int j = 0; j < k; ++j)
                b[j] = get01();
            for (int j = k - 1; j >= 0; --j)
                a[i][j / 63] = (a[i][j / 63] << 1) | b[j];
        }
        int base = (1ull << 63) % mod;
        for (int i = 1; i <= n; ++i)
            for (int j = i + 1; j <= n; ++j)
            {
                int num = 0;
                for (int l = (k - 1) / 63; l >= 0; --l)
                    num = ((ll)num * base % mod + (a[i][l] ^ a[j][l])) % mod;
                num = (ll)num * num % mod * num % mod;
                ans = (ans + num) % mod;
            }
    }
    printf("%d", ans);
    return 0;
}