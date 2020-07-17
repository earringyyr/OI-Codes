#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, rt, cnt, hhead, ttail, sum;
int bo[200005], l[200005], nxt[200005];
int num[200005], head[200005];
int tr[200005][26];
char s[2000005], t[2000005];
struct node
{
    int v;
    int nxt;
} a[400005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k, int fa)
{
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs(a[d].v, k);
            num[k] += num[a[d].v];
        }
        d = a[d].nxt;
    }
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", s + 1);
        int len = strlen(s + 1);
        rt = 0;
        for (int j = 1; j <= len; ++j)
        {
            int k = s[j] - 'a';
            if (!tr[rt][k])
                tr[rt][k] = ++cnt;
            rt = tr[rt][k];
        }
        bo[i] = rt;
    }
    for (int i = 0; i < 26; ++i)
        if (tr[0][i])
            l[++ttail] = tr[0][i];
    while (hhead < ttail)
    {
        ++hhead;
        rt = l[hhead];
        for (int i = 0; i < 26; ++i)
            if (!tr[rt][i])
                tr[rt][i] = tr[nxt[rt]][i];
            else
            {
                nxt[tr[rt][i]] = tr[nxt[rt]][i];
                l[++ttail] = tr[rt][i];
            }
    }
    scanf("%s", t + 1);
    int len = strlen(t + 1);
    rt = 0;
    for (int i = 1; i <= len; ++i)
    {
        int k = t[i] - 'a';
        rt = tr[rt][k];
        ++num[rt];
    }
    for (int i = 1; i <= cnt; ++i)
        ins(nxt[i], i);
    dfs(0, 0);
    for (int i = 1; i <= n; ++i)
        printf("%d\n", num[bo[i]]);
    return 0;
}