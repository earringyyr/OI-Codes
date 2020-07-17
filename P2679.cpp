#include <iostream>
#include <cstdio>
#define mod 1000000007
using namespace std;
int n, m, kk, f[205][205], dp[205][205];
char a[1005], b[205];
int main()
{
    scanf("%d%d%d", &n, &m, &kk);
    scanf("%s", a + 1);
    scanf("%s", b + 1);
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = m; j >= 1; --j)
            for (int k = kk; k >= 1; --k)
            {
                if (a[i] == b[j])
                    dp[j][k] = (dp[j - 1][k] + f[j - 1][k - 1]) % mod;
                else
                    dp[j][k] = 0;
                f[j][k] = (f[j][k] + dp[j][k]) % mod;
            }
    printf("%d", f[m][kk]);
    return 0;
}