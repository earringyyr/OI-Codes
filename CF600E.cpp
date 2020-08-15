#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, sum, cnt;
int rt[100005], c[100005], head[100005];
long long ans[100005];
struct tree
{
    int l;
    int r;
    int num;
    long long ans;
} tr[3000005];
struct node
{
    int v;
    int nxt;
} a[200005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
int merge(int x, int y, int l, int r)
{
    if (!x || !y)
        return x | y;
    if (l == r)
    {
        tr[x].num += tr[y].num;
        return x;
    }
    int mid = (l + r) >> 1;
    tr[x].l = merge(tr[x].l, tr[y].l, l, mid);
    tr[x].r = merge(tr[x].r, tr[y].r, mid + 1, r);
    if (tr[tr[x].l].num > tr[tr[x].r].num)
    {
        tr[x].ans = tr[tr[x].l].ans;
        tr[x].num = tr[tr[x].l].num;
    }
    if (tr[tr[x].r].num > tr[tr[x].l].num)
    {
        tr[x].ans = tr[tr[x].r].ans;
        tr[x].num = tr[tr[x].r].num;
    }
    if (tr[tr[x].l].num == tr[tr[x].r].num)
    {
        tr[x].ans = tr[tr[x].l].ans + tr[tr[x].r].ans;
        tr[x].num = tr[tr[x].l].num;
    }
    return x;
}
void add(int &x, int l, int r, int w)
{
    if (!x)
        x = ++cnt;
    if (l == r)
    {
        ++tr[x].num;
        tr[x].ans = l;
        return;
    }
    int mid = (l + r) >> 1;
    if (w <= mid)
        add(tr[x].l, l, mid, w);
    else
        add(tr[x].r, mid + 1, r, w);
    if (tr[tr[x].l].num > tr[tr[x].r].num)
    {
        tr[x].ans = tr[tr[x].l].ans;
        tr[x].num = tr[tr[x].l].num;
    }
    if (tr[tr[x].r].num > tr[tr[x].l].num)
    {
        tr[x].ans = tr[tr[x].r].ans;
        tr[x].num = tr[tr[x].r].num;
    }
    if (tr[tr[x].l].num == tr[tr[x].r].num)
    {
        tr[x].ans = tr[tr[x].l].ans + tr[tr[x].r].ans;
        tr[x].num = tr[tr[x].l].num;
    }
    return;
}
void dfs(int k, int fa)
{
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs(a[d].v, k);
            merge(rt[k], rt[a[d].v], 1, n);
        }
        d = a[d].nxt;
    }
    add(rt[k], 1, n, c[k]);
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        rt[i] = i;
    cnt = n;
    for (int i = 1; i <= n; ++i)
        scanf("%d", &c[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i)
        printf("%lld ", tr[rt[i]].ans);
    return 0;
}