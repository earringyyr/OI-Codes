#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n, sum, head[1005], siz[1005], f[1005][1005], dp[1005][1005], c[1005][1005];
struct node
{
    int v;
    int nxt;
    int type;
} a[2005];
void ins(int u, int v, int type)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    a[sum].type = type;
    head[u] = sum;
    return;
}
int C(int x, int y)
{
    if (x < 0 || y < 0 || x < y)
        return 0;
    return c[x][y];
}
void dfs(int k, int fa)
{
    siz[k] = 1;
    f[k][1] = 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs(a[d].v, k);
            siz[k] += siz[a[d].v];
            if (a[d].type)
            {
                for (int i = siz[k]; i >= 1; --i)
                {
                    int tmp = 0;
                    for (int j = max(1, i - siz[a[d].v] + 1); j <= min(siz[k] - siz[a[d].v], i); ++j)
                        tmp = (tmp + (ll)f[k][j] * (dp[a[d].v][siz[a[d].v]] - dp[a[d].v][i - j] + mod) % mod * C(i - 1, j - 1) % mod * C(siz[k] - i, siz[k] - siz[a[d].v] - j) % mod) % mod;
                    f[k][i] = tmp;
                }
            }
            else
            {
                for (int i = siz[k]; i >= 1; --i)
                {
                    int tmp = 0;
                    for (int j = 1; j <= min(siz[k] - siz[a[d].v], i - 1); ++j)
                        tmp = (tmp + (ll)f[k][j] * dp[a[d].v][min(siz[a[d].v], i - j)] % mod * C(i - 1, j - 1) % mod * C(siz[k] - i, siz[k] - siz[a[d].v] - j) % mod) % mod;
                    f[k][i] = tmp;
                }
            }
        }
        d = a[d].nxt;
    }
    for (int i = 1; i <= siz[k]; ++i)
        dp[k][i] = (dp[k][i - 1] + f[k][i]) % mod;
    return;
}
int main()
{
    for (int i = 0; i <= 1000; ++i)
        c[i][0] = 1;
    for (int i = 1; i <= 1000; ++i)
        for (int j = 1; j <= i; ++j)
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
    int T;
    scanf("%d", &T);
    while (T--)
    {
        sum = 0;
        memset(head, 0, sizeof(head));
        memset(f, 0, sizeof(f));
        scanf("%d", &n);
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            char type;
            scanf("%d %c%d", &u, &type, &v);
            ++u;
            ++v;
            if (type == '<')
            {
                ins(u, v, 1);
                ins(v, u, 0);
            }
            else
            {
                ins(u, v, 0);
                ins(v, u, 1);
            }
        }
        dfs(1, 0);
        printf("%d\n", dp[1][n]);
    }
    return 0;
}