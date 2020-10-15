#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1234567891;
int n, cc, kk, ans, vis[10], use[10];
int num[15] = {4, 3, 3, 3, 3, 2, 2, 3, 3, 2, 2, 2, 2, 2, 1};
int cnt[15] = {0, 1, 1, 1, 1, 2, 2, 0, 0, 0, 2, 2, 2, 2, 4};
int co[15][2][2] = {{{1, 2}, {3, 4}}, {{1, 1}, {2, 3}}, {{1, 2}, {1, 3}}, {{1, 2}, {3, 3}}, {{1, 2}, {3, 2}}, {{1, 1}, {2, 2}}, {{1, 2}, {1, 2}}, {{1, 2}, {3, 1}}, {{1, 2}, {2, 3}}, {{1, 2}, {2, 1}}, {{1, 1}, {1, 2}}, {{1, 1}, {2, 1}}, {{1, 2}, {1, 1}}, {{1, 2}, {2, 2}}, {{1, 1}, {1, 1}}};
int mar[155];
struct matrix
{
    int a[855][855];
    matrix()
    {
        memset(a, 0, sizeof(a));
    }
    matrix operator*(const matrix &bb) const
    {
        matrix cc;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                for (int k = 1; k <= n; ++k)
                    cc.a[i][j] = (cc.a[i][j] + (ll)a[i][k] * bb.a[k][j] % mod) % mod;
        return cc;
    }
} aa;
matrix ksm(ll k)
{
    matrix bb;
    for (int i = 1; i <= n; ++i)
        bb.a[i][i] = 1;
    while (k)
    {
        if (k & 1)
            bb = bb * aa;
        aa = aa * aa;
        k >>= 1;
    }
    return bb;
}
void dfs(int i, int j, int k)
{
    if (k == num[i] + 1)
    {
        int tot = cnt[i];
        for (int x = 0; x < 2; ++x)
            for (int y = 0; y < 2; ++y)
                if (use[co[i][x][y]] == co[j][x][y])
                    ++tot;
        int tmp = cc;
        for (int x = 1; x <= num[j]; ++x)
            --tmp;
        if (tmp >= 0)
        {
            int sum = 1;
            for (int x = 1; x <= num[i]; ++x)
                if (use[x] == 0)
                {
                    sum = (ll)sum * tmp % mod;
                    --tmp;
                }
            for (int x = 0; x <= kk - tot; ++x)
                aa.a[i * (kk + 1) + x + tot + 1][j * (kk + 1) + x + 1] = (aa.a[i * (kk + 1) + x + tot + 1][j * (kk + 1) + x + 1] + sum) % mod;
        }
        return;
    }
    use[k] = 0;
    dfs(i, j, k + 1);
    for (int l = 1; l <= num[j]; ++l)
        if (!vis[l])
        {
            vis[l] = 1;
            use[k] = l;
            dfs(i, j, k + 1);
            vis[l] = 0;
        }
    return;
}
class TheBrickTowerHardDivOne
{
public:
    int find(int C, int K, long long H)
    {
        cc = C;
        kk = K;
        n = 15 * (K + 1) + 1;
        for (int i = 0; i < 15; ++i)
            for (int j = 0; j < 15; ++j)
                dfs(i, j, 1);
        for (int i = 1; i <= n; ++i)
            aa.a[n][i] = 1;
        matrix bb = ksm(H - 1);
        for (int i = 0; i < 15; ++i)
            if (cnt[i] <= K)
            {
                mar[i * (K + 1) + cnt[i] + 1] = 1;
                for (int j = 1; j <= num[i]; ++j)
                    mar[i * (K + 1) + cnt[i] + 1] = (ll)mar[i * (K + 1) + cnt[i] + 1] * (C - j + 1) % mod;
            }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                ans = (ans + (ll)bb.a[i][j] * mar[j]) % mod;
        return ans;
    }
};
int main()
{
    TheBrickTowerHardDivOne TC12163;
    int C, K;
    long long H;
    scanf("%d%d%lld", &C, &K, &H);
    printf("%d", TC12163.find(C, K, H));
    return 0;
}