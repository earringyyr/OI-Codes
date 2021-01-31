#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n;
int a[100005], b[100005], c[100005];
ll ans;
ll len[100005];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ans = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &c[i]);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &b[i]);
        for (int i = 1; i <= n; ++i)
            if (a[i] > b[i])
                swap(a[i], b[i]);
        for (int i = 2; i <= n; ++i)
        {
            if (i == 2 || a[i] == b[i])
                len[i] = c[i] - 1 + b[i] - a[i] + 2;
            else
                len[i] = max((ll)c[i] - 1 + b[i] - a[i] + 2, c[i] - 1 + 2 + len[i - 1] - (b[i] - a[i]));
            ans = max(ans, len[i]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}