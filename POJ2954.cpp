#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int X1, X2, X3, Y1, Y2, Y3, num;
double dist(int x, int y, int xx, int yy)
{
    return sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy));
}
int gcd(int x, int y)
{
    if (!y)
        return x;
    return gcd(y, x % y);
}
int query(int x, int y, int xx, int yy)
{
    return gcd(abs(x - xx), abs(y - yy));
}
int main()
{
    while (scanf("%d%d%d%d%d%d", &X1, &Y1, &X2, &Y2, &X3, &Y3))
    {
        if (!X1 && !X2 && !X3 && !Y1 && !Y2 && !Y3)
            break;
        double a = dist(X1, Y1, X2, Y2);
        double b = dist(X1, Y1, X3, Y3);
        double c = dist(X2, Y2, X3, Y3);
        double p = (a + b + c) / 2;
        double s = sqrt(p * (p - a) * (p - b) * (p - c));
        s += 1;
        num = query(X1, Y1, X2, Y2) + query(X1, Y1, X3, Y3) + query(X2, Y2, X3, Y3);
        s -= (double)num / 2;
        printf("%.0f\n", fabs(s));
    }
    return 0;
}