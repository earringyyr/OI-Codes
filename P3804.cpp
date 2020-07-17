#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, sum, ans, lst = 1, cnt = 1;
int siz[2000005], head[2000005];
char s[1000005];
struct node
{
    int fa;
    int len;
    int son[26];
} st[2000005];
struct edge
{
    int v;
    int nxt;
} a[2000005];
void build(int k)
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
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
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
    if (siz[k] != 1)
        ans = max(ans, siz[k] * st[k].len);
}
int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i)
        build(s[i] - 'a');
    for (int i = 2; i <= cnt; ++i)
        ins(st[i].fa, i);
    dfs(1);
    printf("%d", ans);
    return 0;
}