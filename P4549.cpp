#include <iostream>
#include <cstdio>
using namespace std;
int n, ans, a[25];
int gcd(int x, int y)
{
    if (y == 0)
        return x;
    return gcd(y, x % y);
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        if (a[i] < 0)
            a[i] = -a[i];
        ans = gcd(ans, a[i]);
    }
    cout << ans;
    return 0;
}