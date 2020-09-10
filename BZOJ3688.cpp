#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int mod = 100007;
int n, k, c[100005][15][2];
struct node
{
    int x;
    int y;
} a[50005];
bool cmp(node aa, node bb)
{
    return aa.x < bb.x;
}
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int dim, int type, int val)
{
    while (x <= 100000)
    {
        c[x][dim][type] += val;
        c[x][dim][type] %= mod;
        x += lowbit(x);
    }
    return;
}
int query(int x, int dim, int type)
{
    int ans = 0;
    while (x >= 1)
    {
        ans += c[x][dim][type];
        ans %= mod;
        x -= lowbit(x);
    }
    return ans;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &a[i].x, &a[i].y);
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = k; j >= 1; --j)
        {
            int ans1 = (query(a[i].y, j - 1, 0) + query(a[i].y, j, 1)) % mod;
            int ans2 = (((query(100000, j - 1, 1) - query(a[i].y, j - 1, 1)) % mod + (query(100000, j, 0) - query(a[i].y, j, 0)) % mod) % mod + mod) % mod;
            add(a[i].y, j, 1, ans1);
            add(a[i].y, j, 0, ans2);
        }
        add(a[i].y, 0, 0, 1);
        add(a[i].y, 0, 1, 1);
    }
    printf("%d", (query(100000, k, 1) + query(100000, k, 0)) % mod);
    return 0;
}