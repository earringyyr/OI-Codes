#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, Q, pos, c[100005], ans[100005];
struct node
{
    int id;
    int l;
    int r;
    bool operator<(const node &bb) const
    {
        return r < bb.r;
    }
} a[100005], b[100005];
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
    scanf("%d%d", &n, &Q);
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d", &a[i].l, &a[i].r);
        if (a[i].l > a[i].r)
            swap(a[i].l, a[i].r);
    }
    sort(a + 1, a + n);
    for (int i = 1; i <= Q; ++i)
    {
        b[i].id = i;
        scanf("%d%d", &b[i].l, &b[i].r);
    }
    sort(b + 1, b + Q + 1);
    for (int i = 1; i <= Q; ++i)
    {
        while (pos < n - 1 && a[pos + 1].r <= b[i].r)
        {
            ++pos;
            add(a[pos].l, 1);
        }
        ans[b[i].id] = b[i].r - b[i].l + 1 - (ask(n) - ask(b[i].l - 1));
    }
    for (int i = 1; i <= Q; ++i)
        printf("%d\n", ans[i]);
    return 0;
}