#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
int a, b, sum, num[15], f[15][15];
int dfs(int pos, int pre, bool st, bool limit)
{
    if (pos == 0)
        return 1;
    if (!limit && f[pos][pre] != -1)
        return f[pos][pre];
    int res = limit ? num[pos] : 9, ans = 0;
    for (int i = 0; i <= res; ++i)
    {
        if (abs(i - pre) < 2)
            continue;
        if (st && !i)
            ans += dfs(pos - 1, -2, true, false);
        else
            ans += dfs(pos - 1, i, false, limit && i == res);
    }
    if (!st && !limit)
        f[pos][pre] = ans;
    return ans;
}
int solve(int x)
{
    sum = 0;
    while (x > 0)
    {
        num[++sum] = x % 10;
        x /= 10;
    }
    memset(f, -1, sizeof(f));
    return dfs(sum, -2, true, true);
}
int main()
{
    scanf("%d%d", &a, &b);
    printf("%d", solve(b) - solve(a - 1));
    return 0;
}