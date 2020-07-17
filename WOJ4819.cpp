#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
int n, k, t, lx, rx, r, g, b, sum, cnt, xt[15], yt[15], use[15], aa[505][505], head[505][505], vis[505][505];
long long ans = -0x7f7f7f7f7f7f7f7f, num, dis[505][505], w[15][15];
char s[505];
struct node
{
    int x;
    int y;
    long long dis;
    node(int aa, int bb, long long cc)
    {
        x = aa;
        y = bb;
        dis = cc;
    }
    bool operator<(const node &bb) const
    {
        return dis > bb.dis;
    }
};
priority_queue<node> q;
struct point
{
    int x;
    int y;
    int w;
    int nxt;
} a[2000005];
void ins(int x, int y, int xx, int yy, int w)
{
    ++sum;
    a[sum].x = xx;
    a[sum].y = yy;
    a[sum].w = w;
    a[sum].nxt = head[x][y];
    head[x][y] = sum;
    return;
}
void dijkstra(int x, int y)
{
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x7f, sizeof(dis));
    dis[x][y] = 0;
    q.push(node(x, y, 0));
    while (!q.empty())
    {
        node id = q.top();
        q.pop();
        int kx = id.x, ky = id.y;
        if (vis[kx][ky])
            continue;
        vis[kx][ky] = 1;
        int d = head[kx][ky];
        while (d)
        {
            int xx = a[d].x, yy = a[d].y;
            if (dis[a[d].x][a[d].y] > dis[kx][ky] + a[d].w)
            {
                dis[a[d].x][a[d].y] = dis[kx][ky] + a[d].w;
                q.push(node(a[d].x, a[d].y, dis[a[d].x][a[d].y]));
            }
            d = a[d].nxt;
        }
    }
    return;
}
void dfs(int id)
{
    if (cnt >= lx && cnt <= rx)
        ans = max(ans, num);
    if (cnt == rx)
        return;
    ++cnt;
    num += t;
    for (int i = 1; i <= k; ++i)
        if (!use[i])
        {
            use[i] = 1;
            num -= w[id][i];
            dfs(i);
            num += w[id][i];
            use[i] = 0;
        }
    num -= t;
    --cnt;
    return;
}
int main()
{
    scanf("%d%d%d%d%d%d%d%d", &n, &k, &t, &lx, &rx, &r, &g, &b);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", s + 1);
        for (int j = 1; j <= n; ++j)
            if (s[j] == 'S')
            {
                xt[0] = i;
                yt[0] = j;
            }
            else if (s[j] == 'T')
            {
                ++cnt;
                xt[cnt] = i;
                yt[cnt] = j;
            }
            else if (s[j] == 'R')
                aa[i][j] = r;
            else if (s[j] == 'G')
                aa[i][j] = g;
            else if (s[j] == 'B')
                aa[i][j] = b;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            if (i != 1)
                ins(i, j, i - 1, j, aa[i - 1][j]);
            if (i != n)
                ins(i, j, i + 1, j, aa[i + 1][j]);
            if (j != 1)
                ins(i, j, i, j - 1, aa[i][j - 1]);
            if (j != n)
                ins(i, j, i, j + 1, aa[i][j + 1]);
        }
    for (int i = 0; i <= k; ++i)
    {
        dijkstra(xt[i], yt[i]);
        for (int j = 1; j <= k; ++j)
            w[i][j] = dis[xt[j]][yt[j]];
    }
    cnt = 0;
    dfs(0);
    printf("%lld", ans);
}