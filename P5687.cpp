#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, m, k, num[3];
int a[300005], b[300005];
ll cnt, ans;
struct node
{
    int type;
    int num;
    node(int aa = 0, int bb = 0)
    {
        type = aa;
        num = bb;
    }
} c[600005];
bool cmp(node aa, node bb)
{
    return aa.num < bb.num;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        c[++k] = node(1, a[i]);
    }
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &b[i]);
        c[++k] = node(2, b[i]);
    }
    sort(c + 1, c + k + 1, cmp);
    for (int i = 1; i <= k; ++i)
    {
        if (c[i].type == 1)
        {
            if (!num[1] || !num[2])
            {
                ans += (ll)c[i].num * (m - 1);
                cnt += m - 1;
            }
            else
            {
                ans += (ll)c[i].num * (m - num[2]);
                cnt += m - num[2];
            }
        }
        else
        {
            if (!num[1] || !num[2])
            {
                ans += (ll)c[i].num * (n - 1);
                cnt += n - 1;
            }
            else
            {
                ans += (ll)c[i].num * (n - num[1]);
                cnt += n - num[1];
            }
        }
        ++num[c[i].type];
        if (cnt == (ll)n * m - 1)
            break;
    }
    printf("%lld", ans);
    return 0;
}