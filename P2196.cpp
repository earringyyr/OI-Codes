#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, ans[2], a[50], w[50][50], f[50], nxt[50];
int dfs(int k)
{
    if (f[k] != -1)
        return f[k];
    f[k] = a[k];
    int ma = 0, id = 0;
    for (int i = k + 1; i <= n; ++i)
        if (w[k][i])
        {
            int tem = dfs(i);
            if (tem > ma)
            {
                id = i;
                ma = tem;
            }
        }
    f[k] += ma;
    nxt[k] = id;
    return f[k];
}
int main()
{
    memset(f, -1, sizeof(f));
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i < n; ++i)
        for (int j = i + 1; j <= n; ++j)
            scanf("%d", &w[i][j]);
    for (int i = 1; i <= n; ++i)
        if (f[i] == -1)
        {
            int tem = dfs(i);
            if (ans[1] < tem)
            {
                ans[0] = i;
                ans[1] = tem;
            }
        }
    int d = ans[0];
    while (d)
    {
        printf("%d ", d);
        d = nxt[d];
    }
    printf("\n%d", ans[1]);
    return 0;
}