#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n, x, pos, ans = 1, num1, num2, num;
void solve(int l, int r)
{
    if (l >= r)
        return;
    int mid = (l + r) >> 1;
    if (mid == pos)
    {
        solve(mid + 1, r);
        return;
    }
    if (mid < pos)
    {
        ans = (ll)ans * num1 % mod;
        --num1;
        --num;
        solve(mid + 1, r);
    }
    else
    {
        ans = (ll)ans * num2 % mod;
        --num2;
        --num;
        solve(l, mid);
    }
    return;
}
int main()
{
    scanf("%d%d%d", &n, &x, &pos);
    num1 = x - 1;
    num2 = n - x;
    num = n - 1;
    solve(0, n);
    for (int i = num; i >= 1; --i)
        ans = (ll)ans * i % mod;
    printf("%d", ans);
    return 0;
}