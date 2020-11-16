#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m;
int a[105], b[105];
int vis[2][105], lst[2][105];
int ans[2][1000005];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        vis[0][a[i]] = 1;
        lst[0][a[i]] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &b[i]);
        vis[1][b[i]] = 1;
        lst[1][b[i]] = i;
        if (!vis[0][b[i]])
        {
            printf("NO");
            return 0;
        }
    }
    for (int i = 1; i <= n; ++i)
        if (vis[0][i] && vis[1][i] && lst[0][i] > lst[1][i])
        {
            printf("NO");
            return 0;
        }
    for (int i = n; i >= 1; --i)
    {
        if (a[i] == b[i])
            continue;
        for (int j = 1; j <= i; ++j)
            if (a[i] == a[j])
            {
                ++m;
                ans[0][m] = a[j];
                ans[1][m] = b[i];
                a[j] = b[i];
            }
    }
    printf("YES\n%d\n", m);
    for (int i = 1; i <= m; ++i)
        printf("%d %d\n", ans[0][i], ans[1][i]);
    return 0;
}