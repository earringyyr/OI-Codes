#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int n, m, k;
int o[300005], p[300005];
int ll[300005], rr[300005], a[300005];
int q[300005], q1[300005], q2[300005];
int c[300005], ans[300005];
vector<int> vec[300005];
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int val)
{
    while (x <= m)
    {
        c[x] += val;
        x += lowbit(x);
    }
    return;
}
int ask(int x)
{
    int num = 0;
    while (x >= 1)
    {
        num += c[x];
        x -= lowbit(x);
    }
    return num;
}
void solve(int l, int r, int L, int R)
{
    if (L > R)
        return;
    if (l == r)
    {
        for (int i = L; i <= R; ++i)
            ans[q[i]] = l;
        return;
    }
    int mid = (l + r) >> 1, cnt1 = 0, cnt2 = 0;
    for (int i = l; i <= mid; ++i)
    {
        if (ll[i] <= rr[i])
        {
            add(ll[i], a[i]);
            add(rr[i] + 1, -a[i]);
        }
        else
        {
            add(1, a[i]);
            add(rr[i] + 1, -a[i]);
            add(ll[i], a[i]);
            add(m + 1, -a[i]);
        }
    }
    for (int i = L; i <= R; ++i)
    {
        int tmp = 0, siz = vec[q[i]].size();
        for (int j = 0; j < siz; ++j)
        {
            tmp += ask(vec[q[i]][j]);
            if (tmp >= p[q[i]])
                break;
        }
        if (tmp >= p[q[i]])
            q1[++cnt1] = q[i];
        else
        {
            p[q[i]] -= tmp;
            q2[++cnt2] = q[i];
        }
    }
    for (int i = l; i <= mid; ++i)
    {
        if (ll[i] <= rr[i])
        {
            add(ll[i], -a[i]);
            add(rr[i] + 1, a[i]);
        }
        else
        {
            add(1, -a[i]);
            add(rr[i] + 1, a[i]);
            add(ll[i], -a[i]);
            add(m + 1, a[i]);
        }
    }
    for (int i = 1; i <= cnt1; ++i)
        q[L + i - 1] = q1[i];
    for (int i = 1; i <= cnt2; ++i)
        q[L + cnt1 + i - 1] = q2[i];
    solve(l, mid, L, L + cnt1 - 1);
    solve(mid + 1, r, L + cnt1, R);
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &o[i]);
        vec[o[i]].push_back(i);
    }
    for (int i = 1; i <= n; ++i)
    {
        q[i] = i;
        scanf("%d", &p[i]);
    }
    scanf("%d", &k);
    for (int i = 1; i <= k; ++i)
        scanf("%d%d%d", &ll[i], &rr[i], &a[i]);
    solve(1, k + 1, 1, n);
    for (int i = 1; i <= n; ++i)
        if (ans[i] == k + 1)
            puts("NIE");
        else
            printf("%d\n", ans[i]);
    return 0;
}