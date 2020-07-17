#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n, m, aa[100005], b[50005], c[100005], pos[100005];
long long cnt;
struct node
{
    int num;
    int tim;
    long long ans;
} a[100005];
inline bool cmp(node aa, node bb)
{
    return aa.num < bb.num;
}
inline bool comp(node aa, node bb)
{
    return aa.tim < bb.tim;
}
inline int lowbit(int x)
{
    return x & -x;
}
inline void add(int x, int val)
{
    while (x <= n)
    {
        c[x] += val;
        x += lowbit(x);
    }
    return;
}
inline int query(int x)
{
    int ans = 0;
    while (x >= 1)
    {
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}
inline void solve(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    solve(l, mid);
    solve(mid + 1, r);
    int i = l, j = mid + 1;
    while (i <= mid)
    {
        while (a[i].num > a[j].num && j <= r)
        {
            add(a[j].tim, 1);
            ++j;
        }
        a[i].ans += query(m + 1) - query(a[i].tim);
        ++i;
    }
    i = l;
    j = mid + 1;
    while (i <= mid)
    {
        while (a[i].num > a[j].num && j <= r)
        {
            add(a[j].tim, -1);
            ++j;
        }
        ++i;
    }
    i = mid;
    j = r;
    while (j >= mid + 1)
    {
        while (a[j].num < a[i].num && i >= l)
        {
            add(a[i].tim, 1);
            --i;
        }
        a[j].ans += query(m + 1) - query(a[j].tim);
        --j;
    }
    i = mid;
    j = r;
    while (j >= mid + 1)
    {
        while (a[j].num < a[i].num && i >= l)
        {
            add(a[i].tim, -1);
            --i;
        }
        --j;
    }
    sort(a + l, a + r + 1, cmp);
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (register int i = 1; i <= n; ++i)
    {
        scanf("%d", &aa[i]);
        pos[aa[i]] = i;
        a[i].num = aa[i];
    }
    for (register int i = 1; i <= m; ++i)
    {
        scanf("%d", &b[i]);
        a[pos[b[i]]].tim = i;
    }
    for (register int i = 1; i <= n; ++i)
        if (!a[i].tim)
            a[i].tim = m + 1;
    for (register int i = 1; i <= n; ++i)
    {
        cnt += query(n) - query(a[i].num);
        add(a[i].num, 1);
    }
    for (int i = 1; i <= n; ++i)
        add(a[i].num, -1);
    solve(1, n);
    sort(a + 1, a + n + 1, comp);
    for (register int i = 1; i <= m; ++i)
    {
        printf("%lld\n", cnt);
        cnt -= a[i].ans;
    }
    return 0;
}