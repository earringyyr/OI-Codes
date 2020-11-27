#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, k;
ll ans, a[300005];
bool cmp(ll aa, ll bb)
{
    return aa > bb;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);
    for (int i = n; i >= 1; --i)
        a[i] = a[i] + a[i + 1];
    sort(a + 2, a + n + 1, cmp);
    for (int i = 1; i <= k; ++i)
        ans += a[i];
    printf("%lld", ans);
    return 0;
}