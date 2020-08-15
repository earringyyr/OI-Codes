#include <iostream>
#include <cstdio>
using namespace std;
int type, n, q, m, sum, a[100005], rt[100005];
struct tree
{
    int l;
    int r;
    int val;
} tr[3000005];
void add(int y, int &x, int l, int r, int w, int val)
{
    x = ++sum;
    tr[x] = tr[y];
    if (l == r)
    {
        tr[x].val = val;
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
        return tr[x].val;
    int mid = (l + r) >> 1;
    if (w <= mid)
        return ask(tr[x].l, l, mid, w);
    else
        return ask(tr[x].r, mid + 1, r, w);
}
int main()
{
    scanf("%d%d%d%d", &type, &n, &q, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = n; i >= 1; --i)
        add(rt[i], rt[i - 1], 1, m, a[i], i);
    for (int i = 1; i <= q; ++i)
    {
        int l, b, pos = 0, p = 1;
        scanf("%d", &l);
        for (int j = 1; j <= l; ++j)
        {
            scanf("%d", &b);
            if (p)
                pos = ask(rt[pos], 1, m, b);
            if (!pos)
                p = 0;
        }
        if (p)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}