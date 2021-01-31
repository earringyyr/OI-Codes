#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, Q, l, r;
int a[300005];
ll k, ans;
ll aa[300005];
int main()
{
    freopen("railway.in", "r", stdin);
    freopen("railway.out", "w", stdout);
    scanf("%d%d", &n, &Q);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= Q; ++i)
    {
        ans = 0;
        scanf("%d%d%lld", &l, &r, &k);
        for (int j = 1; j <= n; ++j)
            aa[j] = a[j];
        for (int len = 1; len <= r - l + 1; ++len)
            for (int j = l; j <= r - len + 1; ++j)
            {
                ll sum = 0;
                for (int l = 0; l < len; ++l)
                    sum += aa[j + l];
                if (sum > k)
                {
                    ans += sum - k;
                    aa[j + len - 1] -= sum - k;
                }
            }
        printf("%lld\n", ans);
    }
    return 0;
}