#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
int n, sum, col, head[1000005], fa[1000005], co[1000005], in[1000005], vis[1000005], len[1000005], s[2000005];
long long cnt, num, ans, tot[1000005], ww[2000005], dis[2000005];
queue<int> q;
struct node
{
    int v;
    int w;
    int next;
} a[2000005];
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
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
    num = max(num, max(ma[0] + ma[1], ma[0] + cnt));
    return ma[0] + w;
}
void solve(int k)
{
    num = 0;
    col = 0;
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
    for (int i = 1; i < col; ++i)
    {
        ww[col + i] = ww[i];
        tot[col + i] = tot[i];
    }
    int h = 1, t = 1;
    s[1] = 1;
    for (int i = 2; i < 2 * col; ++i)
    {
        dis[i] = dis[i - 1] + ww[i];
        while (h <= t && i - s[h] >= col)
            ++h;
        num = max(num, dis[i] - dis[s[h]] + tot[s[h]] + tot[i]);
        while (h <= t && dis[i] - dis[s[t]] + tot[s[t]] <= tot[i])
            --t;
        s[++t] = i;
    }
    ans += num;
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    for (int i = 1; i <= n; ++i)
    {
        int y, l;
        scanf("%d%d", &y, &l);
        ++in[i];
        ++in[y];
        ins(i, y, l);
        ins(y, i, l);
        if (getfather(i) != getfather(y))
            fa[getfather(i)] = getfather(y);
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