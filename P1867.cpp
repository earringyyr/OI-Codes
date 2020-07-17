#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int n, ans = 0;
    double num = 10;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        double a;
        int b;
        cin >> a >> b;
        if (a >= num)
            break;
        num -= a;
        if (num > 10)
            num = 10;
        ans += b;
    }
    int sum = 1, tot = 0;
    while (ans >= sum)
    {
        ++tot;
        ans -= sum;
        sum <<= 1;
    }
    cout << tot << " " << ans;
    return 0;
}