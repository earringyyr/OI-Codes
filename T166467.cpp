#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, maxn, sum;
ll ans;
ll f[305][90005];
struct node
{
    int x;
    int y;
} a[305];
bool cmp(node aa, node bb)
{
    return aa.x * bb.y < bb.x * aa.y;
}
int main()
{
    memset(f, -1, sizeof(f));
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &a[i].x, &a[i].y);
        if (a[i].x < a[i].y)
            swap(a[i].x, a[i].y);
    }
    sort(a + 1, a + n + 1, cmp);
    f[0][0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= maxn; ++j)
            if (f[i - 1][j] != -1)
            {
                f[i][j + a[i].x] = max(f[i][j + a[i].x], f[i - 1][j] + (sum - j) * a[i].x);
                f[i][j + a[i].y] = max(f[i][j + a[i].y], f[i - 1][j] + j * a[i].x);
            }
        maxn += a[i].x;
        sum += a[i].x + a[i].y;
    }
    for (int i = 0; i <= maxn; ++i)
        ans = max(ans, f[n][i]);
    ans *= 2;
    for (int i = 1; i <= n; ++i)
        ans += a[i].x * a[i].y;
    printf("%.2f", (double)ans / 2);
    return 0;
}