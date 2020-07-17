#include <iostream>
#include <cstdio>
#include <iomanip>
using namespace std;
long double k;
int main()
{
    scanf("%15Lf", &k);
    cout << fixed << setprecision(8) << k / 23;
    return 0;
}