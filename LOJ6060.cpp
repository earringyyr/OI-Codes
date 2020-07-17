#include <iostream>
#include <cstdio>
using namespace std;
int n;
long long num, ans, a[100005], p[65];
void ins(long long x)
{

    for (int i = 63; i >= 0; --i)
        if (!(num & (1LL << i)) && (x & (1LL << i)))
        {
            if (!p[i])
            {
                p[i] = x;
                return;
            }
            x ^= p[i];
        }
    for (int i = 63; i >= 0; --i)
        if ((num & (1LL << i)) && (x & (1LL << i)))
        {
            if (!p[i])
            {
                p[i] = x;
                return;
            }
            x ^= p[i];
        }
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &a[i]);
        num ^= a[i];
    }
    for (int i = 1; i <= n; ++i)
        ins(a[i]);
    for (int i = 63; i >= 0; --i)
        if (!(num & (1LL << i)) && !(ans & (1LL << i)))
            ans ^= p[i];
    for (int i = 63; i >= 0; --i)
        if ((num & (1LL << i)) && (ans & (1LL << i)))
            ans ^= p[i];
    printf("%lld", ans);
    return 0;
}