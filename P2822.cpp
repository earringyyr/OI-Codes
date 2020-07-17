#include <iostream>
#include <cstdio>
using namespace std;
int t, k, n, m, f[2005][2005], ans[2005][2005];
int main()
{
    scanf("%d%d", &t, &k);
    for (int i = 0; i <= 2000; ++i)
        f[0][i] = 1;
    for (int i = 1; i <= 2000; ++i)
        for (int j = 1; j <= 2000; ++j)
        {
            ans[i][j] = ans[i - 1][j] + ans[i][j - 1] - ans[i - 1][j - 1];
            if (i <= j)
            {
                f[i][j] = (f[i - 1][j - 1] + f[i][j - 1]) % k;
                if (!f[i][j])
                    ++ans[i][j];
            }
        }
    for (int tt = 1; tt <= t; ++tt)
    {
        scanf("%d%d", &n, &m);
        printf("%d\n", ans[m][n]);
    }
    return 0;
}