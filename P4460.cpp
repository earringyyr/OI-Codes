#include <iostream>
#include <cstdio>
using namespace std;
const int mod = 100000007;
int n, num, now, cnt, ans, top1, top2, x[25], y[25], vis[2][25], use[25][25], f[2000005][25];
inline void dfs(int k, int num)
{
    if (k == n + 1)
    {
        if (cnt >= 4)
            for (register int i = 1; i <= top1; ++i)
                ans = (ans + f[now][vis[0][i]]) % mod;
        for (register int i = 1; i <= top1; ++i)
            for (register int j = 1; j <= top2; ++j)
                if ((use[vis[0][i]][vis[1][j]] & now) == use[vis[0][i]][vis[1][j]])
                    f[now | (1 << (vis[1][j] - 1))][vis[1][j]] = (f[now | (1 << (vis[1][j] - 1))][vis[1][j]] + f[now][vis[0][i]]) % mod;
        return;
    }
    if (num)
    {
        vis[0][++top1] = k;
        now += (1 << (k - 1));
        dfs(k + 1, num - 1);
        --top1;
        now -= (1 << (k - 1));
    }
    if (k + num <= n)
    {
        vis[1][++top2] = k;
        dfs(k + 1, num);
        --top2;
    }
    return;
}
int main()
{
    scanf("%d", &n);
    for (register int i = 1; i <= n; ++i)
        scanf("%d%d", &x[i], &y[i]);
    for (register int i = 1; i <= n; ++i)
        for (register int j = 1; j <= n; ++j)
            if (i != j)
                for (register int k = 1; k <= n; ++k)
                    if (k != i && k != j)
                        if ((x[k] - x[i]) * (y[j] - y[i]) == (x[j] - x[i]) * (y[k] - y[i]))
                            if ((x[i] <= x[k] && x[k] <= x[j]) || (x[i] >= x[k] && x[k] >= x[j]))
                                if ((y[i] <= y[k] && y[k] <= y[j]) || (y[i] >= y[k] && y[k] >= y[j]))
                                    use[i][j] += (1 << (k - 1));
    for (register int i = 1; i <= n; ++i)
        f[1 << (i - 1)][i] = 1;
    for (register int i = 1; i < n; ++i)
    {
        cnt = i;
        dfs(1, i);
    }
    for (register int i = 1; i <= n; ++i)
        now += (1 << (i - 1));
    for (register int i = 1; i <= n; ++i)
        ans = (ans + f[now][i]) % mod;
    printf("%d", ans);
    return 0;
}
