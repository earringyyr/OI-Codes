#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, p, m, num, fr, top;
int vis[20], st[20], cnt[20];
int r[60005], aa[60005], bb[60005];
int tmp[20][60005], ans[20][60005];
int f[20][20][60005];
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
void init(int len)
{
    num = 1;
    while (num < len)
        num <<= 1;
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (num >> 1) : 0);
    return;
}
void ntt(int *c, int type)
{
    for (int i = 0; i < num; ++i)
        if (i < r[i])
            swap(c[i], c[r[i]]);
    for (int mid = 1; mid < num; mid <<= 1)
    {
        int ww = ksm(3, (mod - 1) / (mid << 1));
        if (type == -1)
            ww = ksm(ww, mod - 2);
        for (int j = 0; j < num; j += (mid << 1))
        {
            int w = 1;
            for (int k = 0; k < mid; ++k)
            {
                int x = c[j + k], y = (ll)w * c[j + mid + k] % mod;
                c[j + k] = (x + y) % mod;
                c[j + mid + k] = (x - y + mod) % mod;
                w = (ll)w * ww % mod;
            }
        }
    }
    if (type == -1)
    {
        int inv = ksm(num, mod - 2);
        for (int i = 0; i < num; ++i)
            c[i] = (ll)c[i] * inv % mod;
    }
    return;
}
void KSM(int k)
{
    memset(aa, 0, sizeof(aa));
    memset(bb, 0, sizeof(bb));
    for (int i = 0; i <= min(m, 9); ++i)
        aa[i] = 1;
    bb[0] = 1;
    while (k)
    {
        if (k & 1)
        {
            ntt(aa, 1);
            ntt(bb, 1);
            for (int i = 0; i < num; ++i)
                bb[i] = (ll)bb[i] * aa[i] % mod;
            ntt(aa, -1);
            ntt(bb, -1);
            for (int i = m + 1; i < num; ++i)
                bb[i] = 0;
        }
        ntt(aa, 1);
        for (int i = 0; i < num; ++i)
            aa[i] = (ll)aa[i] * aa[i] % mod;
        ntt(aa, -1);
        for (int i = m + 1; i < num; ++i)
            aa[i] = 0;
        k >>= 1;
    }
    return;
}
int main()
{
    scanf("%d%d%d", &n, &p, &m);
    int now = 1;
    while (1)
    {
        if (!vis[now])
        {
            st[++top] = now;
            vis[now] = top;
        }
        else
        {
            fr = vis[now];
            break;
        }
        now = (now * 10) % p;
    }
    if (n <= top)
        for (int i = 1; i <= n; ++i)
            ++cnt[st[i]];
    else
    {
        for (int i = 1; i < fr; ++i)
            ++cnt[st[i]];
        for (int i = fr; i <= top; ++i)
            cnt[st[i]] = (n - i + 1 + top - fr) / (top - fr + 1) % mod;
    }
    init(2 * m + 1);
    for (int i = 1; i <= 8; ++i)
        aa[i] = 1;
    ntt(aa, 1);
    ntt(aa, -1);
    for (int i = 0; i < p; ++i)
    {
        KSM(cnt[i]);
        for (int j = 0; j <= m; ++j)
            f[i][i * j % p][j] = bb[j];
    }
    ans[0][0] = 1;
    for (int i = 0; i < p; ++i)
    {
        for (int j = 0; j < p; ++j)
        {
            ntt(f[i][j], 1);
            ntt(ans[j], 1);
        }
        memset(tmp, 0, sizeof(tmp));
        for (int j = 0; j < p; ++j)
            for (int k = 0; k < p; ++k)
                for (int l = 0; l < num; ++l)
                    tmp[(j + k) % p][l] = (tmp[(j + k) % p][l] + (ll)f[i][j][l] * ans[k][l]) % mod;
        memset(ans, 0, sizeof(ans));
        for (int j = 0; j < p; ++j)
        {
            ntt(tmp[j], -1);
            for (int k = 0; k <= m; ++k)
                ans[j][k] = tmp[j][k];
        }
    }
    for (int i = 1; i <= m; ++i)
        ans[0][i] = (ans[0][i - 1] + ans[0][i]) % mod;
    for (int i = 0; i <= m; ++i)
        printf("%d ", ans[0][i]);
    return 0;
}