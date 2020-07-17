#include <iostream>
#include <cstdio>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
int n, k, num, sum;
struct tree
{
    int l;
    int r;
    int sum;
    int lazy;
} tr[4000005];
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
        return;
    int mid = (tr[id].l + tr[id].r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    return;
}
void pushdown(int id)
{
    if (tr[id].l != tr[id].r)
    {
        int lazy = tr[id].lazy;
        tr[id].lazy = 0;
        tr[lch].lazy += lazy;
        tr[rch].lazy += lazy;
        tr[lch].sum += lazy * (tr[lch].r - tr[lch].l + 1);
        tr[rch].sum += lazy * (tr[rch].r - tr[rch].l + 1);
    }
    return;
}
void add(int id, int l, int r)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].sum += r - l + 1;
        tr[id].lazy += 1;
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        add(lch, l, r);
    if (l >= mid + 1)
        add(rch, l, r);
    if (l <= mid && r >= mid + 1)
    {
        add(lch, l, mid);
        add(rch, mid + 1, r);
    }
    return;
}
int query(int id, int l, int r)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].sum;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return query(lch, l, r);
    if (l >= mid + 1)
        return query(rch, l, r);
    if (l <= mid && r >= mid + 1)
        return query(lch, l, mid) + query(rch, mid + 1, r);
}
int main()
{
    scanf("%d%d", &n, &k);
    build(1, 1, 1000000);
    for (int i = 1; i <= n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        if (query(1, u, v))
            num++;
        else
            add(1, u, v);
    }
    sum = num;
    for (int i = 1; i <= k; ++i)
    {
        int a;
        scanf("%d", &a);
        if (!query(1, a, a))
        {
            --num;
            add(1, a, a);
        }
    }
    if (num < 0)
        puts("No");
    else
        puts("Yes");
    printf("%d", sum);
    return 0;
}