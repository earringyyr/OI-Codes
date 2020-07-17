#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, x, xx, lst = 1, cnt = 1, ans;
int c[4005], a[4005];
int maxn[4005], minx[4005];
char s[4005];
struct node
{
    int fa;
    int len;
    int son[26];
} st[4005];
void build(int k)
{
    int p = lst;
    lst = ++cnt;
    int np = lst;
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
            st[q].fa = nq;
            st[np].fa = nq;
            while (p && st[p].son[k] == q)
            {
                st[p].son[k] = nq;
                p = st[p].fa;
            }
        }
    }
    return;
}
int main()
{
    scanf("%d", &n);
    scanf("%s", s + 1);
    m = strlen(s + 1);
    memset(minx, 0x7f, sizeof(minx));
    for (int i = 1; i <= m; ++i)
        build(s[i] - 'a');
    for (int i = 1; i <= cnt; ++i)
        ++c[st[i].len];
    for (int i = 1; i <= m; ++i)
        c[i] += c[i - 1];
    for (int i = 1; i <= cnt; ++i)
        a[c[st[i].len]--] = i;
    for (int i = 2; i <= n; ++i)
    {
        scanf("%s", s + 1);
        m = strlen(s + 1);
        int p = 1, len = 0;
        memset(maxn, 0, sizeof(maxn));
        for (int j = 1; j <= m; ++j)
        {
            int k = s[j] - 'a';
            while (p && !st[p].son[k])
            {
                p = st[p].fa;
                len = st[p].len;
            }
            if (p)
            {
                ++len;
                p = st[p].son[k];
                maxn[p] = max(maxn[p], len);
            }
            else
            {
                p = 1;
                len = 0;
            }
            xx = x;
        }
        for (int j = cnt; j >= 1; --j)
        {
            int k = a[j];
            int fa = st[k].fa;
            maxn[fa] = min(st[fa].len, max(maxn[fa], maxn[k]));
            minx[k] = min(minx[k], maxn[k]);
        }
    }
    for (int i = 1; i <= cnt; ++i)
        ans = max(ans, minx[i]);
    printf("%d", ans);
    return 0;
}