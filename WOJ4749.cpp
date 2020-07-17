#include <iostream>
#include <cstdio>
using namespace std;
int n, m, x, y, sum = 1, cnt, col, top, ttop, ans;
int s[1000005], dfn[1000005], low[1000005];
int head[1000005], use[1000005], co[1000005];
int num[1000005], tot[1000005], ss[1000005];
struct node
{
    int v;
    int next;
} a[2000005];
int read()
{
    int x = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
    {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    return x;
}
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void tarjan(int k)
{
    ++cnt;
    dfn[k] = cnt;
    low[k] = cnt;
    ss[++ttop] = k;
    int d = head[k];
    while (d)
    {
        if (!use[d >> 1])
        {
            use[d >> 1] = 1;
            s[++top] = (d >> 1);
            if (!dfn[a[d].v])
            {
                tarjan(a[d].v);
                low[k] = min(low[k], low[a[d].v]);
                if (low[a[d].v] >= dfn[k])
                {
                    ++col;
                    while (s[top] != (d >> 1))
                    {
                        co[s[top]] = col;
                        --top;
                        ++num[col];
                    }
                    co[s[top]] = col;
                    --top;
                    ++num[col];
                    while (ss[ttop] != a[d].v)
                    {
                        --ttop;
                        ++tot[col];
                    }
                    --ttop;
                    tot[col] += 2;
                }
            }
            else
                low[k] = min(low[k], dfn[a[d].v]);
        }
        d = a[d].next;
    }
    return;
}
int main()
{
    n = read();
    m = read();
    for (int i = 1; i <= m; ++i)
    {
        x = read();
        y = read();
        ins(x, y);
        ins(y, x);
    }
    tarjan(1);
    for (int i = 1; i <= m; ++i)
        if (co[i] && tot[co[i]] == num[co[i]])
            ans ^= i;
    printf("%d", ans);
    return 0;
}