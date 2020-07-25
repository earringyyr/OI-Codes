#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int mod = 1000000007;
int n, cnt, k, num, lst[4], siz[2000005];
char s[2000005], ans[2000005];
struct node
{
    int fa;
    int len;
    int son[4];
} st[2000005];
struct sam
{
    int rt, lst;
    inline void build(int k)
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
            st[np].fa = rt;
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
} tr[2000005];
inline void dfs0(int w)
{
    if (siz[w])
        return;
    siz[w] = 1;
    for (register int i = 0; i < 4; ++i)
        if (st[w].son[i])
        {
            dfs0(st[w].son[i]);
            siz[w] = (siz[w] + siz[st[w].son[i]]) % mod;
        }
    return;
}
inline void dfs1(int w)
{
    ++siz[tr[1].rt];
    for (register int i = 1; i <= num; ++i)
        putchar(ans[i]);
    putchar('\n');
    for (register int i = 0; i < 4; ++i)
        if (st[w].son[i])
        {
            ++num;
            if (i == 0)
                ans[num] = 'A';
            else if (i == 1)
                ans[num] = 'C';
            else if (i == 2)
                ans[num] = 'G';
            else if (i == 3)
                ans[num] = 'T';
            dfs1(st[w].son[i]);
            --num;
        }
    return;
}
int main()
{
    scanf("%d", &n);
    for (register int i = 1; i <= n; ++i)
    {
        scanf("%s", s + 1);
        int len = strlen(s + 1);
        ++cnt;
        tr[i].rt = cnt;
        tr[i].lst = cnt;
        for (int j = 1; j <= len; ++j)
            if (s[j] == 'A')
                tr[i].build(0);
            else if (s[j] == 'C')
                tr[i].build(1);
            else if (s[j] == 'G')
                tr[i].build(2);
            else if (s[j] == 'T')
                tr[i].build(3);
    }
    tr[n + 1].rt = cnt + 1;
    for (register int i = n; i >= 1; --i)
    {
        for (register int j = tr[i].rt; j < tr[i + 1].rt; ++j)
            for (register int k = 0; k < 4; ++k)
                if (!st[j].son[k])
                    st[j].son[k] = lst[k];
        for (register int j = 0; j < 4; ++j)
            if (st[tr[i].rt].son[j])
                lst[j] = st[tr[i].rt].son[j];
    }
    scanf("%d", &k);
    if (k)
    {
        ++siz[tr[1].rt];
        putchar('\n');
        for (register int i = 0; i < 4; ++i)
            if (st[tr[1].rt].son[i])
            {
                ++num;
                if (i == 0)
                    ans[num] = 'A';
                else if (i == 1)
                    ans[num] = 'C';
                else if (i == 2)
                    ans[num] = 'G';
                else if (i == 3)
                    ans[num] = 'T';
                dfs1(st[tr[1].rt].son[i]);
                --num;
            }
    }
    else
        dfs0(tr[1].rt);
    printf("%d", siz[tr[1].rt]);
    return 0;
}