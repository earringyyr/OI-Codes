#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int x, n, ans = 0;
    cin >> x >> n;
    for (int i = 1; i <= n; ++i)
    {
        if (x >= 1 && x <= 5)
            ans += 250;
        ++x;
        x %= 7;
    }
    cout << ans;
    return 0;
}