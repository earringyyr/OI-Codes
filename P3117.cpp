#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, H, G, ans, ans_area;
int mp[1005][1005], f[1005][1005];
struct node
{
    int x;
    int y;
    node(int xx = 0, int yy = 0)
    {
        x = xx;
        y = yy;
    }
} h[505], g[505];
bool cmp(node aa, node bb)
{
    return aa.x < bb.x;
}
int calc(int lx, int rx, int ly, int ry)
{
    int x = 1000, xx = 1, y = 1000, yy = 1;
    for (int i = 1; i <= H; ++i)
        if (h[i].x >= lx && h[i].x <= rx && h[i].y >= ly && h[i].y <= ry)
        {
            x = min(x, h[i].x);
            xx = max(xx, h[i].x);
            y = min(y, h[i].y);
            yy = max(yy, h[i].y);
        }
    return (xx - x) * (yy - y);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int x, y;
        char ch;
        scanf("%d%d %c", &x, &y, &ch);
        ++x;
        ++y;
        if (ch == 'H')
        {
            ++mp[x][y];
            h[++H] = node(x, y);
        }
        else
            g[++G] = node(x, y);
    }
    g[++G] = node(0, 0);
    g[++G] = node(0, 1001);
    g[++G] = node(1001, 0);
    g[++G] = node(1001, 1001);
    sort(h + 1, h + H + 1, cmp);
    sort(g + 1, g + G + 1, cmp);
    for (int i = 1; i <= 1001; ++i)
        for (int j = 1; j <= 1001; ++j)
            f[i][j] = f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + mp[i][j];
    for (int i = 1; i <= G; ++i)
    {
        int minx = 0, maxn = 1001;
        for (int j = i + 1; j <= G && maxn - minx >= 2; ++j)
        {
            if (g[j].x - g[i].x < 2)
            {
                if (g[j].y <= g[i].y)
                    minx = max(minx, g[j].y);
                if (g[j].y >= g[i].y)
                    maxn = min(maxn, g[j].y);
                continue;
            }
            int num = f[g[j].x - 1][maxn - 1] - f[g[i].x][maxn - 1] - f[g[j].x - 1][minx] + f[g[i].x][minx];
            if (ans == num)
                ans_area = min(ans_area, calc(g[i].x + 1, g[j].x - 1, minx + 1, maxn - 1));
            if (num > ans)
            {
                ans = num;
                ans_area = calc(g[i].x + 1, g[j].x - 1, minx + 1, maxn - 1);
            }
            if (g[j].y <= g[i].y)
                minx = max(minx, g[j].y);
            if (g[j].y >= g[i].y)
                maxn = min(maxn, g[j].y);
        }
    }
    printf("%d\n%d", ans, ans_area);
    return 0;
}