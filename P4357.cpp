#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
int n, k, rt, cnt, opt;
int minx[200005][2], maxn[200005][2];
priority_queue<ll, vector<ll>, greater<ll> > q;
struct node
{
    int x[2];
} a[100005], p[200005];
struct tree
{
    int l;
    int r;
} tr[200005];
inline bool cmp(node aa, node bb)
{
    return aa.x[opt] < bb.x[opt];
}
inline int solve(int l, int r)
{
    double sum[2][2] = {0};
    for (int i = l; i <= r; ++i)
    {
        sum[0][0] += (ll)a[i].x[0] * a[i].x[0];
        sum[0][1] += a[i].x[0];
        sum[1][0] += (ll)a[i].x[1] * a[i].x[1];
        sum[1][1] += a[i].x[1];
    }
    return sum[0][0] * (r - l + 1) - sum[0][1] * sum[0][1] < sum[1][0] * (r - l + 1) - sum[1][1] * sum[1][1];
}
inline void build(int &id, int l, int r)
{
    if (l > r)
        return;
    id = ++cnt;
    int mid = (l + r) >> 1;
    opt = solve(l, r);
    nth_element(a + l, a + mid, a + r + 1, cmp);
    build(tr[id].l, l, mid - 1);
    build(tr[id].r, mid + 1, r);
    p[id] = a[mid];
    minx[id][0] = a[mid].x[0];
    maxn[id][0] = a[mid].x[0];
    minx[id][1] = a[mid].x[1];
    maxn[id][1] = a[mid].x[1];
    if (tr[id].l)
    {
        minx[id][0] = min(minx[id][0], minx[tr[id].l][0]);
        maxn[id][0] = max(maxn[id][0], maxn[tr[id].l][0]);
        minx[id][1] = min(minx[id][1], minx[tr[id].l][1]);
        maxn[id][1] = max(maxn[id][1], maxn[tr[id].l][1]);
    }
    if (tr[id].r)
    {
        minx[id][0] = min(minx[id][0], minx[tr[id].r][0]);
        maxn[id][0] = max(maxn[id][0], maxn[tr[id].r][0]);
        minx[id][1] = min(minx[id][1], minx[tr[id].r][1]);
        maxn[id][1] = max(maxn[id][1], maxn[tr[id].r][1]);
    }
    return;
}
inline ll ask(int id, node now)
{
    ll sum[2];
    sum[0] = max((ll)(now.x[0] - minx[id][0]) * (now.x[0] - minx[id][0]), (ll)(now.x[0] - maxn[id][0]) * (now.x[0] - maxn[id][0]));
    sum[1] = max((ll)(now.x[1] - minx[id][1]) * (now.x[1] - minx[id][1]), (ll)(now.x[1] - maxn[id][1]) * (now.x[1] - maxn[id][1]));
    return sum[0] + sum[1];
}
inline ll dis(node aa, node bb)
{
    return (ll)(aa.x[0] - bb.x[0]) * (aa.x[0] - bb.x[0]) + (ll)(aa.x[1] - bb.x[1]) * (aa.x[1] - bb.x[1]);
}
inline void query(int id, node now)
{
    ll sum[2] = {-1, -1};
    if (tr[id].l)
        sum[0] = ask(tr[id].l, now);
    if (tr[id].r)
        sum[1] = ask(tr[id].r, now);
    ll tmp = dis(p[id], now);
    if (tmp > q.top())
    {
        q.pop();
        q.push(tmp);
    }
    if (sum[0] > sum[1])
    {
        if (sum[0] > q.top())
            query(tr[id].l, now);
        if (sum[1] > q.top())
            query(tr[id].r, now);
    }
    else
    {
        if (sum[1] > q.top())
            query(tr[id].r, now);
        if (sum[0] > q.top())
            query(tr[id].l, now);
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &a[i].x[0], &a[i].x[1]);
    for (int i = 1; i <= 2 * k; ++i)
        q.push(0);
    build(rt, 1, n);
    for (int i = 1; i <= n; ++i)
        query(rt, a[i]);
    printf("%lld", q.top());
    return 0;
}