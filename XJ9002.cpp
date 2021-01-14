#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, lst, cnt, sum, num, ans;
int p[1000005], q[1000005];
int siz[4000005], head[4000005];
string s[1000005];
struct node
{
    int fa;
    int len;
    int son[26];
} st[4000005];
struct edge
{
    int v;
    int nxt;
} a[4000005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void init()
{
    for (int i = 1; i <= cnt; ++i)
    {
        st[i].fa = 0;
        st[i].len = 0;
        memset(st[i].son, 0, sizeof(st[i].son));
        siz[i] = 0;
        head[i] = 0;
    }
    sum = 0;
    lst = 1;
    cnt = 1;
    return;
}
void build(int k, int val)
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
        siz[lst] = (siz[lst] + val) % mod;
        return;
    }
    lst = ++cnt;
    int np = lst;
    st[np].len = st[p].len + 1;
    siz[np] = val;
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
        siz[k] = (siz[k] + siz[a[d].v]) % mod;
        d = a[d].nxt;
    }
    num = (num + (ll)siz[k] * siz[k] % mod * (st[k].len - st[st[k].fa].len) % mod) % mod;
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &q[i]);
        p[i] = (1 - q[i] + mod) % mod;
    }
    for (int i = 1; i <= n; ++i)
    {
        cin >> s[i];
        int len = s[i].length();
        init();
        for (int j = 0; j < len; ++j)
            build(s[i][j] - 'a', 1);
        for (int i = 2; i <= cnt; ++i)
            ins(st[i].fa, i);
        num = 0;
        dfs(1);
        ans = (ans + num) % mod;
        init();
        for (int j = 0; j < len; ++j)
            build(s[i][j] - 'a', p[i]);
        lst = 1;
        for (int j = len - 1; j >= 0; --j)
            build(s[i][j] - 'a', q[i]);
        for (int i = 2; i <= cnt; ++i)
            ins(st[i].fa, i);
        num = 0;
        dfs(1);
        ans = (ans - num + mod) % mod;
    }
    init();
    for (int i = 1; i <= n; ++i)
    {
        int len = s[i].length();
        lst = 1;
        for (int j = 0; j < len; ++j)
            build(s[i][j] - 'a', p[i]);
        lst = 1;
        for (int j = len - 1; j >= 0; --j)
            build(s[i][j] - 'a', q[i]);
    }
    for (int i = 2; i <= cnt; ++i)
        ins(st[i].fa, i);
    num = 0;
    dfs(1);
    ans = (ans + num) % mod;
    printf("%d", ans);
    return 0;
}