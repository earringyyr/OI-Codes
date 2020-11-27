#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int ans, k;
ll w[105];
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
        {
            w[++k] = v;
            return solve((x - v) / a, (y - v) / b);
        }
        return false;
    }
    bool flg = false;
    int tmp = k;
    if (x % a == 0)
    {
        w[++k] = v;
        flg = solve((x - v) / a, (y - v) / b);
    }
    if (x == b && y == b)
    {
        ++ans;
        if (!flg)
        {
            k = tmp;
            w[++k] = b;
        }
        flg = true;
    }
    return flg;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ans = 0;
        k = 0;
        scanf("%lld%lld%lld", &a, &b, &c);
        if (b == 1)
        {
            if (c == 1)
            {
                if (a == 1)
                    puts("-1");
                else
                {
                    puts("1");
                    puts("0 1");
                }
            }
            else
                puts("0");
        }
        else
        {
            solve(b, c);
            printf("%d\n", ans);
            if (ans)
            {
                printf("%d ", k - 1);
                for (int i = k; i >= 1; --i)
                    printf("%lld ", w[i]);
                putchar('\n');
            }
        }
    }
    return 0;
}