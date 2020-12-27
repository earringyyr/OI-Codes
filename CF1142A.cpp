#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, k, a, b;
ll s1, s2, S1, S2, l1, l2, l3, l4, minx = 1e18, maxn;
ll gcd(ll x, ll y)
{
    if (!y)
        return x;
    return gcd(y, x % y);
}
int main()
{
    scanf("%d%d%d%d", &n, &k, &a, &b);
    s1 = a + 1;
    s2 = k + 1 - a;
    for (int i = 0; i < n; ++i)
    {
        S1 = (ll)i * k + 1 + b;
        S2 = (ll)(i + 1) * k + 1 - b;
        l1 = (S1 - s1 + (ll)n * k) % ((ll)n * k);
        l2 = (S1 - s2 + (ll)n * k) % ((ll)n * k);
        l3 = (S2 - s1 + (ll)n * k) % ((ll)n * k);
        l4 = (S2 - s2 + (ll)n * k) % ((ll)n * k);
        if (!l1)
            l1 = (ll)n * k;
        if (!l2)
            l2 = (ll)n * k;
        if (!l3)
            l3 = (ll)n * k;
        if (!l4)
            l4 = (ll)n * k;
        minx = min(minx, (ll)n * k / gcd((ll)n * k, l1));
        minx = min(minx, (ll)n * k / gcd((ll)n * k, l2));
        minx = min(minx, (ll)n * k / gcd((ll)n * k, l3));
        minx = min(minx, (ll)n * k / gcd((ll)n * k, l4));
        maxn = max(maxn, (ll)n * k / gcd((ll)n * k, l1));
        maxn = max(maxn, (ll)n * k / gcd((ll)n * k, l2));
        maxn = max(maxn, (ll)n * k / gcd((ll)n * k, l3));
        maxn = max(maxn, (ll)n * k / gcd((ll)n * k, l4));
    }
    printf("%lld %lld", minx, maxn);
    return 0;
}