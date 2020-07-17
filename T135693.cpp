#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, l, cnt, head, tail;
int a[1005], bo[1005], dep[1005], ll[1005], nxt[1005], tr[1005][26];
long long ans, f[1005][1005];
char s[1005];
int main()
{
    scanf("%d%d", &n, &l);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", s);
        int len = strlen(s), rt = 0;
        for (int j = 0; j < len; ++j)
        {
            int k = s[j] - 'a';
            if (!tr[rt][k])
                tr[rt][k] = ++cnt;
            rt = tr[rt][k];
            dep[rt] = j + 1;
        }
        bo[rt] += a[i];
    }
    for (int i = 0; i < 26; ++i)
        if (tr[0][i])
            ll[++tail] = tr[0][i];
    while (head < tail)
    {
        ++head;
        int k = ll[head];
        for (int i = 0; i < 26; ++i)
            if (!tr[k][i])
                tr[k][i] = tr[nxt[k]][i];
            else
            {
                nxt[tr[k][i]] = tr[nxt[k]][i];
                bo[tr[k][i]] += bo[tr[nxt[k]][i]];
                ll[++tail] = tr[k][i];
            }
    }
    for (int i = 1; i <= l; ++i)
        for (int j = 0; j <= cnt; ++j)
            if (dep[j] < i)
                for (int k = 0; k < 26; ++k)
                    f[i][tr[j][k]] = max(f[i][tr[j][k]], f[i - 1][j] + bo[tr[j][k]]);
    for (int i = 0; i <= cnt; ++i)
        ans = max(ans, f[l][i]);
    printf("%lld", ans);
    return 0;
}
