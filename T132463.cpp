#include <iostream>
#include <cstdio>
using namespace std;
int n, m, type, cnt, ans, len[300005], rt[300005];
struct tree
{
	int l;
	int r;
	int sum;
} tr[60 * 300005];
int add(int x, int l, int r, int c, int w)
{
	int y = ++cnt;
	if (l == r)
	{
		tr[y].sum = w;
		return y;
	}
	tr[y] = tr[x];
	int mid = (l + r) >> 1;
	if (c <= mid)
		tr[y].l = add(tr[x].l, l, mid, c, w);
	else
		tr[y].r = add(tr[x].r, mid + 1, r, c, w);
	return y;
}
int ask(int id, int l, int r, int c)
{
	if (l == r)
		return tr[id].sum;
	int mid = (l + r) >> 1;
	if (c <= mid)
		return ask(tr[id].l, l, mid, c);
	else
		return ask(tr[id].r, mid + 1, r, c);
}
int main()
{
	scanf("%d%d%d", &n, &m, &type);
	for (int i = 1; i <= n; ++i)
	{
		int x, c;
		scanf("%d%d", &x, &c);
		if (type)
		{
			x ^= ans;
			c ^= ans;
		}
		len[i] = len[x] + 1;
		int w = ask(rt[x], 0, n, x);
		int nxt = ask(w, 1, m, c);
		ans = len[i] - len[nxt];
		printf("%d\n", ans);
		rt[i] = add(rt[x], 0, n, x, add(w, 1, m, c, i));
		rt[i] = add(rt[i], 0, n, i, ask(rt[i], 0, n, nxt));
	}
	return 0;
}