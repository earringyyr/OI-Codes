#include <iostream>
#include <cstdio>
using namespace std;
long long n, a[100005], num;
int main()
{
    cin >> n;
    for (long long i = 1; i <= n; ++i)
        cin >> a[i];
    for (long long i = 2; i <= n; ++i)
        num += max(a[i], a[i - 1]);
    cout << num;
    return 0;
}