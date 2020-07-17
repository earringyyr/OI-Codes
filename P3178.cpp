#include <iostream>
#include <cstdio>
using namespace std;
#define lch id * 2
#define rch id * 2 + 1
long long n, m, sum, cnt;
long long b[100005], head[100005];
long long fa[100005], dep[100005], siz[100005];
long long son[100005], top[100005], dfn[100005], num[100005];
struct node
{
	long long v;
	long long next;
} a[200005];
struct tree
{
	long long l;
	long long r;
	long long num;
	long long lazy;
} tr[400005];
inline long long read()
{
	long long x = 0, f = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}
inline void ins(long long u, long long v)
{
	++sum;
	a[sum].v = v;
	a[sum].next = head[u];
	head[u] = sum;
	return;
}
inline void dfs1(long long id, long long f, long long deep)
{
	fa[id] = f;
	dep[id] = deep;
	siz[id] = 1;
	son[id] = -1;
	long long d = head[id];
	while (d)
	{
		if (a[d].v != f)
		{
			dfs1(a[d].v, id, deep + 1);
			siz[id] += siz[a[d].v];
			if (son[id] == -1 || siz[a[d].v] > siz[son[id]])
				son[id] = a[d].v;
		}
		d = a[d].next;
	}
	return;
}
inline void dfs2(long long id, long long topf)
{
	top[id] = topf;
	dfn[id] = ++cnt;
	num[cnt] = id;
	if (son[id] != -1)
		dfs2(son[id], topf);
	long long d = head[id];
	while (d)
	{
		if (a[d].v != fa[id] && a[d].v != son[id])
			dfs2(a[d].v, a[d].v);
		d = a[d].next;
	}
	return;
}
inline void build(long long id, long long l, long long r)
{
	tr[id].l = l;
	tr[id].r = r;
	if (l == r)
	{
		tr[id].num = b[num[l]];
		return;
	}
	long long mid = (l + r) / 2;
	build(lch, l, mid);
	build(rch, mid + 1, r);
	tr[id].num = tr[lch].num + tr[rch].num;
}
inline void pushdown(long long id)
{
	if (tr[id].l != tr[id].r)
	{
		long long lazy = tr[id].lazy;
		tr[id].lazy = 0;
		tr[lch].lazy += lazy;
		tr[rch].lazy += lazy;
		tr[lch].num += (tr[lch].r - tr[lch].l + 1) * lazy;
		tr[rch].num += (tr[rch].r - tr[rch].l + 1) * lazy;
	}
	return;
}
inline void add(long long id, long long l, long long r, long long val)
{
	pushdown(id);
	if (tr[id].l == l && tr[id].r == r)
	{
		tr[id].lazy += val;
		tr[id].num += val * (tr[id].r - tr[id].l + 1);
		return;
	}
	long long mid = (tr[id].l + tr[id].r) / 2;
	if (r <= mid)
		add(lch, l, r, val);
	if (l >= mid + 1)
		add(rch, l, r, val);
	if (r >= mid + 1 && l <= mid)
	{
		add(lch, l, mid, val);
		add(rch, mid + 1, r, val);
	}
	tr[id].num = tr[lch].num + tr[rch].num;
	return;
}
inline long long ask(long long id, long long l, long long r)
{
	pushdown(id);
	if (tr[id].l == l && tr[id].r == r)
		return tr[id].num;
	long long mid = (tr[id].l + tr[id].r) / 2;
	if (r <= mid)
		return ask(lch, l, r);
	if (l >= mid + 1)
		return ask(rch, l, r);
	if (r >= mid + 1 && l <= mid)
		return ask(lch, l, mid) + ask(rch, mid + 1, r);
}
inline long long lian(long long x, long long y)
{
	long long ans = 0;
	while (top[x] != top[y])
	{
		if (dep[top[x]] < dep[top[y]])
			swap(x, y);
		ans += ask(1, dfn[top[x]], dfn[x]);
		x = fa[top[x]];
	}
	if (dfn[x] > dfn[y])
		swap(x, y);
	ans += ask(1, dfn[x], dfn[y]);
	return ans;
}
int main()
{
	n = read();
	m = read();
	for (long long i = 1; i <= n; ++i)
		b[i] = read();
	for (long long i = 1; i < n; ++i)
	{
		long long from, to;
		from = read();
		to = read();
		ins(from, to);
		ins(to, from);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	build(1, 1, n);
	for (long long i = 1; i <= m; ++i)
	{
		long long pan, x, y;
		pan = read();
		if (pan == 1)
		{
			x = read();
			y = read();
			add(1, dfn[x], dfn[x], y);
		}
		if (pan == 2)
		{
			x = read();
			y = read();
			add(1, dfn[x], dfn[x] + siz[x] - 1, y);
		}
		if (pan == 3)
		{
			x = read();
			printf("%lld\n", lian(1, x));
		}
	}
	return 0;
}