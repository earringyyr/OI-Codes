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
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d", &num[i].a, &num[i].b, &num[i].c);
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