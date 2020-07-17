#include <iostream>
#include <cstdio>
using namespace std;
int n, m, cnt, a[600005], rt[600005];
struct tree
{
    int l;
    int r;
    int sum;
} tr[600005 * 24];
void ins(int y, int &x, int t, int val)
{
    x = ++cnt;
    tr[x] = tr[y];
    ++tr[x].sum;
    if (t == -1)
        return;
    if ((val & (1 << t)) == 0)
        ins(tr[y].l, tr[x].l, t - 1, val);
    else
        ins(tr[y].r, tr[x].r, t - 1, val);
    return;
}
int query(int x, int y, int t, int val)
{
    if (t == -1)
        return 0;
    if ((val & (1 << t)) == 0)
    {
        if (tr[tr[y].r].sum - tr[tr[x].r].sum > 0)
            return (1 << t) + query(tr[x].r, tr[y].r, t - 1, val);
        else
            return query(tr[x].l, tr[y].l, t - 1, val);
    }
    else
    {
        if (tr[tr[y].l].sum - tr[tr[x].l].sum > 0)
            return (1 << t) + query(tr[x].l, tr[y].l, t - 1, val);
        else
            return query(tr[x].r, tr[y].r, t - 1, val);
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        a[i] = a[i] ^ a[i - 1];
        ins(rt[i - 1], rt[i], 23, a[i]);
    }
    for (int i = 1; i <= m; ++i)
    {
        char type;
        scanf(" %c", &type);
        if (type == 'A')
        {
            int x;
            scanf("%d", &x);
            ++n;
            a[n] = x ^ a[n - 1];
            ins(rt[n - 1], rt[n], 23, a[n]);
        }
        else
        {
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);
            if (l != r)
                printf("%d\n", query(rt[max(0, l - 2)], rt[r - 1], 23, x ^ a[n]));
            else
                printf("%d\n", a[l - 1] ^ a[n] ^ x);
        }
    }
    return 0;
}