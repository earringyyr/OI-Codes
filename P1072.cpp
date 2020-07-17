#include <iostream>
#include <cstdio>
#include <cmath>
#define int long long
using namespace std;
int t, a, aa, b, bb;
int gcd(int x, int y)
{
    if (!y)
        return x;
    return gcd(y, x % y);
}
signed main()
{
    scanf("%lld", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        int ans = 0;
        scanf("%lld%lld%lld%lld", &a, &aa, &b, &bb);
        int k = sqrt(bb);
        for (int i = 1; i <= k; ++i)
            if (bb % i == 0)
            {
                int l = i;
                if (gcd(l, a) == aa && gcd(l, b) == l * b / bb)
                    ++ans;
                if (i * i == bb)
                    break;
                l = bb / i;
                if (gcd(l, a) == aa && gcd(l, b) == l * b / bb)
                    ++ans;
            }
        printf("%lld\n", ans);
    }
    return 0;
}