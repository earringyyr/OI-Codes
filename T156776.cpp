#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, cnt = 1, rt;
int sum[2];
int c[200005], id[200005], dis[200005];
int head[2][200005];
struct node
{
    int v;
    int nxt;
} a[2][400005];
void ins(int id, int u, int v)
{
    ++sum[id];
    a[id][sum[id]].v = v;
    a[id][sum[id]].nxt = head[id][u];
    head[id][u] = sum[id];
    return;
}
void dfs1(int k, int fa)
{
    int d = head[0][k];
    while (d)
    {
        if (a[0][d].v != fa)
        {
            if (c[a[0][d].v] != c[k])
            {
                id[a[0][d].v] = ++cnt;
                ins(1, id[k], id[a[0][d].v]);
                ins(1, id[a[0][d].v], id[k]);
            }
            else
                id[a[0][d].v] = id[k];
            dfs1(a[0][d].v, k);
        }
        d = a[0][d].nxt;
    }
    return;
}
void dfs2(int k, int fa)
{
    if (dis[k] > dis[rt])
        rt = k;
    int d = head[1][k];
    while (d)
    {
        if (a[1][d].v != fa)
        {
            dis[a[1][d].v] = dis[k] + 1;
            dfs2(a[1][d].v, k);
        }
        d = a[1][d].nxt;
    }
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &c[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(0, u, v);
        ins(0, v, u);
    }
    id[1] = 1;
    dfs1(1, 0);
    dfs2(1, 0);
    dis[rt] = 0;
    dfs2(rt, 0);
    printf("%d", (dis[rt] + 1) / 2);
    return 0;
}