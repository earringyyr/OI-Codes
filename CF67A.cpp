#include <iostream>
#include <cstdio>
using namespace std;
int n, a[1005];
char s[1005];
int main()
{
    scanf("%d%s", &n, s);
    a[0] = 1;
    for (int i = 1; i < n; ++i)
    {
        if (s[i - 1] == '=')
            a[i] = a[i - 1];
        if (s[i - 1] == 'R')
            a[i] = a[i - 1] + 1;
        if (s[i - 1] == 'L')
        {
            a[i] = 1;
            if (a[i - 1] == 1)
            {
                ++a[i - 1];
                for (int j = i - 1; j >= 1; --j)
                {
                    if (s[j - 1] == '=')
                    {
                        a[j - 1] = a[j];
                        continue;
                    }
                    if (s[j - 1] == 'L' && a[j - 1] == a[j])
                    {
                        ++a[j - 1];
                        continue;
                    }
                    break;
                }
            }
        }
    }
    for (int i = 0; i < n; ++i)
        printf("%d ", a[i]);
    return 0;
}