#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
int n, cnt, num, sum;
char s[300005];
int w[20005], pos[20005];
int l[300005], nxt[300005], head[300005], dfn[300005], gu[300005], ttr[300005][26];
struct node
{
    int v;
    int next;
} a[300005];
struct tree
{
    int l;
    int r;
    int maxn;
    int lazy;
} tr[1200005];
inline void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
inline void insert(char *s)
{
    int len = strlen(s), rt = 1;
    for (int i = 0; i < len; ++i)
    {
        if (!ttr[rt][s[i] - 'a'])
            ttr[rt][s[i] - 'a'] = ++cnt;
        rt = ttr[rt][s[i] - 'a'];
    }
    return;
}
inline void build_fail()
{
    for (int i = 0; i < 26; ++i)
        ttr[0][i] = 1;
    int head = 0, tail = 1;
    l[1] = 1;
    nxt[1] = 0;
    while (head < tail)
    {
        int k = l[++head];
        for (int i = 0; i < 26; ++i)
            if (!ttr[k][i])
                ttr[k][i] = ttr[nxt[k]][i];
            else
            {
                nxt[ttr[k][i]] = ttr[nxt[k]][i];
                l[++tail] = ttr[k][i];
            }
    }
    return;
}
inline void dfs(int k)
{
    dfn[k] = ++num;
    int d = head[k];
    while (d)
    {
        dfs(a[d].v);
        d = a[d].next;
    }
    gu[k] = num;
    return;
}
inline void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    tr[id].maxn = 0;
    tr[id].lazy = 0;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    return;
}
inline void pushdown(int id)
{
    if (tr[id].l != tr[id].r)
    {
        int lazy = tr[id].lazy;
        tr[id].lazy = 0;
        tr[lch].maxn = max(tr[lch].maxn, lazy);
        tr[rch].maxn = max(tr[rch].maxn, lazy);
        tr[lch].lazy = max(tr[lch].lazy, lazy);
        tr[rch].lazy = max(tr[rch].lazy, lazy);
    }
    return;
}
inline void change(int id, int l, int r, int val)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].maxn = max(tr[id].maxn, val);
        tr[id].lazy = max(tr[id].lazy, val);
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        change(lch, l, r, val);
    if (l >= mid + 1)
        change(rch, l, r, val);
    if (l <= mid && r >= mid + 1)
    {
        change(lch, l, mid, val);
        change(rch, mid + 1, r, val);
    }
    tr[id].maxn = max(tr[lch].maxn, tr[rch].maxn);
    return;
}
inline int query(int id, int ww)
{
    pushdown(id);
    if (tr[id].l == tr[id].r)
        return tr[id].maxn;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (ww <= mid)
        return query(lch, ww);
    else
        return query(rch, ww);
}
int main()
{
    int t;
    scanf("%d", &t);
    for (register int tt = 1; tt <= t; ++tt)
    {
        cnt = 1;
        sum = 0;
        num = 0;
        memset(head, 0, sizeof(head));
        memset(ttr, 0, sizeof(ttr));
        scanf("%d", &n);
        for (register int i = 1; i <= n; ++i)
        {
            scanf("%s%d", s + pos[i - 1], &w[i]);
            pos[i] = strlen(s);
            insert(s + pos[i - 1]);
        }
        build_fail();
        for (register int i = 2; i <= cnt; ++i)
            ins(nxt[i], i);
        num = 0;
        dfs(1);
        build(1, 1, cnt);
        int ans = 0;
        for (register int i = 1; i <= n; ++i)
        {
            int tmp = 0, rt = 1;
            for (register int j = pos[i - 1]; j < pos[i]; ++j)
            {
                rt = ttr[rt][s[j] - 'a'];
                tmp = max(tmp, query(1, dfn[rt]));
            }
            tmp += w[i];
            ans = max(ans, tmp);
            change(1, dfn[rt], gu[rt], tmp);
        }
        printf("Case #%d: %d\n", tt, ans);
    }
    return 0;
}