#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int ans;
ll a, b, c;
bool solve(ll x, ll y)
{
    if (!x || !y)
    {
        if (!x && !y)
        {
            ++ans;
            return true;
        }
        return false;
    }
    ll v = y % b;
    if (v)
    {
        if ((x - v) % a == 0)
            return solve((x - v) / a, (y - v) / b);
        return false;
    }
    bool flg = false;
    if (x % a == 0)
        flg = solve((x - v) / a, (y - v) / b);
    if (x == b && y == b)
    {
        ++ans;
        flg = true;
    }
    return flg;
}
int main()
{
    scanf("%lld%lld%lld", &a, &b, &c);
    if (b == 1)
    {
        if (c == 1)
        {
            if (a == 1)
                printf("inf");
            else
                printf("1");
        }
        else
            printf("0");
    }
    else
    {
        solve(b, c);
        printf("%d", ans);
    }
    return 0;
}