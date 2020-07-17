#include <iostream>
#include <cstdio>
using namespace std;
int n;
int main()
{
    cin >> n;
    if (5 * n < 3 * n + 11)
        cout << "Local";
    else
        cout << "Luogu";
    return 0;
}