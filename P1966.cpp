#include <iostream>
#include <cstdio>
#include <algorithm>
#define mod 99999997
using namespace std;
int n, num, ans, c[100005], q[100005];
struct node
{
    int id;
    int num;
} a[100005], b[100005];
bool cmp(node aa, node bb)
{
    return aa.num < bb.num;
}
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
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        a[i].id = i;
        scanf("%d", &a[i].num);
    }
    for (int i = 1; i <= n; ++i)
    {
        b[i].id = i;
        scanf("%d", &b[i].num);
    }
    sort(a + 1, a + n + 1, cmp);
    sort(b + 1, b + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
        q[a[i].id] = b[i].id;
    for (int i = n; i >= 1; --i)
    {
        ans = (ans + query(q[i])) % mod;
        add(q[i] + 1, 1);
    }
    printf("%d", ans);
    return 0;
}