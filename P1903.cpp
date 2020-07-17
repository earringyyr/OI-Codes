#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int n, m, len, l = 1, r, id, num, sum, cnt, c[200005], cc[200005], vis[1000005], ans[200005], q[200005][3];
struct node
{
    int id;
    int l;
    int r;
    int c;
} a[200005];
bool cmp(node aa, node bb)
{
    if ((aa.l - 1) / len == (bb.l - 1) / len)
    {
        if ((aa.r - 1) / len == (bb.r - 1) / len)
            return aa.c < bb.c;
        return aa.r < bb.r;
    }
    return aa.l < bb.l;
}
void add(int x)
{
    if (!vis[c[x]])
        ++cnt;
    ++vis[c[x]];
    return;
}
void del(int x)
{
    --vis[c[x]];
    if (!vis[c[x]])
        --cnt;
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    len = pow(n, 2.0 / 3.0);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &c[i]);
        cc[i] = c[i];
    }
    int l = 1, r = 0, id = 0;
    for (int i = 1; i <= m; ++i)
    {
        char type;
        scanf(" %c", &type);
        if (type == 'Q')
        {
            ++num;
            a[num].id = num;
            scanf("%d%d", &a[num].l, &a[num].r);
            a[num].c = sum;
        }
        else
        {
            ++sum;
            scanf("%d%d", &q[sum][0], &q[sum][1]);
            q[sum][2] = cc[q[sum][0]];
            cc[q[sum][0]] = q[sum][1];
        }
    }
    sort(a + 1, a + num + 1, cmp);
    for (int i = 1; i <= num; ++i)
    {
        while (l < a[i].l)
            del(l++);
        while (l > a[i].l)
            add(--l);
        while (r < a[i].r)
            add(++r);
        while (r > a[i].r)
            del(r--);
        while (id < a[i].c)
        {
            ++id;
            if (a[i].l <= q[id][0] && a[i].r >= q[id][0])
                del(q[id][0]);
            c[q[id][0]] = q[id][1];
            if (a[i].l <= q[id][0] && a[i].r >= q[id][0])
                add(q[id][0]);
        }
        while (id > a[i].c)
        {
            if (a[i].l <= q[id][0] && a[i].r >= q[id][0])
                del(q[id][0]);
            c[q[id][0]] = q[id][2];
            if (a[i].l <= q[id][0] && a[i].r >= q[id][0])
                add(q[id][0]);
            --id;
        }
        ans[a[i].id] = cnt;
    }
    for (int i = 1; i <= num; ++i)
        printf("%d\n", ans[i]);
    return 0;
}