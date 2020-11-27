#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n, a, b;
int t[1000005], f[1000005], g[1000005];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &t[i]);
        if (t[i] == 1)
            ++a;
        else
            ++b;
    }
    f[0] = 1;
    f[1] = 1;
    for (int i = 2; i <= a; ++i)
        f[i] = (f[i - 1] + (ll)(i - 1) * f[i - 2] % mod) % mod;
    g[0] = f[a];
    for (int i = 1; i <= b; ++i)
        g[i] = (ll)g[i - 1] * (a + i) % mod;
    printf("%d\n", g[b]);
    return 0;
}