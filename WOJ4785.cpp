#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, q;
long long g, c[700005];
inline int read_int()
{
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}
inline long long read_long()
{
    long long x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}
inline long long gcd(long long x, long long y)
{
    if (!y)
        return x;
    return gcd(y, x % y);
}
int main()
{
    n = read_int();
    for (int i = 1; i <= n; ++i)
    {
        c[i] = read_long();
        if (i == 1)
            g = c[i];
        else
            g = gcd(g, c[i]);
    }
    sort(c + 1, c + n + 1);
    q = read_int();
    for (int i = 1; i <= q; ++i)
    {
        long long a;
        int b;
        a = read_long();
        b = read_int();
        if (b == 1)
        {
            if (g % a == 0)
                puts("Yes");
            else
                puts("No");
        }
        else
        {
            if (a > 1000000000)
                puts("No");
            else
            {
                if (c[1] <= a * a)
                    puts("No");
                else
                    puts("Yes");
            }
        }
    }
    return 0;
}