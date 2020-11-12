#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
int n, a[100005], lst[100005], vis[100005];
struct tree
{
    int l;
    int r;
    int minx;
} tr[400005];
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    return;
}
void change(int id, int w, int val)
{
    if (tr[id].l == tr[id].r)
    {
        tr[id].minx = val;
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        change(lch, w, val);
    else
        change(rch, w, val);
    tr[id].minx = min(tr[lch].minx, tr[rch].minx);
    return;
}
int query(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].minx;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return query(lch, l, r);
    if (l >= mid + 1)
        return query(rch, l, r);
    if (l <= mid && r >= mid + 1)
        return min(query(lch, l, mid), query(rch, mid + 1, r));
}
int main()
{
    scanf("%d", &n);
    build(1, 1, n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        if (a[i] != 1)
            vis[1] = 1;
        if (a[i] != 1 && query(1, 1, a[i] - 1) > lst[a[i]])
            vis[a[i]] = 1;
        lst[a[i]] = i;
        change(1, a[i], i);
    }
    for (int i = 2; i <= n + 1; ++i)
        if (query(1, 1, i - 1) > lst[i])
            vis[i] = 1;
    for (int i = 1; i <= n + 2; ++i)
        if (!vis[i])
        {
            printf("%d", i);
            break;
        }
    return 0;
}