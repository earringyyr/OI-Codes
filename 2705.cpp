#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int r, b, c, d, e;
    cin >> r >> b >> c >> d >> e;
    if (c + d < 2 * e)
        if (r > b)
            cout << b * e + b * e + (r - b) * c;
        else
            cout << r * e + r * e + (b - r) * d;
    else
        cout << r * c + b * d;
    return 0;
}