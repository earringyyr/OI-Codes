#include <iostream>
#include <cstdio>
using namespace std;
int nn, n, c[5005], f[5005][5005];
int main()
{
    cin >> nn;
    for (int i = 1; i <= nn; ++i)
    {
        int lin;
        cin >> lin;
        if (lin != c[n])
            c[++n] = lin;
    }
    for (int len = 1; len < n; ++len)
        for (int i = 1; i + len <= n; ++i)
        {
            int j = i + len;
            if (c[i] == c[j])
                f[i][j] = f[i + 1][j - 1] + 1;
            else
                f[i][j] = min(f[i + 1][j], f[i][j - 1]) + 1;
        }
    cout << f[1][n];
    return 0;
}