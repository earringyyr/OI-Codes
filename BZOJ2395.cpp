#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, sum, ans[3], head[205], fa[205];
struct edge
{
    int u;
    int v;
    int w;
    int val[2];
} a[10005];
struct node
{
    int x;
    int y;
    node(int xx = 0, int yy = 0)
    {
        x = xx;
        y = yy;
    }
    node operator+(const node &bb) const
    {
        return node(x + bb.x, y + bb.y);
    }
    node operator-(const node &bb) const
    {
        return node(x - bb.x, y - bb.y);
    }
    int operator^(const node &bb) const
    {
        return x * bb.y - y * bb.x;
    }
};
bool cmp_x(edge aa, edge bb)
{
    return aa.val[0] < bb.val[0];
}
bool cmp_y(edge aa, edge bb)
{
    return aa.val[1] < bb.val[1];
}
bool cmp(edge aa, edge bb)
{
    return aa.w < bb.w;
}
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
void ins(int u, int v, int c, int t)
{
    ++sum;
    a[sum].u = u;
    a[sum].v = v;
    a[sum].val[0] = c;
    a[sum].val[1] = t;
    return;
}
void solve(node L, node R)
{
    node Mid;
    for (int i = 0; i < n; ++i)
        fa[i] = i;
    for (int i = 1; i <= m; ++i)
        a[i].w = a[i].val[0] * (L.y - R.y) + a[i].val[1] * (R.x - L.x);
    sort(a + 1, a + m + 1, cmp);
    for (int i = 1; i <= m; ++i)
        if (getfather(a[i].u) != getfather(a[i].v))
        {
            fa[getfather(a[i].u)] = getfather(a[i].v);
            Mid.x += a[i].val[0];
            Mid.y += a[i].val[1];
        }
    if (Mid.x * Mid.y < ans[0])
    {
        ans[0] = Mid.x * Mid.y;
        ans[1] = Mid.x;
        ans[2] = Mid.y;
    }
    else if (Mid.x * Mid.y == ans[0] && Mid.x < ans[1])
    {
        ans[1] = Mid.x;
        ans[2] = Mid.y;
    }
    if (((Mid - L) ^ (R - L)) > 0)
    {
        solve(L, Mid);
        solve(Mid, R);
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, c, t;
        scanf("%d%d%d%d", &u, &v, &c, &t);
        ins(u, v, c, t);
    }
    node L, R;
    for (int i = 0; i < n; ++i)
        fa[i] = i;
    sort(a + 1, a + m + 1, cmp_x);
    for (int i = 1; i <= m; ++i)
        if (getfather(a[i].u) != getfather(a[i].v))
        {
            fa[getfather(a[i].u)] = getfather(a[i].v);
            L.x += a[i].val[0];
            L.y += a[i].val[1];
        }
    for (int i = 0; i < n; ++i)
        fa[i] = i;
    sort(a + 1, a + m + 1, cmp_y);
    for (int i = 1; i <= m; ++i)
        if (getfather(a[i].u) != getfather(a[i].v))
        {
            fa[getfather(a[i].u)] = getfather(a[i].v);
            R.x += a[i].val[0];
            R.y += a[i].val[1];
        }
    ans[0] = min(L.x * L.y, R.x * R.y);
    if (L.x * L.y == ans[0])
    {
        ans[1] = L.x;
        ans[2] = L.y;
        if (R.x * R.y == ans[0])
            if (R.x < ans[1])
            {
                ans[1] = R.x;
                ans[2] = R.y;
            }
    }
    else if (R.x * R.y == ans[0])
    {
        ans[1] = R.x;
        ans[2] = R.y;
    }
    solve(L, R);
    printf("%d %d", ans[1], ans[2]);
    return 0;
}