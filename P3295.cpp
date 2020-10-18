#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n, m, num, ans, lg[100005], fa[100005][25];
int getfather(int x, int y)
{
    if (fa[x][y] == x)
        return x;
    fa[x][y] = getfather(fa[x][y], y);
    return fa[x][y];
}
int ksm(int aa, int k)
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
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= lg[n - i + 1]; ++j)
            fa[i][j] = i;
    for (int i = 1; i <= m; ++i)
    {
        int l1, r1, l2, r2, len;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        len = r1 - l1 + 1;
        for (int j = lg[len]; j >= 0; --j)
            if (len >= (1 << j))
            {
                int u = getfather(l1, j), v = getfather(l2, j);
                if (u != v)
                    fa[u][j] = v;
                l1 += (1 << j);
                l2 += (1 << j);
                len -= (1 << j);
            }
    }
    for (int i = lg[n]; i >= 1; --i)
        for (int j = 1; j <= n - (1 << i) + 1; ++j)
        {
            int w = getfather(j, i);
            int u = getfather(j, i - 1);
            int x = getfather(w, i - 1);
            if (u != x)
                fa[u][i - 1] = x;
            int v = getfather(j + (1 << (i - 1)), i - 1);
            int y = getfather(w + (1 << (i - 1)), i - 1);
            if (v != y)
                fa[v][i - 1] = y;
        }
    for (int i = 1; i <= n; ++i)
        if (getfather(i, 0) == i)
            ++num;
    ans = (ll)9 * ksm(10, num - 1) % mod;
    printf("%d", ans);
    return 0;
}