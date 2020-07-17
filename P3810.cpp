#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, k, ans[100005], c[200005];
struct node
{
    int a;
    int b;
    int c;
    long long ans;
} a[100005];
bool cmp1(node aa, node bb)
{
    if (aa.a == bb.a)
    {
        if (aa.b == bb.b)
            return aa.c < bb.c;
        return aa.b < bb.b;
    }
    return aa.a < bb.a;
}
bool cmp2(node aa, node bb)
{
    if (aa.b == bb.b)
        return aa.c < bb.c;
    return aa.b < bb.b;
}
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int val)
{
    while (x <= k)
    {
        c[x] += val;
        x += lowbit(x);
    }
    return;
}
int query(int x)
{
    int ans = 0;
    while (x >= 1)
    {
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}
void cdq(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    cdq(l, mid);
    cdq(mid + 1, r);
    int i = l, j = mid + 1;
    while (j <= r)
    {
        while (i <= mid && a[i].b <= a[j].b)
        {
            add(a[i].c, 1);
            ++i;
        }
        a[j].ans += query(a[j].c);
        ++j;
    }
    i = l;
    j = mid + 1;
    while (j <= r)
    {
        while (i <= mid && a[i].b <= a[j].b)
        {
            add(a[i].c, -1);
            ++i;
        }
        ++j;
    }
    sort(a + l, a + r + 1, cmp2);
    return;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].c);
    sort(a + 1, a + n + 1, cmp1);
    for (int i = n - 1; i >= 1; --i)
        if (a[i].a == a[i + 1].a && a[i].b == a[i + 1].b && a[i].c == a[i + 1].c)
            a[i].ans += a[i + 1].ans + 1;
    cdq(1, n);
    for (int i = 1; i <= n; ++i)
        ++ans[a[i].ans];
    for (int i = 0; i < n; ++i)
        printf("%d\n", ans[i]);
    return 0;
}