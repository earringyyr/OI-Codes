#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, cnt, rt[200005], a[200005];
struct tree
{
    int l;
    int r;
    int sum;
} tr[4000005];
void insert(int y, int &x, int l, int r, int pos)
{
    x = ++cnt;
    tr[x] = tr[y];
    ++tr[x].sum;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        insert(tr[y].l, tr[x].l, l, mid, pos);
    else
        insert(tr[y].r, tr[x].r, mid + 1, r, pos);
    return;
}
int query(int x, int y, int l, int r, int L, int R)
{
    if (l > r)
        return 0;
    if (l == L && r == R)
        return tr[y].sum - tr[x].sum;
    int mid = (L + R) >> 1;
    if (r <= mid)
        return query(tr[x].l, tr[y].l, l, r, L, mid);
    if (l >= mid + 1)
        return query(tr[x].r, tr[y].r, l, r, mid + 1, R);
    return query(tr[x].l, tr[y].l, l, mid, L, mid) + query(tr[x].r, tr[y].r, mid + 1, r, mid + 1, R);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        insert(rt[i - 1], rt[i], 0, 100000, a[i]);
    }
    for (int i = 1; i <= m; ++i)
    {
        int b, x, l, r, ans = 0;
        scanf("%d%d%d%d", &b, &x, &l, &r);
        for (int i = 30; i >= 0; --i)
            if (b & (1 << i))
            {
                if (!query(rt[l - 1], rt[r], max(0, ans - x), min(100000, ans + (1 << i) - 1 - x), 0, 100000))
                    ans += (1 << i);
            }
            else
            {
                if (query(rt[l - 1], rt[r], max(0, ans + (1 << i) - x), min(100000, ans + ((1 << (i + 1)) - 1) - x), 0, 100000))
                    ans += (1 << i);
            }
        printf("%d\n", ans ^ b);
    }
    return 0;
}