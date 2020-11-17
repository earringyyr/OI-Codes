#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n;
int a[5005], b[5005];
ll ans, f[2][20000005];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    for (int i = 1; i <= n; ++i)
        ++f[0][a[i]];
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            ++f[1][a[i] + a[j]];
    sort(a + 1, a + n + 1);
    int len = unique(a + 1, a + n + 1) - a - 1;
    for (int i = 1; i <= len; ++i)
    {
        ll tmp = f[0][a[i]] * (f[0][a[i]] - 1) * (f[0][a[i]] - 2) / 2 / 3, num = 0;
        for (int j = 1; j <= n; ++j)
            if (b[j] < a[i])
            {
                num += tmp * (f[1][a[i] - b[j]]);
                if (a[i] - b[j] - b[j] == b[j])
                    num -= tmp * (f[0][a[i] - b[j] - b[j]] - 1);
                else if (b[j] < a[i] - b[j])
                    num -= tmp * f[0][a[i] - b[j] - b[j]];
            }
        ans += num / 3;
        tmp = f[0][a[i]] * (f[0][a[i]] - 1) / 2;
        num = 0;
        for (int j = 1; j < i && a[j] <= a[i] - a[j]; ++j)
            if (a[j] < a[i] - a[j])
            {
                ans += tmp * (f[0][a[j]] * (f[0][a[j]] - 1) / 2) * (f[0][a[i] - a[j]] * (f[0][a[i] - a[j]] - 1) / 2);
                num += f[0][a[j]] * f[0][a[i] - a[j]];
            }
            else
            {
                ans += tmp * f[0][a[j]] * (f[0][a[j]] - 1) * (f[0][a[j]] - 2) * (f[0][a[j]] - 3) / 2 / 3 / 4;
                num += f[0][a[j]] * (f[0][a[i] - a[j]] - 1) / 2;
            }
        ll cnt = 0;
        for (int j = 1; j < i && a[j] <= a[i] - a[j]; ++j)
            if (a[j] < a[i] - a[j])
                cnt += tmp * (f[0][a[j]] * (f[0][a[i] - a[j]])) * (num - (f[0][a[j]] * (f[0][a[i] - a[j]])));
            else
                cnt += tmp * (f[0][a[j]] * (f[0][a[i] - a[j]] - 1) / 2) * (num - (f[0][a[j]] * (f[0][a[i] - a[j]] - 1) / 2));
        ans += cnt / 2;
    }
    printf("%lld", ans);
    return 0;
}