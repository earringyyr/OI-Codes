#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, cnt;
int bo[500005], len[500005];
int tr[500005][26];
char s[25], ans[1500005];
void dfs(int k)
{
    if (bo[k])
        ans[++m] = 'P';
    int son = -1, ch;
    for (int i = 0; i < 26; ++i)
        if (tr[k][i])
            if (son == -1 || len[tr[k][i]] > len[son])
            {
                son = tr[k][i];
                ch = 'a' + i;
            }
    for (int i = 0; i < 26; ++i)
        if (tr[k][i] && tr[k][i] != son)
        {
            ans[++m] = 'a' + i;
            dfs(tr[k][i]);
            ans[++m] = '-';
        }
    if (son != -1)
    {
        ans[++m] = ch;
        dfs(son);
        ans[++m] = '-';
    }
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", s + 1);
        int rt = 0, l = strlen(s + 1);
        for (int j = 1; j <= l; ++j)
        {
            int k = s[j] - 'a';
            if (!tr[rt][k])
                tr[rt][k] = ++cnt;
            rt = tr[rt][k];
            len[rt] = max(len[rt], l - j + 1);
        }
        bo[rt] = 1;
    }
    dfs(0);
    while (ans[m] == '-')
        --m;
    printf("%d\n", m);
    for (int i = 1; i <= m; ++i)
    {
        putchar(ans[i]);
        putchar('\n');
    }
    return 0;
}