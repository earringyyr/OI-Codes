#include <iostream>
#include <cstdio>
using namespace std;
int a, b, c;
int main()
{
    scanf("%d%d%d", &a, &b, &c);
    if ((long long)a * a > (long long)b * c)
        puts("Alice");
    else
        puts("Bob");
    return 0;
}