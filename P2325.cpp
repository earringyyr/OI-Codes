#include <iostream>
#include <cstdio>
using namespace std;
int n, b, sum, top, col, head[1005], s[1005], co[1005], ans[1005];
struct node
{
    int v;
    int next;
} a[2005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void dfs(int k, int fa)
{
    int pre = top;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs(a[d].v, k);
            if (top - pre >= b)
            {
                ans[++col] = k;
                while (top > pre)
                {
                    co[s[top]] = col;
                    --top;
                }
            }
        }
        d = a[d].next;
    }
    s[++top] = k;
    return;
}
int main()
{
    scanf("%d%d", &n, &b);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    dfs(1, 0);
    if (!col)
        ans[++col] = 1;
    while (top)
    {
        co[s[top]] = col;
        --top;
    }
    printf("%d\n", col);
    for (int i = 1; i <= n; ++i)
        printf("%d ", co[i]);
    putchar('\n');
    for (int i = 1; i <= col; ++i)
        printf("%d ", ans[i]);
    return 0;
}