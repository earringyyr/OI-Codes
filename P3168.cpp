#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
int m, n, top, cnt, pre = 1, s[100005], e[100005], p[100005], b[100005], rt[100005];
struct node
{
    int t;
    int num;
    node(int aa = 0, int bb = 0)
    {
        t = aa;
        num = bb;
    }
} st[200005];
struct tree
{
    int l;
    int r;
    int num;
    int sum;
} tr[18 * 200005];
bool cmp(node aa, node bb)
{
    return aa.t < bb.t;
}
void ins(int y, int &x, int l, int r, int val)
{
    x = ++cnt;
    tr[x] = tr[y];
    if (val > 0)
    {
        ++tr[x].num;
        tr[x].sum += b[val];
    }
    else
    {
        --tr[x].num;
        tr[x].sum -= b[-val];
    }
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (val > 0)
    {
        if (val <= mid)
            ins(tr[y].l, tr[x].l, l, mid, val);
        else
            ins(tr[y].r, tr[x].r, mid + 1, r, val);
    }
    else
    {
        if (-val <= mid)
            ins(tr[y].l, tr[x].l, l, mid, val);
        else
            ins(tr[y].r, tr[x].r, mid + 1, r, val);
    }
    return;
}
int query(int x, int l, int r, int k)
{
    if (l == r)
    {
        if (k > tr[x].num)
            return tr[x].sum;
        return k * b[l];
    }
    int mid = (l + r) >> 1;
    if (tr[tr[x].l].num >= k)
        return query(tr[x].l, l, mid, k);
    return query(tr[x].r, mid + 1, r, k - tr[tr[x].l].num) + tr[tr[x].l].sum;
}
signed main()
{
    scanf("%lld%lld", &m, &n);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%lld%lld%lld", &s[i], &e[i], &p[i]);
        b[i] = p[i];
    }
    sort(b + 1, b + m + 1);
    int len = unique(b + 1, b + m + 1) - b - 1;
    for (int i = 1; i <= m; ++i)
        p[i] = lower_bound(b + 1, b + len + 1, p[i]) - b;
    for (int i = 1; i <= m; ++i)
    {
        st[++top] = node(s[i], p[i]);
        st[++top] = node(e[i] + 1, -p[i]);
    }
    sort(st + 1, st + top + 1, cmp);
    for (int i = 1; i <= top; ++i)
    {
        if (rt[st[i].t] != rt[st[i - 1].t])
            for (int j = st[i - 1].t + 1; j < st[i].t; ++j)
                rt[j] = rt[st[i - 1].t];
        ins(rt[st[i - 1].t], rt[st[i].t], 1, len, st[i].num);
    }
    for (int i = 1; i <= n; ++i)
    {
        int x, k, a, b, c;
        scanf("%lld%lld%lld%lld", &x, &a, &b, &c);
        k = 1 + ((long long)a * pre + b) % c;
        pre = query(rt[x], 1, len, k);
        printf("%lld\n", pre);
    }
    return 0;
}