#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int n, m, l, r;
int p[2][35][35];
ll ans;
ll f[2][35][35];
ll dp[2][2][35][35][35][35];
int main()
{
    scanf("%d%d%d%d", &n, &m, &l, &r);
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            scanf("%d", &p[0][i][j]);
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            scanf("%d", &p[1][i][j]);
    if ((m && !r) || m < l)
    {
        printf("No");
        return 0;
    }
    ans = inf;
    memset(f, 0x3f, sizeof(f));
    for (int t = 0; t < 2; ++t)
    {
        memset(dp[t][0], 0x3f, sizeof(dp[t][0]));
        dp[t][0][0][0][0][0] = 0;
        for (int i = 0; i < n; ++i)
        {
            memset(dp[t][1], 0x3f, sizeof(dp[t][1]));
            for (int j = 0; j <= i; ++j)
                for (int k = j; k <= m; ++k)
                    for (int x = 0; x <= i; ++x)
                        for (int y = 0; y <= k; ++y)
                            if (dp[t][0][j][k][x][y] < inf)
                                for (int z = 0; z <= m - k; ++z)
                                {
                                    dp[t][1][j + (z != 0)][k + z][x][y] = min(dp[t][1][j + (z != 0)][k + z][x][y], dp[t][0][j][k][x][y] + p[t][i + 1][z]);
                                    dp[t][1][j + (z != 0)][k + z][x + 1][y + z] = min(dp[t][1][j + (z != 0)][k + z][x + 1][y + z], dp[t][0][j][k][x][y] + p[t][i + 1][z]);
                                }
            swap(dp[t][0], dp[t][1]);
        }
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= m; ++j)
                for (int k = l; k <= n; ++k)
                    f[t][i][j] = min(f[t][i][j], dp[t][0][k][m][i][j]);
    }
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            for (int x = 0; x <= i + r - n; ++x)
                for (int y = j; y <= m; ++y)
                    ans = min(ans, f[0][i][j] + f[1][x][y]);
    printf("%lld", ans);
    return 0;
}