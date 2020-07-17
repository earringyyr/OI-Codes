#include <iostream>
#include <cstdio>
using namespace std;
int x, y, ans;
int main()
{
    cin >> x >> y;
    for (int i = x; i <= y; ++i)
        if (i % 4 == 0)
            if (i % 100)
                ++ans;
            else if (i % 400 == 0)
                ++ans;
    cout << ans << endl;
    for (int i = x; i <= y; ++i)
        if (i % 4 == 0)
            if (i % 100)
                cout << i << " ";
            else if (i % 400 == 0)
                cout << i << " ";
    return 0;
}