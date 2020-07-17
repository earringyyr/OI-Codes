#include <iostream>
#include <cstdio>
using namespace std;
double x, num, sum, w[35], v[35];
int n, len, vis[35], ans[35];
void dfs(int k)
{
    if (num > x)
        return;
    if (k == n + 1)
    {
        if ((int)sum > ans[0])
        {
            ans[0] = sum;
            len = 0;
            for (int i = 1; i <= n; ++i)
                if (vis[i])
                    ans[++len] = i;
        }
        return;
    }
    dfs(k + 1);
    vis[k] = 1;
    num += w[k];
    sum += v[k];
    dfs(k + 1);
    vis[k] = 0;
    num -= w[k];
    sum -= v[k];
    return;
}
int main()
{
    scanf("%lf%d", &x, &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lf%lf", &w[i], &v[i]);
    dfs(1);
    printf("%d\n", ans[0]);
    for (int i = 1; i <= len; ++i)
        printf("%d ", ans[i]);
    return 0;
}
