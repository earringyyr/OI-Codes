#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, sum, ans, mo[105];
struct node
{
    int u;
    int v;
    int w;
} a[10005];
bool cmp(node aa, node bb)
{
    return aa.w < bb.w;
}
int getmother(int x)
{
    if (mo[x] == x)
        return x;
    mo[x] = getmother(mo[x]);
    return mo[x];
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int k;
        for (int j = 1; j <= n; ++j)
        {
            scanf("%d", &k);
            if (j < i)
            {
                ++sum;
                a[sum].u = i;
                a[sum].v = j;
                a[sum].w = k;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        mo[i] = i;
    sort(a + 1, a + sum + 1, cmp);
    for (int i = 1; i <= sum; ++i)
        if (getmother(a[i].u) != getmother(a[i].v))
        {
            mo[getmother(a[i].u)] = getmother(a[i].v);
            ans += a[i].w;
        }
    printf("%d", ans);
    return 0;
}