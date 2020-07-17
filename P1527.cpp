#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, qq, c[505][505], q[60005], ans[60005], q1[60005], q2[60005];
struct node
{
    int x;
    int y;
    int xx;
    int yy;
    int k;
} a[60005];
struct point
{
    int x;
    int y;
    int k;
} b[250005];
bool cmp(point aa, point bb)
{
    return aa.k < bb.k;
}
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int y, int val)
{
    for (int i = x; i <= n + 1; i += lowbit(i))
        for (int j = y; j <= n + 1; j += lowbit(j))
            c[i][j] += val;
    return;
}
int query(int x, int y)
{
    int ans = 0;
    for (int i = x; i >= 1; i -= lowbit(i))
        for (int j = y; j >= 1; j -= lowbit(j))
            ans += c[i][j];
    return ans;
}
void solve(int l, int r, int L, int R)
{
    if (L > R)
        return;
    if (l == r)
    {
        for (int i = L; i <= R; ++i)
            ans[q[i]] = b[l].k;
        return;
    }
    int mid = (l + r) >> 1, cnt1 = 0, cnt2 = 0;
    for (int i = l; i <= mid; ++i)
        add(b[i].x + 1, b[i].y + 1, 1);
    for (int i = L; i <= R; ++i)
    {
        int t = query(a[q[i]].xx + 1, a[q[i]].yy + 1) + query(a[q[i]].x, a[q[i]].y) - query(a[q[i]].xx + 1, a[q[i]].y) - query(a[q[i]].x, a[q[i]].yy + 1);
        if (a[q[i]].k <= t)
            q1[++cnt1] = q[i];
        else
        {
            q2[++cnt2] = q[i];
            a[q[i]].k -= t;
        }
    }
    for (int i = 1; i <= cnt1; ++i)
        q[L + i - 1] = q1[i];
    for (int i = 1; i <= cnt2; ++i)
        q[L + cnt1 + i - 1] = q2[i];
    for (int i = l; i <= mid; ++i)
        add(b[i].x + 1, b[i].y + 1, -1);
    solve(l, mid, L, L + cnt1 - 1);
    solve(mid + 1, r, L + cnt1, R);
    return;
}
int main()
{
    scanf("%d%d", &n, &qq);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            int id = (i - 1) * n + j;
            b[id].x = i;
            b[id].y = j;
            scanf("%d", &b[id].k);
        }
    sort(b + 1, b + n * n + 1, cmp);
    for (int i = 1; i <= qq; ++i)
    {
        scanf("%d%d%d%d%d", &a[i].x, &a[i].y, &a[i].xx, &a[i].yy, &a[i].k);
        q[i] = i;
    }
    solve(1, n * n, 1, qq);
    for (int i = 1; i <= qq; ++i)
        printf("%d\n", ans[i]);
    return 0;
}