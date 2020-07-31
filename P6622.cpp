#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, k, num = 1;
int s[100005], cnt[25][25], lg[1 << 23], f[1 << 23], dis[1 << 23], g[1 << 22][23];
int lowbit(int x)
{
    return x & -x;
}
int main()
{
    memset(f, 0x7f, sizeof(f));
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &s[i]);
        --s[i];
    }
    for (int i = 1; i < n; ++i)
        ++cnt[s[i]][s[i + 1]];
    for (int i = 2; i < (1 << m); ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j)
            if (i != j)
                g[0][i] += k * cnt[j][i] - cnt[i][j];
    f[0] = 0;
    dis[0] = 1;
    for (int i = 1; i < (1 << m); ++i)
        dis[i] = dis[i - lowbit(i)] + 1;
    for (int i = 0; i < (1 << m); ++i)
        for (int j = 0; j < m; ++j)
            if (!(i & (1 << j)))
            {
                int l = (i >> (j + 1) << j) + (i - (i >> j << j));
                if (i != 0)
                {
                    int pos = lg[lowbit(i)];
                    if (pos > j)
                        g[l][j] = g[l - (lowbit(i) >> 1)][j];
                    else
                        g[l][j] = g[l - lowbit(i)][j];
                    g[l][j] -= k * cnt[lg[lowbit(i)]][j] - cnt[j][lg[lowbit(i)]];
                    g[l][j] += k * cnt[j][lg[lowbit(i)]] + cnt[lg[lowbit(i)]][j];
                }
                f[i + (1 << j)] = min(f[i + (1 << j)], f[i] + dis[i] * g[l][j]);
            }
    printf("%d", f[(1 << m) - 1]);
    return 0;
}