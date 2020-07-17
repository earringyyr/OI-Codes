#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int t, n, x, y, d;
int main()
{
    cin >> t;
    for (int tt = 1; tt <= t; ++tt)
    {
        int p = 0, ans = 1000000005;
        cin >> n >> x >> y >> d;
        if (abs(y - x) % d == 0)
        {
            p = 1;
            ans = min(ans, abs(y - x) / d);
        }
        if ((y - 1) % d == 0)
        {
            p = 1;
            ans = min(ans, (int)(ceil((double)(x - 1) / d) + (y - 1) / d));
        }
        if ((n - y) % d == 0)
        {
            p = 1;
            ans = min(ans, (int)(ceil((double)(n - x) / d) + (n - y) / d));
        }
        if (p == 1)
            cout << ans << endl;
        else
            cout << -1 << endl;
    }
    return 0;
}