#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cmath>
using namespace std;
int n;
double a[15][15], b[15][15];
int main()
{
    cin >> n;
    for (int i = 1; i <= n + 1; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> b[i][j];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            a[i][j] = 2 * (b[i][j] - b[i + 1][j]);
            a[i][n + 1] += b[i][j] * b[i][j] - b[i + 1][j] * b[i + 1][j];
        }
    for (int i = 1; i <= n; ++i)
    {
        int ma = i;
        for (int j = i + 1; j <= n; ++j)
            if (abs(a[j][i]) > abs(a[ma][i]))
                ma = i;
        for (int j = i; j <= n + 1; ++j)
            swap(a[i][j], a[ma][j]);
        for (int j = 1; j <= n; ++j)
            if (i != j)
            {
                double t = a[j][i] / a[i][i];
                for (int k = i; k <= n + 1; ++k)
                    a[j][k] -= a[i][k] * t;
            }
        double t = a[i][i];
        for (int j = i; j <= n + 1; ++j)
            a[i][j] /= t;
    }
    for (int i = 1; i <= n; ++i)
        cout << fixed << setprecision(3) << a[i][n + 1] << " ";
    return 0;
}