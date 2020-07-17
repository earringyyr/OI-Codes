#include <iostream>
#include <cstdio>
using namespace std;
int k, m, n;
int main()
{
    cin >> k >> m >> n;
    bool p = false;
    for (int i = 1; i <= m; ++i)
    {
        int a, b;
        cin >> a >> b;
        if (a == 0)
        {
            if (b > 0)
            {
                p = true;
                cout << i << " ";
            }
            continue;
        }
        int c = k / a;
        if (c * b >= n)
        {
            p = true;
            cout << i << " ";
        }
    }
    if (!p)
        cout << -1;
    return 0;
}