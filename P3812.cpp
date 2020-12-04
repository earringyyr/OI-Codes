#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n;
ll ans, s[55], w[55];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &s[i]);
        for (int j = 50; j >= 0; --j)
            if ((1LL << j) & s[i])
            {
                if (!w[j])
                {
                    w[j] = s[i];
                    break;
                }
                else
                    s[i] ^= w[j];
            }
    }
    for (int i = 50; i >= 0; --i)
        if ((ans ^ w[i]) > ans)
            ans ^= w[i];
    printf("%lld", ans);
    return 0;
}