#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <cmath>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int l, r, sum, ban[700005];
int vis[10000005], pri[10000005], inv[10000005];
bitset<500> s[505], S[700005];
int ksm(int aa, int k)
{
    int bb = 1;
    while (k)
    {
        if (k & 1)
            bb = (ll)bb * aa % mod;
        aa = (ll)aa * aa % mod;
        k >>= 1;
    }
    return bb;
}
int main()
{
    for (int i = 2; i <= 10000000; ++i)
    {
        if (!vis[i])
        {
            vis[i] = i;
            pri[++sum] = i;
            inv[i] = sum;
        }
        for (int j = 1; j <= sum && vis[i] >= pri[j] && i * pri[j] <= 10000000; ++j)
            vis[i * pri[j]] = pri[j];
    }
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int num = 0;
        memset(ban, 0, sizeof(ban));
        for (int i = 1; i <= 500; ++i)
            s[i].reset();
        for (int i = 1; i <= 700000; ++i)
            S[i].reset();
        scanf("%d%d", &l, &r);
        if (r - l <= 6660)
        {
            int sqr = sqrt(r);
            for (int i = l; i <= r; ++i)
            {
                bitset<500> tmp;
                int w = i;
                for (int j = 1; j <= sum && pri[j] <= sqr; ++j)
                    if (w % pri[j] == 0)
                    {
                        while (w % pri[j] == 0)
                        {
                            w /= pri[j];
                            tmp[j] = (tmp[j] + 1) % 2;
                        }
                    }
                int p = 0;
                if (w > 1)
                {
                    w = inv[w];
                    if (!ban[w])
                    {
                        p = 1;
                        S[w] = tmp;
                        ban[w] = 1;
                    }
                    else
                        tmp ^= S[w];
                }
                if (!p)
                    for (int j = 1; j <= 500; ++j)
                        if (tmp[j])
                        {
                            if (s[j].none())
                            {
                                s[j] = tmp;
                                p = 1;
                                break;
                            }
                            tmp ^= s[j];
                        }
                if (p)
                    ++num;
            }
        }
        else
            for (int i = 1; i <= sum; ++i)
            {
                if (r / pri[i] > (l - 1) / pri[i])
                    ++num;
                if (pri[i] > r)
                    break;
            }
        printf("%d\n", ksm(2, r - l + 1 - num));
    }
    return 0;
}