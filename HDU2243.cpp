#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, L, cnt, head, tail, l[35], bo[35], nxt[35], tr[35][26];
unsigned long long ans;
char s[5];
struct matrix
{
    int siz;
    unsigned long long a[35][35];
    matrix(int Siz)
    {
        siz = Siz;
        memset(a, 0, sizeof(a));
    }
    matrix operator*(const matrix &bb) const
    {
        matrix cc(siz);
        for (int i = 0; i <= siz; ++i)
            for (int j = 0; j <= siz; ++j)
                for (int k = 0; k <= siz; ++k)
                    cc.a[i][j] += a[i][k] * bb.a[k][j];
        return cc;
    }
};
int main()
{
    while (scanf("%d%d", &n, &L) == 2)
    {
        cnt = 0;
        ans = 0;
        head = 0;
        tail = 0;
        memset(tr[0], 0, sizeof(tr[0]));
        memset(nxt, 0, sizeof(nxt));
        memset(bo, 0, sizeof(bo));
        for (int i = 1; i <= n; ++i)
        {
            scanf("%s", s);
            int len = strlen(s), rt = 0;
            for (int j = 0; j < len; ++j)
            {
                int k = s[j] - 'a';
                if (!tr[rt][k])
                {
                    ++cnt;
                    memset(tr[cnt], 0, sizeof(tr[cnt]));
                    tr[rt][k] = cnt;
                }
                rt = tr[rt][k];
            }
            bo[rt] = 1;
        }
        for (int i = 0; i < 26; ++i)
            if (tr[0][i])
                l[++tail] = tr[0][i];
        while (head < tail)
        {
            int k = l[++head];
            for (int i = 0; i < 26; ++i)
                if (tr[k][i])
                {
                    nxt[tr[k][i]] = tr[nxt[k]][i];
                    bo[tr[k][i]] |= bo[tr[nxt[k]][i]];
                    l[++tail] = tr[k][i];
                }
                else
                    tr[k][i] = tr[nxt[k]][i];
        }
        matrix a(cnt + 1), b(cnt + 1);
        for (int i = 0; i <= cnt; ++i)
            for (int j = 0; j < 26; ++j)
                if (!bo[tr[i][j]])
                    ++a.a[i][tr[i][j]];
        for (int i = 0; i <= cnt + 1; ++i)
            a.a[i][cnt + 1] = 1;
        for (int i = 0; i <= cnt + 1; ++i)
            b.a[i][i] = 1;
        int tmp = L;
        while (L)
        {
            if (L & 1)
                b = b * a;
            a = a * a;
            L >>= 1;
        }
        for (int i = 0; i <= cnt + 1; ++i)
            ans -= b.a[0][i];
        L = tmp;
        a = matrix(1);
        b = matrix(1);
        a.a[0][0] = 26;
        a.a[0][1] = 1;
        a.a[1][1] = 1;
        b.a[0][0] = 1;
        b.a[1][1] = 1;
        while (L)
        {
            if (L & 1)
                b = b * a;
            a = a * a;
            L >>= 1;
        }
        ans += b.a[0][0] + b.a[0][1];
        printf("%llu\n", ans);
    }
    return 0;
}