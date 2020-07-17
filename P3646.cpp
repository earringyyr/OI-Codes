#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, a, b, y[2005], g[2005], f[2005][2005];
long long num, sum[2005];
int main()
{
    scanf("%d%d%d", &n, &a, &b);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &y[i]);
        sum[i] = sum[i - 1] + y[i];
    }
    if (a == 1)
    {
        num = (1LL << 41) - 1;
        for (int l = 40; l >= 0; --l)
        {
            memset(g, 0x7f, sizeof(g));
            g[0] = 0;
            num -= (1LL << l);
            for (int i = 1; i <= n; ++i)
                for (int j = 0; j < i; ++j)
                    if (((sum[i] - sum[j]) | num) == num)
                        g[i] = min(g[i], g[j] + 1);
            if (g[n] > b)
                num += (1LL << l);
        }
        printf("%lld", num);
        return 0;
    }
    num = (1LL << 41) - 1;
    for (int l = 40; l >= 0; --l)
    {
        num -= (1LL << l);
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= min(i, b); ++j)
                for (int k = j - 1; k < i; ++k)
                    if (f[k][j - 1] && ((sum[i] - sum[k]) | num) == num)
                    {
                        f[i][j] = 1;
                        break;
                    }
        num += (1LL << l);
        for (int i = a; i <= b; ++i)
            if (f[n][i])
            {
                num -= (1LL << l);
                break;
            }
    }
    printf("%lld", num);
    return 0;
}