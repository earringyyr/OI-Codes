#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define int long long
using namespace std;
int n, K, res, val, s[100005];
unsigned long long ans, a[100005];
vector<int> b;
signed main()
{
    scanf("%lld%lld", &n, &K);
    for (int i = 1; i <= n; ++i)
        scanf("%llu", &a[i]);
    if (K == 1)
    {
        for (int i = 1; i <= n; ++i)
            ans |= a[i];
        printf("%llu", ans >> 1);
        if (ans & 1)
            printf(".5");
        return 0;
    }
    if (K == 2)
    {
        for (int i = 0; i < 32; ++i)
            for (int j = 0; j < 32; ++j)
            {
                bool p = false;
                for (int k = 1; k <= n; ++k)
                    if (a[k] & (1 << i))
                        p = true;
                if (!p)
                    continue;
                p = false;
                for (int k = 1; k <= n; ++k)
                    if (a[k] & (1 << j))
                        p = true;
                if (!p)
                    continue;
                p = false;
                for (int k = 1; k <= n; ++k)
                    if (((a[k] & (1 << i)) ? 1 : 0) != ((a[k] & (1 << j)) ? 1 : 0))
                    {
                        p = true;
                        break;
                    }
                if (i + j - p - 1 < 0)
                    ++res;
                else
                    ans += 1LL << (i + j - p - 1);
            }
        ans += res >> 1;
        printf("%lld", ans);
        if (res & 1)
            printf(".5");
        return 0;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 22; j >= 0; --j)
            if (a[i] & (1 << j))
            {
                if (!s[j])
                {
                    s[j] = a[i];
                    b.push_back(s[j]);
                    break;
                }
                a[i] ^= s[j];
            }
    int siz = b.size();
    for (int i = 1; i < (1 << siz); ++i)
    {
        val = 0;
        for (int j = 0; j < siz; ++j)
            if (i & (1 << j))
                val ^= b[j];
        int x = 0, y = 1;
        for (int j = 1; j <= K; ++j)
        {
            x *= val;
            y *= val;
            x += (y >> siz);
            y &= (1 << siz) - 1;
        }
        ans += x;
        res += y;
        ans += res >> siz;
        res &= (1 << siz) - 1;
    }
    printf("%lld", ans);
    if (res)
        printf(".5");
    return 0;
}