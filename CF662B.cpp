#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x7fffffff;
int n, m, sum, tar, num, tot, top;
int head[100005], vis[100005], rev[100005], st[100005], ans[100005];
struct node
{
    int v;
    int w;
    int nxt;
} a[200005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
bool dfs(int k)
{
    st[++top] = k;
    vis[k] = 1;
    rev[k] = -1;
    int d = head[k];
    while (d)
    {
        if (vis[a[d].v])
        {
            if (rev[k] == -1)
            {
                if (a[d].w == tar)
                    rev[k] = rev[a[d].v];
                else
                    rev[k] = rev[a[d].v] ^ 1;
            }
            else
            {
                if (a[d].w == tar)
                {
                    if (rev[k] != rev[a[d].v])
                        return false;
                }
                else
                {
                    if (rev[k] == rev[a[d].v])
                        return false;
                }
            }
        }
        d = a[d].nxt;
    }
    if (rev[k] == -1)
        rev[k] = 0;
    if (rev[k] == 1)
        ++num;
    d = head[k];
    while (d)
    {
        if (!vis[a[d].v])
            if (!dfs(a[d].v))
                return false;
        d = a[d].nxt;
    }
    return true;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, c;
        char co;
        scanf("%d%d %c", &u, &v, &co);
        if (co == 'B')
            c = 0;
        else
            c = 1;
        ins(u, v, c);
        ins(v, u, c);
    }
    tar = 0;
    memset(vis, 0, sizeof(vis));
    memset(rev, 0, sizeof(rev));
    for (int i = 1; i <= n; ++i)
        if (!vis[i])
        {
            top = 0;
            num = 0;
            if (!dfs(i))
            {
                tot = inf;
                break;
            }
            if (num > top - num)
            {
                num = top - num;
                for (int j = 1; j <= top; ++j)
                    rev[st[j]] ^= 1;
            }
            tot += num;
        }
    ans[0] = tot;
    for (int i = 1; i <= n; ++i)
        ans[i] = rev[i];
    tot = 0;
    tar = 1;
    memset(vis, 0, sizeof(vis));
    memset(rev, 0, sizeof(rev));
    for (int i = 1; i <= n; ++i)
        if (!vis[i])
        {
            top = 0;
            num = 0;
            if (!dfs(i))
            {
                tot = inf;
                break;
            }
            if (num > top - num)
            {
                num = top - num;
                for (int j = 1; j <= top; ++j)
                    rev[st[j]] ^= 1;
            }
            tot += num;
        }
    if (tot < ans[0])
    {
        ans[0] = tot;
        for (int i = 1; i <= n; ++i)
            ans[i] = rev[i];
    }
    if (ans[0] == inf)
        printf("-1");
    else
    {
        printf("%d\n", ans[0]);
        for (int i = 1; i <= n; ++i)
            if (ans[i])
                printf("%d ", i);
    }
    return 0;
}