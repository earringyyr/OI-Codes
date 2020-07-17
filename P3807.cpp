#include <iostream>
#include <cstdio>
using namespace std;
int a[100005];
int ksm(int m, int n, int mod)
{
    int x = 1;
    while (n)
    {
        if (n % 2 == 1)
            x = (long long)x * m % mod;
        m = (long long)m * m % mod;
        n /= 2;
    }
    return x;
}
int c(int m, int n, int p)
{
    if (m > n)
        return 0;
    return (long long)a[n] * ksm(a[m], p - 2, p) % p * ksm(a[n - m], p - 2, p) % p;
}
int lucas(int m, int n, int p)
{
    if (m == 0)
        return 1;
    return (long long)c(m % p, n % p, p) * lucas(m / p, n / p, p) % p;
}
int main()
{
    int t;
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        int n, m, p;
        scanf("%d%d%d", &n, &m, &p);
        n = m + n;
        a[0] = 1;
        for (int i = 1; i <= n; ++i)
            a[i] = (long long)a[i - 1] * i % p;
        printf("%d\n", lucas(m, n, p));
    }
    return 0;
}