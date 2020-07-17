#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <tr1/unordered_map>
using namespace std;
using namespace tr1;
int x, y, a, p, b;
unordered_map<int, int> hsh;
int ksm(int a, int b, int mod)
{
    int c = 1;
    while (b)
    {
        if (b & 1)
            c = (long long)c * a % mod;
        a = (long long)a * a % mod;
        b >>= 1;
    }
    return c;
}
int gcd(int a, int b)
{
    if (!b)
        return a;
    return gcd(b, a % b);
}
void exgcd(int a, int b)
{
    if (!b)
    {
        x = 1;
        y = 0;
        return;
    }
    exgcd(b, a % b);
    int tmp = x;
    x = y;
    y = tmp - a / b * y;
    return;
}
void exBSGS()
{
    if (!a && b)
    {
        puts("No Solution");
        return;
    }
    if (!a && !b)
    {
        puts("1");
        return;
    }
    if (b == 1)
    {
        puts("0");
        return;
    }
    int d, num = 1, cnt = 0;
    while ((d = gcd(a, p)) > 1)
    {
        ++cnt;
        if (b % d)
        {
            puts("No Solution");
            return;
        }
        b /= d;
        p /= d;
        num = (long long)num * (a / d) % p;
        if (num == b)
        {
            printf("%d\n", cnt);
            return;
        }
    }
    hsh.clear();
    int m = ceil(sqrt(p)), sum = b;
    for (int i = 1; i <= m; ++i)
    {
        sum = (long long)sum * a % p;
        hsh[sum] = i;
    }
    int k = ksm(a, m, p);
    for (int i = 1; i <= m; ++i)
    {
        num = (long long)num * k % p;
        if (hsh[num])
        {
            printf("%d\n", cnt + i * m - hsh[num]);
            return;
        }
    }
    puts("No Solution");
    return;
}
int main()
{
    while (scanf("%d%d%d", &a, &p, &b))
    {
        if (a == 0 && p == 0 && b == 0)
            break;
        a %= p;
        b %= p;
        exBSGS();
    }
    return 0;
}