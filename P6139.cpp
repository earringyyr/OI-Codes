#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, lst, cnt = 1;
ll ans;
char s[1000005];
struct node
{
    int fa;
    int len;
    int son[26];
} st[2000005];
void build(int k)
{
    int p = lst;
    if (st[p].son[k])
    {
        int q = st[p].son[k];
        if (st[q].len == st[p].len + 1)
            lst = q;
        else
        {
            lst = ++cnt;
            int nq = lst;
            st[nq] = st[q];
            st[nq].len = st[p].len + 1;
            st[q].fa = nq;
            while (p && st[p].son[k] == q)
            {
                st[p].son[k] = nq;
                p = st[p].fa;
            }
        }
        return;
    }
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
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        lst = 1;
        scanf("%s", s + 1);
        int len = strlen(s + 1);
        for (int j = 1; j <= len; ++j)
            build(s[j] - 'a');
    }
    for (int i = 2; i <= cnt; ++i)
        ans += st[i].len - st[st[i].fa].len;
    printf("%lld", ans);
    return 0;
}