#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
int n, sum, col, top;
int head[200005], co[200005], in[200005], vis[200005], pre[200005], suf[200005], frt[200005], bck[200005];
long long cnt, num, ans;
long long tot[200005], ww[200005], dis[200005], len[200005][3];
queue<int> q;
struct node
{
    int v;
    int w;
    int next;
} a[400005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
long long dfs(int k, int fa, int w)
{
    int d = head[k];
    long long ma[2] = {0};
    while (d)
    {
        if (a[d].v != fa && co[a[d].v])
        {
            cnt += a[d].w;
            long long l = dfs(a[d].v, k, a[d].w);
            cnt -= a[d].w;
            if (l > ma[0])
            {
                ma[1] = ma[0];
                ma[0] = l;
            }
            else if (l > ma[1])
                ma[1] = l;
        }
        d = a[d].next;
    }
    ans = max(ans, max(ma[0] + ma[1], ma[0] + cnt));
    return ma[0] + w;
}
void solve(int k)
{
    tot[++col] = dfs(k, k, 0);
    vis[k] = 1;
    int d = head[k];
    while (d)
    {
        if (!co[a[d].v] && !vis[a[d].v])
        {
            cnt = 0;
            ++col;
            ww[col] = a[d].w;
            vis[a[d].v] = 1;
            tot[col] = dfs(a[d].v, a[d].v, 0);
            d = head[a[d].v];
            continue;
        }
        if (a[d].v == k)
            ww[1] = a[d].w;
        d = a[d].next;
    }
    top = 1;
    dis[1] = ww[1];
    for (int i = 2; i <= col; ++i)
    {
        dis[i] = dis[i - 1] + ww[i];
        num = max(num, dis[i] - dis[top] + tot[top] + tot[i]);
        if (tot[i] - dis[i] > tot[top] - dis[top])
            top = i;
    }
    pre[1] = 1;
    frt[1] = 1;
    len[1][0] = 0;
    for (int i = 2; i < col; ++i)
    {
        pre[i] = pre[i - 1];
        frt[i] = frt[i - 1];
        len[i][0] = max(len[i - 1][0], dis[i] - dis[pre[i]] + tot[i] + tot[pre[i]]);
        if (tot[i] - dis[i] > tot[pre[i]] - dis[pre[i]])
            pre[i] = i;
        if (dis[i] + tot[i] > dis[frt[i]] + tot[frt[i]])
            frt[i] = i;
    }
    suf[col - 1] = col;
    bck[col - 1] = col;
    len[col - 1][1] = 0;
    for (int i = col - 2; i >= 1; --i)
    {
        suf[i] = suf[i + 1];
        bck[i] = bck[i + 1];
        len[i][1] = max(len[i + 1][1], dis[bck[i]] - dis[i + 1] + tot[bck[i]] + tot[i + 1]);
        if (tot[i + 1] - dis[i + 1] > tot[suf[i]] - dis[suf[i]])
            suf[i] = i + 1;
        if (dis[i + 1] + tot[i + 1] > dis[bck[i]] + tot[bck[i]])
            bck[i] = i + 1;
    }
    for (int i = 1; i < col; ++i)
    {
        len[i][2] = dis[frt[i]] + dis[col] - dis[suf[i]] + tot[frt[i]] + tot[suf[i]];
        num = min(num, max(len[i][0], max(len[i][1], len[i][2])));
    }
    ans = max(ans, num);
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int x, y, l;
        scanf("%d%d%d", &x, &y, &l);
        ++in[x];
        ++in[y];
        ins(x, y, l);
        ins(y, x, l);
    }
    for (int i = 1; i <= n; ++i)
        if (in[i] == 1)
            q.push(i);
    while (!q.empty())
    {
        int k = q.front();
        q.pop();
        co[k] = 1;
        int d = head[k];
        while (d)
        {
            --in[a[d].v];
            if (in[a[d].v] == 1)
                q.push(a[d].v);
            d = a[d].next;
        }
    }
    for (int i = 1; i <= n; ++i)
        if (!co[i] && !vis[i])
            solve(i);
    printf("%lld", ans);
    return 0;
}