#include <iostream>
#include <cstdio>
using namespace std;
int m, s, top, num[505], p[10005], vis[505][505];
void dfs(int k)
{
    for (int i = 1; i <= 500; ++i)
        if (vis[k][i])
        {
            --vis[k][i];
            --vis[i][k];
            dfs(i);
        }
    p[++top] = k;
}
int main()
{
    s = -1;
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ++num[u];
        ++num[v];
        ++vis[u][v];
        ++vis[v][u];
        if (s == -1)
            s = min(u, v);
        else
            s = min(s, min(u, v));
    }
    for (int i = 1; i <= 500; ++i)
        if (num[i] & 1)
        {
            s = i;
            break;
        }
    dfs(s);
    for (int i = top; i >= 1; --i)
        printf("%d\n", p[i]);
    return 0;
}