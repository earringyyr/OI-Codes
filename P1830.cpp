#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int n, m, x, y, a[105][105] = {0}, b[105][105];
    cin >> n >> m >> x >> y;
    for (int t = 1; t <= x; ++t)
    {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        for (int i = x1; i <= x2; ++i)
            for (int j = y1; j <= y2; ++j)
            {
                a[i][j]++;
                b[i][j] = t;
            }
    }
    for (int i = 1; i <= y; ++i)
    {
        int xx, yy;
        cin >> xx >> yy;
        if (a[xx][yy] == 0)
            cout << "N" << endl;
        else
            cout << "Y " << a[xx][yy] << " " << b[xx][yy] << endl;
    }
    return 0;
}