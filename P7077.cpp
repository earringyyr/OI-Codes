#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, m, q, hh, tt, mult = 1;
int a[100005];
int type[100005], p[100005], v[100005];
int in[100005], f[100005], l[100005];
int mul[100005], w[100005], ans[100005];
vector<int> vec[100005];
int read()
{
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}
int main()
{
    n = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    m = read();
    for (int i = 1; i <= m; ++i)
    {
        mul[i] = 1;
        type[i] = read();
        if (type[i] == 1)
        {
            p[i] = read();
            v[i] = read();
        }
        else if (type[i] == 2)
        {
            v[i] = read();
            mul[i] = v[i];
        }
        else if (type[i] == 3)
        {
            int c;
            c = read();
            for (int j = 1; j <= c; ++j)
            {
                int tmp;
                tmp = read();
                ++in[tmp];
                vec[i].push_back(tmp);
            }
        }
    }
    for (int i = 1; i <= m; ++i)
        if (!in[i])
            l[++tt] = i;
    while (hh < tt)
    {
        int k = l[++hh];
        for (int i = 0; i < vec[k].size(); ++i)
        {
            --in[vec[k][i]];
            if (!in[vec[k][i]])
                l[++tt] = vec[k][i];
        }
    }
    for (int i = m; i >= 1; --i)
        for (int j = 0; j < vec[l[i]].size(); ++j)
            mul[l[i]] = (ll)mul[l[i]] * mul[vec[l[i]][j]] % mod;
    q = read();
    for (int i = 1; i <= q; ++i)
        f[i] = read();
    for (int i = q; i >= 1; --i)
        if (type[f[i]] == 1)
            ans[p[f[i]]] = (ans[p[f[i]]] + (ll)v[f[i]] * mult % mod) % mod;
        else if (type[f[i]] == 2)
            mult = (ll)mult * mul[f[i]] % mod;
        else
        {
            w[f[i]] = (w[f[i]] + mult) % mod;
            mult = (ll)mult * mul[f[i]] % mod;
        }
    for (int i = 1; i <= m; ++i)
    {
        if (type[l[i]] == 1)
            ans[p[l[i]]] = (ans[p[l[i]]] + (ll)v[l[i]] * w[l[i]] % mod) % mod;
        if (type[l[i]] == 3)
        {
            for (int j = vec[l[i]].size() - 1; j >= 0; --j)
            {
                w[vec[l[i]][j]] = (w[vec[l[i]][j]] + w[l[i]]) % mod;
                w[l[i]] = (ll)w[l[i]] * mul[vec[l[i]][j]] % mod;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        printf("%d ", (int)((ans[i] + (ll)a[i] * mult % mod) % mod));
    return 0;
}