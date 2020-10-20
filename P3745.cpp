#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, m, A, B, C;
int t[100005], b[100005], c[100005][2];
ll CC, ans = -1, sumt[100005], sumb[100005];
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int val, int type)
{
    while (x <= 100000)
    {
        c[x][type] += val;
        x += lowbit(x);
    }
    return;
}
int ask(int x, int type)
{
    int num = 0;
    while (x >= 1)
    {
        num += c[x][type];
        x -= lowbit(x);
    }
    return num;
}
ll check(int mid)
{
    ll num = 0;
    int numt = ask(mid, 0), numb = ask(mid, 1);
    num += ((ll)numt * mid - sumt[numt]) * C;
    ll num1 = (ll)numb * mid - sumb[numb], num2 = sumb[m] - sumb[numb] - (ll)(m - numb) * mid;
    num += min(num1, num2) * A;
    if (num1 < num2)
        num += (num2 - num1) * B;
    return num;
}
int main()
{
    scanf("%d%d%lld", &A, &B, &CC);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &t[i]);
        add(t[i], 1, 0);
    }
    sort(t + 1, t + n + 1);
    for (int i = 1; i <= n; ++i)
        sumt[i] = sumt[i - 1] + t[i];
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &b[i]);
        add(b[i], 1, 1);
    }
    sort(b + 1, b + m + 1);
    for (int i = 1; i <= m; ++i)
        sumb[i] = sumb[i - 1] + b[i];
    int lef = 1, rig = 100000;
    if (CC <= 100000)
        C = CC;
    else
        rig = t[1];
    if (A > B)
        A = B;
    for (int i = lef; i <= rig; ++i)
    {
        if (ans == -1)
            ans = check(i);
        else
            ans = min(ans, check(i));
    }
    printf("%lld", ans);
    return 0;
}