#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n[3];
int f[3][2005][2005];
int g[3][2005][15];
ll ans;
char mp[3][7][2005];
char col[8] = "..X.X..";
char num[10][7][5] = {
    {"XXXX",
     "X..X",
     "X..X",
     "X..X",
     "X..X",
     "X..X",
     "XXXX"},
    {"...X",
     "...X",
     "...X",
     "...X",
     "...X",
     "...X",
     "...X"},
    {"XXXX",
     "...X",
     "...X",
     "XXXX",
     "X...",
     "X...",
     "XXXX"},
    {"XXXX",
     "...X",
     "...X",
     "XXXX",
     "...X",
     "...X",
     "XXXX"},
    {"X..X",
     "X..X",
     "X..X",
     "XXXX",
     "...X",
     "...X",
     "...X"},
    {"XXXX",
     "X...",
     "X...",
     "XXXX",
     "...X",
     "...X",
     "XXXX"},
    {"XXXX",
     "X...",
     "X...",
     "XXXX",
     "X..X",
     "X..X",
     "XXXX"},
    {"XXXX",
     "...X",
     "...X",
     "...X",
     "...X",
     "...X",
     "...X"},
    {"XXXX",
     "X..X",
     "X..X",
     "XXXX",
     "X..X",
     "X..X",
     "XXXX"},
    {"XXXX",
     "X..X",
     "X..X",
     "XXXX",
     "...X",
     "...X",
     "XXXX"}};
int calc(int id, int pos, int val)
{
    if (g[id][pos][val] != -1)
        return g[id][pos][val];
    int cnt = 0;
    if (val == 10)
    {
        for (int i = 0; i < 7; ++i)
            if (mp[id][i][pos] != '.')
                ++cnt;
        g[id][pos][val] = cnt;
        return cnt;
    }
    if (val == 11)
    {
        for (int i = 0; i < 7; ++i)
            if (mp[id][i][pos] != col[i])
                ++cnt;
        g[id][pos][val] = cnt;
        return cnt;
    }
    for (int i = 0; i < 7; ++i)
        for (int j = 0; j < 4; ++j)
            if (num[val][i][j] != mp[id][i][j + pos])
                ++cnt;
    g[id][pos][val] = cnt;
    return cnt;
}
int main()
{
    memset(f, 0x3f, sizeof(f));
    memset(g, -1, sizeof(g));
    ans = 0x7f7f7f7f7f7f7f7f;
    scanf("%d", &n[0]);
    for (int i = 0; i < 7; ++i)
        scanf("%s", mp[0][i] + 1);
    scanf("%d", &n[1]);
    for (int i = 0; i < 7; ++i)
        scanf("%s", mp[1][i] + 1);
    scanf("%d", &n[2]);
    for (int i = 0; i < 7; ++i)
        scanf("%s", mp[2][i] + 1);
    f[0][0][0] = 0;
    for (int i = 1; i <= n[0]; ++i)
    {
        if (i >= 4)
            for (int j = 1; j <= 3; ++j)
                f[0][i][j] = f[0][i - 4][0] + calc(0, i - 3, j - 1);
        if (i >= 5)
            for (int j = 4; j <= 27; ++j)
                f[0][i][j] = f[0][i - 5][(j - 4) / 10 + 1] + calc(0, i - 4, 10) + calc(0, i - 3, (j - 4) % 10);
        if (i >= 2)
            for (int j = 28; j <= 51; ++j)
                f[0][i][j] = f[0][i - 2][j - 24] + calc(0, i - 1, 10) + calc(0, i, 11);
        if (i >= 5)
            for (int j = 52; j <= 195; ++j)
                f[0][i][j] = f[0][i - 5][(j - 52) / 6 + 28] + calc(0, i - 4, 10) + calc(0, i - 3, (j - 52) % 6);
        if (i >= 5)
            for (int j = 196; j <= 1635; ++j)
                f[0][i][j] = f[0][i - 5][(j - 196) / 10 + 52] + calc(0, i - 4, 10) + calc(0, i - 3, (j - 196) % 10);
        for (int j = 0; j <= 1635; ++j)
            f[0][i][j] = min(f[0][i][j], f[0][i - 1][j] + calc(0, i, 10));
    }
    f[1][0][1440] = 0;
    for (int i = 1; i <= n[1]; ++i)
    {
        for (int j = 0; j < 1440; ++j)
        {
            f[1][i][j] = min(f[1][i][j], f[1][i - 1][j] + calc(1, i, 10));
            if (i >= 5)
                for (int k = 0; k < 10; ++k)
                {
                    int l = (10 * j + k) % 1440;
                    f[1][i][l] = min(f[1][i][l], f[1][i - 5][j] + calc(1, i - 4, 10) + calc(1, i - 3, k));
                }
        }
        if (i >= 4)
            for (int j = 1; j < 10; ++j)
                f[1][i][j] = min(f[1][i][j], f[1][i - 4][1440] + calc(1, i - 3, j));
        f[1][i][1440] = f[1][i - 1][1440] + calc(1, i, 10);
    }
    for (int i = 1; i <= n[1]; ++i)
    {
        f[1][i][0] = min(f[1][i][0], f[1][i - 1][0] + calc(1, i, 10));
        if (i >= 4)
            f[1][i][0] = min(f[1][i][0], f[1][i - 4][1440] + calc(1, i - 3, 0));
    }
    f[2][0][0] = 0;
    for (int i = 1; i <= n[2]; ++i)
    {
        if (i >= 4)
            for (int j = 1; j <= 3; ++j)
                f[2][i][j] = f[2][i - 4][0] + calc(2, i - 3, j - 1);
        if (i >= 5)
            for (int j = 4; j <= 27; ++j)
                f[2][i][j] = f[2][i - 5][(j - 4) / 10 + 1] + calc(2, i - 4, 10) + calc(2, i - 3, (j - 4) % 10);
        if (i >= 2)
            for (int j = 28; j <= 51; ++j)
                f[2][i][j] = f[2][i - 2][j - 24] + calc(2, i - 1, 10) + calc(2, i, 11);
        if (i >= 5)
            for (int j = 52; j <= 195; ++j)
                f[2][i][j] = f[2][i - 5][(j - 52) / 6 + 28] + calc(2, i - 4, 10) + calc(2, i - 3, (j - 52) % 6);
        if (i >= 5)
            for (int j = 196; j <= 1635; ++j)
                f[2][i][j] = f[2][i - 5][(j - 196) / 10 + 52] + calc(2, i - 4, 10) + calc(2, i - 3, (j - 196) % 10);
        for (int j = 0; j <= 1635; ++j)
            f[2][i][j] = min(f[2][i][j], f[2][i - 1][j] + calc(2, i, 10));
    }
    for (int i = 0; i < 1440; ++i)
        for (int j = 0; j < 1440; ++j)
        {
            int k = (j - i + 1440) % 1440;
            ans = min(ans, (ll)f[0][n[0]][i + 196] + f[1][n[1]][k] + f[2][n[2]][j + 196]);
        }
    printf("%lld", ans);
    return 0;
}