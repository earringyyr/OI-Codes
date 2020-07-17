#include <iostream>
#include <cstdio>
using namespace std;
int n;
int main()
{
    cin >> n;
    if (n % 3 == 0)
        cout << 1 << " " << 1 << " " << n - 2;
    if (n % 3 == 1)
        cout << 1 << " " << 1 << " " << n - 2;
    if (n % 3 == 2)
        cout << 1 << " " << 2 << " " << n - 3;
    return 0;
}