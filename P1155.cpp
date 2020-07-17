#include <iostream>
#include <cstdio>
using namespace std;
int n, sum, cnt = 1, top[2], aa[1005], head[1005], vis[1005], f[1005], st[2][1005];
struct node
{
    int v;
    int nxt;
} a[4000005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
bool dfs(int k)
{
    int d = head[k];
    while (d)
    {
        if (vis[a[d].v] && vis[k] == vis[a[d].v])
            return false;
        if (!vis[a[d].v])
        {
            vis[a[d].v] = (vis[k] == 1 ? 2 : 1);
            if (!dfs(a[d].v))
                return false;
        }
        d = a[d].nxt;
    }
    return true;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &aa[i]);
    f[n] = aa[n];
    for (int i = n - 1; i >= 1; --i)
        f[i] = min(f[i + 1], aa[i]);
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (f[j + 1] < aa[i] && aa[i] < aa[j])
            {
                ins(i, j);
                ins(j, i);
            }
    for (int i = 1; i <= n; ++i)
        if (!vis[i])
        {
            vis[i] = 1;
            if (!dfs(i))
            {
                printf("0");
                return 0;
            }
        }
    for (int i = 1; i <= n; ++i)
        if (vis[i] == 1)
        {
            while (top[0] > 0 && st[0][top[0]] < aa[i])
            {
                if (top[1] > 0 && st[1][top[1]] == cnt)
                {
                    --top[1];
                    ++cnt;
                    printf("d ");
                }
                if (top[0] > 0 && st[0][top[0]] == cnt)
                {
                    --top[0];
                    ++cnt;
                    printf("b ");
                }
            }
            st[0][++top[0]] = aa[i];
            printf("a ");
        }
        else
        {
            while (top[1] > 0 && st[1][top[1]] < aa[i])
            {
                if (top[0] > 0 && st[0][top[0]] == cnt)
                {
                    --top[0];
                    ++cnt;
                    printf("b ");
                }
                if (top[1] > 0 && st[1][top[1]] == cnt)
                {
                    --top[1];
                    ++cnt;
                    printf("d ");
                }
            }
            while (top[0] > 0 && st[0][top[0]] == cnt)
            {
                --top[0];
                ++cnt;
                printf("b ");
            }
            st[1][++top[1]] = aa[i];
            printf("c ");
        }
    while (cnt <= n)
    {
        while (top[0] > 0 && st[0][top[0]] == cnt)
        {
            --top[0];
            ++cnt;
            printf("b ");
        }
        while (top[1] > 0 && st[1][top[1]] == cnt)
        {
            --top[1];
            ++cnt;
            printf("d ");
        }
    }
    return 0;
}