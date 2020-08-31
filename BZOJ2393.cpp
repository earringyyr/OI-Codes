#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
ll l, r, cnt, a[1000005], b[1000005];
void calc(ll k)
{
    if (k > r)
        return;
    if (k)
        b[++cnt] = k;
    calc(k * 10 + 2);
    calc(k * 10 + 9);
    return;
}
ll gcd(ll x, ll y)
{
    if (!y)
        return x;
    return gcd(y, x % y);
}
ll LCM(ll x, ll y)
{
    return x * y / gcd(x, y);
}
ll solve(ll n, ll lcm, int lst, int num)
{
    ll sum = 0;
    if (num)
        sum = (num & 1 == 1 ? 1 : -1) * n / lcm;
    for (int i = lst + 1; i <= cnt; ++i)
        if (LCM(lcm, a[i]) <= n)
            sum += solve(n, LCM(lcm, a[i]), i, num + 1);
    return sum;
}
int main()
{
    scanf("%lld%lld", &l, &r);
    calc(0);
    sort(b + 1, b + cnt + 1);
    int tmp = 0;
    for (int i = 1; i <= cnt; ++i)
    {
        int p = 1;
        for (int j = 1; j < i; ++j)
            if (b[i] % b[j] == 0)
            {
                p = 0;
                break;
            }
        if (p)
            a[++tmp] = b[i];
    }
    cnt = tmp;
    printf("%lld", solve(r, 1, 0, 0) - solve(l - 1, 1, 0, 0));
    return 0;
}