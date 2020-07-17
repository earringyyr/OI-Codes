#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, Q, ans, cnt, q[4], c[20005], rt[20005];
struct node
{
    int id;
    int num;
} a[20005];
struct tree
{
    int l;
    int r;
    int sum;
    int lmax;
    int rmax;
    tree(int aa = 0, int bb = 0, int cc = 0, int dd = 0, int ee = 0)
    {
        l = aa;
        r = bb;
        sum = cc;
        lmax = dd;
        rmax = ee;
    }
} tr[20 * 20005];
bool cmp(node aa, node bb)
{
    return aa.num < bb.num;
}
void build(int &x, int l, int r)
{
    x = ++cnt;
    if (l == r)
    {
        tr[x].sum = 1;
        tr[x].lmax = 1;
        tr[x].rmax = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(tr[x].l, l, mid);
    build(tr[x].r, mid + 1, r);
    tr[x].sum = tr[tr[x].l].sum + tr[tr[x].r].sum;
    tr[x].lmax = max(tr[tr[x].l].lmax, tr[tr[x].l].sum + tr[tr[x].r].lmax);
    tr[x].rmax = max(tr[tr[x].r].rmax, tr[tr[x].r].sum + tr[tr[x].l].rmax);
    return;
}
void ins(int y, int &x, int l, int r, int k)
{
    x = ++cnt;
    tr[x] = tr[y];
    if (l == r)
    {
        tr[x].sum = -1;
        tr[x].lmax = -1;
        tr[x].rmax = -1;
        return;
    }
    int mid = (l + r) >> 1;
    if (k <= mid)
        ins(tr[y].l, tr[x].l, l, mid, k);
    else
        ins(tr[y].r, tr[x].r, mid + 1, r, k);
    tr[x].sum = tr[tr[x].l].sum + tr[tr[x].r].sum;
    tr[x].lmax = max(tr[tr[x].l].lmax, tr[tr[x].l].sum + tr[tr[x].r].lmax);
    tr[x].rmax = max(tr[tr[x].r].rmax, tr[tr[x].r].sum + tr[tr[x].l].rmax);
    return;
}
tree query(int x, int l, int r, int p, int q)
{
    if (p == l && q == r)
        return tr[x];
    int mid = (l + r) >> 1;
    if (q <= mid)
        return query(tr[x].l, l, mid, p, q);
    if (p >= mid + 1)
        return query(tr[x].r, mid + 1, r, p, q);
    tree ans0, ans1, ans2;
    ans1 = query(tr[x].l, l, mid, p, mid);
    ans2 = query(tr[x].r, mid + 1, r, mid + 1, q);
    ans0.sum = ans1.sum + ans2.sum;
    ans0.lmax = max(ans1.lmax, ans1.sum + ans2.lmax);
    ans0.rmax = max(ans2.rmax, ans2.sum + ans1.rmax);
    return ans0;
}
bool check(int x, int l, int r, int p, int q)
{
    int res = 0;
    if (r + 2 <= p)
        res += query(rt[x], 1, n, r + 1, p - 1).sum;
    res += query(rt[x], 1, n, l, r).rmax + query(rt[x], 1, n, p, q).lmax;
    if (res >= 0)
        return true;
    else
        return false;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        a[i].id = i;
        scanf("%d", &a[i].num);
    }
    sort(a + 1, a + n + 1, cmp);
    build(rt[1], 1, n);
    for (int i = 2; i <= n; ++i)
        ins(rt[i - 1], rt[i], 1, n, a[i - 1].id);
    scanf("%d", &Q);
    for (int i = 1; i <= Q; ++i)
    {
        scanf("%d%d%d%d", &q[0], &q[1], &q[2], &q[3]);
        for (int i = 0; i < 4; ++i)
            q[i] = (q[i] + ans) % n + 1;
        sort(q, q + 4);
        int lef = 1, rig = n;
        while (lef < rig)
        {
            int mid = (lef + rig + 1) >> 1;
            if (check(mid, q[0], q[1], q[2], q[3]))
                lef = mid;
            else
                rig = mid - 1;
        }
        ans = a[lef].num;
        printf("%d\n", ans);
    }
    return 0;
}