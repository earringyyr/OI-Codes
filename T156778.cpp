#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, k, ans;
int c[500005];
struct node
{
    int id;
    int num;
} a[500005];
bool cmp(node aa, node bb)
{
    if (aa.num != bb.num)
        return aa.num < bb.num;
    return aa.id > bb.id;
}
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int val)
{
    while (x <= n)
    {
        c[x] = max(c[x], val);
        x += lowbit(x);
    }
    return;
}
int ask(int x)
{
    int num = 0;
    while (x >= 1)
    {
        num = max(num, c[x]);
        x -= lowbit(x);
    }
    return num;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
    {
        a[i].id = i;
        scanf("%d", &a[i].num);
    }
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
        if (a[i].id >= a[i].num && a[i].id - a[i].num <= k && k - (a[i].id - a[i].num) <= n - a[i].id)
        {
            int tmp = ask(a[i].id - a[i].num + 1) + 1;
            add(a[i].id - a[i].num + 1, tmp);
            ans = max(ans, tmp);
        }
    printf("%d", ans);
    return 0;
}