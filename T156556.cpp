#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007, inf = 0x7f7f7f7f;
int n, cnt, tot, minx, id;
int dfn[4000005];
int tr[4000005][2];
int pos[2005][2005];
int f[2005][2005], g[2005][2005];
int ff[2005][2005], gg[2005][2005];
char s[2005];
void dfs(int k)
{
    dfn[k] = ++tot;
    if (tr[k][0])
        dfs(tr[k][0]);
    if (tr[k][1])
        dfs(tr[k][1]);
    return;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        cnt = 0;
        tot = 0;
        minx = 0;
        id = -1;
        memset(tr[0], 0, sizeof(tr[0]));
        scanf("%s", s + 1);
        n = strlen(s + 1);
        for (int i = 1; i <= n; ++i)
        {
            int rt = 0;
            for (int j = i; j <= n; ++j)
            {
                int k = s[j] - '0';
                if (!tr[rt][k])
                {
                    tr[rt][k] = ++cnt;
                    memset(tr[cnt], 0, sizeof(tr[cnt]));
                }
                rt = tr[rt][k];
                pos[i][j] = rt;
            }
        }
        dfs(0);
        for (int i = 1; i <= n; ++i)
        {
            memset(f[i], 0, sizeof(f[i]));
            memset(g[i], 127, sizeof(g[i]));
            memset(ff[i], 0, sizeof(ff[i]));
            memset(gg[i], 127, sizeof(gg[i]));
            f[i][1] = 1;
            g[i][1] = 1;
            for (int j = 2; j <= i; ++j)
                if (s[j] == '1')
                {
                    if (i - j + 1 > j - 1)
                    {
                        f[i][j] = ff[j - 1][1];
                        g[i][j] = gg[j - 1][1];
                    }
                    else
                    {
                        f[i][j] = ff[j - 1][2 * j - i];
                        g[i][j] = gg[j - 1][2 * j - i];
                        if (dfn[pos[2 * j - i - 1][j - 1]] <= dfn[pos[j][i]])
                        {
                            f[i][j] = (f[i][j] + f[j - 1][2 * j - i - 1]) % mod;
                            g[i][j] = min(g[i][j], g[j - 1][2 * j - i - 1]);
                        }
                    }
                    ++g[i][j];
                }
            for (int j = i; j >= 1; --j)
            {
                ff[i][j] = (ff[i][j + 1] + f[i][j]) % mod;
                gg[i][j] = min(gg[i][j + 1], g[i][j]);
            }
        }
        for (int i = n; i >= 1; --i)
            if (g[n][i] < inf)
            {
                if (id == -1)
                    id = i;
                else
                {
                    if (n - i + 1 > 30)
                        continue;
                    int num1 = 0, num2 = 0;
                    for (int j = id; j <= n; ++j)
                        num1 = (num1 << 1) + s[j] - '0';
                    for (int j = i; j <= n; ++j)
                        num2 = (num2 << 1) + s[j] - '0';
                    if (num1 + g[n][id] > num2 + g[n][i])
                        id = i;
                }
            }
        for (int i = id; i <= n; ++i)
            minx = ((minx << 1) + s[i] - '0') % mod;
        minx = (minx + g[n][id]) % mod;
        printf("%d %d\n", minx, ff[n][1]);
    }
    return 0;
}