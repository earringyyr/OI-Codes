#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int q, id = 1, end, mp[15][15], co[15][15];
bool move(int type, int x, int y, int xx, int yy)
{
    if (x == xx && y == yy)
        return false;
    if (co[x][y] == co[xx][yy])
        return false;
    switch (type)
    {
    case 1:
        if (x == xx && abs(y - yy) <= 1)
            return true;
        if (y == yy && abs(x - xx) <= 1)
            return true;
        return false;
        break;
    case 2:
        if (x == xx || y == yy)
            return false;
        if (abs(x - xx) <= 1 && abs(y - yy) <= 1)
            return true;
        return false;
        break;
    case 3:
        for (int i = -1; i <= 1; i += 2)
            for (int j = -1; j <= 1; j += 2)
                if (!mp[x + i][y + j] && xx == x + 2 * i && yy == y + 2 * j)
                    return true;
        return false;
        break;
    case 4:
        for (int i = -1; i <= 1; i += 2)
            for (int j = -1; j <= 1; j += 2)
            {
                if (!mp[x + i][y] && xx == x + 2 * i && yy == y + j)
                    return true;
                if (!mp[x][y + j] && xx == x + i && yy == y + 2 * j)
                    return true;
            }
        break;
    case 5:
        if (x != xx && y != yy)
            return false;
        if (x == xx)
        {
            for (int i = min(y, yy) + 1; i < max(y, yy); ++i)
                if (mp[x][i])
                    return false;
        }
        if (y == yy)
        {
            for (int i = min(x, xx) + 1; i < max(x, xx); ++i)
                if (mp[i][y])
                    return false;
        }
        return true;
        break;
    case 6:
        for (int i = -1; i <= 1; i += 2)
            for (int j = -1; j <= 1; j += 2)
            {
                if (!mp[x + 2 * i][y + j] && !mp[x + i][y] && xx == x + 3 * i && yy == y + 2 * j)
                    return true;
                if (!mp[x + i][y + 2 * j] && !mp[x][y + j] && xx == x + 2 * i && yy == y + 3 * j)
                    return true;
            }
        return false;
        break;
    case 7:
        if (abs(x - xx) <= 1 && abs(y - yy) <= 1)
            return true;
        return false;
        break;
    }
    return false;
}
int main()
{
    mp[0][0] = 5;
    mp[0][1] = 4;
    mp[0][2] = 3;
    mp[0][3] = 2;
    mp[0][4] = 1;
    mp[0][5] = 2;
    mp[0][6] = 3;
    mp[0][7] = 4;
    mp[0][8] = 5;
    mp[2][0] = 6;
    mp[2][8] = 6;
    mp[3][0] = 7;
    mp[3][2] = 7;
    mp[3][4] = 7;
    mp[3][6] = 7;
    mp[3][8] = 7;
    mp[9][0] = 5;
    mp[9][1] = 4;
    mp[9][2] = 3;
    mp[9][3] = 2;
    mp[9][4] = 1;
    mp[9][5] = 2;
    mp[9][6] = 3;
    mp[9][7] = 4;
    mp[9][8] = 5;
    mp[7][0] = 6;
    mp[7][8] = 6;
    mp[6][0] = 7;
    mp[6][2] = 7;
    mp[6][4] = 7;
    mp[6][6] = 7;
    mp[6][8] = 7;
    co[0][0] = 1;
    co[0][1] = 1;
    co[0][2] = 1;
    co[0][3] = 1;
    co[0][4] = 1;
    co[0][5] = 1;
    co[0][6] = 1;
    co[0][7] = 1;
    co[0][8] = 1;
    co[2][0] = 1;
    co[2][8] = 1;
    co[3][0] = 1;
    co[3][2] = 1;
    co[3][4] = 1;
    co[3][6] = 1;
    co[3][8] = 1;
    co[9][0] = 2;
    co[9][1] = 2;
    co[9][2] = 2;
    co[9][3] = 2;
    co[9][4] = 2;
    co[9][5] = 2;
    co[9][6] = 2;
    co[9][7] = 2;
    co[9][8] = 2;
    co[7][0] = 2;
    co[7][8] = 2;
    co[6][0] = 2;
    co[6][2] = 2;
    co[6][4] = 2;
    co[6][6] = 2;
    co[6][8] = 2;
    scanf("%d", &q);
    while (q--)
    {
        int x, y, xx, yy;
        scanf("%d%d%d%d", &x, &y, &xx, &yy);
        if (end)
        {
            puts("Invalid command");
            continue;
        }
        if (co[x][y] != id)
        {
            puts("Invalid command");
            continue;
        }
        if (!move(mp[x][y], x, y, xx, yy))
        {
            puts("Invalid command");
            continue;
        }
        if (co[x][y] == 1)
            printf("red ");
        else
            printf("blue ");
        switch (mp[x][y])
        {
        case 1:
            printf("captain;");
            break;
        case 2:
            printf("guard;");
            break;
        case 3:
            printf("elephant;");
            break;
        case 4:
            printf("horse;");
            break;
        case 5:
            printf("car;");
            break;
        case 6:
            printf("duck;");
            break;
        case 7:
            printf("soldier;");
            break;
        }
        if (mp[xx][yy])
        {
            if (co[xx][yy] == 1)
                printf("red ");
            else
                printf("blue ");
            switch (mp[xx][yy])
            {
            case 1:
                printf("captain;");
                break;
            case 2:
                printf("guard;");
                break;
            case 3:
                printf("elephant;");
                break;
            case 4:
                printf("horse;");
                break;
            case 5:
                printf("car;");
                break;
            case 6:
                printf("duck;");
                break;
            case 7:
                printf("soldier;");
                break;
            }
        }
        else
            printf("NA;");
        if (mp[xx][yy] == 1)
        {
            printf("no;yes\n");
            end = 1;
            continue;
        }
        mp[xx][yy] = mp[x][y];
        co[xx][yy] = co[x][y];
        mp[x][y] = 0;
        co[x][y] = 0;
        int p = 0;
        for (int i = 0; i < 10 && !p; ++i)
            for (int j = 0; j < 9 && !p; ++j)
                for (int ii = 0; ii < 10 && !p; ++ii)
                    for (int jj = 0; jj < 9 && !p; ++jj)
                        if (co[i][j] && move(mp[i][j], i, j, ii, jj) && mp[ii][jj] == 1)
                            p = 1;
        if (p)
            printf("yes;");
        else
            printf("no;");
        printf("no\n");
        if (id == 1)
            id = 2;
        else
            id = 1;
    }
    return 0;
}