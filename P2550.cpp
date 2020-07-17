#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int a[34], b[34], num[7];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= 7; ++i)
    {
        int p;
        cin >> p;
        a[p]++;
    }
    for (int i = 1; i <= n; ++i)
    {
        memset(b, 0, sizeof(b));
        for (int j = 1; j <= 7; ++j)
        {
            int q;
            cin >> q;
            b[q]++;
        }
        int ans = 0;
        for (int j = 1; j <= 33; ++j)
            ans += min(a[j], b[j]);
        num[ans]++;
    }
    for (int i = 7; i >= 1; --i)
        cout << num[i] << " ";
    return 0;
}