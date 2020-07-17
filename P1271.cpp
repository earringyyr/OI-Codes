#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, a[2000005];
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
        cin >> a[i];
    sort(a + 1, a + m + 1);
    for (int i = 1; i <= m; ++i)
        cout << a[i] << " ";
    return 0;
}