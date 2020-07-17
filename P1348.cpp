#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    long long a, b, ans = 0;
    cin >> a >> b;
    for (long long i = a; i <= b; ++i)
        if (i % 4 == 0 || i % 2 != 0)
            ++ans;
    cout << ans;
    return 0;
}