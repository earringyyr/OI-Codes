#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n, num, minx = 2e9, na = 1, nb, a[15], b[15], use[15];
void dfs(int k)
{
    if (k == n + 1)
    {
        if (num)
            minx = min(minx, abs(na - nb));
        return;
    }
    na *= a[k];
    nb += b[k];
    ++num;
    dfs(k + 1);
    na /= a[k];
    nb -= b[k];
    --num;
    dfs(k + 1);
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &a[i], &b[i]);
    dfs(1);
    printf("%d", minx);
    return 0;
}