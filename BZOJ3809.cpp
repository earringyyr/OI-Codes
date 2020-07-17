#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int n, m, len, a[100005], num[100005], cnt[100005], vis[100005], ans[1000005];
struct node
{
    int id;
    int l;
    int r;
    int a;
    int b;
} s[1000005];
bool cmp(node aa, node bb)
{
    if ((aa.l - 1) / len == (bb.l - 1) / len)
    {
        if (aa.r != bb.r)
            if ((aa.l - 1) / len % 2 == 0)
                return aa.r < bb.r;
            else
                return aa.r > bb.r;
        return aa.l < bb.l;
    }
    else
        return aa.l < bb.l;
}
void add(int k)
{
    if (vis[a[k]] == 0)
    {
        ++num[a[k]];
        ++cnt[(a[k] - 1) / len];
    }
    ++vis[a[k]];
    return;
}
void del(int k)
{
    --vis[a[k]];
    if (vis[a[k]] == 0)
    {
        --num[a[k]];
        --cnt[(a[k] - 1) / len];
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    len = sqrt(n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; ++i)
    {
        s[i].id = i;
        scanf("%d%d%d%d", &s[i].l, &s[i].r, &s[i].a, &s[i].b);
    }
    sort(s + 1, s + m + 1, cmp);
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
        if ((s[i].a - 1) / len == (s[i].b - 1) / len)
            for (int j = s[i].a; j <= s[i].b; ++j)
                ans[s[i].id] += num[j];
        else
        {
            for (int j = s[i].a; j <= ((s[i].a - 1) / len + 1) * len; ++j)
                ans[s[i].id] += num[j];
            for (int j = s[i].b; j > (s[i].b - 1) / len * len; --j)
                ans[s[i].id] += num[j];
            for (int j = (s[i].a - 1) / len + 1; j <= (s[i].b - 1) / len - 1; ++j)
                ans[s[i].id] += cnt[j];
        }
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}