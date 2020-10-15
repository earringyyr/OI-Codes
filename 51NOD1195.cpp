#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <tr1/unordered_map>
#define mpr make_pair
#define pii pair<int, int>
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
using namespace std;
using namespace tr1;
typedef long long ll;
int p, mod, sum;
int vis[50005], pri[50005];
ll ans;
unordered_map<int, int> mp;
ll ksm(ll a, int k)
{
    ll b = 1;
    while (k)
    {
        if (k & 1)
            b = b * a;
        a = a * a;
        k >>= 1;
    }
    return b;
}
inline ll gcd(ll x, ll y)
{
    if (!y)
        return x;
    return gcd(y, x % y);
}
int MOD(int tmp)
{
    if (tmp > mod)
        tmp -= mod;
    return tmp;
}
inline pii f(int n)
{
    if (n == 0)
        return mpr(0, 1);
    pii F = f(n >> 1);
    int x = (ll)F.first * (MOD(2 * F.second) - F.first + mod) % mod;
    int y = MOD((ll)F.first * F.first % mod + (ll)F.second * F.second % mod);
    if (n & 1)
        return mpr(y, (x + y) % mod);
    else
        return mpr(x, y);
}
inline bool check(int n)
{
    pii F = f(n - 1);
    if (F.first == 1 && F.second == 0)
        return true;
    return false;
}
inline int calc(int tmp)
{
    int num = tmp;
    int sqr = sqrt(tmp);
    for (register int i = 1; pri[i] <= sqr && pri[i] <= tmp; ++i)
        if (tmp % pri[i] == 0)
        {
            while (tmp % pri[i] == 0)
            {
                tmp /= pri[i];
                if (check(num / pri[i]))
                    num /= pri[i];
                else
                    break;
            }
            while (tmp % pri[i] == 0)
                tmp /= pri[i];
        }
    if (tmp > 1)
        if (check(num / tmp))
            num /= tmp;
    return num;
}
int main()
{
    for (register int i = 2; i <= 50000; ++i)
    {
        if (!vis[i])
        {
            vis[i] = i;
            pri[++sum] = i;
        }
        for (register int j = 1; j <= sum && i * pri[j] <= 50000 && pri[j] <= vis[i]; ++j)
            vis[i * pri[j]] = pri[j];
    }
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &p);
        ans = 1;
        int sqr = sqrt(p);
        for (register int i = 1; pri[i] <= sqr && pri[i] <= p; ++i)
            if (p / pri[i] * pri[i] == p)
            {
                int k = 0;
                while (p % pri[i] == 0)
                {
                    ++k;
                    p /= pri[i];
                }
                ll tmp;
                if (!mp[pri[i]])
                {
                    if (pri[i] == 2)
                        tmp = 3;
                    else if (pri[i] == 5)
                        tmp = 20;
                    else
                    {
                        if (pri[i] % 5 == 1 || pri[i] % 5 == 4)
                            tmp = pri[i] - 1;
                        else
                            tmp = 2 * pri[i] + 2;
                    }
                    mod = pri[i];
                    mp[pri[i]] = calc(tmp);
                }
                tmp = mp[pri[i]];
                tmp = tmp * ksm(pri[i], k - 1);
                ans = ans * tmp / gcd(ans, tmp);
            }
        if (p > 1)
        {
            ll tmp;
            if (!mp[p])
            {
                if (p == 2)
                    tmp = 3;
                else if (p == 5)
                    tmp = 20;
                else
                {
                    if (p % 5 == 1 || p % 5 == 4)
                        tmp = p - 1;
                    else
                        tmp = 2 * p + 2;
                }
                mod = p;
                mp[p] = calc(tmp);
            }
            tmp = mp[p];
            ans = ans * tmp / gcd(ans, tmp);
        }
        printf("%lld\n", ans);
    }
    return 0;
}