#include <iostream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;
int n;
double ans, ansx, ansy, temx, temy;
const double delta = 0.996;
struct node
{
    double x;
    double y;
    node(double aa = 0, double bb = 0)
    {
        x = aa;
        y = bb;
    }
} a[105];
double dis(node aa, node bb)
{
    return sqrt((aa.x - bb.x) * (aa.x - bb.x) + (aa.y - bb.y) * (aa.y - bb.y));
}
void SA()
{
    temx = ansx;
    temy = ansy;
    for (double T = 3000; T > 1e-15; T *= delta)
    {
        double xx = temx + ((rand() << 1) - RAND_MAX) * T;
        double yy = temy + ((rand() << 1) - RAND_MAX) * T;
        double tem = 0;
        for (int i = 1; i <= n; ++i)
            tem += dis(node(xx, yy), a[i]);
        if (tem - ans < 0)
        {
            temx = xx;
            temy = yy;
            ansx = xx;
            ansy = yy;
            ans = tem;
        }
        else if (exp((ans - tem) / T) > (double)rand() / RAND_MAX)
        {
            temx = xx;
            temy = yy;
        }
    }
    return;
}
void calc()
{
    scanf("%d", &n);
    ansx = 0;
    ansy = 0;
    ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lf%lf", &a[i].x, &a[i].y);
        ansx += a[i].x;
        ansy += a[i].y;
    }
    ansx /= n;
    ansy /= n;
    for (int i = 1; i <= n; ++i)
        ans += dis(node(ansx, ansy), a[i]);
    for (int i = 1; i <= 10; ++i)
        SA();
    printf("%.0f\n", ans);
    return;
}
int main()
{
    srand(time(0));
    int T;
    scanf("%d", &T);
    while (T--)
    {
        calc();
        if (T)
            putchar('\n');
    }
    return 0;
}