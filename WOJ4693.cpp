#include <iostream>
#include <iomanip>
#include <cstdio>
using namespace std;
int t, m, n;
long double cnt, ans, num[255], f[255][255];
long double ask(int k, long double w)
{
    for (int i = n; i >= n - k + 1; --i)
        w *= i;
    for (int i = 1; i <= k; ++i)
        w /= i;
    return w;
}
int main()
{
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        ans = 0;
        scanf("%d%d", &m, &n);
        for (int i = 1; i <= m; ++i)
        {
            f[0][0] = 1;
            for (int j = 1; j <= m; ++j)
                for (int k = 1; k <= m; ++k)
                    if (j - 1 - i < 0)
                        f[j][k] = f[j - 1][k] + f[j - 1][k - 1];
                    else
                        f[j][k] = f[j - 1][k] + f[j - 1][k - 1] - f[j - 1 - i][k - 1];
            num[i] = 0;
            for (int j = 1; j <= min(n, m); ++j)
                num[i] = num[i] + ask(j, f[m][j]);
        }
        cnt = num[m];
        for (int i = m; i >= 1; --i)
            num[i] = num[i] - num[i - 1];
        for (int i = 1; i <= m; ++i)
            ans += i * num[i] / cnt;
        cout << fixed << setprecision(6) << ans << endl;
    }
    return 0;
}