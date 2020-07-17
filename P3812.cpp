#include <iostream>
#include <cstdio>
using namespace std;
long long n, ans, a[55], s[55];
int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &a[i]);
        for (int j = 50; j >= 0; --j)
            if (a[i] & (1LL << j))
            {
                if (!s[j])
                {
                    s[j] = a[i];
                    break;
                }
                a[i] ^= s[j];
            }
    }
    for (int i = 50; i >= 0; --i)
        if ((ans ^ s[i]) > ans)
            ans ^= s[i];
    printf("%lld", ans);
    return 0;
}