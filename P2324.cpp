#include <iostream>
#include <cstdio>
using namespace std;
int t, a[5][5], go[2][8] = {{1, -1, 1, -1, 2, -2, 2, -2}, {2, 2, -2, -2, 1, 1, -1, -1}};
char s[5][5];
bool p;
int h[5][5] = {
    {1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1},
    {0, 0, 2, 1, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0}};
int judge()
{
    int num = 0;
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            if (a[i][j] != h[i][j])
                ++num;
    return num;
}
void dfs(int x, int y, int dep)
{
    if (!dep)
    {
        if (!judge())
            p = true;
        return;
    }
    for (int i = 0; i < 8; ++i)
    {
        int xx = x + go[0][i];
        int yy = y + go[1][i];
        if (xx >= 0 && xx <= 4 && yy >= 0 && yy <= 4)
        {
            swap(a[x][y], a[xx][yy]);
            if (judge() <= dep)
                dfs(xx, yy, dep - 1);
            swap(a[x][y], a[xx][yy]);
        }
    }
    return;
}
int main()
{
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        int x, y;
        p = false;
        for (int i = 0; i < 5; ++i)
        {
            scanf("%s", s[i]);
            for (int j = 0; j < 5; ++j)
            {
                a[i][j] = s[i][j] == '*' ? 2 : s[i][j] - '0';
                if (a[i][j] == 2)
                {
                    x = i;
                    y = j;
                }
            }
        }
        for (int i = 0; i <= 15; ++i)
        {
            dfs(x, y, i);
            if (p)
            {
                printf("%d\n", i);
                break;
            }
        }
        if (!p)
            puts("-1");
    }
    return 0;
}