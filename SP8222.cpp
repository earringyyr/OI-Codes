#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, sum, lst = 1, cnt = 1;
int f[250005], head[500005], siz[500005];
char s[250005];
struct node
{
    int fa;
    int len;
    int son[26];
} st[500005];
struct edge
{
    int v;
    int nxt;
} a[500005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void insert(int k)
{
    int p = lst;
    lst = ++cnt;
    int np = lst;
    siz[np] = 1;
    st[np].len = st[p].len + 1;
    while (p && !st[p].son[k])
    {
        st[p].son[k] = np;
        p = st[p].fa;
    }
    if (!p)
        st[np].fa = 1;
    else
    {
        int q = st[p].son[k];
        if (st[q].len == st[p].len + 1)
            st[np].fa = q;
        else
        {
            int nq = ++cnt;
            st[nq] = st[q];
            st[nq].len = st[p].len + 1;
            st[np].fa = nq;
            st[q].fa = nq;
            while (p && st[p].son[k] == q)
            {
                st[p].son[k] = nq;
                p = st[p].fa;
            }
        }
    }
    return;
}
void dfs(int k)
{
    int d = head[k];
    while (d)
    {
        dfs(a[d].v);
        siz[k] += siz[a[d].v];
        d = a[d].nxt;
    }
    f[st[k].len] = max(f[st[k].len], siz[k]);
    return;
}
int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i)
        insert(s[i] - 'a');
    for (int i = 2; i <= cnt; ++i)
        ins(st[i].fa, i);
    dfs(1);
    for (int i = n - 1; i >= 1; --i)
        f[i] = max(f[i], f[i + 1]);
    for (int i = 1; i <= n; ++i)
        printf("%d\n", f[i]);
    return 0;
}