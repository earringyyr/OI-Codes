#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, k;
long long ans;
struct node
{
    int a;
    int b;
    int c;
} a[200005];
bool cmp(node aa, node bb)
{
    return aa.a > bb.a;
}
bool comp(node aa, node bb)
{
    return aa.c < bb.c;
}
int main()
{
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i].a;
        a[i].c = i;
    }
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
    {
        a[i].b = i;
        if (i <= m * k)
            ans += a[i].a;
    }
    cout << ans << endl;
    sort(a + 1, a + n + 1, comp);
    int num = 0, sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (a[i].b <= m * k)
            num++;
        if (num == m)
        {
            sum++;
            num = 0;
            cout << i << " ";
        }
        if (sum == k - 1)
            return 0;
    }
    return 0;
}