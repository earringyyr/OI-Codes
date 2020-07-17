#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int n;
    cin >> n;
    if (n % 400 == 0)
        cout << 1;
    else if (n % 100 == 0)
        cout << 0;
    else if (n % 4 == 0)
        cout << 1;
    else
        cout << 0;
    return 0;
}