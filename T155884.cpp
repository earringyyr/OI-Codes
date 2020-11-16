#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, t;
int dis[55][55], vis[55][55], use[55][55];
int l[2505][2];
int gox[4] = {-1, 0, 1, 0}, goy[4] = {0, 1, 0, -1};
char s[55][55];
void dist(int x, int y)
{
    memset(dis, -1, sizeof(dis));
    int hh = 0, tt = 1;
    l[1][0] = x;
    l[1][1] = y;
    dis[x][y] = 0;
    while (hh < tt)
    {
        ++hh;
        int X = l[hh][0], Y = l[hh][1];
        for (int i = 0; i < 4; ++i)
        {
            int XX = X + gox[i], YY = Y + goy[i];
            if (XX >= 1 && XX <= n && YY >= 1 && YY <= n && dis[XX][YY] == -1 && s[X][Y] == s[XX][YY])
            {
                dis[XX][YY] = dis[X][Y] + 1;
                ++tt;
                l[tt][0] = XX;
                l[tt][1] = YY;
            }
        }
    }
    return;
}
int dfs(int x, int y)
{
    if (x < 1 || x > n || y < 1 || y > n)
    {
        if (x == 0 || x == n + 1 || y == 0 || y == n + 1)
            return 0;
        return -1;
    }
    if (vis[x][y])
        return -1e9;
    vis[x][y] = 1;
    dist(x, y);
    if (s[x][y] == '*')
    {
        memset(use, 0, sizeof(use));
        int X = x, Y = y, cnt = 0, dir = 0;
        use[x][y] = 1;
        while (1)
        {
            ++cnt;
            X = X + gox[dir];
            Y = Y + goy[dir];
            if (use[X][Y])
            {
                X -= gox[dir];
                Y -= goy[dir];
                dir = (dir + 3) % 4;
                X = X + gox[dir];
                Y = Y + goy[dir];
            }
            use[X][Y] = 1;
            if (X < 1 || X > n || Y < 1 || Y > n || s[X][Y] != '*')
                break;
            dir = (dir + 1) % 4;
        }
        return cnt + dfs(X, Y);
    }
    else if (s[x][y] == 'I')
    {
        int X = 0, Y = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (dis[i][j] != -1 && ((X == 0 && Y == 0) || (dis[i][j] > dis[X][Y])))
                {
                    X = i;
                    Y = j;
                }
        return dis[X][Y] + 2 + dfs(X - 2, Y);
    }
    else if (s[x][y] == 'B')
    {
        int X = 0, Y = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (dis[i][j] != -1 && ((X == 0 && Y == 0) || (dis[i][j] > dis[X][Y])))
                {
                    X = i;
                    Y = j;
                }
        int num = dis[X][Y];
        dist(X, Y);
        X = 0;
        Y = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (dis[i][j] != -1 && ((X == 0 && Y == 0) || (dis[i][j] > dis[X][Y])))
                {
                    X = i;
                    Y = j;
                }
        return dis[X][Y] - num + 2 + dfs(X, Y + 2);
    }
    else
    {
        int X = 0, Y = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (dis[i][j] != -1 && ((X == 0 && Y == 0) || (dis[i][j] > dis[X][Y])))
                {
                    X = i;
                    Y = j;
                }
        return dis[X][Y] + 2 + dfs(X, Y - 2);
    }
}
int main()
{
    while (scanf("%d%d", &n, &t))
    {
        if (n == 0 && t == 0)
            break;
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; ++i)
            scanf("%s", s[i] + 1);
        int w, h;
        scanf("%d%d", &w, &h);
        ++w;
        ++h;
        int tim = dfs(w, h);
        if (tim < 0 || tim > t)
            puts("Die hard");
        else
            printf("%d\n", tim);
    }
    return 0;
}