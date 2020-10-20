#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
int phi[10000005], ans[10000005];
int ksm(int aa, int k, int mod)
{
    int bb = 1;
    while (k)
    {
        if (k & 1)
            bb = (ll)aa * bb % mod;
        aa = (ll)aa * aa % mod;
        k >>= 1;
    }
    return bb;
}
int dfs(int p)
{
    if (p == 1)
        return 0;
    if (ans[p])
        return ans[p];
    phi[p] = p;
    int pp = p;
    for (int i = 2; i * i <= p; ++i)
        if (pp % i == 0)
        {
            while (pp % i == 0)
                pp /= i;
            phi[p] = phi[p] / i * (i - 1);
        }
    if (pp > 1)
        phi[p] = phi[p] / pp * (pp - 1);
    ans[p] = ksm(2, dfs(phi[p]) + phi[p], p);
    return ans[p];
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int p;
        scanf("%d", &p);
        printf("%d\n", dfs(p));
    }
    return 0;
}