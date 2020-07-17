#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, p, k, sum;
int a[4][1000005], atk[4], zt[100];
unsigned int ans;
struct matrix
{
    int siz;
    unsigned int c[100][100];
    matrix()
    {
        memset(c, 0, sizeof(c));
    }
    matrix operator*(const matrix &x) const
    {
        matrix y;
        y.siz = siz;
        for (int i = 1; i <= siz; ++i)
            for (int j = 1; j <= siz; ++j)
                for (int k = 1; k <= siz; ++k)
                    y.c[i][j] += c[i][k] * x.c[k][j];
        return y;
    }
} f;
bool check(int now)
{
    for (int i = 0; i < m; ++i)
        if (now & (1 << i))
        {
            int vis, pos = m - i;
            if (k < pos)
                vis = atk[2] >> (pos - k);
            else
                vis = atk[2] << (k - pos);
            if (vis & now)
                return false;
        }
    return true;
}
bool check2(int now1, int now2)
{
    for (int i = 0; i < m; ++i)
        if (zt[now1] & (1 << i))
        {
            int vis, pos = m - i;
            if (k < pos)
                vis = atk[3] >> (pos - k);
            else
                vis = atk[3] << (k - pos);
            if (vis & zt[now2])
                return false;
        }
    for (int i = 0; i < m; ++i)
        if (zt[now2] & (1 << i))
        {
            int vis, pos = m - i;
            if (k < pos)
                vis = atk[1] >> (pos - k);
            else
                vis = atk[1] << (k - pos);
            if (vis & zt[now1])
                return false;
        }
    return true;
}
void dfs(int k, int now)
{
    if (k == m + 1)
    {
        if (check(now))
            zt[++sum] = now;
        return;
    }
    dfs(k + 1, now << 1);
    dfs(k + 1, now << 1 | 1);
    return;
}
matrix ksm(matrix b, int k)
{
    matrix c;
    c.siz = b.siz;
    for (int i = 1; i <= c.siz; ++i)
        c.c[i][i] = 1;
    while (k)
    {
        if (k & 1)
            c = c * b;
        b = b * b;
        k >>= 1;
    }
    return c;
}
int main()
{
    scanf("%d%d%d%d", &n, &m, &p, &k);
    ++k;
    for (int i = 1; i <= 3; ++i)
        for (int j = 1; j <= p; ++j)
            scanf("%d", &a[i][j]);
    a[2][k] = 0;
    for (int i = 1; i <= 3; ++i)
        for (int j = 1; j <= m; ++j)
            atk[i] = (atk[i] << 1) | a[i][j];
    dfs(1, 0);
    f.siz = sum;
    for (int i = 1; i <= sum; ++i)
        for (int j = 1; j <= sum; ++j)
            if (check2(i, j))
                f.c[i][j] = 1;
    f = ksm(f, n);
    for (int i = 1; i <= sum; ++i)
        ans += f.c[1][i];
    printf("%u", ans);
    return 0;
}