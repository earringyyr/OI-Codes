#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define pii pair<int, int>
#define mp make_pair
int n, m, pos, posy, ans;
int vis[25], minx[25];
struct node
{
    int x;
    int y;
    int len;
} f[25], g[55];
vector<pii> tube[25];
bool cmp(pii aa, pii bb)
{
    return aa.second > bb.second;
}
void dfs1(int k, int h)
{
    vis[k] = 1;
    int siz = tube[k].size();
    for (int i = 0; i < siz; ++i)
    {
        pii tmp = tube[k][i];
        if (tmp.second >= h && !vis[tmp.first])
            dfs1(tmp.first, h);
    }
    return;
}
void dfs2(int k, int maxn)
{
    if (minx[k] >= maxn)
        return;
    minx[k] = maxn;
    int siz = tube[k].size();
    for (int i = 0; i < siz; ++i)
    {
        pii tmp = tube[k][i];
        if (vis[tmp.first])
            dfs2(tmp.first, min(maxn, tmp.second));
    }
    return;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ans = 0;
        scanf("%d", &n);
        memset(minx, 128, sizeof(minx));
        for (int i = 1; i <= n; ++i)
            tube[i].clear();
        for (int i = 1; i <= n; ++i)
            scanf("%d%d%d", &f[i].x, &f[i].y, &f[i].len);
        scanf("%d", &m);
        for (int i = 1; i <= m; ++i)
            scanf("%d%d%d", &g[i].x, &g[i].y, &g[i].len);
        scanf("%d", &pos);
        scanf("%d", &posy);
        if (f[pos].y > posy || f[pos].y + f[pos].len < posy)
        {
            puts("No Solution");
            continue;
        }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                for (int k = 1; k <= m; ++k)
                {
                    if (g[k].x != f[i].x + 1 || g[k].x + g[k].len != f[j].x)
                        continue;
                    if (g[k].y < f[i].y || g[k].y > f[i].y + f[i].len)
                        continue;
                    if (g[k].y < f[j].y || g[k].y > f[j].y + f[j].len)
                        continue;
                    tube[i].push_back(mp(j, g[k].y));
                    tube[j].push_back(mp(i, g[k].y));
                }
        for (int i = 1; i <= n; ++i)
            sort(tube[i].begin(), tube[i].end(), cmp);
        int flg = 0;
        for (int i = min(f[1].y + f[1].len, posy); i >= 0; --i)
        {
            memset(vis, 0, sizeof(vis));
            dfs1(1, i);
            if (vis[pos])
            {
                dfs2(pos, posy);
                for (int j = 1; j <= n; ++j)
                    if (vis[j])
                    {
                        ans += f[j].y + f[j].len - minx[j];
                        if (f[j].y >= minx[j] && (j != 1 || posy == f[j].y))
                        {
                            flg = 1;
                            puts("No Solution");
                            break;
                        }
                    }
                if (!flg)
                {
                    flg = 1;
                    printf("%d\n", ans);
                }
                break;
            }
        }
        if (!flg)
            puts("No Solution");
    }
    return 0;
}