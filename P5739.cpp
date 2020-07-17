#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int n;
    long long ans = 1;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        ans = ans * i;
    cout << ans;
    return 0;
}