#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int n, m, k, top;
int fa[400005], siz[400005];
struct edge
{
    int u;
    int v;
    int l;
    int r;
} a[200005];
struct node
{
    int x;
    int y;
    node(int xx = 0, int yy = 0)
    {
        x = xx;
        y = yy;
    }
} st[400005];
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    return getfather(fa[x]);
}
bool link(int x, int y)
{
    x = getfather(x);
    y = getfather(y);
    if (x == y)
        return false;
    if (siz[x] > siz[y])
        swap(x, y);
    fa[x] = y;
    siz[y] += siz[x];
    return true;
}
void cut(int x, int val)
{
    siz[x] -= val;
    if (fa[x] != x)
        cut(fa[x], val);
    return;
}
void divide(int x, int y)
{
    if (fa[x] != y)
        swap(x, y);
    cut(fa[x], siz[x]);
    fa[x] = x;
    return;
}
void solve(int l, int r, vector<int> vec)
{
    int mid = (l + r) >> 1;
    int tmp = top, flg = 0;
    vector<int> L, R;
    for (int i = 0; i < vec.size(); ++i)
        if (a[vec[i]].l <= l && a[vec[i]].r >= r)
        {
            int x = getfather(a[vec[i]].u);
            int y = getfather(a[vec[i]].v);
            if (x == y)
            {
                flg = 1;
                for (int j = l; j <= r; ++j)
                    puts("No");
                break;
            }
            x = getfather(a[vec[i]].u);
            y = getfather(a[vec[i]].v + n);
            if (link(x, y))
                st[++top] = node(x, y);
            x = getfather(a[vec[i]].u + n);
            y = getfather(a[vec[i]].v);
            if (link(x, y))
                st[++top] = node(x, y);
        }
        else
        {
            if (a[vec[i]].l <= mid)
                L.push_back(vec[i]);
            if (a[vec[i]].r >= mid)
                R.push_back(vec[i]);
        }
    if (!flg)
        if (l == r)
            puts("Yes");
        else
        {
            solve(l, mid, L);
            solve(mid + 1, r, R);
        }
    while (top > tmp)
    {
        divide(st[top].x, st[top].y);
        --top;
    }
    return;
}
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= 2 * n; ++i)
    {
        fa[i] = i;
        siz[i] = 1;
    }
    vector<int> vec;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d%d", &a[i].u, &a[i].v, &a[i].l, &a[i].r);
        if (a[i].l != a[i].r)
        {
            ++a[i].l;
            vec.push_back(i);
        }
    }
    solve(1, k, vec);
    return 0;
}