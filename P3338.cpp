#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const double pi = acos(-1.0);
int n, num = 1, r[400005];
double ans[100005], q[100005];
struct complex
{
    double x;
    double y;
    complex(double xx = 0, double yy = 0)
    {
        x = xx;
        y = yy;
    }
    complex operator+(const complex &bb) const
    {
        return complex(x + bb.x, y + bb.y);
    }
    complex operator-(const complex &bb) const
    {
        return complex(x - bb.x, y - bb.y);
    }
    complex operator*(const complex &bb) const
    {
        return complex(x * bb.x - y * bb.y, x * bb.y + y * bb.x);
    }
} f[400005], g[400005];
void fft(complex *c, int type)
{
    for (int i = 0; i < num; ++i)
        if (i < r[i])
            swap(c[i], c[r[i]]);
    for (int mid = 1; mid < num; mid <<= 1)
    {
        complex w(cos(pi / mid), type * sin(pi / mid));
        for (int j = 0; j < num; j += (mid << 1))
        {
            complex ww(1, 0);
            for (int k = 0; k < mid; ++k)
            {
                complex x = c[j + k], y = ww * c[j + mid + k];
                c[j + k] = x + y;
                c[j + mid + k] = x - y;
                ww = ww * w;
            }
        }
    }
    if (type == -1)
        for (int i = 0; i < num; ++i)
            c[i].x /= num;
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lf", &q[i]);
    while (num <= 2 * n)
        num <<= 1;
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? num >> 1 : 0);
    for (int i = 1; i <= n; ++i)
    {
        f[i].x = q[i];
        g[i].x = 1.0 / i / i;
    }
    fft(f, 1);
    fft(g, 1);
    for (int i = 0; i < num; ++i)
        f[i] = f[i] * g[i];
    fft(f, -1);
    for (int i = 1; i <= n; ++i)
        ans[i] = f[i].x;
    for (int i = 0; i < num; ++i)
    {
        f[i].x = 0;
        f[i].y = 0;
        g[i].x = 0;
        g[i].y = 0;
    }
    for (int i = 0; i < n; ++i)
        f[i].x = q[n - i];
    for (int i = 1; i <= n; ++i)
        g[i].x = 1.0 / i / i;
    fft(f, 1);
    fft(g, 1);
    for (int i = 0; i < num; ++i)
        f[i] = f[i] * g[i];
    fft(f, -1);
    for (int i = 1; i <= n; ++i)
        ans[i] -= f[n - i].x;
    for (int i = 1; i <= n; ++i)
        printf("%.3f\n", ans[i]);
    return 0;
}