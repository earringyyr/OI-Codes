#include <iostream>
#include <cstdio>
using namespace std;
int n;
int main()
{
    cin >> n;
    if (n % 2 == 0)
        cout << "home";
    else
        cout << "contest";
    return 0;
}