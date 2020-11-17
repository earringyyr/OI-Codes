#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, m, w;
int vis[5005], ans[5005];
ll k;
ll fac[5005];
ll c[5005][5005], f[5005][5005];
ll add(ll a, ll b)
{
    if (a == -1 || b == -1)
        return -1;
    if (a + b > k)
        return -1;
    return a + b;
}
ll mul(ll a, ll b)
{
    if (a == 0 || b == 0)
        return 0;
    if (a == -1 || b == -1)
        return -1;
    if (k / a < b)
        return -1;
    return a * b;
}
int main()
{
    scanf("%d%d%lld", &n, &m, &k);
    c[0][0] = 1;
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = mul(fac[i - 1], i);
    for (int i = 1; i <= n; ++i)
    {
        c[i][0] = 1;
        for (int j = 1; j <= n; ++j)
            c[i][j] = add(c[i - 1][j - 1], c[i - 1][j]);
    }
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        f[i][0] = fac[i];
        f[i][1] = mul(i - 1, f[i - 1][0]);
        for (int j = 2; j <= i; ++j)
            f[i][j] = add(mul(i - j, f[i - 1][j - 1]), mul(j - 1, f[i - 1][j - 2]));
    }
    for (int i = 1; i <= n; ++i)
    {
        w = n - i;
        for (int j = 1; j < i; ++j)
            if (ans[j] > i)
                --w;
        for (int j = 1; j <= n; ++j)
            if (!vis[j])
            {
                if (i == j && !m)
                    continue;
                if (i == j)
                    --m;
                if (j > i)
                    --w;
                if (w < m)
                    continue;
                ll tmp = mul(c[w][m], f[n - i - m][w - m]);
                if (tmp == -1 || tmp >= k)
                {
                    ans[i] = j;
                    vis[j] = 1;
                    break;
                }
                else
                {
                    if (i == j)
                        ++m;
                    if (j > i)
                        ++w;
                    k -= tmp;
                }
            }
    }
    for (int i = 1; i <= n; ++i)
        if (ans[i] == 0)
        {
            printf("-1");
            return 0;
        }
    for (int i = 1; i <= n; ++i)
        printf("%d ", ans[i]);
    return 0;
}