#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
int n, cnt, sum, top;
int fa[510005], head[510005], siz[510005];
int st[510005], num[510005], tr[510005][26];
ll ans;
char s[510005];
struct node
{
    int v;
    int nxt;
} a[510005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs1(int k, int f)
{
    if (num[k])
    {
        fa[num[k]] = f;
        siz[num[k]] = 1;
    }
    for (int i = 0; i < 26; ++i)
        if (tr[k][i])
        {
            if (num[k])
                dfs1(tr[k][i], num[k]);
            else
                dfs1(tr[k][i], f);
        }
    if (num[k])
        siz[fa[num[k]]] += siz[num[k]];
    return;
}
void dfs2(int k)
{
    top = 0;
    int d = head[k];
    while (d)
    {
        st[++top] = siz[a[d].v];
        d = a[d].nxt;
    }
    sort(st + 1, st + top + 1);
    int tot = 1;
    for (int i = 1; i <= top; ++i)
    {
        ans += tot;
        tot += st[i];
    }
    d = head[k];
    while (d)
    {
        dfs2(a[d].v);
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
        int len = strlen(s + 1), rt = 0;
        for (int j = len; j >= 1; --j)
        {
            int k = s[j] - 'a';
            if (!tr[rt][k])
                tr[rt][k] = ++cnt;
            rt = tr[rt][k];
        }
        num[rt] = i;
    }
    dfs1(0, 0);
    for (int i = 1; i <= n; ++i)
        ins(fa[i], i);
    dfs2(0);
    printf("%lld", ans);
    return 0;
}