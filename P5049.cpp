#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
int m, n, top, num, col, x, aa = -1, pp;
int sum[500005], l[500005];
int dfn[500005], vis[500005], co[500005], s[500005], low[500005];
int cnt[500005];
vector<int> a[500005];
void targan(int k, int fa)
{
    s[++top] = k;
    dfn[k] = ++num;
    low[k] = dfn[k];
    vis[k] = 1;
    for (int i = 0; i < sum[k]; ++i)
        if (a[k][i] != fa)
        {
            if (!vis[a[k][i]])
            {
                targan(a[k][i], k);
                low[k] = min(low[k], low[a[k][i]]);
            }
            else if (!co[a[k][i]])
                low[k] = min(low[k], low[a[k][i]]);
        }
    if (dfn[k] == low[k])
    {
        col++;
        while (dfn[s[top]] != low[s[top]])
        {
            cnt[col]++;
            co[s[top]] = col;
            top--;
        }
        cnt[col]++;
        co[s[top]] = col;
        top--;
    }
    return;
}
void dfs(int k, int fa)
{
    int aaa = aa;
    vis[k] = 1;
    l[++num] = k;
    for (int i = 0; i < sum[k]; ++i)
        if (!vis[a[k][i]])
        {
            if ((i == sum[k] - 1 || (i == sum[k] - 2 && a[k][sum[k] - 1] == fa)) && !pp && co[k] == x && co[a[k][i]] == x && aaa != -1 && a[k][i] > aaa)
            {
                pp = 1;
                return;
            }
            if (i == sum[k] - 1 || (i == sum[k] - 2 && a[k][sum[k] - 1] == fa))
                aa = aaa;
            else
            {
                if (a[k][i + 1] == fa)
                    aa = a[k][i + 2];
                else
                    aa = a[k][i + 1];
            }
            dfs(a[k][i], k);
        }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ++sum[u];
        ++sum[v];
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i)
        sort(a[i].begin(), a[i].end());
    targan(1, 0);
    num = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= col; ++i)
        if (cnt[i] > 1)
        {
            x = i;
            break;
        }
    dfs(1, 0);
    for (int i = 1; i <= num; ++i)
        cout << l[i] << " ";
    return 0;
}