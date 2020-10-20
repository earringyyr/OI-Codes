#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, p, K, S, head, tail;
int vis[15][15][20005], s[15][15];
int gox[4] = {0, 0, 1, -1}, goy[4] = {1, -1, 0, 0};
int x[155], y[155], xx[155], yy[155], g[155];
int X[15], Y[15], Q[15];
struct node
{
    int x;
    int y;
    int sta;
    int dis;
    node(int xx = 0, int yy = 0, int ssta = 0, int ddis = 0)
    {
        x = xx;
        y = yy;
        sta = ssta;
        dis = ddis;
    }
} l[10000005];
int main()
{
    scanf("%d%d%d", &n, &m, &p);
    scanf("%d", &K);
    for (int i = 1; i <= K; ++i)
        scanf("%d%d%d%d%d", &x[i], &y[i], &xx[i], &yy[i], &g[i]);
    scanf("%d", &S);
    for (int i = 1; i <= S; ++i)
    {
        scanf("%d%d%d", &X[i], &Y[i], &Q[i]);
        s[X[i]][Y[i]] |= (1 << (Q[i] - 1));
    }
    l[++tail] = node(1, 1, s[1][1], 0);
    while (head < tail)
    {
        node k = l[++head];
        if (k.x == n && k.y == m)
        {
            printf("%d", k.dis);
            return 0;
        }
        for (int i = 0; i < 4; ++i)
        {
            int nx = k.x + gox[i];
            int ny = k.y + goy[i];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m)
            {
                int p = 1;
                for (int j = 1; j <= K; ++j)
                    if ((x[j] == k.x && y[j] == k.y && xx[j] == nx && yy[j] == ny) || (x[j] == nx && y[j] == ny && xx[j] == k.x && yy[j] == k.y))
                    {
                        if (g[j] == 0 || !(k.sta & (1 << (g[j] - 1))))
                            p = 0;
                        break;
                    }
                if (!p)
                    continue;
                if (!vis[nx][ny][k.sta | s[nx][ny]])
                {
                    vis[nx][ny][k.sta | s[nx][ny]] = 1;
                    l[++tail] = node(nx, ny, k.sta | s[nx][ny], k.dis + 1);
                }
            }
        }
    }
    printf("%d", -1);
    return 0;
}