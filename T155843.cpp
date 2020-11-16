#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
namespace io_in
{
    char buf[1 << 21], *p1 = buf, *p2 = buf;
    int read()
    {
        int x = 0, f = 1;
        char c = gc();
        while (!isdigit(c))
        {
            if (c == '-')
                f = -1;
            c = gc();
        }
        while (isdigit(c))
        {
            x = (x << 3) + (x << 1) + (c ^ 48);
            c = gc();
        }
        return x * f;
    }
} // namespace io_in
namespace io_out
{
    char buf[1 << 21];
    int p1 = -1;
    const int p2 = (1 << 21) - 1;
    void flush()
    {
        fwrite(buf, 1, p1 + 1, stdout);
        p1 = -1;
        return;
    }
    void pc(char x)
    {
        if (p1 == p2)
            flush();
        buf[++p1] = x;
        return;
    }
    void write(int x)
    {
        char buffer[10];
        int len = -1;
        if (x >= 0)
        {
            do
            {
                buffer[++len] = (x % 10) | 48;
                x /= 10;
            } while (x);
        }
        else
        {
            pc('-');
            do
            {
                buffer[++len] = -(x % 10) | 48;
                x /= 10;
            } while (x);
        }
        while (len >= 0)
            pc(buffer[len--]);
        return;
    }
} // namespace io_out
using namespace io_in;
using namespace io_out;
int n, k, a[1000005], b[1000005];
int main()
{
    n = read();
    k = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    for (int T = 1; T <= k; ++T)
    {
        memset(b, 0, sizeof(b));
        for (int i = 1; i <= n; ++i)
            ++b[a[i]];
        swap(a, b);
        int flg = 1;
        for (int i = 1; i <= n; ++i)
            if (a[i] != b[i])
            {
                flg = 0;
                break;
            }
        if (flg)
            break;
    }
    for (int i = 1; i <= n; ++i)
    {
        write(a[i]);
        pc(' ');
    }
    flush();
    return 0;
}