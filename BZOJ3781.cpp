#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int n, m, k, len, num, a[50005], vis[50005], ans[50005];
struct node
{
    int id;
    int l;
    int r;
} s[50005];
bool cmp(node aa, node bb)
{
    if ((aa.l - 1) / len == (bb.l - 1) / len)
    {
        if (aa.r != bb.r)
            if ((aa.l - 1) / len % 2 == 0)
                return aa.r < bb.r;
            else
                return aa.r > bb.r;
        else
            return aa.l < bb.l;
    }
    else
    {
        if (aa.l != bb.l)
            return aa.l < bb.l;
        return aa.l < bb.l;
    }
}
void add(int k)
{
    num -= vis[a[k]] * vis[a[k]];
    ++vis[a[k]];
    num += vis[a[k]] * vis[a[k]];
    return;
}
void del(int k)
{
    num -= vis[a[k]] * vis[a[k]];
    --vis[a[k]];
    num += vis[a[k]] * vis[a[k]];
    return;
}
int main()
{
    scanf("%d%d%d", &n ,&m, &k);
    len = sqrt(n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; ++i)
    {
        s[i].id = i;
        scanf("%d%d", &s[i].l, &s[i].r);
    }
    sort (s + 1, s + m + 1, cmp);
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i)
    {
        while (l < s[i].l)
            del(l++);
        while (l > s[i].l)
            add(--l);
        while (r < s[i].r)
            add(++r);
        while (r > s[i].r)
            del(r--);
        ans[s[i].id] = num;
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}