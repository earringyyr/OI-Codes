#include <iostream>
#include <cstdio>
using namespace std;
int n, m, c, num, a[300005], rt[300005];
struct node
{
    int l;
    int r;
    int sum;
} tr[300005 * 19];
void ins(int &x, int y, int l, int r, int val)
{
    x = ++num;
    tr[x] = tr[y];
    ++tr[x].sum;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (val <= mid)
        ins(tr[x].l, tr[y].l, l, mid, val);
    else
        ins(tr[x].r, tr[y].r, mid + 1, r, val);
    return;
}
int query(int x, int y, int l, int r, int k)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    if (tr[tr[y].l].sum - tr[tr[x].l].sum > k / 2)
        return query(tr[x].l, tr[y].l, l, mid, k);
    if (tr[tr[y].r].sum - tr[tr[x].r].sum > k / 2)
        return query(tr[x].r, tr[y].r, mid + 1, r, k);
    return 0;
}
int main()
{
    scanf("%d%d", &n, &c);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        ins(rt[i], rt[i - 1], 1, c, a[i]);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        if (!query(rt[a - 1], rt[b], 1, c, b - a + 1))
            puts("no");
        else
            printf("yes %d\n", query(rt[a - 1], rt[b], 1, c, b - a + 1));
    }
    return 0;
}