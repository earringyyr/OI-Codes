#include <iostream>
#include <cstdio>
#include <map>
using namespace std;
int s, t = 123804765, head, tail, x, y;
int q[1000005], a[4][4], go[2][4] = {{1, 0, -1, 0}, {0, 1, 0, -1}};
map<int, int> vis, d;
int ha(int k)
{
    return k;
}
int bfs()
{
    if (s == t)
        return 0;
    q[++tail] = s;
    q[++tail] = t;
    vis[ha(s)] = 1;
    vis[ha(t)] = 2;
    while (head < tail)
    {
        int k = q[++head];
        int id = k;
        for (int i = 3; i >= 1; i--)
            for (int j = 3; j >= 1; j--)
            {
                a[i][j] = k % 10, k /= 10;
                if (a[i][j] == 0)
                {
                    x = i;
                    y = j;
                }
            }
        for (int tt = 0; tt < 4; ++tt)
        {
            int xx = x + go[0][tt];
            int yy = y + go[1][tt];
            if (xx >= 1 && xx <= 3 && yy >= 1 && yy <= 3)
            {
                swap(a[x][y], a[xx][yy]);
                k = 0;
                for (int i = 1; i <= 3; ++i)
                    for (int j = 1; j <= 3; ++j)
                        k = k * 10 + a[i][j];
                if (vis[ha(k)] + vis[ha(id)] == 3)
                    return d[ha(k)] + d[ha(id)] + 1;
                if (vis[ha(k)] == vis[ha(id)])
                {
                    swap(a[x][y], a[xx][yy]);
                    continue;
                }
                d[ha(k)] = d[ha(id)] + 1;
                vis[ha(k)] = vis[ha(id)];
                q[++tail] = k;
                swap(a[x][y], a[xx][yy]);
            }
        }
    }
}
int main()
{
    scanf("%d", &s);
    printf("%d", bfs());
    return 0;
}