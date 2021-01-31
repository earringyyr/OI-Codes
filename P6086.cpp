#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, m;
int fa[5000005], p[5000005], d[5000005];
ll ans;
int main()
{
    scanf("%d%d", &n, &m);
    if (m == 1)
    {
        for (int i = 1; i < n; ++i)
        {
            scanf("%d", &fa[i]);
            ++d[fa[i]];
        }
        int j = 0;
        for (int i = 1; i <= n - 2; ++i)
        {
            ++j;
            while (d[j])
                ++j;
            p[i] = fa[j];
            --d[p[i]];
            while (i < n - 2 && !d[p[i]] && p[i] < j)
            {
                p[i + 1] = fa[p[i]];
                ++i;
                --d[p[i]];
            }
        }
        for (int i = 1; i <= n - 2; ++i)
            ans ^= (ll)i * p[i];
    }
    else
    {
        for (int i = 1; i <= n - 2; ++i)
        {
            scanf("%d", &p[i]);
            ++d[p[i]];
        }
        p[n - 1] = n;
        int j = 0;
        for (int i = 1; i <= n - 1; ++i)
        {
            ++j;
            while (d[j])
                ++j;
            fa[j] = p[i];
            --d[p[i]];
            while (i < n - 1 && !d[p[i]] && p[i] < j)
            {
                fa[p[i]] = p[i + 1];
                ++i;
                --d[p[i]];
            }
        }
        for (int i = 1; i <= n - 1; ++i)
            ans ^= (ll)i * fa[i];
    }
    printf("%lld", ans);
    return 0;
}