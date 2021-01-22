#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
int n, q;
int a[500005];
char s[500005];
struct tree
{
    int l;
    int r;
    int L;
    int R;
    int num;
    int sum;
} tr[2000005];
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
    {
        tr[id].L = a[l];
        tr[id].R = a[l];
        tr[id].num = a[l];
        tr[id].sum = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].L = max(tr[lch].L, tr[lch].sum + tr[rch].L);
    tr[id].R = max(tr[rch].R, tr[rch].sum + tr[lch].R);
    tr[id].num = max(max(tr[lch].num, tr[rch].num), tr[lch].R + tr[rch].L);
    tr[id].sum = tr[lch].sum + tr[rch].sum;
    return;
}
tree ask(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id];
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask(lch, l, r);
    if (l >= mid + 1)
        return ask(rch, l, r);
    tree L = ask(lch, l, mid), R = ask(rch, mid + 1, r);
    tree now = tr[id];
    now.L = max(L.L, L.sum + R.L);
    now.R = max(R.R, R.sum + L.R);
    now.num = max(max(L.num, R.num), L.R + R.L);
    now.sum = L.sum + R.sum;
    return now;
}
int main()
{
    scanf("%d", &n);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; ++i)
        a[i] = (s[i] == 'C' ? 1 : -1);
    build(1, 1, n);
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        tree now = ask(1, l, r);
        printf("%d\n", max(0, now.num) - now.sum);
    }
    return 0;
}