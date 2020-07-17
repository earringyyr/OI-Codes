#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int vis[2000005], a, n;
double t;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> t >> a;
        for (int j = 1; j <= a; ++j)
            vis[(int)floor(j * t)] ^= 1;
    }
    for (int i = 1; i <= 2000000; ++i)
        if (vis[i])
        {
            cout << i;
            return 0;
        }
    return 0;
}