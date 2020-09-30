#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, w, cnt, sum, ans, fa[50005];
struct node
{
    int u;
    int v;
    int c;
    int col;
    bool operator<(const node &bb) const
    {
        if (c != bb.c)
            return c < bb.c;
        return col < bb.col;
    }
} a[100005];
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
int main()
{
    scanf("%d%d%d", &n, &m, &w);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d%d", &a[i].u, &a[i].v, &a[i].c, &a[i].col);
        ++a[i].u;
        ++a[i].v;
    }
    int l = -101, r = 101;
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        cnt = 0;
        sum = 0;
        for (int i = 1; i <= n; ++i)
            fa[i] = i;
        for (int i = 1; i <= m; ++i)
            if (a[i].col == 0)
                a[i].c += mid;
        sort(a + 1, a + m + 1);
        for (int i = 1; i <= m; ++i)
        {
            int u = getfather(a[i].u), v = getfather(a[i].v);
            if (u != v)
            {
                fa[u] = v;
                sum += a[i].c;
                if (a[i].col == 0)
                    ++cnt;
            }
        }
        if (cnt >= w)
        {
            l = mid;
            ans = sum - w * mid;
        }
        else
            r = mid - 1;
        for (int i = 1; i <= m; ++i)
            if (a[i].col == 0)
                a[i].c -= mid;
    }
    printf("%d", ans);
    return 0;
}