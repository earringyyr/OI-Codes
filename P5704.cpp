#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    char a;
    cin >> a;
    cout << char(a - 'a' + 'A');
    return 0;
}