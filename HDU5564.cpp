#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int l, r, k;
struct matrix
{
    int a[75][75];
    matrix()
    {
        memset(a, 0, sizeof(a));
    }
    matrix operator*(const matrix &bb) const
    {
        matrix cc;
        for (int i = 0; i <= 70; ++i)
            for (int j = 0; j <= 70; ++j)
                for (int k = 0; k <= 70; ++k)
                {
                    cc.a[i][j] += (ll)a[i][k] * bb.a[k][j] % mod;
                    cc.a[i][j] %= mod;
                }
        return cc;
    }
    matrix operator^(const matrix &bb) const
    {
        matrix cc;
        for (int i = 0; i <= 70; ++i)
            for (int k = 0; k <= 70; ++k)
            {
                cc.a[i][0] += (ll)a[i][k] * bb.a[k][0] % mod;
                cc.a[i][0] %= mod;
            }
        return cc;
    }
};
int solve(int x)
{
    if (!x)
        return 0;
    matrix a, b;
    for (int i = 0; i < 70; ++i)
        for (int j = 0; j < 70; ++j)
            if ((i / 7) + (j / 7) != k && ((i % 7) * 10 + (j / 7)) % 7 == j % 7)
                a.a[j][i] = 1;
    for (int i = 0; i < 10; ++i)
        a.a[70][7 * i] = 1;
    a.a[70][70] = 1;
    for (int i = 0; i <= 70; ++i)
        b.a[i][i] = 1;
    --x;
    while (x)
    {
        if (x & 1)
            b = b * a;
        a = a * a;
        x >>= 1;
    }
    matrix c;
    for (int i = 1; i < 10; ++i)
        c.a[i * 7 + i % 7][0] = 1;
    c = b ^ c;
    int ans = c.a[70][0];
    for (int i = 0; i < 10; ++i)
        ans = (ans + c.a[7 * i][0]) % mod;
    return ans;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", (solve(r) - solve(l - 1) + mod) % mod);
    }
    return 0;
}