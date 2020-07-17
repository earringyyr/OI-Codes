#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, sum, s[205][205], vis[205], mch[205], head[205];
struct node
{
    int v;
    int nxt;
} a[40005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
bool dfs(int k, int t)
{
    int d = head[k];
    while (d)
    {
        if (vis[a[d].v] != t)
        {
            vis[a[d].v] = t;
            if (!mch[a[d].v] || dfs(mch[a[d].v], t))
            {
                mch[a[d].v] = k;
                return true;
            }
        }
        d = a[d].nxt;
    }
    return false;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        sum = 0;
        memset(head, 0, sizeof(head));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
            {
                scanf("%d", &s[i][j]);
                if (s[i][j] == 1)
                    ins(i, j);
            }
        int num = 0;
        memset(vis, 0, sizeof(vis));
        memset(mch, 0, sizeof(mch));
        for (int i = 1; i <= n; ++i)
            if (dfs(i, i))
                ++num;
        if (num == n)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}