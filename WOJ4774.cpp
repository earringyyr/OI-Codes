#include <iostream>
#include <cstdio>
#include <cmath>
#define int long long
using namespace std;
int n, a, b, c, d, x, y, ans;
int exgcd(int aa, int bb)
{
    if (bb == 0)
    {
        x = 1;
        y = 0;
        return aa;
    }
    int tem = exgcd(bb, aa % bb);
    int tmp = x;
    x = y;
    y = tmp - aa / bb * y;
    return tem;
}
signed main()
{
    scanf("%lld%lld%lld", &n, &a, &b);
    if (a > b)
        swap(a, b);
    c = exgcd(a, b);
    a /= c;
    b /= c;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &d);
        if (d % c != 0)
        {
            printf("-1");
            return 0;
        }
        d /= c;
        int xx = d * x, yy = d * y;
        int t = xx / b;
        xx -= t * b;
        yy += t * a;
        if (xx > 0)
            ans += min(abs(xx) + abs(yy), abs(xx - b) + abs(yy + a));
        else
            ans += min(abs(xx) + abs(yy), abs(xx + b) + abs(yy - a));
    }
    printf("%lld", ans);
    return 0;
}