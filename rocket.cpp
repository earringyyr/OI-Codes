#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, v;
ll sum, ans;
struct node
{
    int x;
    int y;
} a[305], b[305];
bool cmp(node aa, node bb)
{
    return aa.x * bb.y > bb.x * aa.y;
}
int main()
{
    freopen("rocket.in", "r", stdin);
    freopen("rocket.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &a[i].x, &a[i].y);
    for (int s = 0; s < (1 << n); ++s)
    {
        for (int i = 1; i <= n; ++i)
        {
            b[i] = a[i];
            if (s & (1 << (i - 1)))
                swap(b[i].x, b[i].y);
        }
        sort(b + 1, b + n + 1, cmp);
        v = 0;
        sum = 0;
        for (int i = 1; i <= n; ++i)
        {
            sum = sum + (ll)(2 * v + b[i].x) * b[i].y;
            v += b[i].x;
        }
        ans = max(ans, sum);
    }
    printf("%.2f\n", (double)ans / 2);
    return 0;
}