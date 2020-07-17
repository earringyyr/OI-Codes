#include <iostream>
using namespace std;
int main()
{
    long long a, b, c;
    cin >> a >> b >> c;
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % c;
        a = a * a % c;
        b >>= 1;
    }
    cout << ans;
    return 0;
}