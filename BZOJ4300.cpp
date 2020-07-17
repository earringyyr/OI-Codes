#include <iostream>
#include <cstdio>
using namespace std;
int n, ans, a[100005], f[100];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i)
    {
        int num = 0;
        for (int j = 0; j <= 32; ++j)
            if ((1 << j) & a[i])
                num = max(num, f[j] + 1);
        for (int j = 0; j <= 32; ++j)
            if ((1 << j) & a[i])
                f[j] = max(f[j], num);
    }
    for (int i = 0; i <= 32; ++i)
        ans = max(ans, f[i]);
    cout << ans;
    return 0;
}