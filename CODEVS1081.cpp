#include <iostream>
#include <cstdio>
using namespace std;
int n, q, a[100005], c[100005];
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int val)
{
    while (x <= n)
    {
        c[x] += val;
        x += lowbit(x);
    }
    return;
}
int ask(int x)
{
    int ans = 0;
    while (x >= 1)
    {
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        int type;
        scanf("%d", &type);
        if (type == 1)
        {
            int x, y, w;
            scanf("%d%d%d", &x, &y, &w);
            add(x, w);
            add(y + 1, -w);
        }
        else
        {
            int k;
            scanf("%d", &k);
            printf("%d\n", a[k] + ask(k));
        }
    }
    return 0;
}