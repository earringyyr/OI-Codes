#include <iostream>
#include <cstdio>
using namespace std;
void write(long long k)
{
    if (k == 1)
    {
        cout << k << " ";
        return;
    }
    if (k % 2 == 1)
        write(3 * k + 1);
    else
        write(k / 2);
    cout << k << " ";
    return;
}
int main()
{
    long long n;
    cin >> n;
    write(n);
    return 0;
}