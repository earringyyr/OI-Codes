#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int n, a, sum = 0, num = 0, ans = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a;
        if (a)
        {
            if (num > 0)
                sum -= 1 << (num - 1);
            if (sum < 0)
                sum = 0;
            num = 0;
            ++sum;
            if (sum >= 365)
            {
                ans += 6;
                continue;
            }
            if (sum >= 120)
            {
                ans += 5;
                continue;
            }
            if (sum >= 30)
            {
                ans += 4;
                continue;
            }
            if (sum >= 7)
            {
                ans += 3;
                continue;
            }
            if (sum >= 3)
            {
                ans += 2;
                continue;
            }
            ans += 1;
        }
        else
            ++num;
    }
    cout << ans;
    return 0;
}