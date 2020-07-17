#include <iostream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdlib>
#define eps 1e-10
using namespace std;
int n;
double ans;
struct node
{
    double x;
    double y;
    double z;
    node(double xx = 0, double yy = 0, double zz = 0)
    {
        x = xx;
        y = yy;
        z = zz;
    }
    node operator-(const node &bb) const
    {
        return node(x - bb.x, y - bb.y, z - bb.z);
    }
    double operator*(const node &bb) const
    {
        return x * bb.x + y * bb.y + z * bb.z;
    }
    node operator^(const node &bb) const
    {
        return node(y * bb.z - z * bb.y, z * bb.x - x * bb.z, x * bb.y - y * bb.x);
    }
    double dis()
    {
        return sqrt(x * x + y * y + z * z);
    }
} p[105];
double randNoise()
{
    return ((double)rand() / RAND_MAX - 0.5) * eps;
}
node addNoise(node aa)
{
    return node(aa.x + randNoise(), aa.y + randNoise(), aa.z + randNoise());
}
bool check(int p1, int p2, int p3)
{
    double x = 0, y;
    node k = ((p[p1] - p[p2]) ^ (p[p2] - p[p3]));
    for (int i = 1; i <= n; ++i)
        if (i != p1 && i != p2 && i != p3)
        {
            y = (p[i] - p[p1]) * k;
            if (x * y < 0)
                return false;
            x = y;
        }
    return true;
}
int main()
{
    srand(time(0));
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].z);
        p[i] = addNoise(p[i]);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            for (int k = j + 1; k <= n; ++k)
                if (check(i, j, k))
                    ans += ((p[i] - p[j]) ^ (p[j] - p[k])).dis();
    printf("%.6f", ans / 2);
    return 0;
}