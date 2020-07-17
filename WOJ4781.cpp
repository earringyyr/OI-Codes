#include <iostream>
#include <cstdio>
using namespace std;
int n, g[5005][5005];
long long sum[5005], f[5005][5005];
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
inline int read()
{
    int x = 0, f = 1;
    char c = gc();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = gc();
    }
    while (isdigit(c))
    {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = gc();
    }
    return x * f;
}
int main()
{
    n = read();
    for (register int i = 1; i <= n; ++i)
    {
        sum[i] = read();
        sum[i] += sum[i - 1];
    }
    for (register int i = 1; i <= n; ++i)
    {
        f[i][i] = sum[i] - sum[i - 1];
        g[i][i] = i;
    }
    for (register int i = 1; i < n; ++i)
        for (register int j = 1; j + i <= n; ++j)
        {
            int k = j + i;
            f[j][k] = 0x7f7f7f7f7f7f7f7f;
            for (register int l = g[j][k - 1]; l <= g[j + 1][k]; ++l)
                if (f[j][l - 1] + f[l + 1][k] < f[j][k])
                    f[j][k] = f[j][l - 1] + f[l + 1][k], g[j][k] = l;
            f[j][k] += sum[k] - sum[j - 1];
        }
    printf("%lld\n", f[1][n]);
    return 0;
}
