#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, m, cnt, col = 1;
int a[200005], rt[200005];
struct node
{
    int l;
    int r;
    ll num;
} tr[8000005];
void split(int &y, int &x, int l, int r, int L, int R)
{
    if (!y)
        return;
    if (l == L && r == R)
    {
        swap(x, y);
        return;
    }
    x = ++cnt;
    int mid = (l + r) >> 1;
    if (R <= mid)
        split(tr[y].l, tr[x].l, l, mid, L, R);
    if (L >= mid + 1)
        split(tr[y].r, tr[x].r, mid + 1, r, L, R);
    if (L <= mid && R >= mid + 1)
    {
        split(tr[y].l, tr[x].l, l, mid, L, mid);
        split(tr[y].r, tr[x].r, mid + 1, r, mid + 1, R);
    }
    tr[x].num = tr[tr[x].l].num + tr[tr[x].r].num;
    tr[y].num = tr[tr[y].l].num + tr[tr[y].r].num;
    return;
}
int merge(int x, int y)
{
    if (!x || !y)
        return x | y;
    tr[x].l = merge(tr[x].l, tr[y].l);
    tr[x].r = merge(tr[x].r, tr[y].r);
    tr[x].num += tr[y].num;
    return x;
}
void add(int &x, int l, int r, int w, int val)
{
    if (!x)
        x = ++cnt;
    tr[x].num += val;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (w <= mid)
        add(tr[x].l, l, mid, w, val);
    else
        add(tr[x].r, mid + 1, r, w, val);
    return;
}
ll ask1(int x, int l, int r, int L, int R)
{
    if (l == L && r == R)
        return tr[x].num;
    int mid = (l + r) >> 1;
    if (R <= mid)
        return ask1(tr[x].l, l, mid, L, R);
    if (L >= mid + 1)
        return ask1(tr[x].r, mid + 1, r, L, R);
    return ask1(tr[x].l, l, mid, L, mid) + ask1(tr[x].r, mid + 1, r, mid + 1, R);
}
int ask2(int x, int l, int r, int w)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    if (w <= tr[tr[x].l].num)
        return ask2(tr[x].l, l, mid, w);
    else
        return ask2(tr[x].r, mid + 1, r, w - tr[tr[x].l].num);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        add(rt[1], 1, max(n, m), i, a[i]);
    }
    n = max(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int opt, p;
        scanf("%d%d", &opt, &p);
        if (opt == 0)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            split(rt[p], rt[++col], 1, m, x, y);
        }
        else if (opt == 1)
        {
            int t;
            scanf("%d", &t);
            rt[p] = merge(rt[t], rt[p]);
        }
        else if (opt == 2)
        {
            int x, q;
            scanf("%d%d", &x, &q);
            add(rt[p], 1, n, q, x);
        }
        else if (opt == 3)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            printf("%lld\n", ask1(rt[p], 1, n, x, y));
        }
        else if (opt == 4)
        {
            int k;
            scanf("%d", &k);
            if (tr[rt[p]].num < k)
                puts("-1");
            else
                printf("%d\n", ask2(rt[p], 1, n, k));
        }
    }
    return 0;
}