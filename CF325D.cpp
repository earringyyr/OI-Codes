#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int r, c, n, ans;
int top, st[25][2];
int vis[3005][6005];
int fa[18000005], siz[18000005];
int gox[8] = {0, 0, 1, 1, 1, -1, -1, -1}, goy[8] = {1, -1, 0, 1, -1, 0, 1, -1};
int getid(int x, int y)
{
    return (x - 1) * c * 2 + y;
}
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    return getfather(fa[x]);
}
void link(int x, int y)
{
    x = getfather(x);
    y = getfather(y);
    if (x == y)
        return;
    if (siz[x] > siz[y])
        swap(x, y);
    fa[x] = y;
    siz[y] += siz[x];
    ++top;
    st[top][0] = x;
    st[top][1] = y;
    return;
}
void cut(int x, int y)
{
    fa[x] = x;
    siz[y] -= siz[x];
    return;
}
int main()
{
    scanf("%d%d%d", &r, &c, &n);
    if (c == 1)
    {
        printf("0");
        return 0;
    }
    for (int i = 1; i <= 2 * r * c; ++i)
    {
        fa[i] = i;
        siz[i] = 1;
    }
    for (int i = 1; i <= n; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        for (int j = 0; j < 8; ++j)
        {
            int xx, yy;
            xx = x + gox[j];
            yy = y + goy[j];
            if (yy == 0)
                yy = 2 * c;
            if (yy == 2 * c + 1)
                yy = 1;
            if (xx >= 1 && xx <= r && yy >= 1 && yy <= 2 * c && vis[xx][yy])
                link(getid(x, y), getid(xx, yy));
            xx = x + gox[j];
            yy = y + c + goy[j];
            if (yy == 0)
                yy = 2 * c;
            if (yy == 2 * c + 1)
                yy = 1;
            if (xx >= 1 && xx <= r && yy >= 1 && yy <= 2 * c && vis[xx][yy])
                link(getid(x, y + c), getid(xx, yy));
        }
        if (getfather(getid(x, y)) == getfather(getid(x, y + c)))
            while (top)
            {
                cut(st[top][0], st[top][1]);
                --top;
            }
        else
        {
            vis[x][y] = 1;
            vis[x][y + c] = 1;
            top = 0;
            ++ans;
        }
    }
    printf("%d", ans);
    return 0;
}