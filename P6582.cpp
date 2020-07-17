#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
const int mod = 998244353;
typedef long long ll;
int n, m, k, tot, cnt, sum, ans = 1;
int a[1005][1005], num[1005][1005], vis[1005][1005];
int gox[4] = {0, 0, 1, -1}, goy[4] = {1, -1, 0, 0};
char s[1005][1005];
void dfs(int x, int y, int fx, int fy)
{
    vis[x][y] = 1;
    for (int i = 0; i < 4; ++i)
    {
        int xx = x + gox[i], yy = y + goy[i];
        if (xx >= 1 && xx <= n && yy >= 1 && yy <= m && (xx != fx || yy != fy))
            if (a[xx][yy])
                if (vis[xx][yy])
                {
                    puts("0");
                    exit(0);
                }
                else
                    dfs(xx, yy, x, y);
    }
    return;
}
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%s", s[i] + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (s[i][j] == 'O')
                a[i][j] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (a[i][j])
            {
                int num = 0;
                for (int l = 0; l < 4; ++l)
                {
                    int x = i + gox[l], y = j + goy[l];
                    if (x >= 1 && x <= n && y >= 1 && y <= m)
                        if (a[x][y])
                            ++num;
                }
                if (num > 2)
                {
                    puts("0");
                    return 0;
                }
                if (num == 0)
                    ++tot;
                if (num == 1)
                    ++cnt;
                if (num == 2)
                    ++sum;
            }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (!vis[i][j] && a[i][j])
                dfs(i, j, i, j);
    cnt /= 2;
    sum += cnt;
    for (int i = 1; i <= tot; ++i)
        ans = (ll)ans * k % mod;
    for (int i = 1; i <= cnt; ++i)
        ans = (ll)ans * k % mod;
    for (int i = 1; i <= sum; ++i)
        ans = (ll)ans * (k - 1) % mod;
    printf("%d", ans);
    return 0;
}