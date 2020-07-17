#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int a, b, c;
    while (scanf("%d%d%d", &a, &b, &c))
    {
        if (a == 0 && b == 0 && c == 0)
            break;
        if (a + c == 2 * b)
            printf("AP %d\n", b + c - a);
        else
            printf("GP %d\n", b * c / a);
    }
    return 0;
}