#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int m, d, num;
int main()
{
    scanf("%d-%d", &m, &d);
    if (!m)
    {
        m = 1;
        ++num;
    }
    if (!d)
    {
        d = 1;
        ++num;
    }
    if (m > 12)
    {
        ++num;
        m = m % 10;
        if (m < 20)
            m = 10;
        else
        {
            if (m == 2)
                m = 12;
            if (!m)
                m = 10;
        }
    }
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
    {
        if (d > 31)
            ++num;
    }
    else if (m == 2)
    {
        if (d > 28)
            ++num;
    }
    else
    {
        if (d > 30)
            ++num;
    }
    printf("%d", num);
    return 0;
}