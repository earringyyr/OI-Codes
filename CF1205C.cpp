#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, flg;
int a[55][55];
int main()
{
    scanf("%d", &n);
    a[1][1] = 1;
    a[1][2] = 1;
    a[n][n] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if ((i + j) % 2 == 0)
            {
                if (i == 1 && j == 1)
                    continue;
                if (i == n && j == n)
                    continue;
                if (i == 1 && j == 3)
                {
                    printf("? %d %d %d %d\n", 1, 1, 1, 3);
                    fflush(stdout);
                    scanf("%d", &flg);
                    a[1][3] = a[1][1] ^ (flg ^ 1);
                    continue;
                }
                if (i == 3 && j == 1)
                {
                    printf("? %d %d %d %d\n", 1, 1, 3, 1);
                    fflush(stdout);
                    scanf("%d", &flg);
                    a[3][1] = a[1][1] ^ (flg ^ 1);
                    continue;
                }
                if (i == 1)
                {
                    printf("? %d %d %d %d\n", 1, j - 2, 1, j);
                    fflush(stdout);
                    scanf("%d", &flg);
                    a[i][j] = a[1][j - 2] ^ (flg ^ 1);
                    continue;
                }
                if (i == 2)
                {
                    printf("? %d %d %d %d\n", 1, j - 1, 2, j);
                    fflush(stdout);
                    scanf("%d", &flg);
                    a[i][j] = a[1][j - 1] ^ (flg ^ 1);
                    continue;
                }
                printf("? %d %d %d %d\n", i - 2, j, i, j);
                fflush(stdout);
                scanf("%d", &flg);
                a[i][j] = a[i - 2][j] ^ (flg ^ 1);
            }
            else
            {
                if (i == 1 && j == 2)
                    continue;
                if (i == 2 && j == 1)
                    continue;
                if (i == 2 && j == 3)
                {
                    printf("? %d %d %d %d\n", 1, 2, 2, 3);
                    fflush(stdout);
                    scanf("%d", &flg);
                    a[2][3] = a[1][2] ^ (flg ^ 1);
                    printf("? %d %d %d %d\n", 2, 1, 2, 3);
                    fflush(stdout);
                    scanf("%d", &flg);
                    a[2][1] = a[2][3] ^ (flg ^ 1);
                    continue;
                }
                if (i == 1)
                {
                    printf("? %d %d %d %d\n", 1, j - 2, 1, j);
                    fflush(stdout);
                    scanf("%d", &flg);
                    a[i][j] = a[1][j - 2] ^ (flg ^ 1);
                    continue;
                }
                if (i == 2)
                {
                    printf("? %d %d %d %d\n", 1, j - 1, 2, j);
                    fflush(stdout);
                    scanf("%d", &flg);
                    a[i][j] = a[1][j - 1] ^ (flg ^ 1);
                    continue;
                }
                printf("? %d %d %d %d\n", i - 2, j, i, j);
                fflush(stdout);
                scanf("%d", &flg);
                a[i][j] = a[i - 2][j] ^ (flg ^ 1);
            }
    for (int i = 1; i <= n - 2; ++i)
        if (a[i][i] != a[i + 2][i + 2])
        {
            int pp = 0;
            if ((a[i][i] ^ a[i + 1][i] ^ a[i + 1][i + 1] ^ a[i + 1][i + 2]) == 0)
            {
                printf("? %d %d %d %d\n", i, i, i + 1, i + 2);
                fflush(stdout);
                scanf("%d", &flg);
                if (flg && a[i + 1][i] != a[i + 1][i + 1])
                    pp = 1;
                if (!flg && a[i + 1][i] == a[i + 1][i + 1])
                    pp = 1;
            }
            else
            {
                printf("? %d %d %d %d\n", i + 1, i, i + 2, i + 2);
                fflush(stdout);
                scanf("%d", &flg);
                if (flg && a[i + 1][i + 1] != a[i + 1][i + 2])
                    pp = 1;
                if (!flg && a[i + 1][i + 1] == a[i + 1][i + 2])
                    pp = 1;
            }
            if (pp)
                for (int x = 1; x <= n; ++x)
                    for (int y = 1; y <= n; ++y)
                        if ((x + y) % 2 == 1)
                            a[x][y] ^= 1;
            break;
        }
    puts("!");
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
            printf("%d", a[i][j]);
        putchar('\n');
    }
    fflush(stdout);
    return 0;
}