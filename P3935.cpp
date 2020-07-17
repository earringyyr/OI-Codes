#include <iostream>
#include <cstdio>
using namespace std;
const int mod = 998244353;
typedef long long ll;
int calc(ll k)
{
    int ans = 0;
    for (ll l = 1, r; l <= k; l = r + 1)
    {
        r = k / (k / l);
        ans = (ans + ((ll)(k / l) * (r - l + 1) % mod)) % mod;
    }
    return ans;
}
int main()
{
    ll l, r;
    scanf("%lld%lld", &l, &r);
    printf("%d", ((calc(r) - calc(l - 1)) % mod + mod) % mod);
    return 0;
}