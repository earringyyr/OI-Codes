#include <iostream>
#include <cstdio>
using namespace std;
long long n, p, num, ans;
string a[50];
int main()
{
    cin >> n >> p;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = n; i >= 1; --i)
        if (a[i] == "half")
        {
            ans += p * num;
            num *= 2;
        }
        else
        {
            ans += p * num + p / 2;
            num *= 2;
            num += 1;
        }
    cout << ans;
    return 0;
}