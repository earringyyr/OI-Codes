#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n;
int a[2005], b[2005], cat[2005];
int f[2005][2005];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &b[i]);
    cat[0] = 1;
    cat[1] = 1;
    for (int i = 2; i <= n; ++i)
        for (int j = 0; j < i; ++j)
            cat[i] = (cat[i] + (ll)cat[j] * cat[i - j - 1]) % mod;
    f[0][0] = 1;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
        {
            if (i)
                f[i][j] = (f[i][j] + f[i - 1][j]) % mod;
            if (j)
                f[i][j] = (f[i][j] + f[i][j - 1]) % mod;
            for (int k = 0; k < min(i, j); ++k)
                if (a[i - k] == b[j - k])
                    f[i][j] = (f[i][j] - (ll)f[i - k - 1][j - k - 1] * cat[k] % mod + mod) % mod;
                else
                    break;
        }
    printf("%d", f[n][n]);
    return 0;
}