#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, num, b[1000005], c[1000005], ans[1000005][2];
struct node
{
    int id;
    string s;
    bool operator<(const node &bb) const
    {
        return s < bb.s;
    }
} a[1000005];
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
int main()
{
    scanf("%d", &n);
    for (register int i = 1; i <= n; ++i)
    {
        a[i].id = i;
        cin >> a[i].s;
    }
    sort(a + 1, a + n + 1);
    for (register int i = 1; i <= n; ++i)
    {
        b[a[i].id] = i;
        c[i] = a[i].id;
    }
    for (register int i = 1; i <= n; ++i)
        if (b[i] != i)
        {
            ++num;
            ans[num][0] = i;
            ans[num][1] = c[i];
            swap(b[i], b[c[i]]);
            swap(c[b[i]], c[b[c[i]]]);
        }
    write(num);
    pc('\n');
    for (register int i = 1; i <= num; ++i)
    {
        write(ans[i][0]);
        pc(' ');
        write(ans[i][1]);
        pc('\n');
    }
    flush();
    return 0;
}