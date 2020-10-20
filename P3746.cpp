#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, mod, k, r, ans, c[55][55];
struct matrix
{
    int a[55][55];
    matrix()
    {
        memset(a, 0, sizeof(a));
    }
    matrix operator*(const matrix &bb) const
    {
        matrix cc;
        for (int i = 0; i < k; ++i)
            for (int j = 0; j < k; ++j)
                for (int l = 0; l < k; ++l)
                    cc.a[i][j] = (cc.a[i][j] + (ll)a[i][l] * bb.a[l][j] % mod) % mod;
        return cc;
    }
};
matrix ksm(matrix aa, int K)
{
    matrix bb;
    for (int i = 0; i < k; ++i)
        bb.a[i][i] = 1;
    while (K)
    {
        if (K & 1)
            bb = bb * aa;
        aa = aa * aa;
        K >>= 1;
    }
    return bb;
}
int main()
{
    scanf("%d%d%d%d", &n, &mod, &k, &r);
    c[0][0] = 1;
    for (int i = 1; i <= k; ++i)
    {
        c[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
    }
    matrix aa;
    for (int i = 0; i <= k; ++i)
        for (int j = 0; j < k; ++j)
            aa.a[(i + j) % k][j] = (aa.a[(i + j) % k][j] + c[k][i]) % mod;
    aa = ksm(aa, n - 1);
    c[k][0] = (c[k][0] + c[k][k]) % mod;
    for (int i = 0; i < k; ++i)
        ans = (ans + (ll)aa.a[r][i] * c[k][i] % mod) % mod;
    printf("%d", ans);
    return 0;
}