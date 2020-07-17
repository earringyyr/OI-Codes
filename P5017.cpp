#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define inf 0x7f7f7f7f
using namespace std;
int n, m, ans, t[505], f[505][205];
int main()
{
    memset(f, 0x7f, sizeof(f));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &t[i]);
    sort(t + 1, t + n + 1);
    for (int i = 0; i < 2 * m; ++i)
        f[1][i] = i;
    for (int i = 1; i < n; ++i)
        for (int j = 0; j < 2 * m; ++j)
            if (f[i][j] < inf)
            {
                if (t[i] + j >= t[i + 1])
                    f[i + 1][t[i] + j - t[i + 1]] = min(f[i + 1][t[i] + j - t[i + 1]], f[i][j] + t[i] + j - t[i + 1]);
                for (int k = t[i] + j + m >= t[i + 1] ? 0 : t[i + 1] - t[i] - j - m; t[i] + j + m + k - t[i + 1] < 2 * m; ++k)
                    if (t[i] + j + m + k >= t[i + 1])
                        f[i + 1][t[i] + j + m + k - t[i + 1]] = min(f[i + 1][t[i] + j + m + k - t[i + 1]], f[i][j] + t[i] + j + m + k - t[i + 1]);
                if (t[i] + j + m < t[i + 1])
                    for (int k = 0; k < 2 * m; ++k)
                        f[i + 1][k] = min(f[i + 1][k], f[i][j] + k);
            }
    ans = inf;
    for (int i = 0; i < 2 * m; ++i)
        ans = min(ans, f[n][i]);
    printf("%d", ans);
    return 0;
}