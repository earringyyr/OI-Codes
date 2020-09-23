#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, pos = 1, dis[400005][20], Ans[200005];
struct node
{
    int id;
    int x;
    int y;
} a[400005];
bool cmp(node aa, node bb)
{
    return aa.x < bb.x;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        a[i].id = i;
        scanf("%d%d", &a[i].x, &a[i].y);
        if (a[i].x > a[i].y)
            a[i].y += m;
    }
    for (int i = 1; i <= n; ++i)
    {
        a[i + n].x = a[i].x + m;
        a[i + n].y = a[i].y + m;
    }
    sort(a + 1, a + 2 * n + 1, cmp);
    for (int i = 1; i <= 2 * n; ++i)
    {
        while (pos < 2 * n && a[pos + 1].x <= a[i].y)
            ++pos;
        dis[i][0] = pos;
    }
    for (int i = 1; i < 20; ++i)
        for (int j = 1; j <= 2 * n; ++j)
            dis[j][i] = dis[dis[j][i - 1]][i - 1];
    for (int i = 1; i <= 2 * n; ++i)
        if (a[i].id)
        {
            int ans = 0, d = i;
            for (int j = 19; j >= 0; --j)
                if (a[dis[d][j]].y - a[i].x < m)
                {
                    ans += (1 << j);
                    d = dis[d][j];
                }
            Ans[a[i].id] = ans + 2;
        }
    for (int i = 1; i <= n; ++i)
        printf("%d ", Ans[i]);
    return 0;
}