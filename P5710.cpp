#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int x;
    cin >> x;
    int p1 = 0, p2 = 0;
    if (x % 2 == 0)
        p1 = 1;
    if (x > 4 && x <= 12)
        p2 = 1;
    int num = 0;
    if (p1 && p2)
        cout << 1;
    else
        cout << 0;
    cout << " ";
    if (p1 || p2)
        cout << 1;
    else
        cout << 0;
    cout << " ";
    if ((p1 && !p2) || (!p1 && p2))
        cout << 1;
    else
        cout << 0;
    cout << " ";
    if (!p1 && !p2)
        cout << 1;
    else
        cout << 0;
    return 0;
}