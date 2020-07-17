#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int a, num = 0;
    scanf("%d", &a);
    while (a)
    {
        if (a % 8 == 1)
            ++num;
        a /= 8;
    }
    printf("%d", num);
    return 0;
}