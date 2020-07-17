#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, po = -1, p = -1, ans, len[22000005];
char a[22000005], b[11000005];
int main()
{
    int tt;
    cin >> tt;
    for (int t = 1; t <= tt; ++t)
    {
        po = -1;
        p = -1;
        scanf("%s", b);
        n = strlen(b);
        for (int i = 0; i < n; ++i)
        {
            a[2 * i + 1] = b[i];
            a[2 * i] = '#';
        }
        a[2 * n] = '#';
        n = 2 * n + 1;
        for (int i = 0; i < n; ++i)
        {
            if (i > p)
                len[i] = 1;
            else
                len[i] = min(len[2 * po - i], p - i + 1);
            while (i + len[i] < n && i - len[i] >= 0 && a[i + len[i]] == a[i - len[i]])
                ++len[i];
            if (i + len[i] - 1 > p)
            {
                p = i + len[i] - 1;
                po = i;
            }
        }
        ans = 0;
        for (int i = 0; i < n; ++i)
            ans = max(ans, len[i]);
        cout << ans - 1 << endl;
    }
    return 0;
}