#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lch id << 1
#define rch id << 1 | 1
#define int long long
using namespace std;
int n, L, R, Q, ans[100005];
struct point
{
    int id;
    int x;
} s[100005];
struct node
{
    int type;
    int num;
} q[100005];
struct tree
{
    int l;
    int r;
    int minx;
    int maxn;
    int lazy[3];
    int cov;
} tr[400005];
bool cmp(point aa, point bb)
{
    return aa.x < bb.x;
}
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    tr[id].lazy[1] = 1;
    if (l == r)
    {
        tr[id].minx = s[l].x;
        tr[id].maxn = s[l].x;
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].minx = tr[lch].minx;
    tr[id].maxn = tr[rch].maxn;
    return;
}
void pushdown(int id)
{
    if (tr[id].l != tr[id].r)
    {
        if (tr[id].cov)
        {
            int cov = tr[id].cov;
            tr[id].cov = 0;
            tr[lch].cov = cov;
            tr[rch].cov = cov;
            memset(tr[lch].lazy, 0, sizeof(tr[lch].lazy));
            memset(tr[rch].lazy, 0, sizeof(tr[rch].lazy));
            tr[lch].lazy[1] = 1;
            tr[rch].lazy[1] = 1;
            tr[lch].minx = cov;
            tr[rch].minx = cov;
            tr[lch].maxn = cov;
            tr[rch].maxn = cov;
        }
        if (tr[id].lazy[1] > 1)
        {
            int lazy = tr[id].lazy[1];
            tr[id].lazy[1] = 1;
            tr[lch].lazy[0] *= lazy;
            tr[rch].lazy[0] *= lazy;
            tr[lch].lazy[1] *= lazy;
            tr[rch].lazy[1] *= lazy;
            tr[lch].lazy[2] *= lazy;
            tr[rch].lazy[2] *= lazy;
            tr[lch].minx *= lazy;
            tr[rch].minx *= lazy;
            tr[lch].maxn *= lazy;
            tr[rch].maxn *= lazy;
        }
        if (tr[id].lazy[0])
        {
            int lazy = tr[id].lazy[0];
            tr[id].lazy[0] = 0;
            tr[lch].lazy[0] += lazy;
            tr[rch].lazy[0] += lazy;
            tr[lch].minx += lazy;
            tr[rch].minx += lazy;
            tr[lch].maxn += lazy;
            tr[rch].maxn += lazy;
        }
        if (tr[id].lazy[2])
        {
            int lazy = tr[id].lazy[2];
            tr[id].lazy[2] = 0;
            tr[lch].lazy[2] += lazy;
            tr[rch].lazy[2] += lazy;
            tr[lch].minx += lazy * s[tr[lch].l].x;
            tr[rch].minx += lazy * s[tr[rch].l].x;
            tr[lch].maxn += lazy * s[tr[lch].r].x;
            tr[rch].maxn += lazy * s[tr[rch].r].x;
        }
    }
    return;
}
void add(int id, int plu, int mul, int cal)
{
    pushdown(id);
    if (plu)
    {
        tr[id].lazy[0] += plu;
        tr[id].minx += plu;
        tr[id].maxn += plu;
    }
    if (mul)
    {
        tr[id].lazy[1] *= mul;
        tr[id].minx *= mul;
        tr[id].maxn *= mul;
    }
    if (cal)
    {
        tr[id].lazy[2] += cal;
        tr[id].minx += cal * s[tr[id].l].x;
        tr[id].maxn += cal * s[tr[id].r].x;
    }
    return;
}
void modify_l(int id)
{
    pushdown(id);
    if (tr[id].maxn < L)
    {
        tr[id].cov = L;
        memset(tr[id].lazy, 0, sizeof(tr[id].lazy));
        tr[id].lazy[1] = 1;
        tr[id].minx = L;
        tr[id].maxn = L;
        return;
    }
    if (tr[rch].minx < L)
    {
        modify_l(lch);
        modify_l(rch);
    }
    else if (tr[lch].minx < L)
        modify_l(lch);
    tr[id].minx = tr[lch].minx;
    tr[id].maxn = tr[rch].maxn;
    return;
}
void modify_r(int id)
{
    pushdown(id);
    if (tr[id].minx > R)
    {
        tr[id].cov = R;
        memset(tr[id].lazy, 0, sizeof(tr[id].lazy));
        tr[id].lazy[1] = 1;
        tr[id].minx = R;
        tr[id].maxn = R;
        return;
    }
    if (tr[lch].maxn > R)
    {
        modify_r(lch);
        modify_r(rch);
    }
    else if (tr[rch].maxn > R)
        modify_r(rch);
    tr[id].minx = tr[lch].minx;
    tr[id].maxn = tr[rch].maxn;
    return;
}
int query(int id, int pos)
{
    pushdown(id);
    if (tr[id].l == tr[id].r)
        return tr[id].minx;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (pos <= mid)
        return query(lch, pos);
    else
        return query(rch, pos);
}
signed main()
{
    scanf("%lld%lld%lld", &n, &L, &R);
    for (int i = 1; i <= n; ++i)
    {
        char type;
        scanf(" %c", &type);
        if (type == '+')
            q[i].type = 1;
        else if (type == '-')
            q[i].type = 2;
        else if (type == '*')
            q[i].type = 3;
        else
            q[i].type = 4;
        scanf("%lld", &q[i].num);
    }
    scanf("%lld", &Q);
    for (int i = 1; i <= Q; ++i)
    {
        s[i].id = i;
        scanf("%lld", &s[i].x);
    }
    sort(s + 1, s + Q + 1, cmp);
    build(1, 1, Q);
    for (int i = 1; i <= n; ++i)
    {
        if (q[i].type == 1)
            add(1, q[i].num, 0, 0);
        else if (q[i].type == 2)
            add(1, -q[i].num, 0, 0);
        else if (q[i].type == 3)
            add(1, 0, q[i].num, 0);
        else if (q[i].type == 4)
            add(1, 0, 0, q[i].num);
        modify_l(1);
        modify_r(1);
    }
    for (int i = 1; i <= Q; ++i)
        ans[s[i].id] = query(1, i);
    for (int i = 1; i <= Q; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}