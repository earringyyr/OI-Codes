#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char s[100];
int main()
{
    scanf("%s", s);
    int len = strlen(s);
    for (int i = len - 1; i >= 0; --i)
        cout << s[i];
    return 0;
}