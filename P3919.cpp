#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, cnt;
int a[1000005], rt[1000005];
struct tree
{
    int l;
    int r;
    int num;
} tr[30000005];
void build(int &x, int l, int r)
{
    x = ++cnt;
    if (l == r)
    {
        tr[x].num = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(tr[x].l, l, mid);
    build(tr[x].r, mid + 1, r);
    return;
}
void add(int y, int &x, int l, int r, int w, int val)
{
    x = ++cnt;
    tr[x] = tr[y];
    if (l == r)
    {
        tr[x].num = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (w <= mid)
        add(tr[y].l, tr[x].l, l, mid, w, val);
    else
        add(tr[y].r, tr[x].r, mid + 1, r, w, val);
    return;
}
int ask(int x, int l, int r, int w)
{
    if (l == r)
        return tr[x].num;
    int mid = (l + r) >> 1;
    if (w <= mid)
        return ask(tr[x].l, l, mid, w);
    else
        return ask(tr[x].r, mid + 1, r, w);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    build(rt[0], 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int v, type;
        scanf("%d%d", &v, &type);
        if (type == 1)
        {
            int loc, val;
            scanf("%d%d", &loc, &val);
            add(rt[v], rt[i], 1, n, loc, val);
        }
        else
        {
            int loc;
            scanf("%d", &loc);
            rt[i] = rt[v];
            printf("%d\n", ask(rt[i], 1, n, loc));
        }
    }
    return 0;
}