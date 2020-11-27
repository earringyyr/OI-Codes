#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, q, pos, ans[35];
int vis[35], use[35], rev[35];
int a[155];
int len[205];
char s[205][15];
void dfs(int k, int pos)
{
    if (pos == m + 1)
    {
        ++ans[0];
        for (int i = 1; i <= n; ++i)
            ans[i] = vis[i];
        return;
    }
    int res = 0;
    for (int i = pos; i <= m; ++i)
    {
        if (vis[a[i]] == -1)
        {
            res = i - pos;
            break;
        }
        if (i == m)
            res = m - pos + 1;
    }
    for (int j = 1; j <= q; ++j)
        if (len[j] == res)
        {
            for (int i = pos; i <= m; ++i)
            {
                if (vis[a[i]] == -1)
                {
                    dfs(k + 1, i + 1);
                    break;
                }
                if (!vis[a[i]])
                {
                    if (rev[s[j][i - pos + 1] - 'a' + 1])
                        break;
                    vis[a[i]] = s[j][i - pos + 1] - 'a' + 1;
                    rev[s[j][i - pos + 1] - 'a' + 1] = 1;
                    use[a[i]] = k;
                }
                if (vis[a[i]] != s[j][i - pos + 1] - 'a' + 1)
                    break;
                if (i == m)
                    dfs(k + 1, m + 1);
            }
            for (int i = 1; i <= n; ++i)
                if (use[i] == k)
                {
                    rev[vis[i]] = 0;
                    vis[i] = 0;
                    use[i] = 0;
                }
        }
    return;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ans[0] = 0;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; ++i)
            scanf("%d", &a[i]);
        scanf("%d", &q);
        for (int i = 1; i <= q; ++i)
        {
            scanf("%s", s[i] + 1);
            len[i] = strlen(s[i] + 1);
        }
        for (int i = 1; i <= n; ++i)
            if (a[m] != i)
            {
                vis[i] = -1;
                dfs(1, 1);
                vis[i] = 0;
            }
        if (ans[0] == 0)
            puts("No solution");
        if (ans[0] > 1)
            puts("Cannot determine");
        if (ans[0] == 1)
        {
            for (int i = 1; i <= m; ++i)
                if (ans[a[i]] != -1)
                    putchar(ans[a[i]] + 'a' - 1);
                else
                    putchar(' ');
            putchar('\n');
        }
    }
    return 0;
}