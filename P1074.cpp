#include <iostream>
#include <cstdio>
using namespace std;
int ans, num[10], use[10], a[10][10], vis[3][10][10];
int ask(int x, int y)
{
    if (x >= 1 && x <= 3)
    {
        if (y >= 1 && y <= 3)
            return 1;
        if (y >= 4 && y <= 6)
            return 2;
        if (y >= 7 && y <= 9)
            return 3;
    }
    if (x >= 4 && x <= 6)
    {
        if (y >= 1 && y <= 3)
            return 4;
        if (y >= 4 && y <= 6)
            return 5;
        if (y >= 7 && y <= 9)
            return 6;
    }
    if (x >= 7 && x <= 9)
    {
        if (y >= 1 && y <= 3)
            return 7;
        if (y >= 4 && y <= 6)
            return 8;
        if (y >= 7 && y <= 9)
            return 9;
    }
}
void dfs1(int k);
void dfs2(int id, int x, int y);
int main()
{
    for (int i = 1; i <= 9; ++i)
        for (int j = 1; j <= 9; ++j)
        {
            scanf("%d", &a[i][j]);
            if (a[i][j])
            {
                if (vis[0][i][a[i][j]])
                {
                    puts("-1");
                    return 0;
                }
                vis[0][i][a[i][j]] = 1;
                if (vis[1][j][a[i][j]])
                {
                    puts("-1");
                    return 0;
                }
                vis[1][j][a[i][j]] = 1;
                if (vis[2][ask(i, j)][a[i][j]])
                {
                    puts("-1");
                    return 0;
                }
                vis[2][ask(i, j)][a[i][j]] = 1;
            }
            else
                ++num[i];
        }
    dfs1(1);
    if (!ans)
        puts("-1");
    else
        printf("%d", ans);
    return 0;
}
void dfs1(int k)
{
    if (k == 10)
    {
        int sum = 0;
        sum += 6 * (a[1][1] + a[1][2] + a[1][3] + a[1][4] + a[1][5] + a[1][6] + a[1][7] + a[1][8] + a[1][9]);
        sum += 6 * (a[9][1] + a[9][2] + a[9][3] + a[9][4] + a[9][5] + a[9][6] + a[9][7] + a[9][8] + a[9][9]);
        sum += 6 * (a[2][1] + a[3][1] + a[4][1] + a[5][1] + a[6][1] + a[7][1] + a[8][1]);
        sum += 6 * (a[2][9] + a[3][9] + a[4][9] + a[5][9] + a[6][9] + a[7][9] + a[8][9]);
        sum += 7 * (a[2][2] + a[2][3] + a[2][4] + a[2][5] + a[2][6] + a[2][7] + a[2][8]);
        sum += 7 * (a[8][2] + a[8][3] + a[8][4] + a[8][5] + a[8][6] + a[8][7] + a[8][8]);
        sum += 7 * (a[3][2] + a[4][2] + a[5][2] + a[6][2] + a[7][2]);
        sum += 7 * (a[3][8] + a[4][8] + a[5][8] + a[6][8] + a[7][8]);
        sum += 8 * (a[3][3] + a[3][4] + a[3][5] + a[3][6] + a[3][7]);
        sum += 8 * (a[7][3] + a[7][4] + a[7][5] + a[7][6] + a[7][7]);
        sum += 8 * (a[4][3] + a[5][3] + a[6][3]);
        sum += 8 * (a[4][7] + a[5][7] + a[6][7]);
        sum += 9 * (a[4][4] + a[4][5] + a[4][6]);
        sum += 9 * (a[6][4] + a[6][5] + a[6][6]);
        sum += 9 * a[5][4];
        sum += 9 * a[5][6];
        sum += 10 * a[5][5];
        ans = max(ans, sum);
        return;
    }
    int mi = 20, id;
    for (int i = 1; i <= 9; ++i)
        if (!use[i] && num[i] < mi)
        {
            mi = num[i];
            id = i;
        }
    use[id] = 1;
    dfs2(k, id, 1);
    use[id] = 0;
    return;
}
void dfs2(int id, int x, int y)
{
    if (y == 10)
    {
        dfs1(++id);
        return;
    }
    if (a[x][y])
    {
        dfs2(id, x, y + 1);
        return;
    }
    for (int i = 1; i <= 9; ++i)
        if (!vis[0][x][i] && !vis[1][y][i] && !vis[2][ask(x, y)][i])
        {
            vis[0][x][i] = 1;
            vis[1][y][i] = 1;
            vis[2][ask(x, y)][i] = 1;
            a[x][y] = i;
            dfs2(id, x, y + 1);
            vis[0][x][i] = 0;
            vis[1][y][i] = 0;
            vis[2][ask(x, y)][i] = 0;
        }
    a[x][y] = 0;
    return;
}