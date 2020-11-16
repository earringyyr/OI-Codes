#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
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
typedef long long ll;
int n, len;
int l[1000005], top[1000005];
int a[1000005], b[1000005], c[1000005];
ll ans;
vector<int> st[1000005];
int main()
{
    n = read();
    for (int i = 1; i <= n; ++i)
    {
        l[i] = read();
        l[i] += l[i - 1];
        st[i].resize(l[i] - l[i - 1] + 1);
        for (int j = l[i - 1] + 1; j <= l[i]; ++j)
        {
            a[j] = read();
            b[j] = a[j];
            while (top[i] && a[j] <= st[i][top[i]])
                --top[i];
            st[i][++top[i]] = a[j];
        }
    }
    sort(b + 1, b + l[n] + 1);
    len = unique(b + 1, b + l[n] + 1) - b - 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= top[i]; ++j)
        {
            st[i][j] = lower_bound(b + 1, b + len + 1, st[i][j]) - b;
            ++c[st[i][j]];
        }
    for (int i = 1; i <= len; ++i)
        c[i] += c[i - 1];
    for (int i = 1; i <= n; ++i)
    {
        ans += (ll)n * top[i];
        ans += c[st[i][1] - 1];
    }
    printf("%lld", ans);
    return 0;
}