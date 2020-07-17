#include <iostream>
#include <cstdio>
using namespace std;
int x, y, z;
int a, b, c;
int main()
{
    cin >> x >> y >> z;
    cin >> a >> b >> c;
    if (a >= x)
        a -= x;
    else
    {
        cout << "NO";
        return 0;
    }
    b = a + b;
    if (b >= y)
        b -= y;
    else
    {
        cout << "NO";
        return 0;
    }
    c = b + c;
    if (c >= z)
    {
        cout << "YES";
        return 0;
    }
    else
    {
        cout << "NO";
        return 0;
    }
    return 0;
}