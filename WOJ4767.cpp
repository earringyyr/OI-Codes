#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int t, n;
long long a[200005], b[200005], f[200005][3];
char c[200005];
int main()
{
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        scanf("%d", &n);
        b[1] = 1;
        for (int i = 1; i < n; ++i)
        {
            scanf("%lld %c", &a[i], &c[i + 1]);
            if (c[i + 1] == '+')
                b[i + 1] = 1;
            else
                b[i + 1] = -1;
        }
        scanf("%lld", &a[n]);
        f[0][0] = 0;
        f[0][1] = -1000000000000000000;
        f[0][2] = -1000000000000000000;
        for (int i = 1; i <= n; ++i)
            if (b[i] == 1)
            {
                f[i][0] = max(max(f[i - 1][0] + a[i], f[i - 1][1] + a[i]), f[i - 1][2] + a[i]);
                f[i][1] = max(f[i - 1][1] - a[i], f[i - 1][2] - a[i]);
                f[i][2] = f[i - 1][2] + a[i];
            }
            else
            {
                f[i][0] = -1000000000000000000;
                f[i][1] = max(max(f[i - 1][0] - a[i], f[i - 1][1] - a[i]), f[i - 1][2] - a[i]);
                f[i][2] = max(f[i - 1][1] + a[i], f[i - 1][2] + a[i]);
            }
        printf("%lld\n", max(max(f[n][0], f[n][1]), f[n][2]));
    }
    return 0;
}