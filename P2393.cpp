#include <iostream>
#include <iomanip>
#include <cstdio>
using namespace std;
long double a;
unsigned long long ans;
int main()
{
    while (scanf("%Lf", &a) == 1)
        ans += a * 1000000;
    cout << fixed << setprecision(5) << (long double)ans / 1000000;
    return 0;
}