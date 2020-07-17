#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int m, sum = 1, a[105], bo[205], tr[205][26], nxt[205];
char s[205];
long long n, ans;
void insert(int k)
{
    int root = 1, len = strlen(s);
    for (int i = 0; i < len; ++i)
    {
        int k = s[i] - 'a';
        if (!tr[root][k])
            tr[root][k] = ++sum;
        root = tr[root][k];
    }
    bo[root] += a[k];
    return;
}
struct matrix
{
    long long a[205][205];
    matrix()
    {
        memset(a, 0, sizeof(a));
    }
    matrix(long long x)
    {
        for (int i = 1; i <= sum; ++i)
            for (int j = 1; j <= sum; ++j)
                a[i][j] = x;
    }
    matrix operator*(const matrix &bb) const
    {
        matrix cc(-1);
        for (int i = 1; i <= sum; ++i)
            for (int j = 1; j <= sum; ++j)
                for (int k = 1; k <= sum; ++k)
                    if (a[i][k] != -1 && bb.a[k][j] != -1)
                        cc.a[i][j] = max(cc.a[i][j], a[i][k] + bb.a[k][j]);
        return cc;
    }
};
void build()
{
    for (int i = 0; i < 26; ++i)
        tr[0][i] = 1;
    int h = 0, t = 1, q[205];
    q[1] = 1;
    while (h < t)
    {
        ++h;
        int k = q[h];
        for (int i = 0; i < 26; ++i)
            if (tr[k][i])
            {
                nxt[tr[k][i]] = tr[nxt[k]][i];
                bo[tr[k][i]] += bo[tr[nxt[k]][i]];
                q[++t] = tr[k][i];
            }
            else
                tr[k][i] = tr[nxt[k]][i];
    }
    return;
}
matrix ksm(matrix aa, long long k)
{
    matrix x(-1);
    x.a[1][1] = 0;
    while (k)
    {
        if (k & 1)
            x = x * aa;
        aa = aa * aa;
        k >>= 1;
    }
    return x;
}
int main()
{
    scanf("%lld%d", &n, &m);
    for (int i = 1; i <= m; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%s", s);
        insert(i);
    }
    build();
    matrix aa(-1);
    for (int i = 1; i <= sum; ++i)
        for (int j = 0; j < 26; ++j)
            aa.a[i][tr[i][j]] = bo[tr[i][j]];
    aa = ksm(aa, n);
    for (int i = 1; i <= sum; ++i)
        ans = max(ans, aa.a[1][i]);
    printf("%lld", ans);
    return 0;
}