#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#define lch id << 1
#define rch id << 1 | 1
using namespace std;
int n, m, lst, sum, cnt, num, tot;
int head[200005], pos[200005], anc[200005];
int in[200005], out[200005];
int rt[200005], val[200005 * 4];
char s[200005];
struct node
{
    int v;
    int nxt;
} a[200005];
struct pam
{
    int len;
    int fail;
    int son[26];
} tri[200005];
struct tree
{
    int l;
    int r;
    int num;
} tr[200005 * 100];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
int calc(int id)
{
    return tri[id].len - tri[tri[id].fail].len;
}
int getfail(int id, int w)
{
    while (s[w - tri[id].len - 1] != s[w])
        id = tri[id].fail;
    return id;
}
void insert(int k, int w)
{
    int cur = getfail(lst, w);
    if (!tri[cur].son[k])
    {
        lst = ++cnt;
        tri[cnt].len = tri[cur].len + 2;
        tri[cnt].fail = tri[getfail(tri[cur].fail, w)].son[k];
        tri[cur].son[k] = cnt;
        ins(tri[cnt].fail, cnt);
        if (tri[cnt].fail > 1 && calc(cnt) == calc(tri[cnt].fail))
            anc[cnt] = anc[tri[cnt].fail];
        else
            anc[cnt] = cnt;
    }
    lst = tri[cur].son[k];
    pos[w] = tri[cur].son[k];
    return;
}
void dfs(int k)
{
    in[k] = ++num;
    int d = head[k];
    while (d)
    {
        dfs(a[d].v);
        d = a[d].nxt;
    }
    out[k] = num;
    return;
}
void build(int &id, int l, int r, int L, int R)
{
    tr[++tot] = tr[id];
    id = tot;
    if (l == L && r == R)
    {
        ++tr[id].num;
        return;
    }
    int mid = (l + r) >> 1;
    if (R <= mid)
        build(tr[id].l, l, mid, L, R);
    if (L >= mid + 1)
        build(tr[id].r, mid + 1, r, L, R);
    if (L <= mid && R >= mid + 1)
    {
        build(tr[id].l, l, mid, L, mid);
        build(tr[id].r, mid + 1, r, mid + 1, R);
    }
    return;
}
int query(int id, int l, int r, int w)
{
    if (!id || l == r)
        return tr[id].num;
    int mid = (l + r) >> 1;
    if (w <= mid)
        return tr[id].num + query(tr[id].l, l, mid, w);
    else
        return tr[id].num + query(tr[id].r, mid + 1, r, w);
}
void update(int id, int l, int r, int w, int vl)
{
    val[id] = vl;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (w <= mid)
        update(lch, l, mid, w, vl);
    else
        update(rch, mid + 1, r, w, vl);
    return;
}
int ask(int id, int l, int r, int L, int R)
{
    if (!val[id] || (l == L && r == R))
        return val[id];
    int mid = (l + r) >> 1;
    if (R <= mid)
        return ask(lch, l, mid, L, R);
    if (L >= mid + 1)
        return ask(rch, mid + 1, r, L, R);
    return max(ask(lch, l, mid, L, mid), ask(rch, mid + 1, r, mid + 1, R));
}
int main()
{
    int type;
    scanf("%d", &type);
    scanf("%d%d", &n, &m);
    scanf("%s", s + 1);
    lst = 1;
    cnt = 1;
    tri[0].fail = 1;
    tri[1].len = -1;
    tri[1].fail = 1;
    anc[1] = 1;
    ins(1, 0);
    for (int i = 1; i <= n; ++i)
        insert(s[i] - 'a', i);
    dfs(1);
    int l, r;
    for (int i = 1; i <= n; ++i)
    {
        rt[i] = rt[i - 1];
        for (int k = pos[i]; k > 1; k = tri[anc[k]].fail)
        {
            l = max(1, ask(1, 1, num, in[k], out[k]) - tri[k].len + 2);
            r = i - tri[anc[k]].len + 1;
            build(rt[i], 1, n, l, r);
        }
        update(1, 1, num, in[pos[i]], i);
    }
    int ans = 0;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &l, &r);
        l ^= ans * type;
        r ^= ans * type;
        ans = query(rt[r], 1, n, l);
        printf("%d\n", ans);
    }
    return 0;
}