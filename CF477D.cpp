#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007, inf = 0x7f7f7f7f;
int n, cnt, tot, minx, id, ans;
int dfn[25000005];
int tr[25000005][2];
int pos[5005][5005];
int f[5005][5005];
char s[5005];
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
    id = -1;
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i)
    {
        int rt = 0;
        for (int j = i; j <= n; ++j)
        {
            int k = s[j] - '0';
            if (!tr[rt][k])
                tr[rt][k] = ++cnt;
            rt = tr[rt][k];
            pos[i][j] = rt;
        }
    }
    dfs(0);
    for (int i = 1; i <= n; ++i)
    {
        f[i][1] = 1;
        for (int j = 2; j <= i; ++j)
            if (s[j] == '1')
            {
                if (i - j + 1 > j - 1)
                    f[i][j] = f[j - 1][1];
                else
                {
                    f[i][j] = f[j - 1][2 * j - i];
                    if (dfn[pos[2 * j - i - 1][j - 1]] <= dfn[pos[j][i]])
                        f[i][j] = f[j - 1][2 * j - i - 1];
                }
            }
        for (int j = i; j >= 1; --j)
            f[i][j] = (f[i][j + 1] + f[i][j]) % mod;
    }
    ans = f[n][1];
    for (int i = 1; i <= n; ++i)
    {
        memset(f[i], 127, sizeof(f[i]));
        f[i][1] = 1;
        for (int j = 2; j <= i; ++j)
            if (s[j] == '1')
            {
                if (i - j + 1 > j - 1)
                    f[i][j] = f[j - 1][1];
                else
                {
                    f[i][j] = f[j - 1][2 * j - i];
                    if (dfn[pos[2 * j - i - 1][j - 1]] <= dfn[pos[j][i]])
                        f[i][j] = f[j - 1][2 * j - i - 1];
                }
                ++f[i][j];
            }
        for (int j = i; j >= 1; --j)
            f[i][j] = min(f[i][j + 1], f[i][j]);
    }
    for (int i = n; i >= 1; --i)
        if (f[n][i] < inf)
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
                if (num1 + f[n][id] > num2 + f[n][i])
                    id = i;
            }
        }
    for (int i = id; i <= n; ++i)
        minx = ((minx << 1) + s[i] - '0') % mod;
    minx = (minx + f[n][id]) % mod;
    printf("%d\n%d", ans, minx);
    return 0;
}