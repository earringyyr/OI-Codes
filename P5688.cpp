#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lch id << 1
#define rch id << 1 | 1
using namespace std;
int n, m, L;
int a[200005], l[200005];
int s[200005], b[200005];
int dis[200005];
struct tree
{
    struct node
    {
        int l;
        int r;
        int num;
        int ans;
        int lazy;
    } tr[800005];
    void pushup(int id)
    {
        if (tr[lch].num <= tr[rch].num)
        {
            tr[id].num = tr[lch].num;
            tr[id].ans = tr[lch].ans;
        }
        else
        {
            tr[id].num = tr[rch].num;
            tr[id].ans = tr[rch].ans;
        }
        return;
    }
    void pushdown(int id)
    {
        int lazy = tr[id].lazy;
        tr[id].lazy = 0;
        tr[lch].num += lazy;
        tr[rch].num += lazy;
        tr[lch].lazy += lazy;
        tr[rch].lazy += lazy;
        return;
    }
    void build(int id, int l, int r)
    {
        tr[id].l = l;
        tr[id].r = r;
        if (l == r)
        {
            tr[id].num = dis[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(lch, l, mid);
        build(rch, mid + 1, r);
        pushup(id);
        return;
    }
    void add(int id, int l, int r, int val)
    {
        if (tr[id].l == l && tr[id].r == r)
        {
            tr[id].num += val;
            tr[id].lazy += val;
            return;
        }
        pushdown(id);
        int mid = (tr[id].l + tr[id].r) >> 1;
        if (r <= mid)
            add(lch, l, r, val);
        if (l >= mid + 1)
            add(rch, l, r, val);
        if (l <= mid && r >= mid + 1)
        {
            add(lch, l, mid, val);
            add(rch, mid + 1, r, val);
        }
        pushup(id);
        return;
    }
} T1, T2;
int main()
{
    scanf("%d%d%d", &n, &m, &L);
    for (int i = 2; i <= m; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; ++i)
        scanf("%d", &l[i]);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &s[i], &b[i]);
    }
    return 0;
}