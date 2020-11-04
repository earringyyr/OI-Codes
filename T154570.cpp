#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int mod = 1000000007;
int n, m, k, ans, f[4005][2005];
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    f[0][0] = 1;
    for (int i = 1; i <= (n + m - 1) / (k - 1); ++i)
    {
        f[i][0] = 1;
        for (int j = 1; j <= n; ++j)
        {
            for (int l = 1; l <= min(k - 1, j); ++l)
                f[i][j] = (f[i][j] + f[i - 1][j - l]) % mod;
            if (j % (k - 1) == n % (k - 1) && (k - 1) * i - j >= 0 && (k - 1) * i - j <= m - 1 && ((k - 1) * i - j) % (k - 1) == (m - 1) % (k - 1))
                ans = (ans + f[i][j]) % mod;
            f[i][j] = (f[i][j] + f[i - 1][j]) % mod;
        }
    }
    printf("%d", ans);
    return 0;
}