#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
int n, m, sum, id, minx, vis[4], ans[4];
int a[155][155], b[155][155];
int dis[155][155], fa[155][155];
struct node
{
    int x;
    int y;
    int dis;
    node(int xx = 0, int yy = 0, int dd = 0)
    {
        x = xx;
        y = yy;
        dis = dd;
    }
    bool operator<(const node &bb) const
    {
        return dis > bb.dis;
    }
};
priority_queue<node> q;
int getfather(int x, int y)
{
    if (!fa[x][y])
        return y;
    fa[x][y] = getfather(x, fa[x][y]);
    return fa[x][y];
}
void dijkstra(int X, int Y)
{
    memset(fa, 0, sizeof(fa));
    memset(dis, -1, sizeof(dis));
    fa[X][Y] = Y + 1;
    dis[X][Y] = 0;
    q.push(node(X, Y, dis[X][Y] + a[X][Y]));
    while (!q.empty())
    {
        int x = q.top().x;
        int y = q.top().y;
        q.pop();
        for (int i = max(1, x - b[x][y]); i <= min(n, x + b[x][y]); ++i)
            for (int j = max(1, y - (b[x][y] - abs(i - x))); j <= min(m, y + (b[x][y] - abs(i - x))); ++j)
            {
                j = getfather(i, j);
                if (j > m || j > y + (b[x][y] - abs(i - x)))
                    break;
                dis[i][j] = dis[x][y] + a[x][y];
                q.push(node(i, j, dis[i][j] + a[i][j]));
                fa[i][j] = j + 1;
            }
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &b[i][j]);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &a[i][j]);
    int x1, y1, x2, y2, x3, y3;
    scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3);
    dijkstra(x1, y1);
    if (dis[x2][y2] == -1)
        vis[2] = 1;
    if (dis[x3][y3] == -1)
        vis[3] = 1;
    ans[2] += dis[x2][y2];
    ans[3] += dis[x3][y3];
    dijkstra(x2, y2);
    if (dis[x3][y3] == -1)
        vis[3] = 1;
    if (dis[x1][y1] == -1)
        vis[1] = 1;
    ans[3] += dis[x3][y3];
    ans[1] += dis[x1][y1];
    dijkstra(x3, y3);
    if (dis[x1][y1] == -1)
        vis[1] = 1;
    if (dis[x2][y2] == -1)
        vis[2] = 1;
    ans[1] += dis[x1][y1];
    ans[2] += dis[x2][y2];
    for (int i = 1; i <= 3; ++i)
        if (!vis[i] && (!id || ans[i] < minx))
        {
            id = i;
            minx = ans[i];
        }
    if (!id)
        printf("NO");
    else
    {
        if (id == 1)
            printf("X");
        else if (id == 2)
            printf("Y");
        else if (id == 3)
            printf("Z");
        putchar('\n');
        printf("%d", minx);
    }
    return 0;
}