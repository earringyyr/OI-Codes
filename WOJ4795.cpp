#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
long long read()
{
    long long x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
namespace io
{
const int MaxBuff = 1 << 15;
const int Output = 1 << 23;
char B[MaxBuff], *S = B, *T = B;
#define getc() ((S == T) && (T = (S = B) + fread(B, 1, MaxBuff, stdin), S == T) ? 0 : *S++)
char Out[Output], *it = Out;
void flush()
{
    fwrite(Out, 1, it - Out, stdout);
    it = Out;
}
} // namespace io
template <class Type>
void Print(register Type x, register char ch = '\n')
{
    using namespace io;
    if (!x)
        *it++ = '0';
    else
    {
        if (x < 0)
            *it++ = '-', x = -x;
        static int s[100];
        register int t = 0;
        while (x)
            s[++t] = x % 10, x /= 10;
        while (t)
            *it++ = '0' + s[t--];
    }
    *it++ = ch;
}
const int N = 5e4 + 5;
const int M = 21;
const int L = 17;
const int mod = 1e9 + 7;
const long long inf = (long long)1e18 + 1;
int T, n, m, q;
bool p[N][10];
int fail[M], val[L][N][M], trans[M][10], pw[L] = {10};
long long f[N][M], rkl[L][N][M], rkr[L][N][M];
char str[M], s[N], ed[L][N][M];
long long fix(long long x)
{
    return x < inf ? x : inf;
}
void kmp()
{
    fail[0] = fail[1] = 0;
    for (int i = 2; i <= m; ++i)
    {
        int now = fail[i - 1];
        while (now && str[now + 1] != str[i])
            now = fail[now];
        if (str[now + 1] == str[i])
            fail[i] = now + 1;
        else
            fail[i] = 0;
    }
}
void init()
{
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j <= 9; ++j)
        {
            int now = i;
            while (now && str[now + 1] != j + '0')
                now = fail[now];
            if (str[now + 1] != j + '0')
                trans[i][j] = 0;
            else
                trans[i][j] = now + 1;
        }
    }
    for (int j = 0; j <= 9; ++j)
        trans[m][j] = m;
}
void input()
{
    n = read(), q = read();
    scanf("%s%s", str + 1, s + 1);
    m = strlen(str + 1);
    for (int i = 1; i <= n; ++i)
    {
        if (s[i] == '?')
            memset(p[i], 1, sizeof(p[i]));
        else
            memset(p[i], 0, sizeof(p[i])), p[i][s[i] - '0'] = 1;
    }
    kmp(), init();
}
int query(long long k)
{
    if (k > f[1][0])
        return -1;
    int x = 1, y = 0, res = 0;
    while (x <= n)
    {
        for (int i = L - 1; ~i; --i)
        {
            if (x + (1 << i) <= n + 1 && rkl[i][x][y] < k && k <= rkr[i][x][y])
            {
                res = ((long long)res * pw[i] + val[i][x][y]) % mod;
                k -= rkl[i][x][y], y = ed[i][x][y], x += (1 << i);
            }
        }
        if (x > n)
            break;
        for (int i = 0; i <= 9; ++i)
        {
            if (k > f[x + 1][trans[y][i]])
                k -= f[x + 1][trans[y][i]];
            else
            {
                res = (10LL * res + i) % mod;
                ++x, y = trans[y][i];
                break;
            }
        }
    }
    return res;
}
int main()
{
    for (int i = 1; i < L; ++i)
        pw[i] = (long long)pw[i - 1] * pw[i - 1] % mod;
    T = read();
    while (T--)
    {
        input();
        for (int i = 0; i <= m; ++i)
            f[n + 1][i] = (i == m);
        for (int i = n; i >= 0; --i)
        {
            for (int j = 0; j <= m; ++j)
            {
                f[i][j] = 0;
                long long mx = -1;
                int nxt = -1;
                for (int k = 0; k <= 9; ++k)
                {
                    if (p[i][k])
                    {
                        f[i][j] = fix(f[i][j] + f[i + 1][trans[j][k]]);
                        if (f[i + 1][trans[j][k]] > mx)
                            nxt = k, mx = f[i + 1][trans[j][k]];
                    }
                }
                ed[0][i][j] = trans[j][nxt];
                val[0][i][j] = nxt, rkl[0][i][j] = 0;
                for (int k = 0; k < nxt; ++k)
                    if (p[i][k])
                        rkl[0][i][j] = fix(rkl[0][i][j] + f[i + 1][trans[j][k]]);
                rkr[0][i][j] = fix(rkl[0][i][j] + f[i + 1][trans[j][nxt]]);
            }
        }
        for (int k = 1; k < L; ++k)
        {
            int len = (1 << (k - 1));
            for (int i = 1; i + (1 << k) <= n + 1; ++i)
            {
                for (int j = 0; j <= m; ++j)
                {
                    int x = ed[k - 1][i][j];
                    ed[k][i][j] = ed[k - 1][i + len][x];
                    val[k][i][j] = (1LL * val[k - 1][i][j] * pw[k - 1] + val[k - 1][i + len][x]) % mod;
                    rkl[k][i][j] = fix(rkl[k - 1][i][j] + rkl[k - 1][i + len][x]);
                    rkr[k][i][j] = fix(rkl[k - 1][i][j] + rkr[k - 1][i + len][x]);
                }
            }
        }
        while (q--)
        {
            long long k = read();
            Print(query(k));
        }
        io::flush();
    }
    return 0;
}