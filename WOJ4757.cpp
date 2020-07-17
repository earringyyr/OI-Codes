#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, num, s = 1, c[100005], f[100005];
struct node
{
    int id;
    int a;
} a[100005];
inline int read()
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
bool cmp(node aa, node bb)
{
    return aa.a < bb.a;
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
int query(int x)
{
    int ans = 0;
    while (x >= 1)
    {
        ans = max(ans, c[x]);
        x -= lowbit(x);
    }
    return ans;
}
int main()
{
    n = read();
    for (register int i = 1; i <= n; ++i)
    {
        a[i].id = i;
        a[i].a = read();
    }
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
    {
        if (a[i].id >= a[i].a)
            f[i] = query(a[i].id - a[i].a + 1) + 1;
        if (a[i].a != a[i + 1].a)
        {
            for (int j = s; j <= i; ++j)
                if (a[j].id >= a[j].a)
                    add(a[j].id - a[j].a + 1, f[j]);
            s = i + 1;
        }
        num = max(num, f[i]);
    }
    printf("%d", num);
    return 0;
}