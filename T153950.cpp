#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, num = -1, flg;
char a[505][505];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            scanf(" %c", &a[i][j]);
            if (a[i][j] == '#')
                flg = 1;
        }
    if (!flg)
    {
        printf("-1");
        return 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        int cnt = 1;
        for (int j = 1; j <= n; ++j)
            if (a[j][i] == '#')
            {
                cnt = 0;
                break;
            }
        for (int j = 1; j <= n; ++j)
            if (a[i][j] == '.')
                ++cnt;
        if (num == -1 || cnt < num)
            num = cnt;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (a[j][i] == '.')
            {
                ++num;
                break;
            }
    printf("%d", num);
    return 0;
}