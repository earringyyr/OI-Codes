#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int n;
    cin >> n;
    for (int x = 100; x >= 1; --x)
        if (n > 7 * 52 * x && (n - 7 * x * 52) % (21 * 52) == 0)
        {
            cout << x << endl
                 << (n - 7 * x * 52) / (21 * 52);
            break;
        }
    return 0;
}