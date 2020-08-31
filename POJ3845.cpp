#include <iostream>
#include <cstdio>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
const double pi = acos(-1);
int n, d;
double x[105], y[105];
double f, sum, per[105];
double px, py, qx, qy;
double dist(double x, double y, double xx, double yy)
{
    return sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy));
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        sum = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%lf%lf", &x[i], &y[i]);
            if (i > 1)
                sum += dist(x[i], y[i], x[i - 1], y[i - 1]);
        }
        for (int i = 1; i < n; ++i)
            per[i] = dist(x[i], y[i], x[i + 1], y[i + 1]) / sum + per[i - 1];
        scanf("%d%lf", &d, &f);
        for (int dep = 1; dep <= d; ++dep)
        {
            for (int i = 1; i < n; ++i)
                if (per[i] >= f)
                {
                    f = (f - per[i - 1]) / (per[i] - per[i - 1]);
                    px = x[i];
                    py = y[i];
                    qx = x[i + 1];
                    qy = y[i + 1];
                    break;
                }
            double nx = x[1], ny = y[1];
            double deg = atan2(y[n] - y[1], x[n] - x[1]) - atan2(qy - py, qx - px);
            double tim = dist(px, py, qx, qy) / dist(x[1], y[1], x[n], y[n]);
            for (int i = 1; i <= n; ++i)
            {
                double xx = (x[i] - nx) * cos(deg) + (y[i] - ny) * sin(deg);
                double yy = (y[i] - ny) * cos(deg) - (x[i] - nx) * sin(deg);
                x[i] = xx * tim + px;
                y[i] = yy * tim + py;
            }
        }
        printf("(%.6f,%.6f)\n", (qx - px) * f + px, (qy - py) * f + py);
    }
    return 0;
}