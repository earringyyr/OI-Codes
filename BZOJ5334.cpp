#include <iostream>
#include <cstdio>
#include <cstring>
#define lch id << 1
#define rch id << 1 | 1
using namespace std;
int q, mod;
struct tree
{
    int l;
    int r;
    int sum;
} tr[400005];
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
    {
        tr[id].sum = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].sum = ((long long)tr[lch].sum * tr[rch].sum) % mod;
    return;
}
void ins(int id, int l, int r, int val, int type)
{
    if (tr[id].l == l && tr[id].r == r)
    {
        if (type == 0)
            tr[id].sum = 1;
        else
            tr[id].sum = val;
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        ins(lch, l, r, val, type);
    if (l >= mid + 1)
        ins(rch, l, r, val, type);
    tr[id].sum = ((long long)tr[lch].sum * tr[rch].sum) % mod;
    return;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &q, &mod);
        build(1, 1, q);
        for (int i = 1; i <= q; ++i)
        {
            int op, m;
            scanf("%d%d", &op, &m);
            if (op == 1)
                ins(1, i, i, m, 1);
            else
                ins(1, m, m, 0, 0);
            printf("%d\n", tr[1].sum);
        }
    }
    return 0;
}