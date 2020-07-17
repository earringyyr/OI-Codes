#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
int n, sum, head, tail;
int l[30005], nxt[30005], bo[30005];
int vis[30005], tr[30005][2];
char s[30005];
void dfs(int k)
{
    if (bo[k])
        return;
    vis[k] = 2;
    for (int i = 0; i < 2; ++i)
        if (!vis[tr[k][i]])
            dfs(tr[k][i]);
        else if (vis[tr[k][i]] == 2)
        {
            puts("TAK");
            exit(0);
        }
    vis[k] = 1;
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", s + 1);
        int len = strlen(s + 1);
        int rt = 0;
        for (int j = 1; j <= len; ++j)
        {
            int k = s[j] - '0';
            if (!tr[rt][k])
                tr[rt][k] = ++sum;
            rt = tr[rt][k];
        }
        bo[rt] = 1;
    }
    for (int i = 0; i < 2; ++i)
        if (tr[0][i])
            l[++tail] = tr[0][i];
    while (head < tail)
    {
        ++head;
        int rt = l[head];
        for (int i = 0; i < 2; ++i)
            if (!tr[rt][i])
                tr[rt][i] = tr[nxt[rt]][i];
            else
            {
                nxt[tr[rt][i]] = tr[nxt[rt]][i];
                bo[tr[rt][i]] |= bo[tr[nxt[rt]][i]];
                l[++tail] = tr[rt][i];
            }
    }
    dfs(0);
    puts("NIE");
    return 0;
}