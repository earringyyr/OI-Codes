#include <iostream>
#include <cstdio>
using namespace std;
int n, m, w, a[100005];
string b[100005];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &a[i]);
        cin >> b[i];
    }
    for (int i = 1; i <= m; ++i)
    {
        int aa, bb;
        scanf("%d%d", &aa, &bb);
        if ((aa == 0 && a[w] == 0) || (aa == 1 && a[w] == 1))
        {
            w -= bb;
            w = (w % n + n) % n;
        }
        else
        {
            w += bb;
            w = (w % n + n) % n;
        }
    }
    cout << b[w];
    return 0;
}