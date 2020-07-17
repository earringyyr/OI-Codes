#include <iostream>
#include <cstdio>
using namespace std;
int x, y;
void exgcd(int a, int b)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return;
    }
    exgcd(b, a % b);
    int tmp = x;
    x = y;
    y = tmp - a / b * y;
    return;
}
int main()
{
    int a, b;
    cin >> a >> b;
    exgcd(a, b);
    cout << (x % b + b) % b;
    return 0;
}