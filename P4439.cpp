#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int n;
    char s[50];
    cin >> n;
    for (int i = 1; i <= n; ++i)
        scanf(" %c", &s[i]);
    int len = n;
    for (int i = 1; i <= len; ++i)
        if (s[i] == s[i - 1])
            --n;
    cout << n + 1;
    return 0;
}