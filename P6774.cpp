#include <iostream>
#include <cstdio>
using namespace std;
int n, m, p[100005], c[100005];
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
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &p[i]);
    for (int i = 1; i <= m; ++i)
    {
        int x1, x2, y1, y2, ans = 0;
        scanf("%d%d%d%d", &x1, &x2, &y1, &y2);
        for (int j = x1; j <= x2; ++j)
            if (p[j] >= y1 && p[j] <= y2)
            {
                ans += ask(p[j]);
                add(p[j], 1);
            }
        for (int j = x1; j <= x2; ++j)
            if (p[j] >= y1 && p[j] <= y2)
                add(p[j], -1);
        printf("%d\n", ans);
    }
    return 0;
}