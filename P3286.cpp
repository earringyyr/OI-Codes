#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
long long l, r, f[50][2500];
int k, sum, num[50];
long long dfs1(int pos, long long tot, bool limit)
{
    if (!pos)
        return tot;
    if (!limit && f[pos][tot] != -1)
        return f[pos][tot];
    long long ans = 0;
    int res = limit ? num[pos] : k - 1;
    for (int i = 0; i <= res; ++i)
        ans += dfs1(pos - 1, tot + i * (pos - 1), limit && i == res);
    if (!limit)
        f[pos][tot] = ans;
    return ans;
}
long long dfs2(int pos, long long tot, bool limit, int mid)
{
    if (!pos)
        return tot > 0 ? tot : 0;
    if (!limit && f[pos][tot] != -1)
        return f[pos][tot];
    long long ans = 0;
    int res = limit ? num[pos] : k - 1;
    for (int i = 0; i <= res; ++i)
        ans += dfs2(pos - 1, tot + i * ((pos >= mid) ? 1 : -1), limit && i == res, mid);
    if (!limit)
        f[pos][tot] = ans;
    return ans;
}
long long solve(long long x)
{
    sum = 0;
    while (x > 0)
    {
        num[++sum] = x % k;
        x /= k;
    }
    memset(f, -1, sizeof(f));
    long long ans = dfs1(sum, 0, true);
    for (int i = 2; i <= sum; ++i)
    {
        memset(f, -1, sizeof(f));
        ans -= dfs2(sum, 0, true, i);
    }
    return ans;
}
int main()
{
    scanf("%lld%lld%d", &l, &r, &k);
    printf("%lld", solve(r) - solve(l - 1));
    return 0;
}