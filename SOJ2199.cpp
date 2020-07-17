#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, fa[500005], huan[500005];
long long ans;
struct node
{
    int a;
    int b;
    int c;
} num[500005];
int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (isdigit(c))
    {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
bool cmp(node aa, node bb)
{
    return aa.c < bb.c;
}
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
int main()
{
    n = read();
    m = read();
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    for (int i = 1; i <= m; ++i)
    {
        num[i].a = read();
        num[i].b = read();
        num[i].c = read();
    }
    sort(num + 1, num + m + 1, cmp);
    for (int i = 1; i <= m; ++i)
        if (getfather(num[i].a) != getfather(num[i].b) && (!huan[getfather(num[i].a)] || !huan[getfather(num[i].b)]))
        {
            if (huan[getfather(num[i].a)])
                huan[getfather(num[i].b)] = 1;
            fa[getfather(num[i].a)] = getfather(num[i].b);
            ans = ans + num[i].c;
        }
        else if (!huan[getfather(num[i].a)])
        {
            huan[getfather(num[i].a)] = 1;
            ans = ans + num[i].c;
        }
    for (int i = 1; i <= n; ++i)
        if (!huan[getfather(i)])
        {
            printf("No");
            return 0;
        }
    printf("%lld", ans);
    return 0;
}