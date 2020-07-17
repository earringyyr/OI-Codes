#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    long long n, num = 0;
    cin >> n;
    while (n != 1)
    {
        if (n & 1)
            n = 3 * n + 1;
        else
            n = n / 2;
        ++num;
    }
    cout << num;
    return 0;
}