#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, s, m[35], f[35][10005];
int dfs(int k, int num)
{
    if (f[k][num] != -1)
        return f[k][num];
    if (!num)
        return 1;
    f[k][num] = 0;
    for (int i = 1; i <= min(num, m[k]); ++i)
        if (!dfs((k + 1) % (2 * n), num - i))
        {
            f[k][num] = 1;
            break;
        }
    return f[k][num];
}
int main()
{
    while (scanf("%d", &n))
    {
        if (!n)
            break;
        memset(f, -1, sizeof(f));
        scanf("%d", &s);
        for (int i = 0; i < 2 * n; ++i)
            scanf("%d", &m[i]);
        printf("%d\n", dfs(0, s));
    }
    return 0;
}