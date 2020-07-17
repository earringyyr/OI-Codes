#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;
int n, tot, in[1000005], out[1000005], ans[1000005], c[2000005];
vector<int> vec[1000005];
struct point
{
    int sum;
    int fa[1000005];
    int dep[1000005];
    int siz[1000005];
    int top[1000005];
    int son[1000005];
    int head[1000005];
    struct node
    {
        int v;
        int next;
    } a[2000005];
    void ins(int u, int v)
    {
        ++sum;
        a[sum].v = v;
        a[sum].next = head[u];
        head[u] = sum;
        ++sum;
        a[sum].v = u;
        a[sum].next = head[v];
        head[v] = sum;
        return;
    }
    void dfs1(int k)
    {
        son[k] = -1;
        dep[k] = dep[fa[k]] + 1;
        siz[k] = 1;
        int d = head[k];
        while (d)
        {
            if (a[d].v != fa[k])
            {
                fa[a[d].v] = k;
                dfs1(a[d].v);
                if (son[k] == -1 || siz[son[k]] < siz[a[d].v])
                    son[k] = a[d].v;
                siz[k] += siz[a[d].v];
            }
            d = a[d].next;
        }
        return;
    }
    void dfs2(int k, int topf)
    {
        top[k] = topf;
        int d = head[k];
        if (son[k] != -1)
            dfs2(son[k], topf);
        d = head[k];
        while (d)
        {
            if (a[d].v != fa[k] && a[d].v != son[k])
                dfs2(a[d].v, a[d].v);
            d = a[d].next;
        }
        return;
    }
    void dfs3(int k)
    {
        in[k] = ++tot;
        if (son[k] != -1)
            dfs3(son[k]);
        int d = head[k];
        while (d)
        {
            if (a[d].v != fa[k] && a[d].v != son[k])
                dfs3(a[d].v);
            d = a[d].next;
        }
        out[k] = ++tot;
        return;
    }
    int lca(int x, int y)
    {
        while (top[x] != top[y])
        {
            if (dep[top[x]] < dep[top[y]])
                swap(x, y);
            x = fa[top[x]];
        }
        if (dep[x] < dep[y])
            return x;
        else
            return y;
    }
} tr1, tr2;
int lowbit(int x)
{
    return x & -x;
}
void modify(int x, int val)
{
    while (x <= tot)
    {
        c[x] += val;
        x += lowbit(x);
    }
    return;
}
int query(int x)
{
    int y = 0;
    while (x >= 1)
    {
        y += c[x];
        x -= lowbit(x);
    }
    return y;
}
void solve(int k)
{
    int lca = tr1.lca(k, tr2.fa[k]);
    int pre;
    if (k > 1)
        pre = query(in[k]) + query(in[tr2.fa[k]]) - 2 * query(in[lca]);
    int d = tr2.head[k];
    while (d)
    {
        if (tr2.a[d].v != tr2.fa[k])
            solve(tr2.a[d].v);
        d = tr2.a[d].next;
    }
    for (int i = 0; i < vec[k].size(); i++)
    {
        int x = vec[k][i];
        if (x > 0)
        {
            modify(in[x], 1);
            modify(out[x], -1);
        }
        else
        {
            modify(in[-x], -2);
            modify(out[-x], 2);
        }
    }
    if (k > 1)
        ans[k] = query(in[k]) + query(in[tr2.fa[k]]) - 2 * query(in[lca]) - pre;
    return;
}
int main()
{
    int size = 128 << 20;
    __asm__("movq %0,%%rsp\n" ::"r"((char *)malloc(size) + size));
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        tr2.ins(x, y);
    }
    for (int i = 1; i < n; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        tr1.ins(x, y);
    }
    tr1.dfs1(1);
    tr1.dfs2(1, 1);
    tr1.dfs3(1);
    tr2.dfs1(1);
    tr2.dfs2(1, 1);
    for (int i = 1; i < 2 * n - 1; i += 2)
    {
        int x = tr1.a[i].v, y = tr1.a[i + 1].v, lca = tr2.lca(x, y);
        if (tr1.dep[x] < tr1.dep[y])
            swap(x, y);
        vec[x].push_back(x);
        vec[y].push_back(x);
        vec[lca].push_back(-x);
    }
    solve(1);
    for (int i = 1; i < n * 2 - 1; i += 2)
    {
        int x = tr2.a[i].v, y = tr2.a[i + 1].v;
        if (tr2.dep[x] < tr2.dep[y])
            swap(x, y);
        printf("%d ", ans[x]);
    }
    exit(0);
}