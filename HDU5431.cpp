#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, lst, cnt, num, lg[35], a[40005], c[20005];
char s[20005], ans[35];
struct node
{
    int fa;
    int len;
    int son[2];
    int cnt[35];
} st[40005];
void insert(int k)
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
void dfs(int rt, int k, int len)
{
    if (!len)
        return;
    if (st[rt].son[0])
    {
        if (st[st[rt].son[0]].cnt[len - 1] >= k)
        {
            ans[++num] = 'A';
            dfs(st[rt].son[0], k, len - 1);
        }
        else
        {
            ans[++num] = 'B';
            dfs(st[rt].son[1], k - st[st[rt].son[0]].cnt[len - 1], len - 1);
        }
    }
    else
    {
        if ((1 << (len - 1)) >= k)
        {
            ans[++num] = 'A';
            dfs(st[rt].son[0], k, len - 1);
        }
        else
        {
            ans[++num] = 'B';
            dfs(st[rt].son[1], k - (1 << (len - 1)), len - 1);
        }
    }
    return;
}
int main()
{
    for (int i = 0; i <= 30; ++i)
        lg[i] = (1 << i);
    int T;
    scanf("%d", &T);
    while (T--)
    {
        lst = 1;
        cnt = 1;
        memset(c, 0, sizeof(c));
        memset(st, 0, sizeof(st));
        scanf("%s", s + 1);
        n = strlen(s + 1);
        for (int i = 1; i <= n; ++i)
            insert(s[i] - 'A');
        for (int i = 1; i <= cnt; ++i)
            ++c[st[i].len];
        for (int i = 1; i <= n; ++i)
            c[i] += c[i - 1];
        for (int i = 1; i <= cnt; ++i)
            a[c[st[i].len]--] = i;
        for (int i = cnt; i >= 1; --i)
            for (int j = 1; j <= 30; ++j)
                for (int k = 0; k < 2; ++k)
                    if (st[a[i]].son[k])
                        st[a[i]].cnt[j] += st[st[a[i]].son[k]].cnt[j - 1];
                    else
                        st[a[i]].cnt[j] += lg[j - 1];
        int t;
        scanf("%d", &t);
        for (int i = 1; i <= t; ++i)
        {
            num = 0;
            int k;
            scanf("%d", &k);
            int pos = 1;
            for (int j = 1; j <= 30 && k > st[1].cnt[j]; ++j)
            {
                k -= st[1].cnt[j];
                ++pos;
            }
            dfs(1, k, pos);
            for (int j = 1; j <= pos; ++j)
                putchar(ans[j]);
            putchar('\n');
        }
    }
    return 0;
}