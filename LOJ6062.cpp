#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lch id << 1
#define rch id << 1 | 1
using namespace std;
int n, m, h, ans, a[150005], b[150005], c[300005];
struct tree
{
	int l;
	int r;
	int minx;
	int lazy;
} tr[300005 * 4];
void pushdown(int id)
{
	if (tr[id].l != tr[id].r)
	{
		int lazy = tr[id].lazy;
		tr[id].lazy = 0;
		tr[lch].lazy += lazy;
		tr[rch].lazy += lazy;
		tr[lch].minx += lazy;
		tr[rch].minx += lazy;
	}
	return;
}
void build(int id, int l, int r)
{
	tr[id].l = l;
	tr[id].r = r;
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	build(lch, l, mid);
	build(rch, mid + 1, r);
	tr[id].minx = min(tr[lch].minx, tr[rch].minx);
	return;
}
void add(int id, int l, int r, int val)
{
	pushdown(id);
	if (tr[id].l == l && tr[id].r == r)
	{
		tr[id].lazy += val;
		tr[id].minx += val;
		return;
	}
	int mid = (tr[id].l + tr[id].r) >> 1;
	if (r <= mid)
		add(lch, l, r, val);
	if (l >= mid + 1)
		add(rch, l, r, val);
	if (l <= mid && r >= mid + 1)
	{
		add(lch, l, mid, val);
		add(rch, mid + 1, r, val);
	}
	tr[id].minx = min(tr[lch].minx, tr[rch].minx);
	return;
}
int main()
{
	scanf("%d%d%d", &n, &m, &h);
	for (int i = 1; i <= m; ++i)
	{
		scanf("%d", &b[i]);
		b[i] = h - b[i];
		c[i] = b[i];
	}
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &a[i]);
		c[i + m] = a[i];
	}
	sort(c + 1, c + m + n + 1);
	int len = unique(c + 1, c + m + n + 1) - c - 1;
	for (int i = 1; i <= n; ++i)
		a[i] = lower_bound(c + 1, c + len + 1, a[i]) - c;
	for (int i = 1; i <= m; ++i)
		b[i] = lower_bound(c + 1, c + len + 1, b[i]) - c;
	build(1, 1, len);
	for (int i = 1; i <= m; ++i)
		add(1, 1, b[i], -1);
	for (int i = 1; i <= m - 1; ++i)
		add(1, 1, a[i], 1);
	for (int i = m; i <= n; ++i)
	{
		add(1, 1, a[i], 1);
		if (i != m)
			add(1, 1, a[i - m], -1);
		if (tr[1].minx >= 0)
			++ans;
	}
	printf("%d", ans);
	return 0;
}
