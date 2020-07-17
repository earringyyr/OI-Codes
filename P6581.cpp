#include <iostream>
#include <cstdio>
using namespace std;
long long o;
int main()
{
    scanf("%lld", &o);
    if (o > 0)
        printf("%llu", (unsigned long long)o * 2 - 1);
    else
        puts("0");
    return 0;
}