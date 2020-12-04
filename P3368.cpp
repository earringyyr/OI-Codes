#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m;
int a[500005], c[500005];
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
    int num = 0;
    while (x >= 1)
    {
        num += c[x];
        x -= lowbit(x);
    }
    return num;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; ++i)
    {
        int type;
        scanf("%d", &type);
        if (type == 1)
        {
            int x, y, k;
            scanf("%d%d%d", &x, &y, &k);
            add(x, k);
            add(y + 1, -k);
        }
        else
        {
            int x;
            scanf("%d", &x);
            printf("%d\n", ask(x) + a[x]);
        }
    }
    return 0;
}