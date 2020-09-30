#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const double eps = 1e-8;
int n;
struct node
{
    double x;
    double y;
    node(double xx = 0, double yy = 0)
    {
        x = xx;
        y = yy;
    }
    node operator-(const node &bb) const
    {
        return node(x - bb.x, y - bb.y);
    }
    double operator^(const node &bb) const
    {
        return x * bb.y - y * bb.x;
    }
} a[100005], b[100005];
bool cross(node aa, node bb, node cc, node dd)
{
    if (((aa - cc) ^ (aa - bb)) * ((aa - bb) ^ (aa - dd)) < eps)
        return false;
    if (((cc - aa) ^ (cc - dd)) * ((cc - dd) ^ (cc - bb)) < eps)
        return false;
    return true;
}
int main()
{
    while (scanf("%d", &n))
    {
        if (!n)
            break;
        for (int i = 1; i <= n; ++i)
            scanf("%lf%lf%lf%lf", &a[i].x, &a[i].y, &b[i].x, &b[i].y);
        printf("Top sticks: ");
        for (int i = 1; i <= n; ++i)
        {
            int p = 1;
            for (int j = i + 1; j <= n; ++j)
                if (cross(a[i], b[i], a[j], b[j]))
                {
                    p = 0;
                    break;
                }
            if (p)
            {
                printf("%d", i);
                if (i != n)
                    printf(", ");
                else
                    printf(".\n");
            }
        }
    }
    return 0;
}