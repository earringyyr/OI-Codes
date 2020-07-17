#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int n, f[20] = {0};
    cin >> n;
    f[0] = 1;
    f[1] = 1;
    for (int i = 2; i <= n; ++i)
        for (int j = 0; j < i; ++j)
            f[i] += f[j] * f[i - j - 1];
    cout << f[n];
    return 0;
}