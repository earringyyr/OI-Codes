#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char s[200];
int main()
{
    scanf("%s", s);
    int len = strlen(s);
    for (int i = 0; i < len; ++i)
        if (s[i] == 'H' || s[i] == 'Q' || s[i] == '9')
        {
            puts("YES");
            return 0;
        }
    puts("NO");
    return 0;
}