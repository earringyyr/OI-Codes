#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, m;
ll sum;
ll a[50005];
bool cmp(ll aa, ll bb)
{
    return aa > bb;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        sum = 0;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
            scanf("%lld", &a[i]);
        if (n < m)
        {
            puts("0");
            continue;
        }
        sort(a + 1, a + n + 1, cmp);
        for (int i = m + 1; i <= n; ++i)
            sum += a[i];
        for (int i = m; i >= 1; --i)
            if (i == 1)
            {
                a[i] += sum / n;
                printf("%lld\n", a[i]);
            }
            else
            {
                ll tmp = (a[i - 1] - a[i]) * (m - i + 1);
                if (tmp > sum)
                {
                    a[i] += sum / (m - i + 1);
                    printf("%lld\n", a[i]);
                    break;
                }
                else
                    sum -= tmp;
            }
    }
    return 0;
}