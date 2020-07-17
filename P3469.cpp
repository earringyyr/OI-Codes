#include <iostream>
#include <cstdio>
using namespace std;
int n, m, sum, cnt, head[100005], dfn[100005], low[100005], siz[100005];
long long ans[100005];
struct node
{
    int v;
    int next;
} a[1000005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void tarjan(int k)
{
    siz[k] = 1;
    ++cnt;
    dfn[k] = cnt;
    low[k] = cnt;
    int d = head[k], num = 0;
    while (d)
    {
        if (!dfn[a[d].v])
        {
            tarjan(a[d].v);
            low[k] = min(low[k], low[a[d].v]);
            siz[k] += siz[a[d].v];
            if (low[a[d].v] >= dfn[k])
            {
                ans[k] += (long long)num * siz[a[d].v];
                num += siz[a[d].v];
            }
        }
        else
            low[k] = min(low[k], dfn[a[d].v]);
        d = a[d].next;
    }
    ans[k] += (long long)num * (n - num - 1) + n - 1;
    ans[k] *= 2;
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    tarjan(1);
    for (int i = 1; i <= n; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}