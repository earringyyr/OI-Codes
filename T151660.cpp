#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, mod, ans, f[4005][4005];
int main()
{
    scanf("%d%d", &n, &mod);
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)
            f[i][j] = (2 * f[i][j - 1] % mod + (ll)j * f[i - 1][j - 1] % mod) % mod;
    for (int i = 1; i <= n; ++i)
        ans = (ans + (ll)f[i][n] * f[i][n] % mod) % mod;
    for (int i = 2; i <= n; ++i)
        ans = (ans + (ll)f[i][n] * f[i - 1][n] % mod) % mod;
    ans = 2 * ans % mod;
    printf("%d", ans);
    return 0;
}