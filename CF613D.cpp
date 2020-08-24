#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int n, sum, cnt, q, tail, ans;
int head[100005], k[200005];
int fa[100005], dep[100005], son[100005];
int siz[100005], dfn[100005], top[100005];
int st[100005], flg[100005];
struct node
{
    int v;
    int nxt;
} a[200005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
bool cmp(int aa, int bb)
{
    return dfn[aa] < dfn[bb];
}
void dfs1(int k, int f)
{
    siz[k] = 1;
    son[k] = -1;
    fa[k] = f;
    int d = head[k];
    while (d)
    {
        if (a[d].v != f)
        {
            dep[a[d].v] = dep[k] + 1;
            dfs1(a[d].v, k);
            siz[k] += siz[a[d].v];
            if (son[k] == -1 || siz[a[d].v] > siz[son[k]])
                son[k] = a[d].v;
        }
        d = a[d].nxt;
    }
    return;
}
void dfs2(int k, int topf)
{
    dfn[k] = ++cnt;
    top[k] = topf;
    if (son[k] != -1)
        dfs2(son[k], topf);
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa[k] && a[d].v != son[k])
            dfs2(a[d].v, a[d].v);
        d = a[d].nxt;
    }
    return;
}
int LCA(int u, int v)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    if (dfn[u] > dfn[v])
        swap(u, v);
    return u;
}
void dfs(int k)
{
    int num = 0;
    int d = head[k];
    while (d)
    {
        dfs(a[d].v);
        if (flg[a[d].v])
            ++num;
        d = a[d].nxt;
    }
    if (flg[k] && num)
        ans += num;
    if (!flg[k] && num)
    {
        if (num == 1)
            flg[k] = 1;
        else
            ++ans;
    }
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    memset(head, 0, sizeof(head));
    scanf("%d", &q);
    int T = 1;
query:
    while (T <= q)
    {
        ++T;
        sum = 0;
        tail = 0;
        ans = 0;
        scanf("%d", &k[0]);
        for (int i = 1; i <= k[0]; ++i)
        {
            scanf("%d", &k[i]);
            flg[k[i]] = 1;
        }
        sort(k + 1, k + k[0] + 1, cmp);
        int len = k[0];
        if (k[1] != 1)
        {
            st[++tail] = 1;
            k[++k[0]] = 1;
        }
        for (int i = 1; i <= len; ++i)
        {
            if (i == 1)
            {
                st[++tail] = k[i];
                continue;
            }
            if (fa[k[i]] == st[tail])
            {
                puts("-1");
                for (int j = 1; j <= k[0]; ++j)
                {
                    flg[k[j]] = 0;
                    head[k[j]] = 0;
                }
                goto query;
            }
            int lca = LCA(st[tail], k[i]);
            if (lca == st[tail])
            {
                st[++tail] = k[i];
                continue;
            }
            while (tail > 1 && dep[st[tail - 1]] > dep[lca])
            {
                ins(st[tail - 1], st[tail]);
                --tail;
            }
            int tmp = st[tail--];
            if (dep[st[tail]] == dep[lca])
            {
                if (flg[st[tail]] && fa[k[i]] == st[tail])
                {
                    puts("-1");
                    for (int j = 1; j <= k[0]; ++j)
                    {
                        flg[k[j]] = 0;
                        head[k[j]] = 0;
                    }
                    goto query;
                }
                ins(st[tail], tmp);
                st[++tail] = k[i];
            }
            else
            {
                ins(lca, tmp);
                st[++tail] = lca;
                st[++tail] = k[i];
                k[++k[0]] = lca;
            }
        }
        while (tail > 1)
        {
            ins(st[tail - 1], st[tail]);
            --tail;
        }
        dfs(1);
        printf("%d\n", ans);
        for (int i = 1; i <= k[0]; ++i)
        {
            flg[k[i]] = 0;
            head[k[i]] = 0;
        }
    }
    return 0;
}