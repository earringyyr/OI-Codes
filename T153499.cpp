#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, K, sum, ans;
int head[100005], siz[100005];
int f[100005], ff[100005], fff[100005];
struct node
{
    int v;
    int nxt;
} a[200005];
bool cmp(int aa, int bb)
{
    return aa > bb;
}
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k, int fa)
{
    siz[k] = 1;
    int d = head[k], cnt = 0;
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs(a[d].v, k);
            siz[k] += siz[a[d].v];
            if (siz[a[d].v] >= K)
                ++cnt;
        }
        d = a[d].nxt;
    }
    if (K <= 1)
        ++cnt;
    f[k] = -1;
    d = head[k];
    int top = 0, ttop = 0;
    while (d)
    {
        if (a[d].v != fa)
        {
            f[k] = max(f[k], f[a[d].v] + cnt - (siz[a[d].v] >= K ? 1 : 0));
            if (siz[a[d].v] >= K)
                ff[++top] = f[a[d].v];
            else
                fff[++ttop] = f[a[d].v];
        }
        d = a[d].nxt;
    }
    ans = max(ans, f[k] + (n - siz[k] >= max(1, K) ? 1 : 0));
    f[k] = max(f[k], cnt);
    sort(ff + 1, ff + top + 1, cmp);
    sort(fff + 1, fff + ttop + 1, cmp);
    if (n - siz[k] >= max(1, K))
        ++cnt;
    if (top >= 2)
        ans = max(ans, ff[1] + ff[2] + cnt - 2);
    if (top >= 1 && ttop >= 1)
        ans = max(ans, ff[1] + fff[1] + cnt - 1);
    if (ttop >= 2)
        ans = max(ans, fff[1] + fff[2] + cnt);
    return;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ans = 0;
        sum = 0;
        memset(head, 0, sizeof(head));
        scanf("%d%d", &n, &K);
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            ins(u, v);
            ins(v, u);
        }
        dfs(1, 0);
        printf("%d\n", ans);
    }
    return 0;
}