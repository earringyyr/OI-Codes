#include <iostream>
#include <cstdio>
using namespace std;
int n, m, k, vis[1005][1005];
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            int a;
            scanf("%d", &a);
            if (!vis[a][j])
                ++vis[a][0];
            vis[a][j] = 1;
        }
    for (int i = 1; i <= k; ++i)
        printf("%d ", vis[i][0]);
    return 0;
}