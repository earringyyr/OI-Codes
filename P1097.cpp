#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, num, a[200005];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i)
        if (i != 1 && a[i] != a[i - 1])
        {
            cout << a[i - 1] << " " << num << endl;
            num = 1;
        }
        else
            ++num;
    cout << a[n] << " " << num;
    return 0;
}