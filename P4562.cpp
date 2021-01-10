#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int l, r, len, cnt, num, a = 1, c = 1, ans;
int vis[10000005], inv[10000005];
int main()
{
    scanf("%d%d", &l, &r);
    len = r - l + 1;
    for (int i = l; i <= r; ++i)
        if (!vis[i])
        {
            ++num;
            for (int j = i; j <= r; j += i)
                if (!vis[j])
                {
                    vis[j] = 1;
                    ++cnt;
                }
            if (cnt == len)
                break;
        }
    inv[1] = 1;
    for (int i = 2; i <= len; ++i)
        inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;
    for (int i = 1; i <= num; ++i)
        a = (ll)a * i % mod;
    for (int i = 1; i <= len - num; ++i)
        a = (ll)a * i % mod;
    for (int i = num; i <= len; ++i)
    {
        if (i > num)
            c = (ll)c * (i - 1) % mod * inv[i - num] % mod;
        ans = (ans + (ll)i * a % mod * c % mod) % mod;
    }
    printf("%d", ans);
    return 0;
}