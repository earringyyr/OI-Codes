#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, m, num, ans;
int vis[2005][2005];
int f[100005];
void dfs(int x, int y)
{
    if (x == n + 1)
    {
        if (num)
            return;
        for (int i = 1; i <= n; ++i)
        {
            int cnt = 0;
            for (int j = 1; j <= m; ++j)
                if (vis[i][j])
                    ++cnt;
            if (cnt > 2)
                return;
        }
        for (int i = 1; i <= m; ++i)
        {
            int cnt = 0;
            for (int j = 1; j <= n; ++j)
                if (vis[j][i])
                    ++cnt;
            if (cnt > 2)
                return;
        }
        ++ans;
        return;
    }
    if (y == m + 1)
    {
        dfs(x + 1, 1);
        return;
    }
    dfs(x, y + 1);
    if (num)
    {
        --num;
        vis[x][y] = 1;
        dfs(x, y + 1);
        ++num;
        vis[x][y] = 0;
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    if (n == m)
    {
        f[1] = 0;
        f[2] = 1;
        f[3] = 6;
        for (int i = 4; i <= n; ++i)
            f[i] = (ll)499122177 * i % mod * (i - 1) % mod * (i - 1) % mod * ((ll)(2 * i - 3) * f[i - 2] % mod + (ll)(i - 2) * (i - 2) % mod * f[i - 3] % mod) % mod;
        printf("%d", f[n]);
        return 0;
    }
    num = 2 * n;
    dfs(1, 1);
    printf("%d", ans);
    return 0;
}