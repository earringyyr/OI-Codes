#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
typedef long long ll;
int n, m, rt, mod, sum, cnt;
int w[100005];
int head[100005], fa[100005], siz[100005];
int dep[100005], dfn[100005], num[100005];
int top[100005], son[100005], ed[1000005];
struct node
{
	int v;
	int nxt;
} a[200005];
struct tree
{
	int l;
	int r;
	int num;
	int lazy;
} tr[800005];
void ins(int u, int v)
{
	++sum;
	a[sum].v = v;
	a[sum].nxt = head[u];
	head[u] = sum;
	return;
}
void dfs1(int k, int f)
{
	fa[k] = f;
	siz[k] = 1;
	int d = head[k];
	while (d)
	{
		if (a[d].v != f)
		{
			dep[a[d].v] = dep[k] + 1;
			dfs1(a[d].v, k);
			siz[k] += siz[a[d].v];
			if (siz[a[d].v] > siz[son[k]])
				son[k] = a[d].v;
		}
		d = a[d].nxt;
	}
	return;
}
void dfs2(int k, int topf)
{
	++cnt;
	dfn[k] = cnt;
	num[cnt] = k;
	top[k] = topf;
	if (son[k])
		dfs2(son[k], topf);
	int d = head[k];
	while (d)
	{
		if (a[d].v != fa[k] && a[d].v != son[k])
			dfs2(a[d].v, a[d].v);
		d = a[d].nxt;
	}
	ed[k] = cnt;
	return;
}
void build(int id, int l, int r)
{
	tr[id].l = l;
	tr[id].r = r;
	if (l == r)
	{
		tr[id].num = w[num[l]];
		return;
	}
	int mid = (l + r) >> 1;
	build(lch, l, mid);
	build(rch, mid + 1, r);
	tr[id].num = ((ll)tr[lch].num + tr[rch].num) % mod;
	return;
}
void pushdown(int id)
{
	int lazy = tr[id].lazy;
	tr[id].lazy = 0;
	tr[lch].num = (tr[lch].num + (ll)(tr[lch].r - tr[lch].l + 1) * lazy % mod) % mod;
	tr[lch].lazy = ((ll)tr[lch].lazy + lazy) % mod;
	tr[rch].num = (tr[rch].num + (ll)(tr[rch].r - tr[rch].l + 1) * lazy % mod) % mod;
	tr[rch].lazy = ((ll)tr[rch].lazy + lazy) % mod;
	return;
}
void add(int id, int l, int r, int val)
{
	if (tr[id].l == l && tr[id].r == r)
	{
		tr[id].num = (tr[id].num + (ll)(r - l + 1) * val % mod) % mod;
		tr[id].lazy = ((ll)tr[id].lazy + val) % mod;
		return;
	}
	pushdown(id);
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
	tr[id].num = ((ll)tr[lch].num + tr[rch].num) % mod;
	return;
}
int ask(int id, int l, int r)
{
	if (tr[id].l == l && tr[id].r == r)
		return tr[id].num;
	pushdown(id);
	int mid = (tr[id].l + tr[id].r) >> 1;
	if (r <= mid)
		return ask(lch, l, r);
	if (l >= mid + 1)
		return ask(rch, l, r);
	return ((ll)ask(lch, l, mid) + ask(rch, mid + 1, r)) % mod;
}
int main()
{
	scanf("%d%d%d%d", &n, &m, &rt, &mod);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &w[i]);
	for (int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		ins(u, v);
		ins(v, u);
	}
	dfs1(rt, 0);
	dfs2(rt, rt);
	build(1, 1, n);
	for (int i = 1; i <= m; ++i)
	{
		int type, x;
		scanf("%d%d", &type, &x);
		if (type == 1)
		{
			int y, z;
			scanf("%d%d", &y, &z);
			while (top[x] != top[y])
			{
				if (dep[top[x]] < dep[top[y]])
					swap(x, y);
				add(1, dfn[top[x]], dfn[x], z);
				x = fa[top[x]];
			}
			if (dfn[x] > dfn[y])
				swap(x, y);
			add(1, dfn[x], dfn[y], z);
		}
		else if (type == 2)
		{
			int y;
			scanf("%d", &y);
			int ans = 0;
			while (top[x] != top[y])
			{
				if (dep[top[x]] < dep[top[y]])
					swap(x, y);
				ans = ((ll)ans + ask(1, dfn[top[x]], dfn[x])) % mod;
				x = fa[top[x]];
			}
			if (dfn[x] > dfn[y])
				swap(x, y);
			ans = ((ll)ans + ask(1, dfn[x], dfn[y])) % mod;
			printf("%d\n", ans);
		}
		else if (type == 3)
		{
			int z;
			scanf("%d", &z);
			add(1, dfn[x], ed[x], z);
		}
		else
			printf("%d\n", ask(1, dfn[x], ed[x]));
	}
	return 0;
}