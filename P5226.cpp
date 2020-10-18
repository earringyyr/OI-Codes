#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lch id << 1
#define rch id << 1 | 1
using namespace std;
int n, m, num, l;
int a[200005], b[200005];
char c[200005];
struct tree
{
    int l;
    int r;
    int L;
    int R;
    int p;
    int num;
    tree operator+(const tree &bb) const
    {
        tree cc;
        cc.l = l;
        cc.r = bb.r;
        cc.L = L;
        cc.R = bb.R;
        cc.p = p | bb.p;
        cc.num = num + bb.num;
        if ((R == 0 || bb.L == 0) && p && bb.p)
            ++cc.num;
        return cc;
    }
} tr[800005];
void build(int id, int l, int r)
{
    if (l == r)
    {
        tr[id].l = l;
        tr[id].r = r;
        tr[id].L = b[l];
        tr[id].R = b[r];
        if (b[l] == 0)
            tr[id].p = 0;
        else
            tr[id].p = 1;
        tr[id].num = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id] = tr[lch] + tr[rch];
    return;
}
void change(int id, int pos)
{
    if (tr[id].l == tr[id].r)
    {
        tr[id].L = b[pos];
        tr[id].R = b[pos];
        if (b[pos] == 0)
            tr[id].p = 0;
        else
            tr[id].p = 1;
        tr[id].num = 0;
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (pos <= mid)
        change(lch, pos);
    else
        change(rch, pos);
    tr[id] = tr[lch] + tr[rch];
    return;
}
tree query(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id];
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return query(lch, l, r);
    if (l >= mid + 1)
        return query(rch, l, r);
    return query(lch, l, mid) + query(rch, mid + 1, r);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d %c", &a[i], &c[i]);
    if (c[1] == '+')
        b[1] = (a[1] + a[n]) % 10;
    else
        b[1] = (a[1] * a[n]) % 10;
    for (int i = 2; i <= n; ++i)
        if (c[i] == '+')
            b[i] = (a[i - 1] + a[i]) % 10;
        else
            b[i] = (a[i - 1] * a[i]) % 10;
    for (int i = 1; i <= n; ++i)
    {
        a[i + n] = a[i];
        b[i + n] = b[i];
        c[i + n] = c[i];
    }
    build(1, 1, 2 * n);
    for (int i = 1; i <= m; ++i)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            int pos, num;
            char opt;
            scanf("%d%d %c", &pos, &num, &opt);
            ++pos;
            a[pos] = num;
            c[pos] = opt;
            a[pos + n] = num;
            c[pos + n] = opt;
            if (pos == 1)
            {
                if (c[1] == '+')
                {
                    b[1] = (a[1] + a[n]) % 10;
                    b[1 + n] = (a[1 + n] + a[n + n]) % 10;
                }
                else
                {
                    b[1] = (a[1] * a[n]) % 10;
                    b[1 + n] = (a[1 + n] * a[n + n]) % 10;
                }
                change(1, 1);
                change(1, 1 + n);
            }
            else
            {
                if (c[pos] == '+')
                {
                    b[pos] = (a[pos - 1] + a[pos]) % 10;
                    b[pos + n] = (a[pos - 1 + n] + a[pos + n]) % 10;
                }
                else
                {
                    b[pos] = (a[pos - 1] * a[pos]) % 10;
                    b[pos + n] = (a[pos - 1 + n] * a[pos + n]) % 10;
                }
                change(1, pos);
                change(1, pos + n);
            }
            if (pos == n)
            {
                if (c[1] == '+')
                {
                    b[1] = (a[1] + a[n]) % 10;
                    b[1 + n] = (a[1 + n] + a[n + n]) % 10;
                }
                else
                {
                    b[1] = (a[1] * a[n]) % 10;
                    b[1 + n] = (a[1 + n] * a[n + n]) % 10;
                }
                change(1, 1);
                change(1, 1 + n);
            }
            else
            {
                if (c[pos + 1] == '+')
                {
                    b[pos + 1] = (a[pos] + a[pos + 1]) % 10;
                    b[pos + 1 + n] = (a[pos + n] + a[pos + 1 + n]) % 10;
                }
                else
                {
                    b[pos + 1] = (a[pos] * a[pos + 1]) % 10;
                    b[pos + 1 + n] = (a[pos + n] * a[pos + 1 + n]) % 10;
                }
                change(1, pos + 1);
                change(1, pos + 1 + n);
            }
        }
        else
        {
            int pos;
            scanf("%d", &pos);
            ++pos;
            int tmp = b[pos];
            b[pos] = a[pos];
            b[pos + n] = a[pos + n];
            change(1, pos);
            change(1, pos + n);
            if (query(1, pos, pos + n).num == 0)
            {
                if (b[pos] == 0)
                    printf("0\n");
                else
                    printf("-1\n");
                continue;
            }
            int lef = 0, rig = n / 2;
            while (lef < rig)
            {
                int mid = (lef + rig + 1) >> 1;
                if (query(1, pos + mid, pos + n - mid).num > 0)
                    lef = mid;
                else
                    rig = mid - 1;
            }
            b[pos] = tmp;
            b[pos + n] = tmp;
            change(1, pos);
            change(1, pos + n);
            printf("%d\n", lef + 1);
        }
    }
    return 0;
}