#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int k, n, p;
int t[105], s[105], d[105], st[105], ed[105];
int moveDirection, elevatorFloor, isAvailable, isMove, elevatorPeople, endPeople;
void timeConvert(int tim)
{
    int mm = tim / 60, ss = tim % 60;
    if (mm == 0)
        printf("00");
    else if (mm < 10)
        printf("0%d", mm);
    else
        printf("%d", mm);
    putchar(':');
    if (ss == 0)
        printf("00");
    else if (ss < 10)
        printf("0%d", ss);
    else
        printf("%d", ss);
    return;
}
bool moveIn(int id, int tim)
{
    if (elevatorPeople < p && !st[id] && t[id] <= tim && s[id] == elevatorFloor && moveDirection == (d[id] - s[id]) / abs(d[id] - s[id]))
        return true;
    return false;
}
bool moveOut(int id)
{
    if (st[id] && !ed[id] && d[id] == elevatorFloor)
        return true;
    return false;
}
bool moveIn2(int id, int tim)
{
    if (!st[id] && t[id] <= tim && s[id] == elevatorFloor)
        return true;
    return false;
}
bool moveIn3(int id, int tim)
{
    if (elevatorPeople != 0)
        return false;
    for (int i = 1; i <= n; ++i)
        if (!st[i] && t[i] <= tim && s[i] != elevatorFloor && (s[i] - elevatorFloor) / abs(s[i] - elevatorFloor) == moveDirection)
            return false;
    if (!st[id] && t[id] <= tim && s[id] == elevatorFloor)
        return true;
    return false;
}
int main()
{
    scanf("%d%d%d", &k, &n, &p);
    elevatorFloor = k;
    isAvailable = 1;
    for (int i = 1; i <= n; ++i)
        scanf("%d%d%d", &t[i], &s[i], &d[i]);
    for (int tim = 0; tim <= 1200; ++tim)
    {
        if (endPeople == n)
            break;
        if (!isAvailable)
        {
            if (!isMove)
            {
                int num = 0;
                for (int i = 1; i <= n; ++i)
                    if (moveOut(i))
                    {
                        ed[i] = 1;
                        ++num;
                        --elevatorPeople;
                        ++endPeople;
                    }
                if (num)
                {
                    timeConvert(tim);
                    printf(" %d people leave the elevator.\n", num);
                    if (elevatorPeople == 0)
                    {
                        int flg = 0;
                        for (int i = 1; i <= n; ++i)
                            if (!st[i] && t[i] <= tim)
                            {
                                flg = 1;
                                break;
                            }
                        if (flg)
                            continue;
                        isAvailable = 1;
                        moveDirection = 0;
                    }
                    continue;
                }
                for (int i = 1; i <= n; ++i)
                    if (moveIn(i, tim))
                    {
                        st[i] = 1;
                        ++num;
                        ++elevatorPeople;
                    }
                if (num)
                {
                    timeConvert(tim);
                    printf(" %d people enter the elevator.\n", num);
                    continue;
                }
                if (elevatorPeople == 0)
                {
                    int flg = 0;
                    for (int i = 1; i <= n; ++i)
                        if (!st[i] && t[i] <= tim && s[i] != elevatorFloor && (s[i] - elevatorFloor) / abs(s[i] - elevatorFloor) == moveDirection)
                        {
                            flg = 1;
                            break;
                        }
                    if (flg)
                    {
                        flg = 0;
                        for (int i = 1; i <= n; ++i)
                            if (!st[i] && t[i] <= tim && s[i] != elevatorFloor && (s[i] - elevatorFloor) / abs(s[i] - elevatorFloor) == moveDirection)
                            {
                                isMove = 1;
                                flg = 1;
                                timeConvert(tim);
                                if (moveDirection == 1)
                                    printf(" The elevator starts to move up from floor %d.\n", elevatorFloor);
                                else
                                    printf(" The elevator starts to move down from floor %d.\n", elevatorFloor);
                                break;
                            }
                        if (flg)
                            continue;
                        for (int i = 1; i <= n; ++i)
                            if (!st[i] && t[i] <= tim && s[i] != elevatorFloor && (s[i] - elevatorFloor) / abs(s[i] - elevatorFloor) != moveDirection)
                            {
                                isMove = 1;
                                moveDirection *= -1;
                                flg = 1;
                                timeConvert(tim);
                                if (moveDirection == 1)
                                    printf(" The elevator starts to move up from floor %d.\n", elevatorFloor);
                                else
                                    printf(" The elevator starts to move down from floor %d.\n", elevatorFloor);
                                break;
                            }
                        if (flg)
                            continue;
                        isAvailable = 1;
                        moveDirection = 0;
                        continue;
                    }
                    for (int i = 1; i <= n; ++i)
                        if (moveIn2(i, tim))
                        {
                            st[i] = 1;
                            ++num;
                            ++elevatorPeople;
                        }
                    if (num)
                    {
                        moveDirection *= -1;
                        timeConvert(tim);
                        printf(" %d people enter the elevator.\n", num);
                        continue;
                    }
                    isAvailable = 1;
                    moveDirection = 0;
                    --tim;
                    continue;
                }
                timeConvert(tim);
                if (moveDirection == 1)
                    printf(" The elevator starts to move up from floor %d.\n", elevatorFloor);
                else
                    printf(" The elevator starts to move down from floor %d.\n", elevatorFloor);
                isMove = 1;
            }
            else
            {
                elevatorFloor += moveDirection;
                int flg = 0;
                for (int i = 1; i <= n; ++i)
                    if (moveIn(i, tim) || moveOut(i))
                    {
                        timeConvert(tim);
                        isMove = 0;
                        printf(" The elevator stops at floor %d.\n", elevatorFloor);
                        --tim;
                        flg = 1;
                        break;
                    }
                if (!flg)
                    for (int i = 1; i <= n; ++i)
                        if (moveIn3(i, tim))
                        {
                            timeConvert(tim);
                            isMove = 0;
                            moveDirection *= -1;
                            printf(" The elevator stops at floor %d.\n", elevatorFloor);
                            --tim;
                            break;
                        }
            }
        }
        else
        {
            {
                int minx = 114514, startDirect = 0;
                for (int i = 1; i <= n; ++i)
                    if (!st[i] && t[i] <= tim && t[i] <= minx)
                    {
                        minx = t[i];
                        isMove = 1;
                        isAvailable = 0;
                        if (s[i] == elevatorFloor)
                        {
                            if (!startDirect || (startDirect == 1 && moveDirection != 1))
                                moveDirection = (d[i] - s[i]) / abs(d[i] - s[i]);
                            startDirect = 1;
                        }
                        if (!startDirect)
                        {
                            if (s[i] > elevatorFloor)
                                moveDirection = 1;
                            if (s[i] < elevatorFloor && moveDirection != 1)
                                moveDirection = -1;
                        }
                    }
                if (startDirect)
                    isMove = 0;
            }
            if (!isAvailable)
                if (isMove)
                {
                    for (; tim <= 1200; ++tim)
                    {
                        int num = 0;
                        for (int i = 1; i <= n; ++i)
                            if (moveIn(i, tim))
                            {
                                st[i] = 1;
                                ++num;
                                ++elevatorPeople;
                            }
                        if (num)
                        {
                            timeConvert(tim);
                            printf(" %d people enter the elevator.\n", num);
                            num = 1;
                        }
                        if (num == 0)
                            break;
                    }
                    timeConvert(tim);
                    if (moveDirection == 1)
                        printf(" The elevator starts to move up from floor %d.\n", elevatorFloor);
                    else
                        printf(" The elevator starts to move down from floor %d.\n", elevatorFloor);
                }
                else
                    --tim;
        }
    }
    return 0;
}