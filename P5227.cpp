#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int n, m, k, num, top;
int fa[100005], siz[100005];
int vis[200005];
struct edge
{
    int u;
    int v;
} a[200005];
struct ask
{
    int c;
    int s[5];
} q[100005];
struct node
{
    int x;
    int y;
    node(int xx = 0, int yy = 0)
    {
        x = xx;
        y = yy;
    }
} st[100005];
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
    --num;
    return true;
}
void cut(int x, int val)
{
    siz[x] -= val;
    if (fa[x] != x)
        cut(fa[x], val);
    ++num;
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
    int tmp = top;
    for (int i = l; i <= r; ++i)
        for (int j = 1; j <= q[i].c; ++j)
            vis[q[i].s[j]] = 1;
    vector<int> vec1;
    for (int i = 0; i < vec.size(); ++i)
        if (!vis[vec[i]])
        {
            int x = getfather(a[vec[i]].u);
            int y = getfather(a[vec[i]].v);
            if (link(x, y))
                st[++top] = node(x, y);
        }
        else
            vec1.push_back(vec[i]);
    for (int i = l; i <= r; ++i)
        for (int j = 1; j <= q[i].c; ++j)
            vis[q[i].s[j]] = 0;
    if (l == r)
    {
        if (num == 1)
            puts("Connected");
        else
            puts("Disconnected");
    }
    else
    {
        int mid = (l + r) >> 1;
        solve(l, mid, vec1);
        solve(mid + 1, r, vec1);
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
    scanf("%d%d", &n, &m);
    num = n;
    for (int i = 1; i <= n; ++i)
    {
        fa[i] = i;
        siz[i] = 1;
    }
    for (int i = 1; i <= m; ++i)
        scanf("%d%d", &a[i].u, &a[i].v);
    scanf("%d", &k);
    for (int i = 1; i <= k; ++i)
    {
        scanf("%d", &q[i].c);
        for (int j = 1; j <= q[i].c; ++j)
        {
            scanf("%d", &q[i].s[j]);
            vis[q[i].s[j]] = 1;
        }
    }
    vector<int> vec1;
    for (int i = 1; i <= m; ++i)
        if (!vis[i])
            link(a[i].u, a[i].v);
        else
            vec1.push_back(i);
    memset(vis, 0, sizeof(vis));
    solve(1, k, vec1);
    return 0;
}