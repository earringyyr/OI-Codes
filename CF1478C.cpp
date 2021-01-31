#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n;
ll sum;
ll a[200005];
ll d[200005];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        sum = 0;
        int flg = 1;
        scanf("%d", &n);
        for (int i = 1; i <= 2 * n; ++i)
            scanf("%lld", &d[i]);
        sort(d + 1, d + 2 * n + 1);
        for (int i = 2 * n; i >= 2; i -= 2)
        {
            if (d[i] != d[i - 1])
            {
                flg = 0;
                break;
            }
            if (d[i] % 2 != 0)
            {
                flg = 0;
                break;
            }
            d[i] /= 2;
            if (d[i] <= sum)
            {
                flg = 0;
                break;
            }
            d[i] -= sum;
            if (d[i] % (i / 2) == 0)
            {
                a[i / 2] = d[i] / (i / 2);
                sum += a[i / 2];
            }
            else
            {
                flg = 0;
                break;
            }
        }
        sort(a + 1, a + n + 1);
        for (int i = 2; i <= n; ++i)
            if (a[i] == a[i - 1])
            {
                flg = 0;
                break;
            }
        if (flg)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}