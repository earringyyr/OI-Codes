#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int n, m, K, tim, uu, vv;
int mch[105], pr[105], vis[105];
int mp[105][105];
vector<int> g[105];
bool dfs(int k)
{
    for (int i = 0; i < g[k].size(); ++i)
        if (vis[g[k][i]] != tim && !pr[g[k][i]])
        {
            if (k == uu && g[k][i] == vv)
                continue;
            vis[g[k][i]] = tim;
            if (!mch[g[k][i]] || dfs(mch[g[k][i]]))
            {
                mch[g[k][i]] = k;
                return true;
            }
        }
    return false;
}
int check(int k)
{
    memset(mch, 0, sizeof(mch));
    for (int i = k + 1; i <= n; ++i)
    {
        ++tim;
        if (!dfs(i))
            return 0;
    }
    for (int i = 1; i <= n; ++i)
        if (!pr[i])
        {
            uu = mch[i];
            vv = i;
            mch[i] = 0;
            ++tim;
            if (dfs(uu))
            {
                uu = 0;
                vv = 0;
                return 2;
            }
            mch[i] = uu;
            uu = 0;
            vv = 0;
        }
    return 1;
}
void solve(int k)
{
    if (k == n + 1)
    {
        --K;
        return;
    }
    if (K == 0)
        return;
    for (int i = 0; i < g[k].size(); ++i)
        if (!pr[g[k][i]])
        {
            pr[g[k][i]] = k;
            int tmp = check(k);
            if (tmp == 1)
                --K;
            if (tmp == 2)
                solve(k + 1);
            pr[g[k][i]] = 0;
            if (K == 0)
                return;
        }
    return;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(pr, 0, sizeof(pr));
        memset(vis, 0, sizeof(vis));
        memset(mp, 0, sizeof(mp));
        for (int i = 1; i <= n; ++i)
            g[i].clear();
        scanf("%d%d%d", &n, &m, &K);
        ++K;
        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            v -= n;
            if (!mp[u][v])
            {
                mp[u][v] = 1;
                g[u].push_back(v);
            }
        }
        solve(1);
        if (K == 0)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}