#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;
typedef long long ll;
int n, a[1000005];
long long b[1000005], c[1000005], d[1000005];
long long rd()
{
    return ((ll)rand() << 32) + rand();
}
int calc()
{
    int ans = 1;
    for (int i = 1; i <= n; ++i)
        b[i] = b[i - 1] ^ c[a[i]];
    for (int i = 1; i <= n; ++i)
        if (a[i] == 1)
        {
            int maxn = 1;
            for (int j = i + 1; j <= n; ++j)
            {
                if (a[j] == 1)
                    break;
                if (a[j] > maxn)
                    maxn = a[j];
                if (j - maxn >= 0 && j - maxn < i)
                    if ((b[j] ^ b[j - maxn]) == d[maxn])
                        ans = max(ans, maxn);
            }
        }
    return ans;
}
int main()
{
    srand(time(0));
    for (int i = 1; i <= 1000000; ++i)
    {
        c[i] = rd();
        d[i] = d[i - 1] ^ c[i];
    }
    int T;
    scanf("%d", &T);
    while (T--)
    {
        bool p = false;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &a[i]);
            if (a[i] == 1)
                p = true;
        }
        if (!p)
        {
            puts("0");
            continue;
        }
        int ans = calc();
        for (int i = 1; i <= n / 2; ++i)
            swap(a[i], a[n - i + 1]);
        ans = max(ans, calc());
        printf("%d\n", ans);
    }
    return 0;
}