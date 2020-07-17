#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
int n, cnt = 1, lst = 1, siz[200005], c[100005], a[200005];
ll ans, num[200005];
char s[100005];
struct node
{
    int fa;
    int len;
    int son[26];
} st[200005];
void build(int k)
{
    int p = lst;
    lst = ++cnt;
    int np = lst;
    st[np].len = st[p].len + 1;
    siz[np] = 1;
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
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ans = 0;
        cnt = 1;
        lst = 1;
        memset(st, 0, sizeof(st));
        memset(c, 0, sizeof(c));
        memset(siz, 0, sizeof(siz));
        scanf("%s", s + 1);
        n = strlen(s + 1);
        for (int i = 1; i <= n; ++i)
            build(s[i] - 'a');
        for (int i = 1; i <= cnt; ++i)
            ++c[st[i].len];
        for (int i = 1; i <= n; ++i)
            c[i] += c[i - 1];
        for (int i = 1; i <= cnt; ++i)
            a[c[st[i].len]--] = i;
        for (int i = cnt; i >= 1; --i)
            siz[st[a[i]].fa] += siz[a[i]];
        for (int i = 1; i <= cnt; ++i)
            ans += (ll)siz[i] * siz[i] * (st[i].len - st[st[i].fa].len);
        printf("%lld\n", ans);
    }
    return 0;
}