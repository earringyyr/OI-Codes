#include <iostream>
#include <cstdio>
#define mod 10007
using namespace std;
int a, b, k, n, m, ans;
int ksm(int x, int k)
{
    int y = 1;
    while (k)
    {
        if (k & 1)
            y = y * x % mod;
        x = x * x % mod;
        k >>= 1;
    }
    return y;
}
int c(int x, int y)
{
    int num = 1;
    for (int i = 1; i <= y; ++i)
        num = (num * i) % mod;
    for (int i = 1; i <= x; ++i)
        num = (num * ksm(i, mod - 2)) % mod;
    for (int i = 1; i <= (y - x); ++i)
        num = (num * ksm(i, mod - 2)) % mod;
    return num;
}
int main()
{
    scanf("%d%d%d%d%d", &a, &b, &k, &n, &m);
    a %= mod;
    b %= mod;
    ans = (ksm(a, n) * ksm(b, m)) % mod;
    ans = (ans * c(n, k)) % mod;
    printf("%d", ans);
    return 0;
}