#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n, m;
struct node
{
    int a[150][150];
    node()
    {
        memset(a, 0, sizeof(a));
    }
    node operator*(const node &bb)
    {
        node cc;
        for (int i = 0; i < (1 << m); ++i)
            for (int j = 0; j < (1 << m); ++j)
                for (int k = 0; k < (1 << m); ++k)
                {
                    cc.a[i][j] += (ll)a[i][k] * bb.a[k][j] % mod;
                    cc.a[i][j] %= mod;
                }
        return cc;
    }
};
int main()
{
    while (scanf("%d%d", &n, &m) == 2)
    {
        node a, b;
        for (int i = 0; i < (1 << m); ++i)
            for (int j = 0; j < (1 << m); ++j)
            {
                int p = 1;
                for (int k = 0; k < m; ++k)
                {
                    if (k > 0 && (j & (1 << k)) && (i & (1 << (k - 1))) && !(j & (1 << (k - 1))) && !(i & (1 << k)))
                    {
                        p = 0;
                        break;
                    }
                    if (k < m - 1 && (j & (1 << k)) && (i & (1 << (k + 1))) && !(j & (1 << (k + 1))) && !(i & (1 << k)))
                    {
                        p = 0;
                        break;
                    }
                }
                if (p)
                    a.a[i][j] = 1;
            }
        for (int i = 0; i < (1 << m); ++i)
            b.a[i][i] = 1;
        while (n)
        {
            if (n & 1)
                b = b * a;
            a = a * a;
            n >>= 1;
        }
        int ans = 0;
        for (int i = 0; i < (1 << m); ++i)
            ans = (ans + b.a[0][i]) % mod;
        printf("%d\n", ans);
    }
    return 0;
}