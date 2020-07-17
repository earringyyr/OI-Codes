#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, t, k, lst = 1, cnt = 1;
int siz[1000005], a[1000005], num[1000005], cc[500005];
char s[500005];
struct node
{
    int fa;
    int len;
    int son[26];
} st[1000005];
void build(int c)
{
    int p = lst;
    lst = ++cnt;
    int np = lst;
    siz[np] = 1;
    st[np].len = st[p].len + 1;
    while (p && !st[p].son[c])
    {
        st[p].son[c] = np;
        p = st[p].fa;
    }
    if (!p)
        st[np].fa = 1;
    else
    {
        int q = st[p].son[c];
        if (st[q].len == st[p].len + 1)
            st[np].fa = q;
        else
        {
            int nq = ++cnt;
            st[nq] = st[q];
            st[nq].len = st[p].len + 1;
            st[np].fa = nq;
            st[q].fa = nq;
            while (p && st[p].son[c] == q)
            {
                st[p].son[c] = nq;
                p = st[p].fa;
            }
        }
    }
    return;
}
int main()
{
    scanf("%s", s + 1);
    scanf("%d%d", &t, &k);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i)
        build(s[i] - 'a');
    for (int i = 1; i <= cnt; ++i)
        ++cc[st[i].len];
    for (int i = 1; i <= n; ++i)
        cc[i] += cc[i - 1];
    for (int i = 1; i <= cnt; ++i)
        a[cc[st[i].len]--] = i;
    for (int i = cnt; i >= 1; --i)
        if (t == 0)
            siz[a[i]] = 1;
        else
            siz[st[a[i]].fa] += siz[a[i]];
    siz[1] = 0;
    for (int i = cnt; i >= 1; --i)
    {
        num[a[i]] = siz[a[i]];
        for (int j = 0; j < 26; ++j)
            if (st[a[i]].son[j])
                num[a[i]] += num[st[a[i]].son[j]];
    }
    if (k > num[1])
        printf("-1");
    else
    {
        int p = 1;
        k -= siz[p];
        while (k > 0)
        {
            for (int i = 0; i < 26; ++i)
                if (k > num[st[p].son[i]])
                    k -= num[st[p].son[i]];
                else
                {
                    p = st[p].son[i];
                    k -= siz[p];
                    putchar('a' + i);
                    break;
                }
        }
    }
    return 0;
}