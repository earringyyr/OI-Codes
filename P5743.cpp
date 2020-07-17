#include <iostream>
#include <cstdio>
using namespace std;
int n, ans = 1;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
        ans = (ans + 1) * 2;
    cout << ans;
    return 0;
}