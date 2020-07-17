#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int m, n, sum, head[55];
unsigned long long base = 2333, ans[55][55];
struct node
{
    int v;
    int nxt;
} a[105];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
unsigned long long dfs(int k, int fa)
{
    int d = head[k], s[55], num = 0, siz = 0;
    while (d)
    {
        if (a[d].v != fa)
        {
            ++siz;
            s[++num] = dfs(a[d].v, k);
        }
        d = a[d].nxt;
    }
    if (!num)
        return 1;
    sort(s + 1, s + num + 1);
    unsigned long long sum = 0, cnt = 1;
    for (int i = 1; i <= num; ++i)
    {
        sum += cnt * s[i];
        cnt *= base;
    }
    sum *= siz;
    return sum + 1;
}
int main()
{
    scanf("%d", &m);
    for (int t = 1; t <= m; ++t)
    {
        scanf("%d", &n);
        sum = 0;
        memset(head, 0, sizeof(head));
        for (int i = 1; i <= n; ++i)
        {
            int x;
            scanf("%d", &x);
            if (x)
            {
                ins(x, i);
                ins(i, x);
            }
        }
        for (int i = 1; i <= n; ++i)
            ans[t][i] = dfs(i, i);
        sort(ans[t] + 1, ans[t] + n + 1);
        bool p = true;
        for (int i = 1; i <= t && p; ++i)
            for (int j = 1; j <= n; ++j)
            {
                if (ans[i][j] != ans[t][j])
                    break;
                if (j == n)
                {
                    printf("%d\n", i);
                    p = false;
                }
            }
    }
    return 0;
}