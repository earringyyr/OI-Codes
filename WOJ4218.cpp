#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int t, top, s[10], row[10][10], col[10][10], squ[10][10], a[10][10][105];
char ss[20][20];
int find(int x, int y)
{
    if (x <= 3)
    {
        if (y <= 3)
            return 1;
        if (y <= 6)
            return 2;
        if (y <= 9)
            return 3;
    }
    if (x <= 6)
    {
        if (y <= 3)
            return 4;
        if (y <= 6)
            return 5;
        if (y <= 9)
            return 6;
    }
    if (x <= 9)
    {
        if (y <= 3)
            return 7;
        if (y <= 6)
            return 8;
        if (y <= 9)
            return 9;
    }
    return 0;
}
int main()
{
    for (int i = 1; i <= 19; ++i)
    {
        scanf("%s", ss[i]);
        if (!(i & 1))
            for (int j = 1; j < 19; j += 2)
                a[i >> 1][(j >> 1) + 1][0] = ss[i][j] ^ 48;
    }
    for (int i = 1; i <= 9; ++i)
        for (int j = 1; j <= 9; ++j)
            if (a[i][j][0])
            {
                int k = a[i][j][0];
                row[i][k] = 1;
                col[j][k] = 1;
                squ[find(i, j)][k] = 1;
            }
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        char type[10];
        scanf("%s", type);
        if (type[0] == 'I')
        {
            for (int i = 1; i <= 9; ++i)
                for (int j = 1; j <= 9; ++j)
                    a[i][j][tt] = a[i][j][tt - 1];
            int x, y, k;
            scanf("%d%d%d", &x, &y, &k);
            if (a[x][y][tt])
            {
                puts("Error!");
                continue;
            }
            if (row[x][k])
            {
                puts("Error:row!");
                continue;
            }
            if (col[y][k])
            {
                puts("Error:column!");
                continue;
            }
            if (squ[find(x, y)][k])
            {
                puts("Error:square!");
                continue;
            }
            a[x][y][tt] = k;
            row[x][k] = 1;
            col[y][k] = 1;
            squ[find(x, y)][k] = 1;
            puts("OK!");
        }
        if (type[0] == 'D')
        {
            for (int i = 1; i <= 9; ++i)
                for (int j = 1; j <= 9; ++j)
                    a[i][j][tt] = a[i][j][tt - 1];
            int x, y;
            scanf("%d%d", &x, &y);
            if (!a[x][y][tt])
            {
                puts("Error!");
                continue;
            }
            int k = a[x][y][tt];
            a[x][y][tt] = 0;
            row[x][k] = 0;
            col[y][k] = 0;
            squ[find(x, y)][k] = 0;
            puts("OK!");
        }
        if (type[0] == 'Q')
        {
            for (int i = 1; i <= 9; ++i)
                for (int j = 1; j <= 9; ++j)
                    a[i][j][tt] = a[i][j][tt - 1];
            int x, y;
            scanf("%d%d", &x, &y);
            if (a[x][y][tt])
            {
                puts("Error!");
                continue;
            }
            top = 0;
            for (int i = 1; i <= 9; ++i)
                if (!row[x][i] && !col[y][i] && !squ[find(x, y)][i])
                    s[++top] = i;
            printf("%d\n", top);
            for (int i = 1; i <= top; ++i)
                printf("%d\n", s[i]);
        }
        if (type[0] == 'M')
        {
            memset(row, 0, sizeof(row));
            memset(col, 0, sizeof(col));
            memset(squ, 0, sizeof(squ));
            int x, y, ans[2] = {0};
            scanf("%d%d", &x, &y);
            for (int i = 1; i <= 9; ++i)
                for (int j = 1; j <= 9; ++j)
                {
                    if (a[i][j][x])
                    {
                        int k = a[i][j][x];
                        if (!row[i][k] && !col[j][k] && !squ[find(i, j)][k])
                        {
                            a[i][j][tt] = k;
                            row[i][k] = 1;
                            col[j][k] = 1;
                            squ[find(i, j)][k] = 1;
                            ++ans[0];
                        }
                    }
                    if (!a[i][j][tt] && a[i][j][y])
                    {
                        int k = a[i][j][y];
                        if (!row[i][k] && !col[j][k] && !squ[find(i, j)][k])
                        {
                            a[i][j][tt] = k;
                            row[i][k] = 1;
                            col[j][k] = 1;
                            squ[find(i, j)][k] = 1;
                            ++ans[1];
                        }
                    }
                }
            if (x == y)
                ans[1] = ans[0];
            printf("%d %d\n", ans[0], ans[1]);
        }
        if (type[0] == 'P')
        {
            for (int i = 1; i <= 9; ++i)
                for (int j = 1; j <= 9; ++j)
                    a[i][j][tt] = a[i][j][tt - 1];
            for (int i = 1; i <= 9; ++i)
            {
                for (int j = 1; j <= 19; ++j)
                    if (j & 1)
                        putchar('+');
                    else
                        putchar('-');
                putchar('\n');
                for (int j = 1; j <= 9; ++j)
                    printf("|%d", a[i][j][tt]);
                putchar('|');
                putchar('\n');
            }
            for (int i = 1; i <= 19; ++i)
                if (i & 1)
                    putchar('+');
                else
                    putchar('-');
            putchar('\n');
        }
    }
    return 0;
}