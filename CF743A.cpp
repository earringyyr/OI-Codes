#include <iostream>
#include <cstdio>
using namespace std;
int n, a, b;
char s[100005];
int main()
{
    cin >> n >> a >> b;
    scanf("%s", s);
    if (s[a - 1] == s[b - 1])
        cout << 0;
    else
        cout << 1;
    return 0;
}