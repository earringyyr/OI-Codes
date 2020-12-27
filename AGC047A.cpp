#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, cnt;
int c[55];
ll ans, a[200005];
struct node
{
    int tw;
    int fv;
} b[200005];
ll read(int id)
{
    ll x = 0, num = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    if (ch == '.')
    {
        ch = getchar();
        while (isdigit(ch))
        {
            x = (x << 3) + (x << 1) + (ch ^ 48);
            ++num;
            ch = getchar();
        }
    }
    b[id].tw += 9 - num;
    b[id].fv += 9 - num;
    return x;
}
bool cmp(node aa, node bb)
{
    return aa.tw < bb.tw;
}
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int val)
{
    while (x <= 50)
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
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        a[i] = read(i);
        while (a[i] % 2 == 0)
        {
            ++b[i].tw;
            a[i] /= 2;
        }
        while (a[i] % 5 == 0)
        {
            ++b[i].fv;
            a[i] /= 5;
        }
    }
    sort(b + 1, b + n + 1, cmp);
    int j = n + 1;
    for (int i = 1; i <= n; ++i)
    {
        while (j - 1 > i && b[i].tw + b[j - 1].tw >= 18)
        {
            add(b[j - 1].fv + 1, 1);
            ++cnt;
            --j;
        }
        if (j <= i)
        {
            add(b[j].fv + 1, -1);
            --cnt;
            ++j;
        }
        ans += cnt - ask(18 - b[i].fv);
    }
    printf("%lld", ans);
    return 0;
}