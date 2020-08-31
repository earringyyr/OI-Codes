#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, K, sum, head[500005], siz[500005];
ll f[500005], g[500005], len[500005][2];
struct node
{
    int v;
    int w;
    int nxt;
} a[1000005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs1(int k, int fa)
{
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs1(a[d].v, k);
            siz[k] += siz[a[d].v];
            if (siz[a[d].v])
            {
                f[k] += f[a[d].v] + 2 * a[d].w;
                if (len[a[d].v][0] + a[d].w > len[k][0])
                {
                    len[k][1] = len[k][0];
                    len[k][0] = len[a[d].v][0] + a[d].w;
                }
                else if (len[a[d].v][0] + a[d].w > len[k][1])
                    len[k][1] = len[a[d].v][0] + a[d].w;
            }
        }
        d = a[d].nxt;
    }
    return;
}
void dfs2(int k, int fa)
{
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            if (siz[a[d].v] == K)
                g[a[d].v] = f[a[d].v];
            else if (!siz[a[d].v])
            {
                g[a[d].v] = g[k] + 2 * a[d].w;
                len[a[d].v][0] = len[k][0] + a[d].w;
            }
            else
            {
                g[a[d].v] = g[k];
                if (len[k][0] == len[k][1])
                {
                    if (len[k][0] + a[d].w > len[a[d].v][0])
                    {
                        len[a[d].v][1] = len[a[d].v][0];
                        len[a[d].v][0] = len[k][0] + a[d].w;
                    }
                    else if (len[k][0] + a[d].w > len[a[d].v][1])
                        len[a[d].v][1] = len[k][0] + a[d].w;
                }
                else
                {
                    if (len[a[d].v][0] + a[d].w == len[k][0])
                    {
                        if (len[k][1] + a[d].w > len[a[d].v][0])
                        {
                            len[a[d].v][1] = len[a[d].v][0];
                            len[a[d].v][0] = len[k][1] + a[d].w;
                        }
                        else if (len[k][1] + a[d].w > len[a[d].v][1])
                            len[a[d].v][1] = len[k][1] + a[d].w;
                    }
                    else
                    {
                        if (len[k][0] + a[d].w > len[a[d].v][0])
                        {
                            len[a[d].v][1] = len[a[d].v][0];
                            len[a[d].v][0] = len[k][0] + a[d].w;
                        }
                        else if (len[k][0] + a[d].w > len[a[d].v][1])
                            len[a[d].v][1] = len[k][0] + a[d].w;
                    }
                }
            }
            dfs2(a[d].v, k);
        }
        d = a[d].nxt;
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &K);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        ins(u, v, w);
        ins(v, u, w);
    }
    for (int i = 1; i <= K; ++i)
    {
        int pos;
        scanf("%d", &pos);
        siz[pos] = 1;
    }
    dfs1(1, 0);
    g[1] = f[1];
    dfs2(1, 0);
    for (int i = 1; i <= n; ++i)
        printf("%lld\n", g[i] - len[i][0]);
    return 0;
}