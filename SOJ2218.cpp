#include <iostream>
#include <cstdio>
using namespace std;
int n, m, p, a[105][105], b[105][105], c[105][105];
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> a[i][j];
    cin >> p;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= p; ++j)
            cin >> b[i][j];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= p; ++j)
            for (int k = 1; k <= m; ++k)
                c[i][j] += a[i][k] * b[k][j];
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= p; ++j)
            cout << c[i][j] << " ";
        cout << endl;
    }
    return 0;
}