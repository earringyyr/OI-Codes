#include <iostream>
#include <cstdio>
using namespace std;
int n, num;
int main()
{
    scanf("%d", &n);
    num = n / 3 * 2;
    n %= 3;
    if (n)
        ++num;
    printf("%d", num);
    return 0;
}