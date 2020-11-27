#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, top;
int h[10000005], st[10000005];
int pw[100005], PW[100005];
int ipw[100005], iPW[100005];
int ksm(int k)
{
    return (ll)pw[k % 10000] * PW[k / 10000];
}
int iksm(int k)
{
    return (ll)ipw[k % 10000] * iPW[k / 100000];
}
int main()
{
    pw[0] = 1;
    PW[0] = 1;
    ipw[0] = 1;
    iPW[0] = 1;
    for (int i = 1; i <= 100000; ++i)
    {
        pw[i] = (ll)pw[i - 1] * 2 % mod;
        ipw[i] = (ll)ipw[i - 1] * 499122177 % mod;
    }
    for (int i = 1; i <= 100000; ++i)
    {
        PW[i] = (ll)PW[i - 1] * pw[100000] % mod;
        iPW[i] = (ll)iPW[i - 1]
    }
    for (int i = 1; i <= n; ++i)
        scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &h[i]);
    h[0] = 1;
    f[0] = ksm(h[1]);
    for (int i = 2; i <= n; ++i)
        if (h[i] >= h[i - 1])
        {
        }
        else
        {
        }

    t = 1;
    v[1] = p(h[1]);
    h[0] = 1;
    A(s, v[1]);
    A(s2, p(h[1] + h[0]));
    for (i = 2; i <= n; i++)
    {
        int P = h[i] >= h[i - 1] ? (i - 1) : i, nv = 0;
        m = (m + max(h[i] - h[i - 1], 0)) % (M - 1);
        while (t && h[pos[t]] >= h[P])
            A(nv, v[t]), A(s, M - v[t]), A(s2, M - 1ll * v[t] * p(h[pos[t]]) % M), t--;
        nv = (nv << 1) % M, A(nv, 1ll * s2 * ip(h[P]) % M), t++, v[t] = nv, pos[t] = P, A(s, nv), A(s2, 1ll * nv * p(h[P]) % M);
    }
    return printf("%d\n", (int)(1ll * s * p(m) % M)), 0;
    return 0;
}