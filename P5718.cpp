#include <iostream>
#include <cstdio>
using namespace std;
int minx = 1000000;
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        int a;
        cin >> a;
        if (minx > a)
            minx = a;
    }
    cout << minx;
    return 0;
}