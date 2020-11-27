#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
typedef long long ll;
int n, k;
ll ans;
struct node
{
    int a;
    int b;
} w[100005];
struct tree
{
    int l;
    int r;
    int pos;
    int maxn;
    int num;
    int lazy;
} tr[400005];
bool cmp(node aa, node bb)
{
    if (aa.a != bb.a)
        return aa.a > bb.a;
    return aa.b < bb.b;
}
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    tr[id].num = (l + k) / 2;
    tr[id].lazy = 0;
    if (l == r)
    {
        tr[id].pos = l;
        tr[id].maxn = w[l].b;
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    if (tr[lch].maxn > tr[rch].maxn)
    {
        tr[id].pos = tr[lch].pos;
        tr[id].maxn = tr[lch].maxn;
    }
    else
    {
        tr[id].pos = tr[rch].pos;
        tr[id].maxn = tr[rch].maxn;
    }
    tr[id].num = min(tr[lch].num, tr[rch].num);
    return;
}
void change(int id, int pos)
{
    if (tr[id].l == tr[id].r)
    {
        tr[id].maxn = -1;
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (pos <= mid)
        change(lch, pos);
    else
        change(rch, pos);
    if (tr[lch].maxn > tr[rch].maxn)
    {
        tr[id].pos = tr[lch].pos;
        tr[id].maxn = tr[lch].maxn;
    }
    else
    {
        tr[id].pos = tr[rch].pos;
        tr[id].maxn = tr[rch].maxn;
    }
    return;
}
void pushdown(int id)
{
    int lazy = tr[id].lazy;
    tr[id].lazy = 0;
    tr[lch].num -= lazy;
    tr[lch].lazy += lazy;
    tr[rch].num -= lazy;
    tr[rch].lazy += lazy;
}
void add(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r)
    {
        --tr[id].num;
        ++tr[id].lazy;
        return;
    }
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        add(lch, l, r);
    if (l >= mid + 1)
        add(rch, l, r);
    if (l <= mid && r >= mid + 1)
    {
        add(lch, l, mid);
        add(rch, mid + 1, r);
    }
    tr[id].num = min(tr[lch].num, tr[rch].num);
    return;
}
int ask(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].num;
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask(lch, l, r);
    if (l >= mid + 1)
        return ask(rch, l, r);
    return min(ask(lch, l, mid), ask(rch, mid + 1, r));
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ans = 0;
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &w[i].a);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &w[i].b);
        sort(w + 1, w + n + 1, cmp);
        build(1, 1, n);
        for (int i = 1; i <= (n + k) / 2; ++i)
        {
            int flg = 0;
            while (!flg)
            {
                int pos = tr[1].pos;
                change(1, pos);
                if (ask(1, pos, n) == 0)
                    continue;
                flg = 1;
                add(1, pos, n);
                ans += w[pos].b;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}