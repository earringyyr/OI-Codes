#include <iostream>
#include <cstdio>
using namespace std;
int n, m, cnt, maxn, minx, ans, a[100005], rt[100005];
struct tree
{
    int l;
    int r;
    int sum;
} tr[40 * 100005];
void ins(int y, int &x, int l, int r, int val)
{
    x = ++cnt;
    tr[x] = tr[y];
    tr[x].sum += val;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (val <= mid)
        ins(tr[y].l, tr[x].l, l, mid, val);
    else
        ins(tr[y].r, tr[x].r, mid + 1, r, val);
    return;
}
int query(int x, int y, int l, int r, int L, int R)
{
    if (l == L && r == R)
        return tr[y].sum - tr[x].sum;
    int mid = (l + r) >> 1;
    if (R <= mid)
        return query(tr[x].l, tr[y].l, l, mid, L, R);
    if (L >= mid + 1)
        return query(tr[x].r, tr[y].r, mid + 1, r, L, R);
    return query(tr[x].l, tr[y].l, l, mid, L, mid) + query(tr[x].r, tr[y].r, mid + 1, r, mid + 1, R);
}
signed main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        maxn = max(maxn, a[i]);
    }
    for (int i = 1; i <= n; ++i)
        ins(rt[i - 1], rt[i], 1, maxn, a[i]);
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        minx = 0;
        ans = 0;
        while (minx + 1 <= maxn)
        {
            int sum = query(rt[l - 1], rt[r], 1, maxn, minx + 1, min(ans + 1, maxn));
            if (sum == 0)
                break;
            minx = ans + 1;
            ans += sum;
        }
        printf("%d\n", ans + 1);
    }
    return 0;
}