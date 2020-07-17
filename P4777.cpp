#include <iostream>
#include <cstdio>
using namespace std;
int n;
long long x, y, a[100005], b[100005];
long long qmul(long long c, long long d, long long mod)
{
    long long x = c * d - (long long)((long double)c * d / mod) * mod;
    return x < 0 ? x + mod : (x > mod ? x - mod : x);
}
void exgcd(long long c, long long d)
{
    if (d == 0)
    {
        x = 1;
        y = 0;
        return;
    }
    exgcd(d, c % d);
    long long z = x;
    x = y;
    y = z - c / d * y;
    return;
}
long long gcd(long long c, long long d)
{
    if (d == 0)
        return c;
    return gcd(d, c % d);
}
long long lcm(long long c, long long d)
{
    long long e = gcd(c, d);
    return c / e * d;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld%lld", &a[i], &b[i]);
    for (int i = 2; i <= n; ++i)
    {
        exgcd(a[i - 1], a[i]);
        x = (x % a[i] + a[i]) % a[i];
        x = qmul(x, ((b[i] - b[i - 1]) % a[i] + a[i]) % a[i] / gcd(a[i - 1], a[i]), a[i] / gcd(a[i - 1], a[i]));
        b[i] = a[i - 1] * x + b[i - 1];
        a[i] = lcm(a[i - 1], a[i]);
        b[i] = (b[i] % a[i] + a[i]) % a[i];
    }
    cout << b[n];
    return 0;
}