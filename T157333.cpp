#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
ll p, q, b;
ll gcd(ll x, ll y)
{
    if (!y)
        return x;
    return gcd(y, x % y);
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld%lld%lld", &p, &q, &b);
        if (!p)
        {
            puts("No");
            continue;
        }
        ll g = gcd(p, q);
        p /= g;
        q /= g;
        b = gcd(b, q);
        while (b > 1)
        {
            q /= b;
            b = gcd(b, q);
        }
        if (q > 1)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}