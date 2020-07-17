#include <iostream>
#include <cstdio>
using namespace std;
int n, x, y, a[100][100];
int main()
{
    cin >> n;
    x = 1;
    y = n / 2 + 1;
    a[x][y] = 1;
    for (int i = 2; i <= n * n; ++i)
    {
        if (x == 1 && y != n)
        {
            x = n;
            y = y + 1;
        }
        else if (x != 1 && y == n)
        {
            x = x - 1;
            y = 1;
        }
        else if (x == 1 && y == n)
        {
            x = x + 1;
            y = y;
        }
        else if (x != 1 && y != n)
        {
            if (!a[x - 1][y + 1])
            {
                x = x - 1;
                y = y + 1;
            }
            else
            {
                x = x + 1;
                y = y;
            }
        }
        a[x][y] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
            cout << a[i][j] << " ";
        cout << endl;
    }
    return 0;
}