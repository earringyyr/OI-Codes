#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int main()
{
    int ans = 0;
    char s[10005];
    scanf("%s", s);
    int len = strlen(s);
    for (int i = 1; i < len; ++i)
        if (s[i] != s[i - 1])
        {
            ++ans;
            if (s[0] == '0')
                s[0] = '1';
            else
                s[0] = '0';
        }
    if (s[0] == '0')
        ++ans;
    cout << ans;
    return 0;
}