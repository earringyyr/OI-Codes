#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int h, ans;
int p[300005], vis[300005], sum[300005];
void dfs2(int k, int mul, int tim, int type)
{
    if (k == 1)
        return;
    mul = (ll)k * mul % mod;
    if (type)
    {
        if (vis[k] < tim)
        {
            vis[k] = tim;
            sum[k] = 0;
        }
        sum[k] = (sum[k] + mul) % mod;
    }
    else if (vis[k ^ 1] == tim)
        ans = (ans + (ll)sum[k ^ 1] * (k / 2) % mod * mul % mod) % mod;
    dfs2(k >> 1, mul, tim, type);
    return;
}
void dfs1(int k, int mul, int tim, bool type)
{
    mul = (ll)k * mul % mod;
    if (k >= (1 << (h - 1)))
    {
        dfs2(p[k], mul, tim, type);
        return;
    }
    dfs1(k << 1, mul, tim, type);
    dfs1(k << 1 | 1, mul, tim, type);
    return;
}
int main()
{
    scanf("%d", &h);
    for (int i = (1 << (h - 1)); i < (1 << h); ++i)
    {
        scanf("%d", &p[i]);
        p[i] += (1 << (h - 1)) - 1;
    }
    for (int i = 1; i < (1 << (h - 1)); ++i)
    {
        dfs1(i << 1, i, i, true);
        dfs1(i << 1 | 1, 1, i, false);
    }
    printf("%d", ans);
    return 0;
}