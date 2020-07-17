#include <iostream>
#include <cstdio>
#include <cstring>
#include <tr1/unordered_map>
using namespace std;
using namespace tr1;
int n, lst = 1, cnt = 1;
long long ans;
struct node
{
    int fa;
    int len;
    unordered_map<int, int> son;
} st[200005];
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
    ans += st[np].len - st[st[np].fa].len;
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        scanf("%d", &x);
        build(x);
        printf("%lld\n", ans);
    }
    return 0;
}