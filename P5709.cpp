#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int main()
{
    int m, t, s;
    cin >> m >> t >> s;
    if (s > m * t)
        cout << 0;
    else
        cout << m - ceil((double)s / t);
    return 0;
}