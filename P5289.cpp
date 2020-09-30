#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, c, c0, c1, d0, d1, k, sum, ans;
int b[1005], s[1005], num[1005];
int ban[1005], p[1005];
int f[2505], g[2505];
int F[2505][2505], G[2505][2505];
vector<int> ci[1005];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ans = 0;
        sum = 0;
        memset(p, -1, sizeof(p));
        memset(num, 0, sizeof(num));
        memset(ban, 0, sizeof(ban));
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        memset(F, 0, sizeof(F));
        memset(G, 0, sizeof(G));
        for (int i = 1; i <= c; ++i)
            ci[i].clear();
        scanf("%d%d", &n, &c);
        scanf("%d%d%d%d", &c0, &c1, &d0, &d1);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d%d", &b[i], &s[i]);
            ci[b[i]].push_back(i);
            num[b[i]] += s[i];
            sum += s[i];
        }
        scanf("%d", &k);
        for (int i = 1; i <= k; ++i)
        {
            int id;
            scanf("%d", &id);
            ban[b[id]] = 1;
            scanf("%d", &p[id]);
        }
        f[0] = 1;
        g[0] = 1;
        for (int i = 1; i <= c; ++i)
            if (!ban[i] && ci[i].size())
                for (int j = c0; j >= num[i]; --j)
                    f[j] = (f[j] + f[j - num[i]]) % mod;
        for (int i = 1; i <= n; ++i)
            if (p[i] == -1)
                for (int j = d0; j >= s[i]; --j)
                    g[j] = (g[j] + g[j - s[i]]) % mod;
        for (int i = 1; i <= c0; ++i)
            f[i] = (f[i] + f[i - 1]) % mod;
        for (int i = 1; i <= d0; ++i)
            g[i] = (g[i] + g[i - 1]) % mod;
        int C = 0, D = 0;
        F[0][0] = 1;
        for (int i = 1; i <= c; ++i)
            if (ban[i])
            {
                C = min(C + num[i], c0);
                for (int j = 0; j <= C; ++j)
                    for (int K = 0; K <= D; ++K)
                        G[j][K] = F[j][K];
                int siz = ci[i].size();
                for (int j = 0; j < siz; ++j)
                    if (p[ci[i][j]] != -1)
                    {
                        int k = ci[i][j];
                        D = min(D + s[k], d0);
                        if (p[k] <= 1)
                            for (int x = 0; x <= C; ++x)
                                for (int y = D; y >= s[k]; --y)
                                    G[x][y] = (G[x][y] + G[x][y - s[k]]) % mod;
                        if (p[k] == 1)
                            for (int x = 0; x <= C; ++x)
                            {
                                for (int y = D; y >= s[k]; --y)
                                    F[x][y] = F[x][y - s[k]];
                                for (int y = s[k] - 1; y >= 0; --y)
                                    F[x][y] = 0;
                            }
                        if (p[k] >= 2)
                            for (int x = 0; x <= C; ++x)
                                for (int y = D; y >= s[k]; --y)
                                    F[x][y] = (F[x][y] + F[x][y - s[k]]) % mod;
                        if (p[k] == 3)
                            for (int x = 0; x <= C; ++x)
                            {
                                for (int y = D; y >= s[k]; --y)
                                    G[x][y] = G[x][y - s[k]];
                                for (int y = s[k] - 1; y >= 0; --y)
                                    G[x][y] = 0;
                            }
                    }
                for (int j = C; j >= num[i]; --j)
                    for (int k = 0; k <= D; ++k)
                        F[j][k] = F[j - num[i]][k];
                for (int j = num[i] - 1; j >= 0; --j)
                    for (int k = 0; k <= D; ++k)
                        F[j][k] = 0;
                for (int j = 0; j <= C; ++j)
                    for (int k = 0; k <= D; ++k)
                        F[j][k] = (F[j][k] + G[j][k]) % mod;
            }
        for (int i = 0; i <= C; ++i)
            for (int j = 0; j <= D; ++j)
            {
                int lf = max(0, sum - c1 - i), rf = c0 - i;
                int lg = max(0, sum - d1 - j), rg = d0 - j;
                if (lf <= rf && lg <= rg)
                {
                    int numf = f[rf], numg = g[rg];
                    if (lf)
                        numf = (numf - f[lf - 1] + mod) % mod;
                    if (lg)
                        numg = (numg - g[lg - 1] + mod) % mod;
                    ans = (ans + (ll)numf * numg % mod * F[i][j] % mod) % mod;
                }
            }
        printf("%d\n", ans);
    }
    return 0;
}