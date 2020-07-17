#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
int n, k;
ll ans;
int main()
{
    scanf("%d%d", &n, &k);
    ans = (ll)n * k;
    for (int l = 1, r; l <= min(n, k); l = r + 1)
    {
        r = min(k / (k / l), n);
        ans -= (ll)(k / l) * (l + r) * (r - l + 1) / 2;
    }
    printf("%lld", ans);
    return 0;
}