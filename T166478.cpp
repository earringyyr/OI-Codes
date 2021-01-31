#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int Q, lst, cnt = 1, top, mx;
int type[2000005], k[2000005], w[2000005];
int ed[2000005], q[2000005];
int maxn[4000005];
ll c[4000005];
char s[2000005];
struct node
{
    int fa;
    int len;
    int son[26];
} st[4000005];
int lowbit(int x)
{
    return x & -x;
}
void add(int x, ll val)
{
    while (x <= mx)
    {
        c[x] += val;
        x += lowbit(x);
    }
    return;
}
ll ask(int x)
{
    ll num = 0;
    while (x >= 1)
    {
        num += c[x];
        x -= lowbit(x);
    }
    return num;
}
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
    scanf("%d", &Q);
    for (int i = 1; i <= Q; ++i)
    {
        scanf("%d", &type[i]);
        if (type[i] == 1)
        {
            scanf("%d%s", &w[i], s + 1);
            int len = strlen(s + 1);
            mx = max(mx, len);
            lst = 1;
            for (int j = 1; j <= len; ++j)
            {
                build(s[j] - 'a');
                q[++top] = lst;
            }
        }
        else
            scanf("%d", &k[i]);
        ed[i] = top;
    }
    for (int i = 1; i <= Q; ++i)
        if (type[i] == 1)
            for (int j = ed[i - 1] + 1; j <= ed[i]; ++j)
            {
                int d = q[j];
                while (d && maxn[d] < w[i])
                {
                    add(st[st[d].fa].len + 1, w[i] - maxn[d]);
                    add(st[d].len + 1, maxn[d] - w[i]);
                    maxn[d] = w[i];
                    d = st[d].fa;
                }
            }
        else
            printf("%lld\n", ask(k[i]));
    return 0;
}