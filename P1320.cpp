#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char s[400005];
int main()
{
    scanf("%s", s + 1);
    int n = strlen(s + 1), sum = 0, cnt = 0;
    cout << n << " ";
    for (int i = 2; i <= n; ++i)
        scanf("%s", s + (i - 1) * n + 1);
    for (int i = 1; i <= n * n; ++i)
        if (sum & 1)
        {
            if (s[i] != '1')
            {
                cout << cnt << " ";
                cnt = 1;
                ++sum;
            }
            else
                ++cnt;
        }
        else
        {
            if (s[i] != '0')
            {
                cout << cnt << " ";
                cnt = 1;
                ++sum;
            }
            else
                ++cnt;
        }
    cout << cnt;
    return 0;
}