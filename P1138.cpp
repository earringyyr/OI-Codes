#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, k, l, a[10005];
int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    sort(a + 1, a + n + 1);
    l = unique(a + 1, a + n + 1) - a - 1;
    if (l < k)
        cout << "NO RESULT";
    else
        cout << a[k];
    return 0;
}