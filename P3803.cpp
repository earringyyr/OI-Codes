#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n, m, num, sum;
int r[4000005];
double pi = acos(-1.0);
struct complex
{
    double x;
    double y;
    complex(double a = 0, double b = 0)
    {
        x = a;
        y = b;
    }
    complex operator+(complex a)
    {
        return complex(x + a.x, y + a.y);
    }
    complex operator-(complex a)
    {
        return complex(x - a.x, y - a.y);
    }
    complex operator*(complex a)
    {
        return complex(x * a.x - y * a.y, x * a.y + y * a.x);
    }
} f[4000005], g[4000005];
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
                ww = w * ww;
            }
        }
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; ++i)
        scanf("%lf", &f[i].x);
    for (int i = 0; i <= m; ++i)
        scanf("%lf", &g[i].x);
    num = 1;
    while (num <= m + n)
    {
        num <<= 1;
        ++sum;
    }
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) << (sum - 1));
    fft(f, 1);
    fft(g, 1);
    for (int i = 0; i < num; ++i)
        f[i] = f[i] * g[i];
    fft(f, -1);
    for (int i = 0; i <= m + n; ++i)
        printf("%d ", (int)(f[i].x / num + 0.5));
    return 0;
}