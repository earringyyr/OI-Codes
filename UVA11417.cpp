#include <iostream>
#include <cstdio>
using namespace std;
int gcd(int x, int y)
{
    if (!y)
        return x;
    return gcd(y, x % y);
}
int main()
{
    int n;
    while (cin >> n)
    {
        if (!n)
            return 0;
        int ans = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = i + 1; j <= n; ++j)
                ans += gcd(i, j);
        cout << ans << endl;
    }
    return 0;
}